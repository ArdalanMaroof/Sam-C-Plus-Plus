#pragma once
#include <iostream>
#include "BaseEmployee.h"
// add support to keep track of number of CommissionEmployee
class CommissionEmployee : virtual public BaseEmployee
{
public:
	CommissionEmployee(std::string first = {},
		std::string last = {},
		std::string sin = {},
		double rate = { 0.10 }) :
		BaseEmployee(first, last, sin),
		commisionRate(rate),
		grossSale(0.)

	{
		++sNumCommissionEmployees;
		std::cout << "CommissionEmployee created:" << "Commission=" << commisionRate << std::endl;
	}


	~CommissionEmployee()
	{
		--sNumCommissionEmployees;
		std::cout << "~CommissionEmployee.\n";
	}

	void setGrossSale(double sale)
	{
		grossSale = sale;
	}
	double getGrossSale() const
	{
		return grossSale;
	}
	void setcommisionRate(double sale)
	{
		commisionRate = sale;
	}
	double getcommisionRate() const
	{
		return commisionRate;
	}	
	
	virtual double earning() const override
	{
		return grossSale * commisionRate;
	}

private:
	double grossSale;
	double commisionRate;
	static int sNumCommissionEmployees;
// add friend operator<< and friend operator>> overrides bellow:

	friend std::ostream& operator<<(std::ostream& os, const CommissionEmployee* cEmp)
	{
		os << dynamic_cast<const BaseEmployee*>(cEmp);
		os << "Commission Rate: " << cEmp->commisionRate << "\nGross Sale: " << cEmp->grossSale << std::endl;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, CommissionEmployee& cEmp)
	{
		is >> dynamic_cast<BaseEmployee&>(cEmp);
		std::cout << "Enter commission rate: ";
		is >> cEmp.commisionRate;
		std::cout << "Enter gross sale: ";
		is >> cEmp.grossSale;
		return is;

	}
};

int CommissionEmployee::sNumCommissionEmployees = 0;