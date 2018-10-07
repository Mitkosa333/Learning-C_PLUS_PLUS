#include "Basic.h"

bool ifPowerOf2(unsigned num)
{
	return !((num)&(num - 1));
}

long long SecondsPassed()
{
	return time(0);
}

void ParseIdAndCurTimeIntoChar(char* number, unsigned id)
{
	long long seconds = time(0);
	char numberBuffer[64] = { 0 };
	unsigned idTEMP = id;
	long long secondsTEMP = seconds;
	int num = 0;

	int sizeId = 0;
	while (idTEMP != 0)
	{
		num = idTEMP % 10;
		idTEMP /= 10;
		numberBuffer[sizeId] = num + '0';
		sizeId++;
	}

	numberBuffer[sizeId] = '\0';

	int sizeIdTEMP = sizeId;

	for (int i = 0; sizeIdTEMP > 0; i++)
	{
		number[i] = numberBuffer[sizeIdTEMP - 1];
		sizeIdTEMP--;
	}

	number[sizeId] = ' ';

	int sizeSeconds = 0;
	while (secondsTEMP != 0)
	{
		num = secondsTEMP % 10;
		secondsTEMP /= 10;
		numberBuffer[sizeSeconds] = num + '0';
		sizeSeconds++;
	}

	numberBuffer[sizeSeconds] = '\0';

	int sizeSecondsTEMP = sizeSeconds;

	for (int i = 0; sizeSecondsTEMP > 0; i++)
	{
		number[i + sizeId + 1] = numberBuffer[sizeSecondsTEMP - 1];
		sizeSecondsTEMP--;
	}

	number[sizeId + sizeSeconds + 1] = '.';
	number[sizeId + sizeSeconds + 2] = 't';
	number[sizeId + sizeSeconds + 3] = 'x';
	number[sizeId + sizeSeconds + 4] = 't';
	number[sizeId + sizeSeconds + 5] = '\0';

}
