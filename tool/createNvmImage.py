#==================================================================================================
#   Project              : RTD AUTOSAR 4.4
#   Platform             : CORTEXM
#   Peripheral           : 
#   Dependencies         : none
#
#   Autosar Version      : 4.4.0
#   Autosar Revision     : ASR_REL_4_4_REV_0000
#   Autosar Conf.Variant :
#   SW Version           : 1.0.1
#   Build Version        : SJA11XX_RTD_1_0_1_P02_HF01_D2510_ASR_REL_4_4_REV_0000_20251021
#
#   Copyright 2021-2025 NXP
#
#   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be  used strictly in accordance with the applicable license terms.  By expressly  accepting such terms or by downloading, installing, activating and/or otherwise  using the software, you are agreeing that you have read, and that you agree to  comply with and are bound by, such license terms.  If you do not agree to be  bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.
#==================================================================================================

from __future__ import print_function
import sys, os
try:
    import elftools.elf.elffile as elf
except ImportError:
    sys.exit("""You need Pyelftools package!
            install it from https://pypi.org/project/pyelftools/
            or run pip install pyelftools .""")
try:
    import Cryptodome.Hash.SHA256 as sha256
    import Cryptodome.Hash.SHA384 as sha384
    import Cryptodome.Signature.PKCS1_PSS as rsa_pss_signature
    import Cryptodome.Signature.DSS as ecc_dss_signature
    import Cryptodome.PublicKey.RSA as rsa_key
    import Cryptodome.PublicKey.ECC as ecc_key
    import Cryptodome.Util.number as conversion
except ImportError:
    sys.exit("""You need Cryptodome package!
            install it from https://pypi.org/project/pycryptodomex/
            or run pip install pycryptodomex .""")

import base64

import argparse

# Constants
FW_HEADER_SIZE = 0x20
FW_DATA_OFFSET = 0x18

def ParseArguments() :
    """Parse and check arguments received from command line."""
    # Create object for arguments parser and define required arguments
    parser = argparse.ArgumentParser(description="Parse compiled binary file to flash configuration", argument_default=argparse.SUPPRESS)
    parser.add_argument("-bf", "--bin-file",
                        type=argparse.FileType(mode="rb"),
                        required=True,
                        help="Binary file absolute path")
    parser.add_argument("-rv", "--root-key-ver",
                        type=int,
                        help="Root key version")
    parser.add_argument("-rd", "--root-key-dir",
                        type=os.path.abspath,
                        help="Root key directory")
    parser.add_argument("-fv", "--fsk-key-ver",
                        type=int,
                        help="FSK key version")
    parser.add_argument("-fd", "--fsk-key-dir",
                        type=os.path.abspath,
                        help="FSK key directory")
    parser.add_argument("-s", "--secure-build",
                        action="store_true",
                        help="Use secure build mode")
    parser.add_argument("-nh", "--nonsecure-hash",
                        action="store_true",
                        help="Use Non-Secure Image Layout with SHA-256")
    parser.add_argument("-vt", "--verify-type",
                        type=str,
                        help="Verification type RSA /P-256 (ECDSA P-256) /P-384 (ECDSA P-384)")
    parser.add_argument("remainder",
                        nargs=argparse.REMAINDER)
    # Parse received arguments
    options = parser.parse_args()
    # Check received paths from arguments
    if hasattr(options, "secure_build") :
        if (options.root_key_ver is None) or (options.fsk_key_ver is None) :
            parser.error("-s/--secure-build requires -rv/--root-key-ver and -fv/--fsk-key-ver")
    # Return object with arguments
    return options

def CreateBinFile(filePath, fileContent, logMessage) :
    """Writes bin file content to a new file"""
    with open(os.path.join(filePath, "flash_image.bin"), "w+b") as fileStream :
        fileStream.write(fileContent)
    print("\n" + logMessage)
    sys.exit()

def FindPrivateKey(directory, type="RSA") :
    """Search given directory for private keys in .pem format
    and return a tuple containing all key values found and their respective subdirectory locations"""
    keyList = list()
    for subdir, _, files in os.walk(directory):
        for fileName in [fileName for fileName in files if fileName.endswith(".pem")] :
            with open(os.path.join(subdir, fileName)) as fileStream :
                if type == "RSA": # RSA
                    privateKey = rsa_key.importKey(fileStream.read())
                else : # ECDSA
                    privateKey = ecc_key.import_key(fileStream.read())
                if privateKey.has_private():
                    keyList.append((privateKey,subdir))
    return tuple(keyList)

def WriteFSKBinFile(key, keyDir):
    """Write a private-public key pair to disk in .pem format"""
    if key.has_private():
        keySubdir = os.path.join(keyDir, "FSK_Private_Key")
        keyName = "fsk_priv_key.pem"
    else:
        keySubdir = os.path.join(keyDir, "FSK_Public_Key")
        keyName = "fsk_pub_key.pem"
    os.makedirs(keySubdir, exist_ok=True)
    keyType = "" # String
    if (type(key.export_key(format="PEM")) == bytes) :
        keyType = "b" # Bytes
    with open(os.path.join(keySubdir, keyName), "w+" + keyType) as streamWriter:
        streamWriter.write(key.export_key(format="PEM"))
        
def WriteRootPemFile(key, keyDir):
    """Write a private-public key pair to disk in .pem format"""
    if key.has_private():
        keySubdir = os.path.join(keyDir, "Root_Private_Key")
        keyName = "root_priv_key.pem"
    else:
        keySubdir = os.path.join(keyDir, "Root_Public_Key")
        keyName = "root_pub_key.pem"
    os.makedirs(keySubdir, exist_ok=True)
    keyType = "" # String
    if (type(key.export_key(format="PEM")) == bytes) :
        keyType = "b" # Bytes
    with open(os.path.join(keySubdir, keyName), "w+" + keyType) as streamWriter:
        streamWriter.write(key.export_key(format="PEM"))
        
def CreateRootKeyPair(argv) :
    if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
        print ("\nConstructing new ECDSA Root private-public key pair")
        print ("Generated key pair can be found in directory " + argv.root_key_dir)
        rootPrivateKey = ecc_key.generate(curve="P-384") # Public Root Key P-384
        rootPublicKey = rootPrivateKey.public_key()
    else :
        print ("\nConstructing new RSA Root private-public key pair")
        print ("Generated key pair can be found in directory " + argv.root_key_dir)
        rootPrivateKey = rsa_key.generate(2048) # e is 65537 by default
        rootPublicKey = rootPrivateKey.publickey()
    WriteRootPemFile(rootPrivateKey, argv.root_key_dir)
    WriteRootPemFile(rootPublicKey, argv.root_key_dir)
    return rootPublicKey, rootPrivateKey

def CreateFSKKeyPair(argv) :
    if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
        print ("\nConstructing new ECDSA FSK private-public key pair")
        print ("Generated key pair can be found in directory " + argv.fsk_key_dir)
        cotPrivateKey = ecc_key.generate(curve=argv.verify_type) # P-256/P-384
        cotPublicKey = cotPrivateKey.public_key()
    else :
        print ("\nConstructing new RSA FSK private-public key pair")
        print ("Generated key pair can be found in directory " + argv.fsk_key_dir)
        cotPrivateKey = rsa_key.generate(2048) # e is 65537 by default
        cotPublicKey = cotPrivateKey.publickey()
    WriteFSKBinFile(cotPrivateKey, argv.fsk_key_dir)
    WriteFSKBinFile(cotPublicKey, argv.fsk_key_dir)
    return cotPublicKey, cotPrivateKey
        
def WriteRootHashAsCArrayToCFile(hash, fileDir):
    with open(os.path.join(fileDir, "root_key_hash.h"), "w+") as streamWriter:
        streamWriter.write("#ifndef ROOT_KEY_HASH_H \n")
        streamWriter.write("#define ROOT_KEY_HASH_H \n")
        streamWriter.write("\n")
        streamWriter.write("uint8_t rootHash[] = {0x")
        streamWriter.write(hash[0:2])
        for i in range(2, len (hash), 2):
            streamWriter.write(", 0x" + hash[i:i+2])
        streamWriter.write("};\n\n")
        streamWriter.write("#endif")
    print ("\nC header file containing hashed root public key created in " + os.path.join(fileDir, "root_key_hash.h"))

def SecureBuild(argv, newBinContent, unsecuredContent) :
    """Create a programmable SJA1110 .bin app image as indicated in SJA1110 secure image format"""
    imageHeaderContent = bytearray(newBinContent[0:24])  # extract first 24 bytes
    newContent = bytearray()
    newContent += imageHeaderContent # append valid marker, clk and pin settings
    # make a new directory and save new key pair
    if (argv.root_key_dir is None) or (not argv.root_key_dir) or (argv.root_key_dir == os.getcwd()) :
        argv.root_key_dir = os.path.join(os.path.dirname(argv.bin_file.name), "..", "board", "Root_Key")
        rootPrivDir = os.path.join(argv.root_key_dir, "Root_Private_Key")
        rootPublicKey, rootPrivateKey = CreateRootKeyPair(argv)
    else : 
        # see if there is a root key pair in directory
        print(argv.root_key_dir)
        keyTuple = FindPrivateKey(argv.root_key_dir, argv.verify_type)
        if len (keyTuple) > 1:
            print ("\nError, more than one private key exists in " + argv.root_key_dir)
            print ("Building unsecured instead of secured image")
            CreateBinFile(os.path.dirname(argv.bin_file.name), newBinContent, "Created unsecured image successfully")
        elif len (keyTuple) == 1 :
            rootPrivateKey = keyTuple[0][0]
            if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
                rootPublicKey = ecc_key.construct(curve=rootPrivateKey.curve, point_x=rootPrivateKey.pointQ.x, point_y=rootPrivateKey.pointQ.y)
            else :
                rootPublicKey = rsa_key.construct((rootPrivateKey.n, 65537))
            rootPrivDir = keyTuple[0][1]
        else :
            print ("No private key detected in directory")
            rootPublicKey, rootPrivateKey = CreateRootKeyPair(argv)
            rootPrivDir = os.path.join(argv.root_key_dir, "Root_Private_Key")

    if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
        newContent += rootPublicKey.export_key(format="raw")[1:]  # append public root key
        rootPubHash = sha384.new()
        rootPubHash.update(rootPublicKey.export_key(format="raw")[1:])
    else :
        newContent += conversion.long_to_bytes(rootPublicKey.n)  # append public root key
        rootPubHash = sha256.new()
        rootPubHash.update(conversion.long_to_bytes(rootPublicKey.n))
    with open(os.path.join(rootPrivDir, "rootHash.bin"),"wb") as StreamWriter:
        StreamWriter.write(rootPubHash.digest())
    WriteRootHashAsCArrayToCFile(rootPubHash.hexdigest(), rootPrivDir)
    print("\nPublic root key hash generated in " + rootPrivDir)

    # make a new directory and save new key pair
    if (argv.fsk_key_dir is None) or (not argv.fsk_key_dir) or (argv.fsk_key_dir == os.getcwd()) :
        argv.fsk_key_dir = os.path.join(os.path.dirname(argv.bin_file.name), "..", "board", "FSK_key")
        cotPublicKey, cotPrivateKey = CreateFSKKeyPair(argv)
    else :
        # see if there is a FSK key pair in directory
        keyTuple = FindPrivateKey(argv.fsk_key_dir, argv.verify_type)
        if len (keyTuple) > 1:
            print ("\nError, more than one private key exists in " + argv.fsk_key_dir)
            print ("Building unsecured instead of secured image")
            CreateBinFile(os.path.dirname(argv.bin_file.name), newBinContent, "Created unsecured image successfully")
        elif len (keyTuple) == 1:
            cotPrivateKey = keyTuple[0][0]
            if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
                cotPublicKey = ecc_key.construct(curve=cotPrivateKey.curve, point_x=cotPrivateKey.pointQ.x, point_y=cotPrivateKey.pointQ.y)
            else :
                cotPublicKey = rsa_key.construct((cotPrivateKey.n,65537))
        else:
            print ("No private key detected in directory")
            cotPublicKey, cotPrivateKey = CreateFSKKeyPair(argv)

    # Build CotT Header
    if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
        eccVer = 0x00
        if argv.verify_type == "P-384" :
            eccVer = 0x09
        constList = [int(argv.fsk_key_ver), 0xE0, eccVer, 0x01, 0x02, 0x03, 0x04, 0x05]
        cotHeader = bytearray(constList)
        cotHeader += cotPublicKey.export_key(format="raw")[1:]
        if argv.verify_type == "P-256" :
            cotReserved32 = [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                             0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
                             0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                             0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20]
            cotHeader += bytearray(cotReserved32)
    else :
        constList = [int(argv.fsk_key_ver), 0xE0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06]
        cotHeader = bytearray(constList)
        cotHeader += conversion.long_to_bytes(cotPublicKey.n)
    if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
        cotHASH = sha384.new()
        cotHASH.update(cotHeader)
        cotSignature = ecc_dss_signature.new(rootPrivateKey, "fips-186-3").sign(cotHASH)
    else :
        cotHASH = sha256.new()
        cotHASH.update(cotHeader)
        cotSignature = rsa_pss_signature.new(rootPrivateKey).sign(cotHASH)
    newContent += cotHeader
    newContent += cotSignature


    firmware = bytearray()
    firmware += newBinContent[24:24 + 8]  # append length and entry ptr
    constList[0] = int(argv.root_key_ver)
    constList[1] = 0xE1
    firmware += bytearray(constList)
    firmware += newBinContent[32:]
    if (argv.verify_type == "P-256") or (argv.verify_type == "P-384") :
        if (argv.verify_type == "P-256") :
            firmwareHASH = sha256.new()
        else :
            firmwareHASH = sha384.new()
        firmwareHASH.update(firmware)
        firmwareSignature = ecc_dss_signature.new(cotPrivateKey, "fips-186-3").sign(firmwareHASH)
    else :
        firmwareHASH = sha256.new()
        firmwareHASH.update(firmware)
        firmwareSignature = rsa_pss_signature.new(cotPrivateKey).sign(firmwareHASH)
    newContent += firmware
    newContent += firmwareSignature
    if (len (unsecuredContent) > 0):
        newContent += unsecuredContent
    if (argv.verify_type == "P-256") :
        logMessage = "Created secured image with ECDSA/ECC P-256 signature verification successfully"
    elif (argv.verify_type == "P-384") :
        logMessage = "Created secured image with ECDSA/ECC P-384 signature verification successfully"
    else :
        logMessage = "Created secured image with RSA2048 signature verification successfully"
    CreateBinFile(os.path.dirname(argv.bin_file.name), newContent, logMessage)

if __name__ == "__main__":
    # Parse command line arguments
    argv = ParseArguments()

    oldBinFile = argv.bin_file

    # Get nvmImageHeader Section Address
    oldBinPath = os.path.relpath(argv.bin_file.name)
    elfPath = os.path.splitext(oldBinPath)[0] + ".elf"
    elfStream = open(elfPath, "rb")
    elfFile = elf.ELFFile(elfStream)
    nvmSection = elfFile.get_section_by_name(".nvmImageHeaderSectionBlock")
    if (nvmSection == None):
        nvmSection = elfFile.get_section_by_name(".nvmImageHeaderSection")
    nvmOffset = nvmSection.header["sh_addr"]
    # IAR section
    if (nvmOffset == 0):
        symbolsSection = elfFile.get_section_by_name(".symtab")
        for symbol in symbolsSection.iter_symbols():
            if symbol.name == "NVM_IMAGE_HEADER$$Base":
                nvmOffset = symbol.entry.st_value
    elfStream.close()

    # Move header

    # Read everything in the file, keep only app data, without fw_header
    olfBinContent = oldBinFile.read()
    oldBinApp = olfBinContent[0:nvmOffset]
    # Read 32 bytes from end of file
    oldBinFwHeader = olfBinContent[nvmOffset:nvmOffset+FW_HEADER_SIZE]
    oldBinAppUnsecure = olfBinContent[nvmOffset+FW_HEADER_SIZE:]
    if len (oldBinAppUnsecure) > 0:
        oldBinAppUnsecure += bytearray(FW_HEADER_SIZE)

    # Recreate the bin file
    newBinContent = oldBinFwHeader + oldBinApp
    oldBinFile.close()

    if hasattr(argv, "nonsecure_hash") :
        fwData = newBinContent[FW_DATA_OFFSET:]
        fwDataHASH = sha256.new()
        fwDataHASH.update(fwData)

    if hasattr(argv, "secure_build") :
        # Secure build creation
        SecureBuild(argv, newBinContent, oldBinAppUnsecure)
    else :
        if hasattr(argv, "nonsecure_hash") :
            newBinContent += fwDataHASH.digest()
            logMessage = "Created unsecured image with hash SHA-256 successfully"
        else :
            logMessage = "Created unsecured image successfully"
        CreateBinFile(os.path.dirname(argv.bin_file.name), newBinContent + oldBinAppUnsecure, logMessage)

