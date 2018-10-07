#ifndef CHECKDATES_H
#define CHECKDATES_H

const unsigned MAX_DATE = 10;

class CheckDates
{
public:
	bool isDateValid(const char*);
	bool does_date_exist(const unsigned, const unsigned, const unsigned);

private:
	bool check_format(const char*);
	bool is_leap_year(const unsigned);
};
#endif // !CHECKDATES_H
