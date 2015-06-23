#include "commander.h"
#include "assert.h"

enum {
	C_STATE=0,
	C_STIMULUS,
	C_NEW_STATE,
	C_ACTION,
};


#define N_TRANS 2
static const uint16_t trans_table[N_TRANS][4] = {
	{X_MANUAL, S_ARM, X_MANUAL|X_ARMED, A_ARM},
	{X_MANUAL|X_ARMED, S_DISARM, X_MANUAL, A_DISARM},
};

uint16_t command(uint16_t state, uint16_t stimulus) {
	int i;
	for (i=0; i<N_TRANS; i++) {
		if (state == trans_table[i][C_STATE] &&
				stimulus == trans_table[i][C_STIMULUS]) {
			switch (trans_table[i][C_ACTION]) {
				case A_NONE:
					break;
				case A_HELLO:
					break;
				case A_ARM:
					break;
				case A_DISARM:
					break;
			    default:
					break;
			}
			state = trans_table[i][C_NEW_STATE];
		}
	}
	if (state == X_MANUAL|X_ARMED && stimulus == S_DISARM) {
		assert(state == X_MANUAL);
	}
	return state;
}
