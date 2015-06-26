#include <inttypes.h>
#include <stdarg.h>

#include <px4/fsm.h>
#include <px4/cprover_stub.h>

void fsm_init(fsm_t *this, uint8_t trans_num, uint8_t guard_num,
	      const uint32_t * trans_table,
		  const uint8_t * guard_is_bitmask)
{
	this->trans_num = trans_num;
	this->guard_num = guard_num;
	this->trans_table = trans_table;
	this->guard_is_bitmask = guard_is_bitmask;
}

uint32_t fsm_update(fsm_t *this, uint32_t state,
		uint32_t request, const uint32_t * status)
{
	// local variables
	uint8_t i = 0;
	uint8_t j = 0;
	va_list argp;
	uint8_t n = this->guard_num + 2;

	uint32_t tbl_state = 0;
	uint32_t tbl_request = 0;
	uint32_t tbl_guard = 0;
	
	// for each transition in the table
	for (i = 0; i < this->trans_num; i++) {

		tbl_state = this->trans_table[n*i];
		tbl_request = this->trans_table[n*i + 1];

		// if the state and the requested state match the table
		if (state == tbl_state && request == tbl_request) {

			// check each guard condition
			j = 0;
			while (j < this->guard_num) {
				tbl_guard = this->trans_table[n*i + 2 + j];

				// if using a bitmask guard
				if (this->guard_is_bitmask[j]) {
					// break if using a bitmask guard and
					// not a masked match
				    if ((status[j] & tbl_guard) != tbl_guard) {
						break;
					}
				// if not uing a bitmask
				} else { 
					// break if the guard doesn't match
					// the status or the any flag
					if (!((status[j] == tbl_guard) ||
						(tbl_guard == ANY_FLAG))) {
						break;
					}
				}
				j++;
				if (j >= this->guard_num) {
					return request;
				}
			}
		}
	}

	// if we have gotten here, there are no valid
	// transitions, so return the current state
	return state;
}
