//
// Created by pedro on 15/10/2023.
//

#ifndef UNTITLED1_STUDENT_H
#define UNTITLED1_STUDENT_H


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;
/**
 * @brief Represents a student with a name, UP number, and a set of classes.
 * 
 * The Student class provides methods to access and modify student information.
 */
class Student {
public:
    explicit Student(const string& input_line);
    Student();
    string getName() const;
    int getUP() const;
    set<pair<string, string>> getClasses() const;

    void add_class(const pair<string, string>& new_class);

    friend ostream& operator<< (ostream& out, const Student& s);
    bool operator<(const Student& right) const;
    bool operator>(const Student& right) const;
    bool operator==(const Student& right) const;

private:
    string name;
    int upNumber;
    set<pair<string, string>> classes = {}; // UCCode,ClassCode
};


#endif //UNTITLED1_STUDENT_H
