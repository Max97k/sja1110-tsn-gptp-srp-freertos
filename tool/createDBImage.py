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

import os, argparse

def ParseArguments() :
    """Parse and check arguments received from command line."""
    # Create object for arguments parser and define required arguments
    parser = argparse.ArgumentParser(description="Parse compiled binary file to flash configuration", argument_default=argparse.SUPPRESS)
    parser.add_argument("-bf", "--binary-file",
                        type=argparse.FileType(mode="rb"),
                        help="Firmware binary path")
    parser.add_argument("-bfsize", "--partition-size",
                        type=int,
                        default=0,
                        help="Size of partition")
    parser.add_argument("-bfaddr", "--partition-address",
                        type=int,
                        default=0,
                        help="Address of partition")
    parser.add_argument("-sf", "--second-image",
                        type=argparse.FileType(mode="rb"),
                        help="Second binary path")
    parser.add_argument("remainder",
                        nargs=argparse.REMAINDER)
    # Parse received arguments
    options = parser.parse_args()
    # Check for size
    fw_length = len (options.binary_file.read())
    if (fw_length > options.partition_size):
        parser.error("Partition size is smaller than firmware size " + str(fw_length) + ". Aborting job!")
    # Return object with arguments
    return options

if __name__ == "__main__":
    # Parse command line arguments
    argv = ParseArguments()
    argv.binary_file.seek(0)
    firmware = argv.binary_file.read()
    outputFolder = os.path.dirname(argv.binary_file.name)
    diFirmwareContent = bytearray()
    diValidMarker = 0x5995599559955995
    diFirmwareContent += bytearray(diValidMarker.to_bytes(length=8, byteorder="little"))
    diFirmwareContent += bytearray(argv.partition_address.to_bytes(4, byteorder="little"))
    diFirmwareContent += bytearray(argv.partition_address.to_bytes(4, byteorder="little"))
    diFirmwareContent += bytearray((argv.partition_address + argv.partition_size).to_bytes(4, byteorder="little"))
    diFirmwareContent += bytearray((argv.partition_address + argv.partition_size).to_bytes(4, byteorder="little"))
    if (argv.partition_address - len (diFirmwareContent) > 0):
        diFirmwareContent += bytearray(argv.partition_address - len (diFirmwareContent))
    diFirmwareContent += bytearray(firmware)
    if (argv.partition_address + argv.partition_size - len (diFirmwareContent)):
        diFirmwareContent += bytearray(argv.partition_address + argv.partition_size - len (diFirmwareContent))
    if hasattr(argv, "second_image") :
        print("Create Dualbank firmware image as a different image")
        diFirmwareContent += bytearray(argv.second_image.read())
    else:
        print("Create Dualbank firmware image as a redundant copy of the first image")
        diFirmwareContent += bytearray(firmware)
    argv.binary_file.close()
    if os.path.exists(os.path.join(outputFolder, "flash_image_single_bank.bin")):
    	os.remove(os.path.join(outputFolder, "flash_image_single_bank.bin"))
    os.rename(argv.binary_file.name, os.path.join(outputFolder, "flash_image_single_bank.bin"))
    with open(os.path.join(outputFolder,"flash_image.bin"),"w+b") as streamWriter:
        streamWriter.write(diFirmwareContent)
        print("Dualbank firmware image created successfully")
