#include "CheckDates.h"

bool CheckDates::isDateValid(const char * new_word)
{
	if (!check_format(new_word))
	{
		return false;
	}

	const unsigned day = new_word[0] * 10 + new_word[1];
	const unsigned month = new_word[3] * 10 + new_word[4];
	const unsigned year = new_word[6] * 1000 + new_word[7] * 100 + new_word[8] * 10 + new_word[9];

	return does_date_exist(day, month, year);
}

bool CheckDates::does_date_exist(const unsigned day, const unsigned month, const unsigned year)
{
	bool validation = true;

	if (day == 0)
	{
		validation = false;
	}

	switch (month)
	{
	case 2:
	{
		if (is_leap_year(year))
		{
			if (day > 29)
			{
				validation = false;
			}
		}
		else
		{
			if (day > 28)
			{
				validation = false;
			}
		}
	}
		break;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
	{
		if (day > 31)
		{
			validation = false;
		}
	}
	break;
	case 4: case 6: case 9: case 11:
	{
		if (day > 30)
		{
			validation = false;
		}

	}
	break;
	default:
	{
		validation = false;

	}
	break;
	}

	return validation;

}

bool CheckDates::check_format(const char * new_word)
{
	for (unsigned i = 0; i < MAX_DATE; i++)
	{
		if (i == 2 || i == 5)
		{
			if (!(new_word[i] == '-'))
			{
				return false;
			}
		}
		else if (!(new_word[i] >= '0' && new_word[i] <= '9'))
		{
			return false;
		}
	}

	if (new_word[MAX_DATE] == '\0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckDates::is_leap_year(const unsigned year)
{
	return ((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0));
}
