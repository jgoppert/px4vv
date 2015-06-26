#pragma once

#include <inttypes.h>

typedef struct fsm_t {
	uint8_t trans_num;
	uint8_t guard_num;
	const uint32_t *trans_table;
	const uint8_t *guard_is_bitmask;
} fsm_t;

void fsm_init(fsm_t *this, uint8_t trans_num,
		uint8_t guard_num, const uint32_t * trans_table,
		const uint8_t * guard_is_bitmask);

enum fsm_flags_t {
	ANY_FLAG = 123456789, // flag to indicate any state allowable
};

uint32_t fsm_update(fsm_t *this, uint32_t state,
		uint32_t request, const uint32_t * status);
