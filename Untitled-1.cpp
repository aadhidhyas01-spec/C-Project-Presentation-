#include<iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>   // FIXED

using namespace std;

struct Course {
    int courseId;
    string title;
    string instructor;
    list<int> enrolledStudents;
    map<int, float> studentProgress;
};

struct Student {
    int studentId;
    string name;
};

unordered_map<int, Course> courses;
unordered_map<int, Student> students;

void separator() {
    cout << string(55, '=') << "\n";
}

// 1. Add Course
void addCourse() {
    Course c;
    cout << "\n--- Add Course ---\n";
    cout << "Enter Course ID   : ";
    cin >> c.courseId;

    if (courses.count(c.courseId)) {
        cout << "[Error] Course ID already exists.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // FIXED
    cout << "Enter Course Title: ";
    getline(cin, c.title);

    cout << "Enter Instructor  : ";
    getline(cin, c.instructor);

    courses[c.courseId] = c;
    cout << "[OK] Course added successfully.\n";
}

// 2. Enroll Student
void enrollStudent() {
    int studentId, courseId;
    string name;

    cout << "\n--- Enroll Student ---\n";
    cout << "Enter Student ID  : ";
    cin >> studentId;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // FIXED

    if (!students.count(studentId)) {
        cout << "Enter Student Name: ";
        getline(cin, name);
        students[studentId] = {studentId, name};
    }

    cout << "Enter Course ID   : ";
    cin >> courseId;

    if (!courses.count(courseId)) {
        cout << "[Error] Course not found.\n";
        return;
    }

    Course &c = courses[courseId];

    if (find(c.enrolledStudents.begin(), c.enrolledStudents.end(), studentId) != c.enrolledStudents.end()) {
        cout << "[Warning] Already enrolled.\n";
        return;
    }

    c.enrolledStudents.push_back(studentId);
    c.studentProgress[studentId] = 0.0f;

    cout << "[OK] Student enrolled.\n";
}

// 3. View Courses
void viewCourses() {
    cout << "\n--- All Courses ---\n";

    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }

    for (auto &pair : courses) {
        Course &c = pair.second;

        cout << "ID: " << c.courseId
             << ", Title: " << c.title
             << ", Instructor: " << c.instructor
             << ", Students: " << c.enrolledStudents.size()
             << endl;
    }
}

// 4. Track Progress
void trackProgress() {
    int studentId, courseId;
    float progress;

    cout << "\n--- Track Progress ---\n";
    cout << "Enter Student ID : ";
    cin >> studentId;

    cout << "Enter Course ID  : ";
    cin >> courseId;

    if (!courses.count(courseId)) {
        cout << "[Error] Course not found.\n";
        return;
    }

    Course &c = courses[courseId];

    if (!c.studentProgress.count(studentId)) {
        cout << "[Error] Student not enrolled.\n";
        return;
    }

    cout << "Current Progress: " << c.studentProgress[studentId] << "%\n";
    cout << "Enter New Progress: ";
    cin >> progress;

    // clamp between 0 and 100
    progress = max(0.0f, min(100.0f, progress));

    c.studentProgress[studentId] = progress;

    cout << "[OK] Updated.\n";
}

// 5. List Students
void listStudentsPerCourse() {
    int courseId;
    cout << "\nEnter Course ID: ";
    cin >> courseId;

    if (!courses.count(courseId)) {
        cout << "[Error] Course not found.\n";
        return;
    }

    Course &c = courses[courseId];

    if (c.enrolledStudents.empty()) {   // FIXED
        cout << "No students enrolled.\n";
        return;
    }

    for (int sid : c.enrolledStudents) {
        string name = students.count(sid) ? students[sid].name : "Unknown";
        float prog = c.studentProgress[sid];

        cout << sid << " - " << name << " - " << prog << "%\n";
    }
}

// 6. Remove Enrollment
void removeEnrollment() {
    int studentId, courseId;

    cout << "\nEnter Student ID: ";
    cin >> studentId;

    cout << "Enter Course ID : ";
    cin >> courseId;

    if (!courses.count(courseId)) {
        cout << "[Error] Course not found.\n";
        return;
    }

    Course &c = courses[courseId];

    auto it = find(c.enrolledStudents.begin(), c.enrolledStudents.end(), studentId);

    if (it == c.enrolledStudents.end()) {
        cout << "[Error] Not enrolled.\n";
        return;
    }

    c.enrolledStudents.erase(it);
    c.studentProgress.erase(studentId);

    cout << "[OK] Removed.\n";
}

// 7. Analytics
void generateAnalytics() {
    int courseId;
    cout << "\nEnter Course ID: ";
    cin >> courseId;

    if (!courses.count(courseId)) {
        cout << "[Error] Course not found.\n";
        return;
    }

    Course &c = courses[courseId];

    int total = c.studentProgress.size();   // FIXED
    cout << "Total Students: " << total << endl;

    if (total == 0) return;

    float sum = 0;
    for (auto &p : c.studentProgress) {
        sum += p.second;
    }

    cout << "Average Progress: " << (sum / total) << "%\n";

    vector<pair<int, float>> vec(c.studentProgress.begin(), c.studentProgress.end());

    sort(vec.begin(), vec.end(), [](const pair<int,float>& a, const pair<int,float>& b) {
        return a.second > b.second;
    });

    cout << "Top Students:\n";

    for (int i = 0; i < vec.size() && i < 3; i++) {
        int sid = vec[i].first;
        float prog = vec[i].second;

        string name = students.count(sid) ? students[sid].name : "Unknown";

        cout << sid << " (" << name << ") - " << prog << "%\n";
    }
}

// MAIN
int main() {
    int choice;

    do {
        separator();
        cout << "1.Add Course\n2.Enroll Student\n3.View Courses\n4.Track Progress\n";
        cout << "5.List Students\n6.Remove Enrollment\n7.Analytics\n0.Exit\n";
        separator();

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addCourse(); break;
            case 2: enrollStudent(); break;
            case 3: viewCourses(); break;
            case 4: trackProgress(); break;
            case 5: listStudentsPerCourse(); break;
            case 6: removeEnrollment(); break;
            case 7: generateAnalytics(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
