#include <iostream>
#include <vector>
#include "TextTable.h"
#include "colors.h"


using namespace std;

struct Employee {
    string id;
    string name, job;
    double basic_Salary;
    double it, epf, ma, hra, ta, gross, deduction, net_salary;
};

double deduct(double z, double y) {
    return z - y;
}


Employee insertData() {
    Employee employee;
    cout << FGRN("Enter Employee ID : ");
    cin >> employee.id;
    cout << FGRN("Enter Employee name : ");
    cin >> employee.name;
    cout << FGRN("Enter Employee Job : ");
    cin >> employee.job;
    cout << FGRN("Enter Employee basic salary : ");
    cin >> employee.basic_Salary;

    /*employee.id = "123";
    employee.name = "Faysal Hossain";
    employee.job = "Android";
    employee.basic_Salary = 500;*/

    if (employee.basic_Salary <= 3000) {
        employee.it = employee.basic_Salary * 0.1;
        employee.hra = 300;
    }

    if (employee.basic_Salary > 3000 && employee.basic_Salary <= 5000) {
        employee.it = employee.basic_Salary * 0.12;
        employee.hra = 500;
    }

    if (employee.basic_Salary > 5000) {
        employee.it = employee.basic_Salary * 0.15;
        employee.hra = 750;
    }

    employee.epf = employee.basic_Salary * 0.12;
    employee.ma = 200;

    cout << FGRN("How much do wish to reimburse  allowance? from 0 - 300 : ");
    cin >> employee.ta;
    employee.ta = 150;
    employee.ta = static_cast <double>(employee.ta);


    while (employee.ta > 300 || employee.ta < 0) {
        cout << FGRN("Error please put in a number between 0 and 300 " << "\n");
        cin >> employee.ta;
    }

    employee.gross = employee.basic_Salary + employee.hra + employee.ma + employee.ta;
    employee.deduction = employee.it + employee.epf;
    employee.net_salary = deduct(employee.gross, employee.deduction);

    return employee;
}

void displayEmployee(Employee employee, TextTable &table);


int main() {
    string answer;
    vector<Employee> empList;

    cout << BOLD(FRED("Taylor's University")) << endl;
    cout << FCYN("Employee Management SYSTEM") << endl;
    cout << FMAG("---------------------------") << endl;

    do {
        Employee emp = insertData();
        empList.push_back(emp);

        cout << FBLU("Do you wish to add another user? : ");
        cin >> answer;
    } while (answer != "no");

    TextTable headerTable('-', '|', '+');
    headerTable.add("  Here are the details of the Employee's Payroll  ");
    headerTable.endOfRow();
    headerTable.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << headerTable;

    TextTable table('-', '|', '+');
    table.add("  Employee Id  ");
    table.add("  Employee Name  ");
    table.add("  Employee Job  ");
    table.add("  Basic Salary  ");
    table.add("  Net salary  ");
    table.endOfRow();

    for (const Employee &emp: empList) {
        displayEmployee(emp, table);
    }

    table.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << table;

    cout << FBLU("Thank You") << endl;
    cout << BOLD(FBLU("Developed By - Faysal | Youssef | Rainaf | Atul")) << endl;


    return 0;

}

void displayEmployee(Employee employee, TextTable &table) {
    table.add(employee.id);
    table.add(employee.name);
    table.add(employee.job);
    table.add(to_string(employee.basic_Salary));
    table.add(to_string(employee.net_salary));
    table.endOfRow();
}
