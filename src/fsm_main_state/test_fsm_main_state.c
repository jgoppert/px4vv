#include "fsm_main_state.h"
#include <assert.h>
#include <inttypes.h>

#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */

const char * uint32_to_bin(uint32_t x)
{
    static char b[33];
    b[0] = '\0';

    uint32_t z;
    for (z = (1 << 31); z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    return b;
}

int main(int argc, char * argv[]) {
    assert(fsm_main_state_update(
               MAIN_STATE_MANUAL,
               MAIN_STATE_AUTO_MISSION,
               STAT_GLOBAL_POSITION_VALID)
           == MAIN_STATE_AUTO_MISSION);
    return 0;
}
