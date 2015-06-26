#include <assert.h>
#include <inttypes.h>

#include <px4/commander/fsm_main_state.h>

int main(int argc, char *argv[])
{
	// test manual -> auto
	assert(fsm_main_state_update(
		       MAIN_STATE_MANUAL,
		       MAIN_STATE_AUTO_MISSION,
		       STAT_GLOBAL_POSITION_VALID,
		       NAVIGATION_STATE_ANY,
		       ARMING_STATE_ARMED,
		       VEHICLE_TYPE_FIXED_WING,
		       RC_IN_MODE_DEFAULT)
	       == MAIN_STATE_AUTO_MISSION);
	assert(fsm_main_state_update(
		       MAIN_STATE_MANUAL,
		       MAIN_STATE_AUTO_MISSION,
		       ~STAT_GLOBAL_POSITION_VALID,
		       NAVIGATION_STATE_ANY,
		       ARMING_STATE_ARMED,
		       VEHICLE_TYPE_FIXED_WING,
		       RC_IN_MODE_DEFAULT)
	       == MAIN_STATE_MANUAL);
	return 0;
}
