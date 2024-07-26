#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "BaseEmployee.h"
#include "CommissionEmployee.h"
#include "SalaryCommisionEmployee.h"
#include "SalaryEmployee.h"
#include "Date.h"
#include "PhoneNumber.h"

using namespace std;

//int BaseEmployee::sNumEmployees{};

int main(int argc, char** argv)
{
    vector<BaseEmployee*> employees;
    vector<SalaryEmployee*> salaryEmployees;
    vector<CommissionEmployee*> commissionEmployees;
    vector<SalaryCommissionEmployee*> salaryCommissionEmployees;

    if (argc < 2)
    {
        std::cout << "Usage: assignmentTests.exe filename\n";
        return 1;
    }
    else
    {
        std::cout << "Processing input file " << argv[1] << endl;

        // Opening input file for processing
        ifstream fs(argv[1]);

        if (!fs.is_open()) {
            std::cout << "Error opening file: " << argv[1] << endl;
            return 1;
        }

        string line;
        getline(fs, line); // skip the header line

        while (getline(fs, line)) {
            if (line[0] == '/' || line.empty())
            {
                continue; // skip commented lines or empty lines
            }

            // Read employee name
            stringstream ss(line);
            string firstname, lastname, SIN, phoneNumStr, startDateStr, employeeType;
            ss >> firstname >> lastname >> SIN >> phoneNumStr >> startDateStr >> employeeType;

            std::stringstream phoneStream(phoneNumStr);
            PhoneNumber phoneNumber;
            phoneStream >> phoneNumber;

            std::stringstream dateStream(startDateStr);
            Date startDate;
            dateStream >> startDate;

            if (employeeType == "SalaryEmployee")
            {
                double salary;
                string salaryStr;
                ss >> salaryStr;
                salary = (salaryStr == "DNA") ? 0 : stod(salaryStr);

                std::cout << "Creating SalaryEmployee: " << firstname << " " << lastname << " with salary " << salary << std::endl;

                SalaryEmployee* sEmp = new SalaryEmployee(firstname, lastname, SIN, salary);
                sEmp->setBaseSalary(salary);
                employees.push_back(sEmp);
                salaryEmployees.push_back(sEmp);

            }
            else if (employeeType == "CommissionEmployee")
            {
                double commissionRate, grossSale;
                string commissionRateStr, grossSaleStr;
                ss >> grossSaleStr >> commissionRateStr;
                commissionRate = (commissionRateStr == "DNA") ? 0 : stod(commissionRateStr);
                grossSale = (grossSaleStr == "DNA") ? 0 : stod(grossSaleStr);

                std::cout << "Creating CommissionEmployee: " << firstname << " " << lastname << " with commission rate " << commissionRate << " and gross sale " << grossSale << std::endl;

                CommissionEmployee* cEmp = new CommissionEmployee(firstname, lastname, SIN, commissionRate);
                cEmp->setGrossSale(grossSale);
                employees.push_back(cEmp);
                commissionEmployees.push_back(cEmp);

            }
            else if (employeeType == "SalaryCommissionEmployee")
            {
                double salary, commissionRate, grossSale;
                string salaryStr, commissionRateStr, grossSaleStr;
                ss >> salaryStr >> commissionRateStr >> grossSaleStr;
                salary = (salaryStr == "DNA") ? 0 : stod(salaryStr);
                commissionRate = (commissionRateStr == "DNA") ? 0 : stod(commissionRateStr);
                grossSale = (grossSaleStr == "DNA") ? 0 : stod(grossSaleStr);

                std::cout << "Creating SalaryCommissionEmployee: " << firstname << " " << lastname << " with salary " << salary << ", commission rate " << commissionRate << ", and gross sale " << grossSale << std::endl;

                SalaryCommissionEmployee* scEmp = new SalaryCommissionEmployee(firstname, lastname, SIN, salary, commissionRate);
                scEmp->setGrossSale(grossSale);
                employees.push_back(scEmp);
                salaryCommissionEmployees.push_back(scEmp);
            }
            else
            {
                std::cout << "Unknown employee type: " << employeeType << std::endl;
            }
        }

        fs.close();

        // Display all employees
        for (const auto& emp : employees)
        {
            std::cout << emp->to_string() << std::endl;
        }

        // Cleanup
        for (auto& emp : employees)
        {
            delete emp;
        }
    }

    return 0;
}

