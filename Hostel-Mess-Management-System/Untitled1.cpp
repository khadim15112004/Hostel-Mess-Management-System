#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_DAYS = 31;

// Simple struct (data only, no OOP)
struct Student {
    int id;
    string name;
    bool foodOn[MAX_DAYS]; // true = ON, false = OFF
    int totalActiveDays;
    float bill;
};

// Global data (for simplicity)
Student students[MAX_STUDENTS];
int studentCount = 0;
float perDayCharge = 0.0;
int daysInMonth = 30; // default

// Function declarations
void addStudent();
int findStudentById(int id);
void markFoodOnOff();
void setPerDayCharge();
void setDaysInMonth();
void calculateMonthlyBills();
void showStudentReport();
void showAllStudents();

int main() {
    int choice;

    // Initialize all foodOn to false
    for (int i = 0; i < MAX_STUDENTS; i++) {
        students[i].id = -1;
        students[i].totalActiveDays = 0;
        students[i].bill = 0.0;
        for (int d = 0; d < MAX_DAYS; d++) {
            students[i].foodOn[d] = false;
        }
    }

    do {
        cout << "\n===== Hostel Mess Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Mark Food ON/OFF for a Day\n";
        cout << "3. Set Per Day Food Charge\n";
        cout << "4. Set Days in Month\n";
        cout << "5. Calculate Monthly Bills\n";
        cout << "6. Show Single Student Report\n";
        cout << "7. Show All Students Summary\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                markFoodOnOff();
                break;
            case 3:
                setPerDayCharge();
                break;
            case 4:
                setDaysInMonth();
                break;
            case 5:
                calculateMonthlyBills();
                break;
            case 6:
                showStudentReport();
                break;
            case 7:
                showAllStudents();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Cannot add more students. Limit reached.\n";
        return;
    }

    int id;
    string name;
    cout << "\n--- Add Student ---\n";
    cout << "Enter student ID: ";
    cin >> id;

    // Check duplicate ID
    if (findStudentById(id) != -1) {
        cout << "Student with this ID already exists.\n";
        return;
    }

    cout << "Enter student name: ";
    cin.ignore(); // clear buffer
    getline(cin, name);

    students[studentCount].id = id;
    students[studentCount].name = name;
    students[studentCount].totalActiveDays = 0;
    students[studentCount].bill = 0.0;
    for (int d = 0; d < MAX_DAYS; d++) {
        students[studentCount].foodOn[d] = false;
    }

    studentCount++;
    cout << "Student added successfully.\n";
}

int findStudentById(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

void markFoodOnOff() {
    if (studentCount == 0) {
        cout << "No students available. Add students first.\n";
        return;
    }

    int id, day, choice;
    cout << "\n--- Mark Food ON/OFF ---\n";
    cout << "Enter student ID: ";
    cin >> id;

    int index = findStudentById(id);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter day of month (1-" << daysInMonth << "): ";
    cin >> day;

    if (day < 1 || day > daysInMonth || day > MAX_DAYS) {
        cout << "Invalid day.\n";
        return;
    }

    cout << "1. Food ON\n";
    cout << "2. Food OFF\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        students[index].foodOn[day - 1] = true;
        cout << "Food marked ON for day " << day << ".\n";
    } else if (choice == 2) {
        students[index].foodOn[day - 1] = false;
        cout << "Food marked OFF for day " << day << ".\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void setPerDayCharge() {
    cout << "\n--- Set Per Day Food Charge ---\n";
    cout << "Enter per day charge (Rs): ";
    cin >> perDayCharge;

    if (perDayCharge < 0) {
        perDayCharge = 0;
    }

    cout << "Per day charge set to Rs " << perDayCharge << endl;
}

void setDaysInMonth() {
    cout << "\n--- Set Days in Month ---\n";
    cout << "Enter number of days in month (1-31): ";
    cin >> daysInMonth;

    if (daysInMonth < 1 || daysInMonth > 31) {
        cout << "Invalid value. Keeping previous value: " << daysInMonth << endl;
    } else {
        cout << "Days in month set to: " << daysInMonth << endl;
    }
}

void calculateMonthlyBills() {
    if (perDayCharge <= 0) {
        cout << "Set per day charge first.\n";
        return;
    }

    cout << "\n--- Calculating Monthly Bills ---\n";
    for (int i = 0; i < studentCount; i++) {
        int activeDays = 0;
        for (int d = 0; d < daysInMonth && d < MAX_DAYS; d++) {
            if (students[i].foodOn[d]) {
                activeDays++;
            }
        }
        students[i].totalActiveDays = activeDays;
        students[i].bill = activeDays * perDayCharge;
    }

    cout << "Monthly bills calculated for all students.\n";
}

void showStudentReport() {
    if (studentCount == 0) {
        cout << "No students available.\n";
        return;
    }

    int id;
    cout << "\n--- Student Report ---\n";
    cout << "Enter student ID: ";
    cin >> id;

    int index = findStudentById(id);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    Student &s = students[index];
    cout << "\nStudent ID: " << s.id << endl;
    cout << "Name      : " << s.name << endl;
    cout << "Days in Month: " << daysInMonth << endl;
    cout << "Per Day Charge: Rs " << perDayCharge << endl;

    cout << "Food Status (Day: ON/OFF):\n";
    for (int d = 0; d < daysInMonth; d++) {
        cout << "Day " << (d + 1) << ": ";
        if (s.foodOn[d])
            cout << "ON\n";
        else
            cout << "OFF\n";
    }

    cout << "Total Active Days: " << s.totalActiveDays << endl;
    cout << "Total Bill       : Rs " << s.bill << endl;
}

void showAllStudents() {
    if (studentCount == 0) {
        cout << "No students available.\n";
        return;
    }

    cout << "\n--- All Students Summary ---\n";
    cout << "ID\tName\t\tActiveDays\tBill\n";
    cout << "---------------------------------------------\n";
    for (int i = 0; i < studentCount; i++) {
        cout << students[i].id << "\t"
             << students[i].name << "\t\t"
             << students[i].totalActiveDays << "\t\t"
             << "Rs " << students[i].bill << endl;
    }
}

