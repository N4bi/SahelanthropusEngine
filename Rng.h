#ifndef __RNG_H__
#define __RNG_H__
#include <stdint.h>

class Rng
{

public:

	unsigned int random();
	float floatRandom();
	int intRandom(int min, int max);
	void setZ(unsigned int _z);

private:

	unsigned int z = 0;
};



#endif // !__RNG_H__
