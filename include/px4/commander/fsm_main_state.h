#pragma once

#include <px4/uORB/vehicle_status.h>

/**
 * Runs the main state transition table.
 */
main_state_t fsm_main_state_update(main_state_t state,
				   main_state_t request, status_t status,
				   navigation_state_t nav_state,
				   arming_state_t arming_state,
				   vehicle_type_t vehicle_type,
				   rc_in_mode_t rc_in_mode);
