#include <inttypes.h>
#include <assert.h>

#include <px4/commander/fsm_main_state.h>

/**
 * Private Data Section
 * ====================
 * */

/**
 * This is the transition table and defines the FSM behaviour.
 */
enum { // table columns
	T_STATE = 0, // current vehicle state
	T_REQUEST, // requested vehicle state
	T_STATUS_GUARD, // guard conditions
	T_NAVIGATION_GUARD,
	T_ARMING_GUARD,
	T_VEHICLE_TYPE_GUARD,
	T_RC_IN_GUARD,
	T_NUM,
};
enum { TRANS_NUM = 3};
static long int main_state_trans_table[TRANS_NUM][T_NUM] = {
	{
		// rule 0
		MAIN_STATE_ANY, MAIN_STATE_AUTO_MISSION,
		STAT_GLOBAL_POSITION_VALID,
		NAVIGATION_STATE_ANY,
		ARMING_STATE_ARMED,
		VEHICLE_TYPE_ANY,
		RC_IN_MODE_ANY,
	},
	{
		// rule 1
		MAIN_STATE_ANY, MAIN_STATE_AUTO_RTL,
		STAT_GLOBAL_POSITION_VALID | STAT_HOME_POSITION_VALID,
		NAVIGATION_STATE_ANY,
		ARMING_STATE_ARMED,
		VEHICLE_TYPE_ANY,
		RC_IN_MODE_ANY,
	},
	{
		// rule 2
		MAIN_STATE_ANY, MAIN_STATE_AUTO_RTL,
		STAT_GLOBAL_POSITION_VALID | STAT_HOME_POSITION_VALID,
		NAVIGATION_STATE_ANY,
		ARMING_STATE_ARMED,
		VEHICLE_TYPE_ANY,
		RC_IN_MODE_ANY,
	},
};

/**
 * Public Method Section
 * =====================
 * */

/**
 * Runs the main state transition table.
 */
main_state_t fsm_main_state_update(main_state_t state,
				   main_state_t request, status_t status,
				   navigation_state_t nav_state,
				   arming_state_t arming_state,
				   vehicle_type_t vehicle_type,
				   rc_in_mode_t rc_in_mode)
{
	int i = 0;

	for (i = 0; i < TRANS_NUM; i++) {
		main_state_t tbl_state = main_state_trans_table[i][T_STATE];
		main_state_t tbl_request = main_state_trans_table[i][T_REQUEST];
		status_t tbl_status_guard = main_state_trans_table[i][T_STATUS_GUARD];
		navigation_state_t tbl_nav_guard =
			main_state_trans_table[i][T_NAVIGATION_GUARD];
		arming_state_t tbl_arming_guard =
			main_state_trans_table[i][T_ARMING_GUARD];
		vehicle_type_t tbl_vehicle_type_guard =
			main_state_trans_table[i][T_VEHICLE_TYPE_GUARD];
		rc_in_mode_t  tbl_rc_in_guard =
			main_state_trans_table[i][T_RC_IN_GUARD];

		if (((state == tbl_state) ||
		     tbl_state == MAIN_STATE_ANY) &&
		    (request == tbl_request) &&
		    ((status & tbl_status_guard) == tbl_status_guard) &&
		    ((nav_state == tbl_nav_guard) ||
		     tbl_nav_guard == NAVIGATION_STATE_ANY) &&
		    ((arming_state == tbl_arming_guard) ||
		     tbl_arming_guard == ARMING_STATE_ANY) &&
		    ((vehicle_type == tbl_vehicle_type_guard) ||
		     tbl_vehicle_type_guard == VEHICLE_TYPE_ANY) &&
		    ((rc_in_mode == tbl_rc_in_guard) ||
		     tbl_rc_in_guard == RC_IN_MODE_ANY)
		   ) {

			state = tbl_request;
			break;
		}
	}

	return state;
};
