#include <inttypes.h>
#include <assert.h>

#include <px4/uORB/vehicle_status.h>

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
	T_RC_IN_GUARD,
	T_NUM,
};
enum { TRANS_NUM = 3};
static long int arming_state_trans_table[TRANS_NUM][T_NUM] = {
	{
		// rule 0 TODO, safety switch as stat?
		ARMING_STATE_ANY, ARMING_STATE_ARMED,
		STAT_GLOBAL_POSITION_VALID,
		RC_IN_MODE_ANY,
	},
};

/**
 * Public Method Section
 * =====================
 * */

/**
 * Runs the arming state transition table.
 */
arming_state_t fsm_arming_state_update(
		arming_state_t state,
		arming_state_t request,
		status_t status,
		rc_in_mode_t rc_in_mode)
{
	int i = 0;

	for (i = 0; i < TRANS_NUM; i++) {
		arming_state_t tbl_state = arming_state_trans_table[i][T_STATE];
		arming_state_t tbl_request = arming_state_trans_table[i][T_REQUEST];
		status_t tbl_status_guard =
			arming_state_trans_table[i][T_STATUS_GUARD];
		rc_in_mode_t  tbl_rc_in_guard =
			arming_state_trans_table[i][T_RC_IN_GUARD];

		if (((state == tbl_state) ||
		     tbl_state == ARMING_STATE_ANY) &&
		    (request == tbl_request) &&
		    ((status & tbl_status_guard) == tbl_status_guard) &&
		    ((rc_in_mode == tbl_rc_in_guard) ||
			 tbl_rc_in_guard == RC_IN_MODE_ANY)
		   ) { 
			state = tbl_request;
			break;
		}
	}

	return state;
};
