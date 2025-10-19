//
// Created by pedro on 15/10/2023.
//

#include <iomanip>
#include "Student.h"
/**
 * @brief Constructor for initializing a Student object from a formatted input line.
 * 
 * Parses the input line to extract UP number, name, and classes information.
 * @details Time Complexity: O(n)
 * @param input_line The input line containing student information in a formatted manner.
 */
Student::Student(const string &input_line) {
    string feel, feel2;
    istringstream input (input_line);
    getline(input, feel, ',');
    upNumber = stoi(feel);
    getline(input, feel, ',');
    name = feel;
    getline(input, feel, ',');
    getline(input, feel2, '\r');

    classes.insert(make_pair(feel, feel2));
}

Student::Student() {
    upNumber = 0;
    name = "";
}

void Student::add_class(const pair<string, string>& new_class) {
    classes.insert(new_class);
}

std::ostream& operator<< (std::ostream& out, const Student& s){
    out << std::setw(26) << std::left << s.getName() << s.getUP();
    out << "   ";
    return out;
}


bool Student::operator<(const Student& right) const{
    return this->getUP() < right.getUP();
}

bool Student::operator>(const Student& right) const{
    return this->getUP() > right.getUP();
}

bool Student::operator==(const Student& right) const{
    return upNumber == right.getUP();
}

string Student::getName() const{
    return name;
}

int Student::getUP() const {
    return upNumber;
}

set<pair<string, string>> Student::getClasses() const{
    return classes;
}
