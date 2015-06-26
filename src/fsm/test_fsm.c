#include <px4/fsm.h>
#include <assert.h>

int main(int argc, char *argv[]) {
	fsm_t fsm;
	uint32_t trans_table[] = {
		0, 1, 1, 0,
		1, 0, 0, 1,
	};
	uint8_t bitmask_guards[2] = {0, 1};
	fsm_init(&fsm, 2, 2,
			trans_table, bitmask_guards);

	assert(fsm_update(&fsm, 0, 1, 1, 0) == 1);
	assert(fsm_update(&fsm, 0, 1, 0, 0) == 0);
	assert(fsm_update(&fsm, 1, 0, 0, 1) == 0);
	assert(fsm_update(&fsm, 1, 0, 0, 0) == 1);
	return 0;
}
