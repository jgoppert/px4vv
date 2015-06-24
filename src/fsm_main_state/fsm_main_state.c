#include <inttypes.h>
#include "fsm_main_state.h"

#include <assert.h>

/**
 * Private Data Section
 * ====================
 * */

enum { // table columns
    T_STATE = 0, // current vehicle state
    T_REQUEST = 1, // requested vehicle state
    T_STATUS_GUARD = 2, // guard conditions for status
    T_ARMING_GUARD = 3, // guard conditions for arming state
    T_NUM = 4,
};

enum { TRANS_NUM = 2};

static long int main_state_trans_table[TRANS_NUM][T_NUM] = {
    {   MAIN_STATE_ANY, MAIN_STATE_AUTO_MISSION,
        STAT_GLOBAL_POSITION_VALID, 0
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
                                   main_state_t request, status_t status) {
    int i = 0;
    for (i=0; i<TRANS_NUM; i++) {
        main_state_t tbl_state = main_state_trans_table[i][T_STATE];
        main_state_t tbl_request = main_state_trans_table[i][T_REQUEST];
        status_t tbl_status_guard = main_state_trans_table[i][T_STATUS_GUARD];
        if (	((state == tbl_state) ||
                 tbl_state == MAIN_STATE_ANY) &&
                (request == tbl_request) &&
                (status & tbl_status_guard)) {
            state = tbl_request;
            break;
        }
    }
    assert (state == MAIN_STATE_AUTO_MISSION);
    return state;
};
