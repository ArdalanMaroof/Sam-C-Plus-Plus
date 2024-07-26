#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "SalaryEmployee.h"
#include "CommissionEmployee.h"

class SalaryCommissionEmployee : public SalaryEmployee, public CommissionEmployee
{
public:
	SalaryCommissionEmployee(std::string first = {},
		std::string last = {},
		std::string sin = {}, double pay = { 35000. }, double rate = { 0.10 }) :
		BaseEmployee(first, last, sin),
		SalaryEmployee(first, last, sin, pay), 
		CommissionEmployee(first, last, sin, rate)
	{
		setSalary(pay);
		setcommisionRate(rate);
		++sNumSalaryCommissionEmployees;
	}

	~SalaryCommissionEmployee() 
	{
		std::cout << "salarycommission employee deleted";
		--sNumSalaryCommissionEmployees;
	}

	virtual double earning() const override
	{
		return SalaryEmployee::earning() + CommissionEmployee::earning();
	}

	virtual std::string to_string() const override
	{	
		return "SalaryCommisionEmployee: " + BaseEmployee::to_string() + ", earning=" + std::to_string(earning());
	}

private:

// add static variable to keep track of number of SalComm Employees.
	static int sNumSalaryCommissionEmployees;

	friend std::ostream& operator<<(std::ostream& os, const SalaryCommissionEmployee* salComm)
	{
		std::cout<<"To be done by students. Use BaseEmployee string coversion operator to print the base info. THen add salary print out.\n";
		os << dynamic_cast<const BaseEmployee*>(salComm);
		os << "Salary: " << salComm->getSalary() << "\nCommission Rate: " << salComm->getcommisionRate()
			<< "\nGross Sale: " << salComm->getGrossSale() << std::endl;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, SalaryCommissionEmployee& salComm)
	{
		// todo: implement this. Use BaseEmployee input opearator for receiving base info.
		is >> dynamic_cast<BaseEmployee&>(salComm);
		double salary, commissionRate, grossSale;

		std::cout << "Enter salary: ";
		is >> salary;
		salComm.setSalary(salary); // Set salary using the setter method

		std::cout << "Enter commission rate: ";
		is >> commissionRate;
		salComm.setcommisionRate(commissionRate); // Set commission rate using the setter method

		std::cout << "Enter gross sale: ";
		is >> grossSale;
		salComm.setGrossSale(grossSale); // Set gross sale using the setter method

        return is;

	}
};
int SalaryCommissionEmployee::sNumSalaryCommissionEmployees = 0;
