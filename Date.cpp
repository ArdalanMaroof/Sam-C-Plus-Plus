#include <iostream>
#include <string>
#include "Date.h"
#include <ctime>

// initialize static member:
const std::array<unsigned int, 13> Date::days{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// constructor
Date::Date(unsigned int m, unsigned int d, unsigned int y)
{
	setDate(m, d, y);
}
// example : Date d1{12, 27, 2020}; d1.setDate(12, 26, 2020);
void Date::setDate(unsigned m, unsigned d, unsigned y)
{
	if (m >= 1 && m <= 12)
		month = m;
	else
		throw std::invalid_argument{ "Month must be 1-12" };
	
	if (y >= 1900 && y <= 2100)
		year = y;
	else
		throw std::invalid_argument{ "Year must be >=1900 and <=2100" };

	if ((d >= 1 && d <= days[m]) || (m==2 && leapYear(y) && d <= 29) )
		day = d;
	else
		throw std::invalid_argument{ "Day is out of range for the current month and year" };
}

// overloading prefix increment operator. Incrementing day
Date& Date::operator++()
{
	helpIncrement(); // takes care of incrementing day
	return *this;
}
// overloading postfix increment. Note the dummy integer argument which is not used, so has no name
Date Date::operator++(int)
{
	Date temp{ *this }; 
	helpIncrement();
	return temp;
}


Date& Date::operator+=(unsigned d)
{
	for (int i = 0; i < d; ++i)
		helpIncrement();

	return *this;

}

// checks to see if we are in a leap year or not
bool Date::leapYear(unsigned y)
{
	return (y % 400 == 0)  ||
						 (y % 100 != 0 && y % 4 == 0);
}

bool Date::endOfMonth(unsigned d) const
{
	bool isEndOfMonth{ false };
	if (month == 2 && leapYear(year) ) 
		isEndOfMonth = (d == 29);
	else // means we are not in a feb of a leap year
		isEndOfMonth = (d == days[month]);

	return isEndOfMonth;
}

// implement method yearsEmployed() bellow. It computes how many calendar year
// employee has been working till now. 
// Use function time(0) and function localtime_s() to implement this function.
// Refer to https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm.
int Date::yearsEmployed() const
{
	// to be done by students
	//Get the current time
	time_t now = time(0);

	//convert it to local time
	tm currentTime{};
	localtime_s(&currentTime, &now);

	int currentYear = currentTime.tm_year + 1900; // tm_year is years since 1900
	int currentMonth = currentTime.tm_mon + 1;   // tm_mon is months since January (0-11)
	int currentDay = currentTime.tm_mday;         // tm_mday is day of the month

	// Compute the number of years
	int years = currentYear - year;

	// Check if the anniversary hasn't occurred yet this year
	if (currentMonth < month || (currentMonth == month && currentDay < day))
	{
		years--;
	}

	return years;
}

// increments the day and takes care of changes needed to month and year
void Date::helpIncrement()
{
	// if day is no tend of the month
	if (!endOfMonth(day))
		++day;
	else  // here take care of the case when day is end of moth
	{
		if (month < 12)
		{
			++month;
			day = 1;
		}
		else
		{
			++year;
			month = 1;
			day = 1;
		}
	}
}
