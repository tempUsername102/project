#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <vector>

using namespace std;

void writeFile();
vector<string> splitString(string line);
void writeReport(string text);
void pressKey();


class Account {
public:
    Account(string accNum, string nationalNum, long long blnc, int y, int m, int d, bool stts);
    Account(string nationalNum);

    string getAccountNumber() {return accountNumber;}
    string getCustomerNationalNumber() {return customerNationalNumber;}
    long long getBalance() {return balance;}
    int getOpeningYear() {return openingYear;}
    int getOpeningMonth() {return openingMonth;}
    int getOpeningDay() {return openingDay;}
    bool getStatus() {return status;}
        
        
    void checkStatus();
    void changeStatus();
    void increaseBalance();
    void receiveBalance();
    void showAccount();
private:
    string accountNumber,
            customerNationalNumber;
    long long balance;
    int openingYear,
        openingMonth,
        openingDay;
    bool status;
};


class Person {
public:
    void setPersonDetails();

    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    string getUsername() { return username; }
    string getPassword() { return password; }
    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }
    

    void setFirstName(string f) { firstName = f; }
    void setLastName(string l) { lastName = l; }
    void setusername(string u) { username = u; }
    void setPassword(string p) { password = p; }
    void setYear(int y) { year = y; }
    void setMonth(int m) { month = m; }
    void setDay(int d) { day = d; }



    void showPersonDetails();

private:
    string firstName,
            lastName,
            username,
            password;
    int year,
        month,
        day;
};


class Employee: public Person {
public:
    Employee ():
        timeOff(0), overtime(0) {};

    void setEmployeeDetails(string personnelNum = "");

    string getPersonnelNumber() { return personnelNumber; }
    int getTimeOff() { return timeOff; }
    int getOvertime() { return overtime; }
    long long getSalary() { return salary; }
    

    void setPersonnelNumber(string pn) { personnelNumber = pn; }
    void setTimeOff(int to) { timeOff = to; }
    void setOvertime(int o) { overtime = o; }
    void setSalary(long long s) { salary = s; }

    void addTimeOff();
    void addOvertime();
    void showEmployeeDetails();

private:
    string  personnelNumber;
    int timeOff,
        overtime;
    long long salary;
};


class Manager: public Employee {};


class Customer: public Person {
public:
    void setCustomerInfo(string nationalNum = "");

    string getNationalNumber() { return nationalNumber; }
    vector<Account> getAccounts() { return accounts; }

    void setNationalNumber(string nn) { nationalNumber = nn; }
    void newAcc(Account a) { accounts.push_back(a); }
    int findAccount(string accountNum);

    void changeAccountStatus(int index) {accounts.at(index).changeStatus();}

    void addAccount();
    void deleteAccount(int accountIndex);
    void increaseAnAccountBalance();
    void receiveBalanceFromAnAccount();
    void SetActive();
    void showCustomer();

private:
    string nationalNumber;

    vector<Account> accounts;
};


class Bank {
public:
    void firstTimeManager();

    long long findCustomer();
    int findEmployee(string personnelNum);

    bool PersonnelNumberIsDuplicate(string pn);

    void addEmployee();
    void deleteEmployee();
    void deleteAccount();
    void employeeMenu();
    void customerMenu();
    
    Manager getManager() {return manager;}
    vector<Employee> getEmployees() {return employees;}
    vector<Customer> getCustomers() {return customers;}
    
    void setManager(string f, string l, string u, string p, int y, int m, int d, string pn, int to, int o, long long s) {
        manager.setFirstName(f);
        manager.setLastName(l);
        manager.setusername(u);
        manager.setPassword(p);
        manager.setYear(y);
        manager.setMonth(m);
        manager.setDay(d);
        manager.setPersonnelNumber(pn);
        manager.setTimeOff(to);
        manager.setOvertime(o);
        manager.setSalary(s);
    }
    void newEmployee(string f, string l, string u, string p, int y, int m, int d, string pn, int to, int o, long long s) {
        Employee e;
        e.setFirstName(f);
        e.setLastName(l);
        e.setusername(u);
        e.setPassword(p);
        e.setYear(y);
        e.setMonth(m);
        e.setDay(d);
        e.setPersonnelNumber(pn);
        e.setTimeOff(to);
        e.setOvertime(o);
        e.setSalary(s);
        employees.push_back(e);
    }

    void newCustomer(Customer c) {customers.push_back(c);}

private:
    Manager manager;
    vector<Employee> employees;
    vector<Customer> customers;
    string branchName,
            branchCode;
};


vector<Employee> globalEmployees;
vector<Customer> globalCustomers;


Account::Account(string accNum, string nationalNum, long long blnc, int y, int m, int d, bool stts) {
    accountNumber = accNum;
    customerNationalNumber = nationalNum;
    balance = blnc;
    openingYear = y;
    openingMonth = m;
    openingDay = d;
    status = stts;
}
Account::Account(string nationalNum) {
    while (true) {
        cout << "Enter account number (Must be 16 digits): ";
        cin >> accountNumber;

        if (accountNumber.size() != 16) {
            continue;
        }

        for (char c: accountNumber) {
            if (c < '0' || c > '9') {
                continue;
            }
        }

        for (Customer c: globalCustomers) {
            for (Account a: c.getAccounts()) {
                if (accountNumber == a.getAccountNumber()) {
                    cout << "This account number is duplicate.\n";
                    continue;
                }
            }
        }
        break;
    }

    while (true) {
        cout << "Enter account opening date (Day Mounth Year): ";
        cin >> openingDay >> openingMonth >> openingYear;

        if (openingDay >= 1 && openingDay <= 31 && openingMonth >= 1 && openingMonth <= 12 && openingYear >= 1350 && openingYear <= 1401) {
            break;
        }
    }

    do {
        cout << "Enter account balance (Can't be less than 50000): ";
        cin >> balance;

    } while (balance < 50000);

    customerNationalNumber = nationalNum;

    status = true;

    writeReport("Account \"" + getAccountNumber() + "\" for customer with national number \"" + customerNationalNumber + "\" created.");
    cout << "\nAccount \"" + getAccountNumber() + "\" for customer with national number \"" + customerNationalNumber + "\" created.\n";
    pressKey();
}
void Account::changeStatus() {
    char opt;
    cout << "Are you sure you want to " << (status? "deactivate": "activate") << " the account? (Y/N) ";
    cin >> opt;
    if (opt == 'Y' || opt == 'y') {
        status = !status;
        writeReport("Account \"" + getAccountNumber() + "\" " + (status? "activated.": "deactivated.\n"));
        cout << "\nAccount \"" + getAccountNumber() + "\" " + (status? "activated.": "deactivated.\n");
        pressKey();
    }

}
void Account::increaseBalance() {
    if (status) {
        long long adding = 0;
        while (adding <= 0) {
            cout << "Enter the amount of money: ";
            cin >> adding;
            if (adding > 0) {
                balance += adding;
                writeReport("Account \"" + getAccountNumber() + "\" balance increased with amount " + to_string(adding));
                cout << "\nAccount \"" + getAccountNumber() + "\" balance increased with amount " + to_string(adding) + '\n';
            }
        }
    }
    else {
        cout << "\nThe account is not active." << endl;
    }
}
void Account::receiveBalance() {
    if (status) {
        long long receiving;
        cout << "\nThe account balance is " << balance;
        cout << "\n\nEnter the amount of money you want to receive: ";
        cin >> receiving;
        if (receiving >= 0 && balance - receiving >= 0) {
            balance -= receiving;
            writeReport("Account " + getAccountNumber() + " balance decreased with amount " + to_string(receiving));
            cout << "\nAccount " + getAccountNumber() + " balance decreased with amount " + to_string(receiving) + '\n';
        }
        else {
            cout << "\nYour account balance is not enough.\n";
        }
    }
    else {
        cout << "\nyour account is Inactive.\n";
    }

}
void Account::showAccount() {
    cout << "\n\tAccount Number: " << accountNumber
         << "\n\tOpening Date:   " << openingYear << "/" << openingMonth << "/" << openingDay
         << "\n\tBalance:        " << balance
         << "\n\tAccount Status: " << (status ? "Active" : "Inactive") << '\n';
}


void Person::setPersonDetails() {
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;

    while (true) {
        cout << "Enter date of birth (Day Month Year): ";
        cin >> day >> month >> year;
        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1300 && year <= 1401) {
            break;
        }
    }


    cout << "Enter username: ";
    cin >> username;
 

    cout << "Enter password: ";
    cin >> password;
}
void Person::showPersonDetails() {
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Data: " << day << "/" << month << "/" << year << endl;
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
}


void Employee::setEmployeeDetails(string personnelNum) {
    setPersonDetails();
    if (personnelNum == "") {
        while (true) {
            cout << "Enter the personnel number (Must be 3 digits): ";
            bool cntnue = false;
            cin >> personnelNum;

            if (personnelNum.size() != 3) {
                continue;
            }

            for (char c: personnelNum) {
                if (c < '0' || c > '9') {
                    cntnue = true;
                    break;
                }
            }
            if (cntnue) {
                continue;
            }
            break;
        }
    }
    personnelNumber = personnelNum;

    cout << "Enter salary: ";
    cin >> salary;
    writeReport("Employee \"" + getFirstName() + ' ' + getLastName() + "\" with username \"" + getUsername() + "\" added.");
    cout << "\nEmployee \"" + getFirstName() + ' ' + getLastName() + "\" with username \"" + getUsername() + "\" added.\n\n";
    cout << "Press any key to continue.";
    getch();
}
void Employee::addTimeOff() {
    int TO = 0;
    while (TO <= 0) {
        system("cls");
        cout << "Taking Time Off\n"
                "\nEnter the hours off you want: ";
        cin >> TO;
    }

    int temp = timeOff;
    // timeOff += TO;

    if ((timeOff + TO) > 15) {
        string tempText = (timeOff > 15)? "is": "will be";
        cout << "Your time off " + tempText + " more than 15 hours;\n"
                "Therefore 100 thousand Tomans will be deducted from your salary for every hour of leave.\n"
                "Are you sure you want to take the time off? (Y/N) ";
        char opt;
        cin >> opt;
        if (opt == 'Y' || opt == 'y') {
            timeOff += TO;
            salary -= min(timeOff - 15, timeOff - temp) * 100000;
            cout << "\nYour new salary = " << getSalary() << endl;
            writeReport("Employee \"" + getFirstName() + ' ' + getLastName() + "\" with username " + getUsername() + " added " + to_string(TO) + " hours off.");
        }
    }
    else {
        timeOff += TO;
        cout << "You can have " << 15 - timeOff << " more hours off now." << endl;
        writeReport("Employee \"" + getFirstName() + ' ' + getLastName() + "\" with username " + getUsername() + " added " + to_string(TO) + " hours off.");
    }
    pressKey();
}
void Employee::addOvertime() {
    if (overtime < 12) {
        int h = 0;
        while (h <= 0 || h > 12 || h + overtime > 12) {
            cout << "Enter overtime hours (You can't take more than 12 hours off in total): ";
            cin >> h;
        }

        overtime += h;

        setSalary(getSalary() + (h * 120000));
        writeReport("Employee \"" + getFirstName() + ' ' + getLastName() + "\" with username " + getUsername() + " took " + to_string(h) + " hours overtime.");
        cout << "You took " + to_string(h) + " hours overtime.\n";
        cout << "Your new salary: " << getSalary() << '\n';
        pressKey();
    }
    else {
        cout << "You can't have more overtime hours.";
    }
}
void Employee::showEmployeeDetails() {
    showPersonDetails();
    cout << "Personnel Number: " << personnelNumber
         << "\nSalary: " << salary
         << "\nhours Off: " << timeOff
         << "\nOvertime Hours: " << overtime << '\n';
    pressKey();
}


void Customer::setCustomerInfo(string nationalNum) {
    setPersonDetails();

    if (nationalNum == "") {
        while (true) {
            cout << "Enter national Number (Must be 10 digits): ";
            bool cntnue = false;
            cin >> nationalNum;

            if (nationalNum.size() != 10) {
                continue;
            }

            for (char c: nationalNum) {
                if (c < '0' || c > '9') {
                    cntnue = true;
                    break;
                }
            }

            for (Customer c: globalCustomers) {
                if (c.getNationalNumber() == nationalNum) {
                    cout << "This national number is duplicate.\n";
                    cntnue = true;
                    break;
                }
            }
            if (cntnue) {
                continue;
            }
            break;
        }
    }
    nationalNumber = nationalNum;
    Account a(nationalNumber);
    accounts.push_back(a);
}
void Customer::showCustomer() {
    showPersonDetails();
    string temp = getAccounts().size() == 1? ":": "s:";
    cout << "National Number: " << getNationalNumber()
         << "\n\nAccount" + temp;
    for (Account a: accounts) {
        a.showAccount();
    }
    cout << '\n';
}
void Customer::addAccount() {
    Account a(nationalNumber);
    accounts.push_back(a);
}
int Customer::findAccount(string accountNum) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts.at(i).getAccountNumber() == accountNum) {
            return i;
        }
    }
    return -1;
}
void Customer::deleteAccount(int accountIndex) {
    writeReport("Account \"" + accounts.at(accountIndex).getAccountNumber() + "\" for customer with national number \"" + nationalNumber + "\" deleted.");
    cout << "\nAccount \"" + accounts.at(accountIndex).getAccountNumber() + "\" for customer with national number \"" + nationalNumber + "\" deleted.";
    accounts.erase(accounts.begin() + accountIndex);
}
void Customer::increaseAnAccountBalance() {
    bool notFound = true;
    string accNum;
    system("cls");
    cout << "Increasing Balance\n"
            "\nEnter account number: ";
    cin >> accNum;
    for (unsigned int i = 0; i < accounts.size(); i++) {
        if (accounts.at(i).getAccountNumber() == accNum) {
            accounts.at(i).increaseBalance();
            notFound = false;
        }
    }
    if (notFound) {
        cout << "\nYou don't have such account.\n";
    }
    pressKey();
}
void Customer::receiveBalanceFromAnAccount() {
    bool notFound = true;
    string accNum;
    system("cls");
    cout << "Receving Cash"
            "\n\nEnter account number: ";
    cin >> accNum;
    for (unsigned int i = 0; i < accounts.size(); i++) {
        if (accounts.at(i).getAccountNumber() == accNum) {
            accounts.at(i).receiveBalance();
            pressKey();
            notFound = false;
        }
    }

    if (notFound) {
        cout << "\nYou don't have such account.\n";
        pressKey();
    }
}


void Bank::firstTimeManager() {
    system("cls");
    cout << "You must enter the information of the bank manager.\n\n";
    manager.setEmployeeDetails();
    globalEmployees.push_back(manager);
}
void Bank::addEmployee() {
    Employee a;
    a.setEmployeeDetails();
    employees.push_back(a);
    globalEmployees.push_back(a);
}
void Bank::deleteAccount() {
    string accountNum;

    while (true) {
        system("cls");
        cout << "Deleting Account\n"
                "\nEnter the account number (Must be 16 digits): ";
        bool cntnue = false;
        cin >> accountNum;

        if (accountNum.size() != 16) {
            continue;
        }

        for (char c: accountNum) {
            if (c < '0' || c > '9') {
                cntnue = true;
                break;
            }
        }
        if (cntnue) {
            continue;
        }
        break;
    }
    for (int i = 0; i < customers.size(); i++) {
        for (int j = 0; j < customers.at(i).getAccounts().size(); j++) {
            if (customers.at(i).getAccounts().at(j).getAccountNumber() == accountNum) {
                customers.at(i).deleteAccount(j);
                if (customers.at(i).getAccounts().size() == 0) {
                    customers.erase(customers.begin() + i);
                    cout << "\n\nThe customer was deleted because he/she no longer had an account.";
                }
                cout << "\n\nPress any key to continue.";
                getch();
                return;
            }
        }
    }
    cout << "\nSuch account does not exist.\n";
    pressKey();
}
bool Bank::PersonnelNumberIsDuplicate(string pn) {
    for (Employee e: employees) {
        if (e.getPersonnelNumber() == pn ) {
            return true;
        }
    }
    if (manager.getPersonnelNumber() == pn) {
        return true;
    }
    return false;
}
int Bank::findEmployee(string personnelNum) {
    for (int i = 0; i < employees.size(); i++) {
        if (employees.at(i).getPersonnelNumber() == personnelNum) {
            return i;
        }
    }
    return -1;
}
long long Bank::findCustomer() {
    string nationalNum;
    cout << '\n';
    while (true) {
        cout << "Enter the customer national Number (Must be 10 digits): ";
        bool cntnue = false;
        cin >> nationalNum;

        if (nationalNum.size() != 10) {
            continue;
        }

        for (char c: nationalNum) {
            if (c < '0' || c > '9') {
                cntnue = true;
                break;
            }
        }
        if (cntnue) {
            continue;
        }
        break;
    }
    for (int i = 0; i < customers.size(); i++) {
        if (customers.at(i).getNationalNumber() == nationalNum) {
            return i;
        }
    }
    return -stoll(nationalNum);
}
void Bank::deleteEmployee() {
    string PN;
    cout << "Enter personnel number: ";
    cin >> PN;

    bool notFound = true;
    for (unsigned int i = 0; i < employees.size(); i++) {
        if (employees.at(i).getPersonnelNumber() == PN) {
            writeReport("Employee \"" + employees.at(i).getFirstName() + ' ' + employees.at(i).getLastName() + "\" with username \"" + employees.at(i).getUsername() + "\" deleted.");
            employees.erase(employees.begin() + i);
            notFound = false;
        }
    }
    if (notFound) {
        cout << "There is no employee with such personnel number.\n" << endl;
    }

    for (unsigned int i = 0; i < globalEmployees.size(); i++) {
        if (globalEmployees.at(i).getPersonnelNumber() == PN) {
            globalEmployees.erase(globalEmployees.begin() + i);
            break;
        }
    }
}
void Bank::employeeMenu() {
    string userN, pass;
    system("cls");
    cout << "Employee Login\n"
            "\nEnter your username: ";
    cin >> userN;
    cout << "Enter your password: ";
    cin >> pass;

    int EmployeeNumber;
    bool foundEmployee = false;
    for (unsigned int i = 0; i < employees.size(); i++) {
        if (employees.at(i).getUsername() == userN && employees.at(i).getPassword() == pass) {
            EmployeeNumber = i;
            foundEmployee = true;
        }
    }

    bool FoundManager = false;
    if (manager.getUsername() == userN && manager.getPassword() == pass) {
        FoundManager = true;
    }

    if (foundEmployee) {
        writeReport("Employee \"" + employees.at(EmployeeNumber).getLastName() + "\" with username \"" + employees.at(EmployeeNumber).getUsername() + "\" logged in.");
        int choice = -1;
        while (choice != 0) {
            system("cls");
            cout << "Employee Menu\n"
                 << "\n1: take time off"
                 << "\n2: get Overtime"
                 << "\n3: Show personal information"
                 << "\n4: Show customer information with national number"
                 << "\n5: Add new customer"
                 << "\n6: Delete customer account"
                 << "\n7: Set customer account status"
                 << "\n0: back\n" 
                 << "\nSelect an option: ";


            cin >> choice;
            if (choice == 1) {
                employees.at(EmployeeNumber).addTimeOff();
            }
            else if (choice == 2) {
                employees.at(EmployeeNumber).addOvertime();
            }
            else if (choice == 3) {
                system("cls");
                employees.at(EmployeeNumber).showEmployeeDetails();
            }
            else if (choice == 4) {
                int customerIndex = findCustomer();
                if (customerIndex != -1) {
                    system("cls");
                    customers.at(customerIndex).showCustomer();
                    pressKey();
                }
                else {
                    cout << "\nThere is no customer with such national number.\n";
                    pressKey();
                }
            }
            else if (choice == 5) {
                system("cls");
                cout << "Adding Account\n";
                long long customerIndex = findCustomer();
                if (customerIndex >= 0) {
                    customers.at(customerIndex).addAccount();
                }
                else {
                    Customer c;
                    c.setCustomerInfo(to_string(-customerIndex));
                    customers.push_back(c);
                }
            }
            else if (choice == 6) {
                deleteAccount();
            }
            else if (choice == 7) {
                string accountNum;
                while (true) {
                    system("cls");
                    cout << "Changing account status\n"
                            "\nEnter the account number (Must be 16 digits): ";
                    bool cntnue = false;
                    cin >> accountNum;

                    if (accountNum.size() != 16) {
                        continue;
                    }

                    for (char c: accountNum) {
                        if (c < '0' || c > '9') {
                            cntnue = true;
                            break;
                        }
                    }
                    if (cntnue) {
                        continue;
                    }
                    break;
                }
                bool notFound = true;
                for (int i = 0; i < customers.size(); i++) {
                    int index = customers.at(i).findAccount(accountNum);
                    if (index != -1) {
                        customers.at(i).changeAccountStatus(index);
                        notFound = false;
                        break;
                    }
                }
                if (notFound) {
                    cout << "\nSuch account does not exist.\n";
                    pressKey();
                }
            }
        }
        writeReport("Employee \"" + employees.at(EmployeeNumber).getLastName() + "\" with username \"" + employees.at(EmployeeNumber).getUsername() + "\" logged out.");
    }
    else if (FoundManager) {
        writeReport("Manager \"" + manager.getFirstName() + ' ' + manager.getLastName() + "\" with username \"" + manager.getUsername() + "\" logged in.");
        int choice = -1;
        while (choice != 0) {
            system("cls");
            cout << "Manager Menu\n"
                 << "\n1: Request time off"
                 << "\n2: Request Overtime"
                 << "\n3: Show personal information"
                 << "\n4: Show customer information with national number"
                 << "\n5: Add customer account"
                 << "\n6: Delete customer account"
                 << "\n7: Set customer account status"
                 << "\n8: Show Employee information"
                 << "\n9: Add employee"
                 << "\n10: dismiss Employee"
                 << "\n0: back\n"
                 << "\nSelect an option: ";
            cin >> choice;
            if (choice == 1) {
                manager.addTimeOff();
            }
            else if (choice == 2) {
                manager.addOvertime();
            }
            else if (choice == 3) {
                system("cls");
                manager.showEmployeeDetails();
            }
            else if (choice == 4) {
                long long customerIndex = findCustomer();
                if (customerIndex >= 0) {
                    system("cls");
                    customers.at(customerIndex).showCustomer();
                    pressKey();

                }
                else {
                    cout << "\nThere is no customer with such national number.\n";
                    pressKey();
                }
            }
            else if (choice == 5) {
                system("cls");
                cout << "Adding Account\n";
                long long customerIndex = findCustomer();
                if (customerIndex >= 0) {
                    customers.at(customerIndex).addAccount();
                }
                else {
                    Customer c;
                    c.setCustomerInfo(to_string(-customerIndex));
                    customers.push_back(c);
                }
            }
            else if (choice == 6) {
                deleteAccount();
            }
            else if (choice == 7) {
                string accountNum;
                while (true) {
                    system("cls");
                    cout << "Changing account status\n"
                            "\nEnter the account number (Must be 16 digits): ";
                    bool cntnue = false;
                    cin >> accountNum;

                    if (accountNum.size() != 16) {
                        continue;
                    }

                    for (char c: accountNum) {
                        if (c < '0' || c > '9') {
                            cntnue = true;
                            break;
                        }
                    }
                    if (cntnue) {
                        continue;
                    }
                    break;
                }
                bool notFound = true;
                for (int i = 0; i < customers.size(); i++) {
                    int index = customers.at(i).findAccount(accountNum);
                    if (index != -1) {
                        customers.at(i).changeAccountStatus(index);
                        notFound = false;
                        break;
                    }
                }
                if (notFound) {
                    cout << "\nSuch account does not exist.\n";
                    pressKey();
                }
            }
            else if (choice == 8) {
                string personnelNum;
                cout << '\n';
                while (true) {
                    cout << "Finding Employee\n"
                            "\nEnter the employee personnel number (Must be 3 digits): ";
                    bool cntnue = false;
                    cin >> personnelNum;

                    if (personnelNum.size() != 3) {
                        continue;
                    }

                    for (char c: personnelNum) {
                        if (c < '0' || c > '9') {
                            cntnue = true;
                            break;
                        }
                    }
                    if (cntnue) {
                        continue;
                    }
                    break;
                }
                int index = findEmployee(personnelNum);
                if (index == -1) {
                    cout << "\nsuch employee does not exist.\n";
                    getch();
                }
                else {
                    employees.at(index).showEmployeeDetails();
                }
            }
            else if (choice == 9) {
                string personnelNum;
                system("cls");
                cout << "Adding Employee\n";
                while (true) {
                    cout << "\nEnter the employee personnel number (Must be 3 digits): ";
                    bool cntnue = false;
                    cin >> personnelNum;

                    if (personnelNum.size() != 3) {
                        continue;
                    }

                    for (char c: personnelNum) {
                        if (c < '0' || c > '9') {
                            cntnue = true;
                            break;
                        }
                    }
                    if (cntnue) {
                        continue;
                    }
                    if (PersonnelNumberIsDuplicate(personnelNum)) {
                        cout << "\nThe personnel number is duplicate.\n";
                        continue;
                    }
                    break;
                }
                Employee e;
                e.setEmployeeDetails(personnelNum);
                employees.push_back(e);
                
            }
            else if (choice == 10) {
                string personnelNum;
                cout << '\n';
                while (true) {
                    system("cls");
                    cout << "Dismissing Employee\n"
                            "\nEnter the employee personnel number (Must be 3 digits): ";
                    bool cntnue = false;
                    cin >> personnelNum;

                    if (personnelNum.size() != 3) {
                        continue;
                    }

                    for (char c: personnelNum) {
                        if (c < '0' || c > '9') {
                            cntnue = true;
                            break;
                        }
                    }
                    if (cntnue) {
                        continue;
                    }
                    break;
                }
                int index = findEmployee(personnelNum);
                if (index == -1) {
                    cout << "\nsuch employee does not exist.\n";
                    pressKey();
                }
                else {
                    cout << "\nAre you sure you want dismiss \"" + employees.at(index).getFirstName() + ' ' + employees.at(index).getLastName() + "\"? (Y/N) ";
                    char dismiss;
                    cin >> dismiss;
                    if (dismiss == 'Y' || dismiss == 'y') {
                        employees.erase(employees.begin() + index);
                        cout << "\nThe employee was deleted.\n";
                    }
                    pressKey();
                }
            }
        }
        writeReport("Manager \"" + manager.getFirstName() + ' ' + manager.getLastName() + "\" with username \"" + manager.getUsername() + "\" logged out.");
    }
    else {
        cout << "\nThere is no such employee.\n";
        pressKey();
    }
}
void Bank::customerMenu() {
	string UN, Pass;

    system("cls");
	cout << "Customer Log In\n"
            "\nEnter your username: ";
	cin >> UN;
	cout << "Enter your password: ";
	cin >> Pass;
	int index = -1;
	for (unsigned int i = 0; i < customers.size(); i++) {
		if (customers.at(i).getUsername() == UN && customers.at(i).getPassword() == Pass) {
			index = i;
		}
	}
	if (index == -1) {
        cout << "\nSuch customer does not exist.\n";
        pressKey();
	}
	else {
		writeReport("Customer with username \"" + customers.at(index).getUsername() + "\" logged in.");
        int choice = -1;
		while (choice != 0) {
            system("cls");
			cout << "Customer Menu\n"
			     << "\n1: Increase an account balance"
			     << "\n2: Receive cash"
			     << "\n3: Show information"
			     << "\n0: Back"
                 << "\n\nSelect an option: ";
			cin >> choice;
            
            if (choice == 1) {
                customers.at(index).increaseAnAccountBalance();
            }
            else if (choice == 2) {
                customers.at(index).receiveBalanceFromAnAccount();
            }
            else if (choice == 3) {
                system("cls");
                customers.at(index).showCustomer();
                pressKey();
            }
		}
        writeReport("Customer with username \"" + customers.at(index).getUsername() + "\" logged out.");
	}
}

void writeReport(string text) {
    time_t now = time(0);
    tm* Time = localtime(&now);
    ofstream fout("Report.txt", ios::app);
    if (fout) {
        fout << text << " - " << 1900 + Time->tm_year << "/" << 1 + Time->tm_mon << "/" << Time->tm_mday << " - " << Time->tm_hour << ":" << Time->tm_min << ":" << Time->tm_sec << "\n";
        fout.close();
    }
    else {
        cerr << "Error in file" << endl;
    }
}

void pressKey() {
    cout << "\nPress any key to back.";
    getch();
}

int readfile(Bank& bank) {
    ifstream file ("File.txt");
    if (file.is_open()) {
        string line;
        getline(file, line);
        file.close();

        vector<string> vect = splitString(line);

        bank.setManager(vect[0], vect[1], vect[2], vect[3], stoi(vect[4]), stoi(vect[5]), stoi(vect[6]), vect[7], stoi(vect[8]), stoi(vect[9]), stoll(vect[10]));
        int i = 11;
        int loopMax = stoi(vect[i]);
        for (int j = 0; j < loopMax; j++) {
            bank.newEmployee(vect[i+1], vect[i+2], vect[i+3], vect[i+4], stoi(vect[i+5]), stoi(vect[i+6]), stoi(vect[i+7]), vect[i+8], stoi(vect[i+9]), stoi(vect[i+10]), stoll(vect[i+11]));
            i += 11;
        }
        loopMax = stoi(vect[++i]);
        for (int j = 0; j < loopMax; j++) {
            Customer c;

            c.setFirstName(vect[++i]);
            c.setLastName(vect[++i]);
            c.setusername(vect[++i]);
            c.setPassword(vect[++i]);
            c.setYear(stoi(vect[++i]));
            c.setMonth(stoi(vect[++i]));
            c.setDay(stoi(vect[++i]));
            c.setNationalNumber(vect[++i]);

            int loopMax2 = stoi(vect[++i]);
            for (int k = 0; k < loopMax2; k++) {
                Account a(vect[i+1], c.getNationalNumber(), stoll(vect[i+2]), stoi(vect[i+3]), stoi(vect[i+4]), stoi(vect[i+5]), (vect[i+6] == "1"? true: false));
                i += 6;
                c.newAcc(a);
            }
            bank.newCustomer(c);
        }
        return 1;
    }
    else {
        return 0;
    }
}

void writeFile(Bank& bank) {
    ofstream fout("File.txt");
    
    fout << bank.getManager().getFirstName() << ','
        << bank.getManager().getLastName() << ','
        << bank.getManager().getUsername() << ','
        << bank.getManager().getPassword() << ','
        << bank.getManager().getYear() << ','
        << bank.getManager().getMonth() << ','
        << bank.getManager().getDay() << ','
        << bank.getManager().getPersonnelNumber() << ','
        << bank.getManager().getTimeOff() << ','
        << bank.getManager().getOvertime() << ','
        << bank.getManager().getSalary() << ',';
    
    fout << bank.getEmployees().size() << ',';
    for (Employee e: bank.getEmployees()) {
        fout << e.getFirstName() << ','
            << e.getLastName() << ','
            << e.getUsername() << ','
            << e.getPassword() << ','
            << e.getYear() << ','
            << e.getMonth() << ','
            << e.getDay() << ','
            << e.getPersonnelNumber() << ','
            << e.getTimeOff() << ','
            << e.getOvertime() << ','
            << e.getSalary() << ',';
    }
    
    fout << bank.getCustomers().size() << ',';
    for (Customer c: bank.getCustomers()) {
        fout << c.getFirstName() << ','
            << c.getLastName() << ','
            << c.getUsername() << ','
            << c.getPassword() << ','
            << c.getYear() << ','
            << c.getMonth() << ','
            << c.getDay() << ','
            << c.getNationalNumber() << ',';
        
        fout << c.getAccounts().size() << ',';
        for (Account a: c.getAccounts()) {
            fout << a.getAccountNumber() << ','
                << a.getBalance() << ','
                << a.getOpeningYear() << ','
                << a.getOpeningMonth() << ','
                << a.getOpeningDay() << ','
                << (a.getStatus()? '1': '0') << ',';
        }
    }
    
   fout.close();
}

vector<string> splitString(string line) {
    vector<string> vect;
    vect.push_back("");
    for (char i: line) {
        if (i == ',') {
            vect.push_back("");
        }
        else {
            vect[vect.size() - 1] += i;
        }
    }
    vect.pop_back();
    return vect;
}

int main() {
    Bank bank;
    int fileExistence = readfile(bank);
    if (fileExistence == 0) {
        bank.firstTimeManager();
    }

    int option = -1;

    while (option != 0) {
        system("cls");
        cout << "Bank Main Menu\n\n"
                "1: Employee\n"
                "2: Customer\n"
                "0: Exit\n"
                "\nSelect an option: ";
        cin >> option;

        if (option == 1) {
            bank.employeeMenu();
        }
        else if (option == 2) {
            bank.customerMenu();
        }
        writeFile(bank);
    }


    cout << "\nGoodbye!\n";
    getch();

    return 0;
}