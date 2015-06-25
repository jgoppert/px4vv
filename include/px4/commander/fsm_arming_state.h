#pragma once

#include <px4/uORB/vehicle_status.h>

/**
 * Runs the main state transition table.
 */
arming_state_t fsm_arming_state_update(
		arming_state_t state,
		arming_state_t request,
		status_t status,
		rc_in_mode_t rc_in_mode);
