#include <inttypes.h>
#include <stdarg.h>

#include <px4/fsm.h>
#include <px4/cprover_stub.h>


void fsm_init(fsm_t *this, uint8_t trans_num, uint8_t guard_num,
	      uint32_t * trans_table, uint8_t * guard_is_bitmask)
{
	this->trans_num = trans_num;
	this->guard_num = guard_num;
	this->trans_table = trans_table;
	this->guard_is_bitmask = guard_is_bitmask;
}

uint32_t fsm_update(fsm_t *this, uint32_t state, uint32_t request, ...)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t match = 0;
	uint8_t tbl_state = 0;
	uint8_t tbl_request = 0;
	va_list argp;
	va_start(argp, request);
	uint8_t n = this->guard_num + 2;
	uint32_t status[this->guard_num];

	for (j = 0; j < this->guard_num; j++) {
		status[j] = va_arg(argp, uint32_t);
	}

	for (i = 0; i < this->trans_num; i++) {
		tbl_state = this->trans_table[n*i];
		tbl_request = this->trans_table[n*i + 1];
		if (state == tbl_state && request == tbl_request) {
			for (j = 0; j < this->guard_num; j++) {
				uint32_t tbl_guard = this->trans_table[n*i + 2 + j];
				if (this->guard_is_bitmask[j] &&
				    ((status[j] & tbl_guard) != tbl_guard)) {
					break;

				} else if (
					((status[j] & tbl_guard) != tbl_guard)
					&& tbl_guard != ANY_FLAG)	{
					break;
				}
			}

			if (j == this->guard_num) {
				match = 1;
			}
		}
	}
	if (match) {
		state = request;
	}
	return state;
}
