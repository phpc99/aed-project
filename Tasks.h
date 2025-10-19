//
// Created by pedro on 15/10/2023.
//

#ifndef UNTITLED1_TASKS_H
#define UNTITLED1_TASKS_H


#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>
#include <sstream>
#include <set>
#include <fstream>
#include <algorithm>
#include "Class.h"
#include "Student.h"
#include "Data.h"
/**
 * @brief Represents a set of tasks related to student and class information.
 * 
 * The Tasks class provides methods to perform various tasks on student and class data.
 */
class Tasks {
public:
    Tasks(string f1, string f2, string f3);
    // TODO: Task 1
    list<Class> getScheduleOfStudent(int upNumber);
    list<Class> getScheduleOfClass(const string& UCCode, const string& ClassCode);
    // TODO: Task 2
    list<Student> getStudentsOfYear(int year);
    list<Student> getStudentsOfUC(const string& UCCode);
    list<Student> getStudentsOfClass(const string& UCCode, const string& ClassCode);
    // TODO: Task3
    list<Student> getStudentsWithNClasses(int n);

    // TODO: Task4
    bool studentExists(int studentUP);
    int getNumberOfUCs(int studentUP);
    unordered_map<string, int> getUCClassesOccupancy(const string &UCCode) const;
    list<string> getAvailableUCClasses(int studentUP, const string &UCCode, const std::string &oldUC);
    bool isUCInStudentSchedule(int studentUP, const string &UCCode);
    bool isClassInStudentSchedule(int studentUP, const string &UCCode, const string &ClassCode);
    bool checkClassAvailability(int studentUP, const string &UCCode, const string &ClassCode, const string &oldUC, const string &oldClass);
    int getClassOccupancyDisparity(const string &UCCode) const;
    bool checkNewDisparity(const string &UCCode, const string &ClassCode) const;
    void appendToFile(const string &filename, const string &line);
    string getStudentName(const int &studentUpNumber);
    void removeFromFile(const string &filename, const string &lineToDelete);

    // TODO: Task5
    unordered_map<string, int> getUCOccupation();

private:
    vector<Student> students = {};
    unordered_map<string, unordered_map<string, classInfo>> classes = {};
};


#endif //UNTITLED1_TASKS_H
