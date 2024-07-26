#pragma once
#include <string>
#include <iostream>
#include <iomanip> // this is to support setw

#include "PhoneNumber.h"
#include "Date.h"

class BaseEmployee
{
public:
	BaseEmployee(std::string fn = {}, std::string ln = {}, std::string sn = {}, int salary = 0) : firstName(fn), lastName(ln), SIN(sn)//, baseSalary(salary)
	{
		++sNumEmployees;
	}

	virtual ~BaseEmployee()
	{
		--sNumEmployees;
		std::cout << "~BaseEmployee: " << firstName << " " << lastName << " deleted" << std::endl;
	}

	std::string getFirstName() const
	{
		return firstName;
	}

	// add getter for lastname, SIN, baseSalary
	std::string getLastName() const
	{
		return lastName;
	}
	std::string getSIN() const
	{
		return SIN;
	}
	int getBaseSalary() const
	{
		return baseSalary;
	}
	

	std::string getFullName() const
	{
		return firstName + " " + lastName;
	}

	// add setter for baseSalary
	void setBaseSalary(int newSalary) {
		baseSalary = newSalary;
	}

	operator std::string() const // string converter for BaseEmployee class
	{
		// todo: add  phone number and starting date to the following string output.
		return "Employee: " + firstName + " " + lastName + ", SIN: " + SIN + ", Phone Number: " + phone.to_string() + ", Start Date: " + startDate.to_string();
	}


	static int getNumEmployees() //const // it is a "class" method vs "obj" method
	{
		return sNumEmployees;
	}

	std::string getPhoneNumber() const
	{
		return phone.to_string();
	}

	virtual double earning() const = 0; 

	int getYearsWorked() const
	{
		return startDate.yearsEmployed();
	}
	
	virtual std::string to_string() const
	{
		return "Employee: " + firstName + " " + lastName + ", SIN: " + SIN + ", phone number: " + phone.to_string() + ", startDate: " + startDate.to_string();
	}

protected:
	std::string firstName, lastName, SIN;
	PhoneNumber phone;
	Date startDate;
	int baseSalary{};

private:
	static int sNumEmployees; // to keep track of total number of employees.

	friend std::ostream& operator<<(std::ostream& os, const BaseEmployee* bEmp)
	{
		os << std::left << std::setw(19) <<
			"Employee Name:" << bEmp->firstName << " " << bEmp->lastName << std::left << std::setw(20) <<
			"\nStart Date: " << bEmp->startDate << std::left << std::setw(20) <<
			"\nPhone Number: " << bEmp->phone << std::left << std::setw(20) << std::endl;
		
		return os;
	}

	// add overload for output operator >> bellow:

	friend std::istream& operator>>(std::istream& is, BaseEmployee& bEmp)
	{
		std:: cout << "Enter first name: ";
		is >> bEmp.firstName;
		std::cout << "Enter last name: ";
		is >> bEmp.lastName;
		std::cout << "Enter SIN: ";
		is >> bEmp.SIN;
		std::cout << "Enter phone number (format: (604)313-2121): ";
		is >> bEmp.phone;
		std::cout << "Enter start date (format: day-month-year): ";
		is >> bEmp.startDate;
		std::cout << "Enter base salary: ";
		is >> bEmp.baseSalary;

		return is;
	}

};
int BaseEmployee::sNumEmployees = 0;