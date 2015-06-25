#include "fsm_main_state.h"
#include <assert.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
	// intentional failed assertion to demo model checking
	// and failure trace
	assert(fsm_main_state_update(
		       MAIN_STATE_MANUAL,
		       MAIN_STATE_AUTO_RTL,
		       STAT_GLOBAL_POSITION_VALID,
			   NAVIGATION_STATE_ANY,
			   ARMING_STATE_ARMED,
			   VEHICLE_TYPE_FIXED_WING,
			   RC_IN_MODE_DEFAULT)
	       == MAIN_STATE_AUTO_RTL);
	return 0;
}
