
/**---Header-----**/
#include <iostream>
#include <vector>
#include "TextTable.h"
#include "colors.h"

using namespace std;


/**----  declaration of struct Employee ---**/
struct Employee {
    string id;
    string name, job;
    float basic_Salary;
    float it, epf, ma, hra, ta, gross, deduction, net_salary;
};

/**---- deducts the given codes ---**/
float deduct(float z, float y) {
    return z - y;
}

/**---- Calculation ---**/
Employee calculation(Employee &employee) {
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

    cout << FGRN("How much do wish to reimburse? ( max 300 RM ): ");
    cin >> employee.ta;

    /**---- Validation ---**/
    while (employee.ta > 300 || employee.ta <= 0) {
        cout << BOLD(FRED(" ERROR; please enter a number between 0 and 300 ")) << endl;
        cin >> employee.ta;
    }

    employee.ta = static_cast <float>(employee.ta);

    /**---- Calculation of Net salary ---**/
    employee.gross = employee.basic_Salary + employee.hra + employee.ma + employee.ta;
    employee.deduction = employee.it + employee.epf;
    employee.net_salary = deduct(employee.gross, employee.deduction);
    return employee;
}

/**---- input of user ---**/
Employee insertData() {
    Employee employee;
    cout << FGRN("Enter Employee ID : ");
    getline(cin, employee.id);
    cout << FGRN("Enter Employee name : ");
    getline(cin, employee.name);
    cout << FGRN("Enter Employee Job : ");
    getline(cin, employee.job);
    cout << FGRN("Enter Employee basic salary : ");
    cin >> employee.basic_Salary;
    return calculation(employee);
}

/**---- Output function ---**/
void displayEmployee(Employee employee, TextTable &table) {
    table.add(employee.id);
    table.add(employee.name);
    table.add(employee.job);
    table.add(to_string(employee.basic_Salary));
    table.add(to_string(employee.net_salary));
    table.endOfRow();
}

/**---- Main Function ---**/
int main() {
    string answer;
    vector<Employee> empList;

    cout << BOLD(FRED("Taylor's University")) << endl;
    cout << FCYN("Employee Management SYSTEM") << endl;
    cout << FMAG("---------------------------") << endl;

    do {
        Employee emp = insertData();
        empList.push_back(emp);
        emp = {};
        cin.clear();
        cin.ignore();

        /**---- New user check ---**/
        cout << FBLU("Do you wish to add another user? : ");
        getline(cin, answer);
    } while (answer != "no");

/**---- Output ---**/
    TextTable headerTable('-', '|', '+');
    headerTable.add("Employee's Payroll  Details ");
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

    table.setAlignment(0, TextTable::Alignment::RIGHT);
    cout << table;

    cout << FYEL("Thank You") << endl;
    cout << BOLD(FBLU("Developed By - Faysal | Youssef | Rainaf | Atul")) << endl;


    return 0;

}

