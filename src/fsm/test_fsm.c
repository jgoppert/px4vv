#include <px4/fsm.h>
#include <assert.h>

int main(int argc, char *argv[]) {

	fsm_t fsm;
	enum {n_trans=2};
	enum {n_guard=2};

	const uint32_t trans_table[] = {
		// state, request, guard1, guard2
		0, 1, 1, 0,
		1, 0, 0, 1,
	};

	const uint8_t bitmask_guards[2] = {1, 0};
	fsm_init(&fsm, n_trans, n_guard, trans_table, bitmask_guards);

	const uint32_t status_1[n_guard] = {1, 0};
	assert(fsm_update(&fsm, 0, 1, status_1) == 1);

	const uint32_t status_2[n_guard] = {0, 0};
	assert(fsm_update(&fsm, 0, 1, status_2) == 0);

	const uint32_t status_3[n_guard] = {0, 1};
	assert(fsm_update(&fsm, 1, 0, status_3) == 0);

	const uint32_t status_4[n_guard] = {0, 0};
	assert(fsm_update(&fsm, 1, 0, status_4) == 1);

	fsm_t fsm2;

	enum {n_guard2=3};
	enum {n_trans2=3};
	const uint32_t trans_table2[] = {
		// state, request, guard1, guard2, guard3
		0, 1, 1, 0, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
	};

	const uint8_t bitmask_guards2[n_guard2] = {0, 0, 0};
	fsm_init(&fsm2, n_trans2, n_guard2, trans_table2, bitmask_guards2);

	const uint32_t status2_1[n_guard2] = {1, 0, 1};
	assert(fsm_update(&fsm, 0, 1, status2_1) == 1);

	const uint32_t status2_2[n_guard2] = {1, 0, 0};
	assert(fsm_update(&fsm, 0, 1, status2_2) == 1);

	const uint32_t status2_3[n_guard2] = {0, 0, 1};
	assert(fsm_update(&fsm, 0, 1, status2_3) == 0);

	return 0;
}
