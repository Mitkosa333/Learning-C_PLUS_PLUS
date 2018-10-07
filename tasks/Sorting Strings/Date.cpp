#include "Date.h"

Date::Date(const char * word)
{
	type = DATE;
	content = new char[strlen(word) + 1];
	strncpy(content, word, strlen(word) + 1);
}

Date & Date::operator=(const Date & obj)
{
	if (this != &obj)
	{
		Word::operator=(obj);
	}
	return*this;
}

unsigned Date::compare(const Word & obj) const
{
	return (strcmp(getType(), obj.getType()) == 0)
		? dayDifference(obj.getContent()) 
		: 0;
}

Word * Date::clone() const
{
	return new Date(*this);
}

unsigned Date::dayDifference(const char* word) const
{
	unsigned day1 = content[0] * 10 + content[1];
	unsigned month1 = content[3] * 10 + content[4];
	unsigned year1 = content[6] * 1000 + content[7] * 100 + content[8] * 10 + content[9];

	unsigned day2 = word[0] * 10 + word[1];
	unsigned month2 = word[3] * 10 + word[4];
	unsigned year2 = word[6] * 1000 + word[7] * 100 + word[8] * 10 + word[9];

	if ((year1 - year2 >= -1 && year1 - year2 <= 1) && (month1 - month2 >= 4 && month1 - month2 <= -4))
	{
		if (year1 > year2)
		{
			return checkTheDifference(day2, month2, year2, day1, month1, year1);
		}
		else if (year1 < year2)
		{
			return checkTheDifference(day1, month1, year1, day2, month2, year2);
		}
		else
		{
			if (month1 > month2)
			{
				return checkTheDifference(day2, month2, year2, day1, month1, year1);
			}
			else if (month1 < month2)
			{
				return checkTheDifference(day1, month1, year1, day2, month2, year2);
			}
			else
			{
				if (day1 > day2)
				{
					return checkTheDifference(day2, month2, year2, day1, month1, year1);
				}
				else if (day1 < day2)
				{
					return checkTheDifference(day1, month1, year1, day2, month2, year2);
				}
				else
				{
					return 100;
				}
			}
		}
	}
	else
	{
		return 0;
	}
}

unsigned Date::checkTheDifference(unsigned day1, unsigned month1, unsigned year1, unsigned day2, unsigned month2, unsigned year2) const
{
	int counter = 100;
	CheckDates checks;

	while (1)
	{
		if (checks.does_date_exist(day1 + 1, month1, year1))
		{
			day1++;
		}
		else if ((checks.does_date_exist(day1, month1 + 1, year1)))
		{
			month1++;
		}
		else
		{
			year1++;
		}

		if (day1 == day2 && month1 == month2 && year1 == year2)
		{
			return counter;
		}

		counter--;

		if (counter <= 0)
		{
			return 0;
		}	
	}
}




	


