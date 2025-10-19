//
// Created by pedro on 15/10/2023.
//

#include <climits>
#include "Tasks.h"

Tasks::Tasks(string f1, string f2, string f3) {
    Data data(f1, f2, f3);
    students = data.getStudents();
    classes = data.getClasses();
}
/**
 * @brief Gets the schedule of classes for a specific student based on UP number.
 * @details Time Complexity: O(n)
 * @param upNumber The UP number of the student.
 * @return A list of Class objects representing the schedule of the student.
 */
list<Class> Tasks::getScheduleOfStudent(int upNumber) {
    int idx = Data::binarySearchStudent(students, upNumber);
    if (students[idx].getUP() != upNumber) return {};
    list<Class> result = {};
    for (const auto &student_class: students[idx].getClasses()) {
        result.splice(result.end(), classes[student_class.first][student_class.second].schedule);
    }
    return result;
}

list<Class> Tasks::getScheduleOfClass(const string &UCCode, const string &ClassCode) {
    list<Class> scheduleClass = classes[UCCode][ClassCode].schedule;
    return scheduleClass;
}
/**
 * @brief Retrieves a list of students belonging to a specific academic year.
 *
 * This function iterates over the classes data structure, identifies students
 * enrolled in classes of the specified academic year, and returns a list of unique students.
 *
 * @param year The academic year to filter students.
 * @return A list of unique students belonging to the specified academic year.
 */
list<Student> Tasks::getStudentsOfYear(int year) {
    list<Student> result = {};
    set<int> upCodesOfStudents = {};
    // Iterate over the classes data structure to collect unique UP codes.
    for (const auto &UCCode: classes) {
        for (const auto &ClassCode: UCCode.second) {
            if (Class::getYear(ClassCode.first) == year) {
                for (auto upNumber: ClassCode.second.students) {
                    upCodesOfStudents.insert(upNumber);
                }
            }
        }
    }
    // Iterate over the set of unique UP codes and search for each student in the students vector.
    for (auto upNumber: upCodesOfStudents) {
        int idx = Data::binarySearchStudent(students, upNumber);
        if (students[idx].getUP() != upNumber) continue;
        result.push_back(students[idx]);
    }
    return result;
}

list<Student> Tasks::getStudentsOfUC(const string &findUCCode) {
    list<Student> result = {};
    list<int> upCodesOfStudents = {};

    for (const auto &UCCode: classes) {
        if (UCCode.first == findUCCode) {
            for (auto ClassCode: UCCode.second) {
                upCodesOfStudents.splice(upCodesOfStudents.end(), ClassCode.second.students);
            }
        }
    }

    for (auto upNumber: upCodesOfStudents) {
        int idx = Data::binarySearchStudent(students, upNumber);
        if (students[idx].getUP() != upNumber) continue;
        result.push_back(students[idx]);
    }

    return result;
}

list<Student> Tasks::getStudentsOfClass(const string &findUCCode, const string &findClassCode) {
    list<Student> result = {};
    list<int> upCodesOfStudents = {};

    for (const auto &UCCode: classes) {
        if (UCCode.first == findUCCode) {
            for (auto ClassCode: UCCode.second) {
                if (ClassCode.first == findClassCode) {
                    upCodesOfStudents.splice(upCodesOfStudents.end(), ClassCode.second.students);
                }
            }
        }
    }

    for (auto upNumber: upCodesOfStudents) {
        int idx = Data::binarySearchStudent(students, upNumber);
        if (students[idx].getUP() != upNumber) continue;
        result.push_back(students[idx]);
    }

    return result;
}
/**
 * @brief Retrieves a list of students with at least a specified number of enrolled classes.
 *
 * This function iterates over the list of students, filters those with at least
 * the specified number of enrolled classes, and returns a list of matching students.
 * @details Time Complexity: O(n)
 * @param n The minimum number of classes a student should have to be included in the result.
 * @return A list of students with at least the specified number of enrolled classes.
 */
list<Student> Tasks::getStudentsWithNClasses(int n) {
    list<Student> result = {};

    for (auto student: students) {
        if (student.getClasses().size() >= n) {
            result.push_back(student);
        }
    }
    return result;
}

unordered_map<string, int> Tasks::getUCOccupation() {
    unordered_map<string, int> result;


    for (const auto &UCCode: classes) {
        result[UCCode.first] = 0;
        for (const auto &ClassCode: UCCode.second) {
            int classOccupation = ClassCode.second.students.size();
            result[UCCode.first] += classOccupation;
        }
    }
    return result;
}

//Get the number of UCs a student is enrolled in - total classes / 2 (T and TP classes)
int Tasks::getNumberOfUCs(int studentUP) {
    int number_of_UCs = getScheduleOfStudent(studentUP).size() / 2;
    return number_of_UCs;
}

//Get the occupancy of all the classes in a specific UC
std::unordered_map<std::string, int> Tasks::getUCClassesOccupancy(const std::string &UCCode) const {
    std::unordered_map<std::string, int> occupancy;
    auto classesIterator = classes;
    auto ucIterator = classes.find(UCCode);
    if (ucIterator != classes.end()) {
        for (const auto &classPair: ucIterator->second) {
            occupancy[classPair.first] = classPair.second.students.size();
        }
    }
    return occupancy;
}

/**
 * @brief Retrieves a list of available classes for a student in a specific UC, considering occupancy and schedule compatibility.
 *
 * This function determines the available classes for a student in a particular UC, taking into account
 * the occupancy limit and ensuring compatibility with the student's existing schedule. It excludes the old UC's class during compatibility checking.
 *
 * @param studentUP The UP number of the student.
 * @param UCCode The code of the UC for which available classes are requested.
 * @param oldUC The code of the old UC (to exclude its class during compatibility checking).
 * @return A list of available class codes for the student in the specified UC.
 */
std::list<std::string> Tasks::getAvailableUCClasses(int studentUP, const std::string &UCCode, const std::string &oldUC) {
    std::list<std::string> availableClasses;
    auto classOccupancy = getUCClassesOccupancy(UCCode);

    int studentIdx = Data::binarySearchStudent(students, studentUP);
    if (students[studentIdx].getUP() != studentUP) {
        return availableClasses; // Student not found, return an empty list
    }

    auto studentSchedule = getScheduleOfStudent(studentUP);

    for (const auto &[classCode, occupancy]: classOccupancy) {
        if (occupancy < 25) {
            std::list<Class> classSchedules = getScheduleOfClass(UCCode, classCode);
            if (!classSchedules.empty()) {
                const Class &firstClassSchedule = classSchedules.front();

                // Check if the schedules are compatible
                bool isCompatible = true;
                for (const auto &class1: studentSchedule) {
                    // Skip the class from the old UC during compatibility checking
                    if (class1.getUcCode() == oldUC) {
                        continue;
                    }
                    if (class1.overlapsWith(firstClassSchedule)) {
                        isCompatible = false;
                        break;
                    }
                }
                if (isCompatible) {
                    availableClasses.push_back(classCode);
                }
            }
        }
    }
    return availableClasses;
}

//Check if a student exists by their UP number - sign in
bool Tasks::studentExists(int studentUP) {
    int studentIdx = Data::binarySearchStudent(students, studentUP);
    if (studentIdx < 0 || studentIdx >= students.size() || students[studentIdx].getUP() != studentUP) {
        return false;
    }
    return true;
}

/**
 * @brief Checks if a student is enrolled in classes of a specific UC.
 *
 * This function performs a binary search to find the student with the specified UP number
 * and checks if the student is enrolled in any classes associated with the given UC code.
 * @details Time Complexity: O(n)
 * @param studentUP The UP number of the student.
 * @param UCCode The UC code to check for enrollment.
 * @return True if the student is enrolled in classes of the specified UC, false otherwise.
 */
bool Tasks::isUCInStudentSchedule(int studentUP, const std::string &UCCode) {
    int idx = Data::binarySearchStudent(students, studentUP);
    if (idx < 0 || idx >= students.size() || students[idx].getUP() != studentUP) {
        std::cerr << "Student with UP " << studentUP << " not found." << std::endl;
        return false;
    }
    const auto &studentClasses = students[idx].getClasses();
    for (const auto &student_class : studentClasses) {
        if (student_class.first == UCCode) {
            return true;
        }
    }
    return false;
}

//Check if a class is in a student's schedule
bool Tasks::isClassInStudentSchedule(int studentUP, const std::string &UCCode, const std::string &ClassCode) {
    int idx = Data::binarySearchStudent(students, studentUP);
    if (idx < 0 || idx >= students.size() || students[idx].getUP() != studentUP) {
        std::cerr << "Student with UP " << studentUP << " not found." << std::endl;
        return false;
    }
    const auto &studentClasses = students[idx].getClasses();
    for (const auto &[studentUCCode, studentClassCode] : studentClasses) {
        if (studentUCCode == UCCode && studentClassCode == ClassCode) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks the availability of a class for enrollment by a student.
 *
 * This function verifies if a class is available for enrollment by a student based on various criteria,
 * including class existence, occupancy, disparity checking, and schedule compatibility.
 * @details Time Complexity: O(n)
 * @param studentUP The UP number of the student.
 * @param UCCode The UC code of the class.
 * @param ClassCode The code of the class.
 * @param oldUC The old UC code (to exclude its class during compatibility checking).
 * @param oldClass The old class code (to exclude it during compatibility checking).
 * @return True if the class is available for enrollment, false otherwise.
 */
bool Tasks::checkClassAvailability(int studentUP, const std::string &UCCode, const std::string &ClassCode, const std::string &oldUC, const std::string &oldClass) {
    // Check if the class exists and get its current occupancy
    auto ucIterator = classes.find(UCCode);
    if (ucIterator == classes.end()) return false; // UC not found

    auto classIterator = ucIterator->second.find(ClassCode);
    if (classIterator == ucIterator->second.end()) return false; // Class not found

    int currentOccupancy = getStudentsOfClass(UCCode, ClassCode).size();
    if (currentOccupancy >= 25) return false; // Class is full

    if (checkNewDisparity(UCCode, ClassCode)) return false;

    // Check schedule compatibility
    auto studentSchedule = getScheduleOfStudent(studentUP);
    list<Class> classSchedule = getScheduleOfClass(UCCode, ClassCode);
    if (classSchedule.empty()) return false; // Class has no schedule

    for (const auto &class1 : studentSchedule) {
        // Skip the class from the old UC during compatibility checking
        if (class1.getUcCode() == oldUC && class1.getClassCode() == oldClass) {
            continue;
        }
        if (class1.overlapsWith(classSchedule.front())) {
            return false; // Schedule conflict
        }
    }

    return true; // All checks passed, the class is available
}

//Get the disparity between the occupancy of the classes in a UC
int Tasks::getClassOccupancyDisparity(const std::string &UCCode) const {
    const auto &occupancy = getUCClassesOccupancy(UCCode);

    if (occupancy.empty()) return 0; // If there are no classes, return disparity as 0

    int minOccupancy = INT_MAX; // Set to maximum possible value initially
    int maxOccupancy = INT_MIN; // Set to minimum possible value initially

    for (const auto &[classCode, occupancyCount] : occupancy) {
        if (occupancyCount < minOccupancy) {
            minOccupancy = occupancyCount;
        }
        if (occupancyCount > maxOccupancy) {
            maxOccupancy = occupancyCount;
        }
    }

    return maxOccupancy - minOccupancy;
}

//Check if adding a student to a class will increase disparity between classes occupancy
bool Tasks::checkNewDisparity(const std::string &UCCode, const std::string &ClassCode) const {
    auto occupancy = getUCClassesOccupancy(UCCode);
    int currentDisparity = getClassOccupancyDisparity(UCCode);

    // If the class is not in the UC, adding a student to it will not increase disparity
    if (occupancy.find(ClassCode) == occupancy.end()) return false;

    // Simulate adding a student to the class
    occupancy[ClassCode] += 1;

    // Calculate new disparity
    int minOccupancy = occupancy.begin()->second;
    int maxOccupancy = occupancy.begin()->second;
    for (const auto &[classCode, occupancyCount] : occupancy) {
        if (occupancyCount < minOccupancy) minOccupancy = occupancyCount;
        if (occupancyCount > maxOccupancy) maxOccupancy = occupancyCount;
    }

    int newDisparity = maxOccupancy - minOccupancy;
    return newDisparity > currentDisparity + 4;
}

//Get the student name given a UP number
std::string Tasks::getStudentName(const int &studentUpNumber) {
    int idx = Data::binarySearchStudent(students, studentUpNumber);
    if (students[idx].getUP() != studentUpNumber) return {};
    return students[idx].getName();
}

//Add new class and UC information to the students file
void Tasks::appendToFile(const std::string& filename, const std::string& line) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    file << line << std::endl;

    if (!file) {
        std::cerr << "Error writing to file." << std::endl;
    }
}

/**
 * @brief Removes a specific line from a text file.
 *
 * This function reads the content of a text file, searches for a specific line to delete,
 * and overwrites the original file with the remaining lines. It only writes back if the line
 * to delete was found.
 *
 * @param filename The name of the file to modify.
 * @param lineToDelete The line to search for and delete from the file.
 */
void Tasks::removeFromFile(const std::string &filename, const std::string &lineToDelete) {
    std::ifstream filein(filename); // File to read from

    if (!filein) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (getline(filein, line)) {
        // Check if the line contains the substring
        if (line.find(lineToDelete) == std::string::npos) {
            lines.push_back(line);
        } else {
            found = true; // Mark that the line was found
        }
    }

    filein.close();

    // Only write back if the line to delete was found
    if (found) {
        std::ofstream fileout(filename); // Open the same file to overwrite it

        if (!fileout) {
            std::cerr << "Error opening file for writing." << std::endl;
            return;
        }

        // Write all lines except the one to delete back to the original file
        for (const auto& i : lines) {
            fileout << i << "\n";
        }

        fileout.close();
    } else {
        std::cerr << "Line to delete was not found." << std::endl;
    }
}

