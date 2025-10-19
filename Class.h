//
// Created by pedro on 15/10/2023.
//

#ifndef UNTITLED1_CLASS_H
#define UNTITLED1_CLASS_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <set>
#include <iomanip>
#include <unordered_map>

using namespace std;

class Class {
public:
    explicit Class(const string& input_line);

    string getClassCode() const { return classCode; }
    string getWeekday() const { return weekday; }
    float getStartLesson() const { return start_lesson; }
    float getDuration() const { return duration; }
    string getType() const { return type; }
    string getUcCode() const { return UCCode; }
    bool overlapsWith(const Class& other) const;


    friend ostream& operator<< (ostream& out, const Class& c);
    bool operator< (const Class &right);

    static int getYear(string ClassCode);
private:
    string classCode;
    string UCCode;
    string weekday;
    float start_lesson; // 10.5 = 10:30
    float duration;     // 1.5 = 1h 30min
    string type;
    unordered_map<string, int> map_weekday =
            {
                    {"Monday" , 0},
                    {"Tuesday" , 1},
                    {"Wednesday" , 2},
                    {"Thursday" , 3},
                    {"Friday" , 4},
            };


};


#endif //UNTITLED1_CLASS_H
