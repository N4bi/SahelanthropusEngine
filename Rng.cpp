#include "Rng.h"
#include <stdlib.h>

#define FLOAT_MAX 4294967295.0f
unsigned int Rng::random()
{
	static unsigned int x = 2463534242U;
	static unsigned int y = 123456789U;
	static unsigned int z = 43219876;
	static unsigned int c = 6543217;
	static unsigned lfsr = 0x8102;

	y = 314527869 * y + 1234567; // Linear congruental generator
	lfsr = (-(lfsr & 1)) & 0xd0000001u ^ lfsr >> 1;  // Galois LFSR

	if (lfsr & 1)
	{
		unsigned long long t;
		t = FLOAT_MAX * x + c;
		c = t >> 32;
		x = t;
	}
	else
	{
		//Xorshift
		z ^= (z << 5);
		z ^= (z >> 7);
		z ^= (z << 22);
	}

	return (x + y + z);

}

