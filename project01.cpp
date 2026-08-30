#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_NAME_LENGTH = 50;
const int MAX_COURSE_LENGTH = 50;
const int MAX_DEPT_LENGTH = 40;

struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char course[MAX_COURSE_LENGTH];
    char department[MAX_DEPT_LENGTH];
    float cgpa;
};

Student students[MAX_STUDENTS];
int studentCount = 0;

// Display a heading in a simple centered format
void showHeading(const string &text) {
    cout << "\n============================================================\n";
    cout << "                    " << text << "\n";
    cout << "============================================================\n";
}

// Check whether a student ID is already used
bool isUniqueID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id)
            return false;
    }
    return true;
}

// Read and validate CGPA
float readCGPA() {
    float cgpa;

    while (true) {
        cin >> cgpa;

        if (!cin.fail() && cgpa >= 0.0 && cgpa <= 10.0)
            return cgpa;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid CGPA. Enter a value between 0 and 10: ";
    }
}

// Add a new student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "\nStudent database is full.\n";
        return;
    }

    showHeading("ADD STUDENT");

    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    while (!isUniqueID(id)) {
        cout << "ID already exists. Enter another ID: ";
        cin >> id;
    }

    students[studentCount].id = id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Student Name: ";
    cin.getline(students[studentCount].name, MAX_NAME_LENGTH);

    cout << "Enter Age: ";
    cin >> students[studentCount].age;

    while (cin.fail() || students[studentCount].age < 15 ||
           students[studentCount].age > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age. Enter age between 15 and 100: ";
        cin >> students[studentCount].age;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Course: ";
    cin.getline(students[studentCount].course, MAX_COURSE_LENGTH);

    cout << "Enter Department: ";
    cin.getline(students[studentCount].department, MAX_DEPT_LENGTH);

    cout << "Enter CGPA (0-10): ";
    students[studentCount].cgpa = readCGPA();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    studentCount++;
    cout << "\nStudent added successfully!\n";
}

// Display all students in a table
void displayStudents() {
    if (studentCount == 0) {
        cout << "\nNo student records available.\n";
        return;
    }

    showHeading("STUDENT RECORDS");

    cout << left
         << setw(8)  << "ID"
         << setw(22) << "Name"
         << setw(8)  << "Age"
         << setw(20) << "Course"
         << setw(18) << "Department"
         << setw(8)  << "CGPA" << endl;

    cout << string(84, '-') << endl;

    for (int i = 0; i < studentCount; i++) {
        cout << left
             << setw(8)  << students[i].id
             << setw(22) << students[i].name
             << setw(8)  << students[i].age
             << setw(20) << students[i].course
             << setw(18) << students[i].department
             << fixed << setprecision(2)
             << setw(8) << students[i].cgpa << endl;
    }
}

// Search student using ID
void searchByID() {
    int id;
    cout << "\nEnter Student ID: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "\nStudent Found\n";
            cout << "ID         : " << students[i].id << endl;
            cout << "Name       : " << students[i].name << endl;
            cout << "Age        : " << students[i].age << endl;
            cout << "Course     : " << students[i].course << endl;
            cout << "Department : " << students[i].department << endl;
            cout << "CGPA       : " << fixed << setprecision(2)
                 << students[i].cgpa << endl;
            return;
        }
    }

    cout << "\nStudent record not found.\n";
}

// Search student using name
void searchByName() {
    char name[MAX_NAME_LENGTH];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter Student Name: ";
    cin.getline(name, MAX_NAME_LENGTH);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            cout << "\nStudent Found\n";
            cout << "ID         : " << students[i].id << endl;
            cout << "Name       : " << students[i].name << endl;
            cout << "Course     : " << students[i].course << endl;
            cout << "Department : " << students[i].department << endl;
            cout << "CGPA       : " << fixed << setprecision(2)
                 << students[i].cgpa << endl;
            return;
        }
    }

    cout << "\nStudent record not found.\n";
}

// Update student details
void updateStudent() {
    int id;
    cout << "\nEnter Student ID to update: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new Name: ";
            cin.getline(students[i].name, MAX_NAME_LENGTH);

            cout << "Enter new Age: ";
            cin >> students[i].age;

            while (cin.fail() || students[i].age < 15 ||
                   students[i].age > 100) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age. Enter age between 15 and 100: ";
                cin >> students[i].age;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new Course: ";
            cin.getline(students[i].course, MAX_COURSE_LENGTH);

            cout << "Enter new Department: ";
            cin.getline(students[i].department, MAX_DEPT_LENGTH);

            cout << "Enter new CGPA (0-10): ";
            students[i].cgpa = readCGPA();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nStudent details updated successfully!\n";
            return;
        }
    }

    cout << "\nStudent record not found.\n";
}

// Delete a student by ID
void deleteStudent() {
    int id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            char confirm;
            cout << "Delete " << students[i].name << "'s record? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < studentCount - 1; j++)
                    students[j] = students[j + 1];

                studentCount--;
                cout << "\nRecord deleted successfully.\n";
            } else {
                cout << "\nDeletion cancelled.\n";
            }
            return;
        }
    }

    cout << "\nStudent record not found.\n";
}

// Sort students according to CGPA
void sortByCGPA() {
    if (studentCount < 2) {
        cout << "\nNot enough records to sort.\n";
        return;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].cgpa < students[j + 1].cgpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "\nStudents sorted by CGPA (highest to lowest).\n";
}

// Display database statistics
void displayStatistics() {
    if (studentCount == 0) {
        cout << "\nNo records available for statistics.\n";
        return;
    }

    float totalCGPA = 0;
    int totalAge = 0;
    int highestIndex = 0;

    for (int i = 0; i < studentCount; i++) {
        totalCGPA += students[i].cgpa;
        totalAge += students[i].age;

        if (students[i].cgpa > students[highestIndex].cgpa)
            highestIndex = i;
    }

    cout << "\n---------------- STATISTICS ----------------\n";
    cout << "Total Students : " << studentCount << endl;
    cout << "Average Age    : " << fixed << setprecision(2)
         << (float)totalAge / studentCount << endl;
    cout << "Average CGPA   : " << fixed << setprecision(2)
         << totalCGPA / studentCount << endl;
    cout << "Top Student    : " << students[highestIndex].name
         << " (" << students[highestIndex].cgpa << ")" << endl;
}

// Main menu
int main() {
    int choice;

    do {
        showHeading("COLLEGE STUDENT RECORD MANAGER");

        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search by ID\n";
        cout << "4. Search by Name\n";
        cout << "5. Update Student\n";
        cout << "6. Delete Student\n";
        cout << "7. Sort by CGPA\n";
        cout << "8. Display Statistics\n";
        cout << "9. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchByID(); break;
            case 4: searchByName(); break;
            case 5: updateStudent(); break;
            case 6: deleteStudent(); break;
            case 7: sortByCGPA(); break;
            case 8: displayStatistics(); break;
            case 9: cout << "\nThank you for using the system!\n"; break;
            default: cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
