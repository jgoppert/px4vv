# PX4 verification and validation version

[![Build Status](https://travis-ci.org/jgoppert/px4vv.svg)](https://travis-ci.org/jgoppert/px4vv)

This is a prototype codebase for a platform indepdent px4 compatible autopilot that is verified with the CBMC model checker. Note that CBMC is simpler with the C language instead of C++, so I'm rewriting the chunks of the code by hand in C for now.

This could result in a new codebase written in C or some of the functions developed here could be pulled back into the main codebase written in C and C++ as V&V version of the current modules.

## Install

###Dependencies:

#### CBMC

http://www.cprover.org/cbmc/

Example dependencies install for linux:
```bash
sudo apt-get install cmake cbmc
mkdir build
cd build
cmake ..
make
```
## Example

Transition rules are written in a human readable form in the source code, for instance:

```c

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
```

You can run the built in testing and model checking suite as follow:
```bash
~/git/px4vv/build$ ctest
Test project git/px4vv/build
    Start 1: test_run_fsm_main_state_auto_mission
1/4 Test #1: test_run_fsm_main_state_auto_mission ...........   Passed    0.00 sec
    Start 2: test_cbmc_fsm_main_state_auto_mission
2/4 Test #2: test_cbmc_fsm_main_state_auto_mission ..........   Passed    0.23 sec
    Start 3: test_run_fsm_main_state_intentional_failure
3/4 Test #3: test_run_fsm_main_state_intentional_failure ....***Exception: Other  0.12 sec
    Start 4: test_cbmc_fsm_main_state_intentional_failure
4/4 Test #4: test_cbmc_fsm_main_state_intentional_failure ...***Failed    0.25 sec

50% tests passed, 2 tests failed out of 4

Total Test time (real) =   0.61 sec

The following tests FAILED:
	  3 - test_run_fsm_main_state_intentional_failure (OTHER_FAULT)
	  4 - test_cbmc_fsm_main_state_intentional_failure (Failed)
Errors while running CTest
```

If you want to see what the failure trace was for the model checking errors, you can
run ctest in verbose mode:
```bash
ctest -V
4: State 157 file git/px4vv/src/fsm_main_state/fsm_main_state.c line 82 function fsm_main_state_update thread 0
4: ----------------------------------------------------
4:   tbl_rc_in_guard=/*enum*/4 (4)
4: 
4: State 167 file git/px4vv/src/fsm_main_state/fsm_main_state.c line 72 function fsm_main_state_update thread 0
4: ----------------------------------------------------
4:   i=3 (00000000000000000000000000000011)
4: 
4: State 171 file git/px4vv/src/fsm_main_state/fsm_main_state.c line 102 function fsm_main_state_update thread 0
4: ----------------------------------------------------
4:   return_value_fsm_main_state_update$1=/*enum*/0 (0)
4: 
4: Violated property:
4:   file git/px4vv/src/fsm_main_state/test_fsm_main_state_intentional_failure.c line 9 function main
4:   assertion fsm_main_state_update( MAIN_STATE_MANUAL, MAIN_STATE_AUTO_RTL, STAT_GLOBAL_POSITION_VALID, NAVIGATION_STATE_ANY, ARMING_STATE_ARMED, VEHICLE_TYPE_FIXED_WING, RC_IN_MODE_DEFAULT) == MAIN_STATE_AUTO_RTL
4:   FALSE
4: 
4: VERIFICATION FAILED
4/4 Test #4: test_cbmc_fsm_main_state_intentional_failure ...***Failed    0.24 sec

50% tests passed, 2 tests failed out of 4

Total Test time (real) =   0.60 sec

The following tests FAILED:
	  3 - test_run_fsm_main_state_intentional_failure (OTHER_FAULT)
	  4 - test_cbmc_fsm_main_state_intentional_failure (Failed)
Errors while running CTest
```

