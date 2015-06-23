#include <inttypes.h>

enum {
	S_ARM = 0,
	S_DISARM,
	S_MANUAL,
	S_STABILIZED,
	S_GUIDED,
	S_AUTO,
	S_SAFETY_ON,
	S_SAFETY_OFF,
};

enum {
	X_ARMED = 1 << 1,
	X_MANUAL = 1 << 2,
	X_GUIDED = 1 << 3,
	X_AUTO = 1 << 4,
	X_SAFETY = 1 << 5,
};

enum {
	A_NONE=0,
	A_HELLO,
	A_ARM,
	A_DISARM,
};

uint16_t command(uint16_t state, uint16_t transition);
