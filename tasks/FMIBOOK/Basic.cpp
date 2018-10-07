#include "Basic.h"

bool ifPowerOf2(unsigned num)
{
	return !((num)&(num - 1));
}
