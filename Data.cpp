//
// Created by pedro on 15/10/2023.
//

#include "Data.h"

#include <utility>

Data::Data(std::string f1, std::string f2, std::string f3)
        : classes_fm(std::move(f1)), classes_per_uc_fm(std::move(f2)), students_classes_fm(std::move(f3)) {

    read_students();
    read_classes();
    fill_classes();
}
/**
 * @brief Reads student data from a file and populates the Data object.
 *
 * This function reads student data from the specified file, creates Student objects,
 * and adds them to the Data object's list of students. If a student with the same UP number
 * already exists, it adds the new class to the existing student; otherwise, it inserts
 * the new student into the list in sorted order based on UP number.
 */
void Data::read_students() {
    ifstream inn(students_classes_fm);
    string line;
    getline(inn, line);

    while (getline(inn, line)){
        Student student(line); ///< Create a Student object from the input line.
        int idx = binarySearchStudent(students, student.getUP()); ///< Binary search for the student's UP number.
        if(idx < students.size() && students[idx] == student){
            students[idx].add_class(*student.getClasses().begin()); ///< Add class to existing student.
        } else {
            students.insert(students.begin() + idx, student); ///< Insert new student in sorted order.
        }
    }
}

void Data::read_classes() {
    ifstream inn(classes_fm);
    string line;
    getline(inn, line);

    while (getline(inn, line)){
        Class read_class(line);

        string UC = read_class.getUcCode();
        string ClassCode = read_class.getClassCode();

        if(classes.find(UC) == classes.end()) {
            classes[UC] = unordered_map<std::string, classInfo>{};
        }
        if(classes[UC].find(ClassCode) == classes[UC].end()) {
            classes[UC][ClassCode] = classInfo{};
        }

        classes[UC][ClassCode].schedule.push_back(read_class);
    }
}
/**
 * @brief Fills the classes data structure with student information.
 *
 * This function iterates through the list of students, retrieves their enrolled classes,
 * and updates the classes data structure with the corresponding student information.
 * It associates each class with the UP numbers of the students enrolled in that class.
 */
void Data::fill_classes() {
    for(auto student : students){
        for(auto student_class: student.getClasses()){
            classes[student_class.first][student_class.second].students.push_back(student.getUP());
        }
    }
}

vector<Student> Data::getStudents() {
    return students;
}

unordered_map<string, unordered_map<string, classInfo>> Data::getClasses() {
    return classes;
}
/**
 * @brief Performs binary search for a target UP number in a sorted vector of students.
 *
 * This function performs a binary search on a sorted vector of students to find the index
 * of the student with the specified UP number. If the UP number is found, the function returns
 * the index of the matching student; otherwise, it returns the index where the student should be inserted
 * to maintain the sorted order.
 * @details Time Complexity: O(log n)
 * @param students The sorted vector of students to search.
 * @param targetUP The UP number to search for.
 * @return The index of the student with the target UP number or the insertion point in the sorted vector.
 */
int Data::binarySearchStudent(const std::vector<Student>& students, int targetUP) {
    int left = 0;
    int right = (int) students.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (students[mid].getUP() == targetUP)
            return mid;

        if (students[mid].getUP() < targetUP) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}