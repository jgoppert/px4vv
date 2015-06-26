#include <assert.h>
#include <inttypes.h>

#include <px4/commander/fsm_arming_state.h>

int main(int argc, char *argv[])
{
	assert(fsm_arming_state_update(
		       ARMING_STATE_STANDBY,
		       ARMING_STATE_ARMED,
		       STAT_GLOBAL_POSITION_VALID,
		       RC_IN_MODE_DEFAULT)
	       == ARMING_STATE_ARMED);
	return 0;
}
