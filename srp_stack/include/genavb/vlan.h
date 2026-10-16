/*
 * Copyright 2022-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 \file
 \brief GenAVB/TSN public API
 \details 802.1Q FDB Static VLAN Registration definitions.
*/
#ifndef _GENAVB_PUBLIC_VLAN_H_
#define _GENAVB_PUBLIC_VLAN_H_

#include "genavb/types.h"

/** \cond RTOS */

/**
 * \defgroup vlan			802.1Q FDB Static VLAN Registration
 * \ingroup library
 *
 * This API is used to manage FDB Static VLAN Registration entries of a given network bridge (as defined in IEEE 802.1Q-2018 Sections 8.8.2 and 12.7.5.1).
 *
 */

/**
 * \ingroup vlan
 */
typedef enum {
	GENAVB_VLAN_ADMIN_CONTROL_FORBIDDEN = 0,
	GENAVB_VLAN_ADMIN_CONTROL_FIXED,
	GENAVB_VLAN_ADMIN_CONTROL_NORMAL,
	GENAVB_VLAN_ADMIN_CONTROL_REGISTERED,		/**< Internal only, reserved for MVRP */
	GENAVB_VLAN_ADMIN_CONTROL_NOT_REGISTERED,	/**< Internal only, reserved for MVRP */
} genavb_vlan_admin_control_t;

/**
 * \ingroup vlan
 * VLAN Registration port map
 * 802.1Q-2018 - 8.8.2
 */
struct genavb_vlan_port_map {
	unsigned int port_id;
	genavb_vlan_admin_control_t control;
	bool untagged;
};

/** \endcond */

int genavb_vlan_update(uint16_t vid, struct genavb_vlan_port_map *map);
int genavb_vlan_delete(uint16_t vid);
int genavb_vlan_read(uint16_t vid, bool *dynamic, struct genavb_vlan_port_map *map);
int genavb_vlan_dump(uint32_t *token, uint16_t *vid, bool *dynamic, struct genavb_vlan_port_map *map);
int genavb_vlan_set_port_default(unsigned int port_id, uint16_t vid);
int genavb_vlan_get_port_default(unsigned int port_id, uint16_t *vid);

#endif /* _GENAVB_PUBLIC_VLAN_H_ */
