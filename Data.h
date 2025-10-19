//
// Created by pedro on 15/10/2023.
//

#ifndef UNTITLED1_DATA_H
#define UNTITLED1_DATA_H
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

struct classInfo{
    list<int> students = {};
    list<Class> schedule = {};
};

using namespace std;

/**
 * @brief The Class class represents a class schedule entry.
 *
 * This class provides functionality to store and manipulate information
 * about a class, including its code, weekday, start time, duration, and type.
 */
class Data {
public:
    Data(string f1, string f2, string f3);

    vector<Student> getStudents();
    unordered_map<string, unordered_map<string, classInfo>> getClasses();

    static int binarySearchStudent(const std::vector<Student>& students, int targetUP);

private:
    string classes_fm = "classes.csv";
    string classes_per_uc_fm = "classes_per_uc.csv";
    string students_classes_fm = "students_classes,csv";
    vector<Student> students = {};
    unordered_map<string, unordered_map<string, classInfo>> classes = {};
    void read_students();
    void read_classes();
    void fill_classes();
};


#endif //UNTITLED1_DATA_H
