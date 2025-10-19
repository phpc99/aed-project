//
// Created by pedro on 28/10/2023.
//

#ifndef UNTITLED1_MENU_H
#define UNTITLED1_MENU_H

#include "Tasks.h"
#include "Request.h"
/**
 * @class Menu
 * @brief Represents the menu interface for managing scheduling, student enrollment, and administrative tasks.
 */
class Menu {
public:
    explicit Menu(std::queue<Request> &requestsQueue, queue<Request> &processedRequestsQueue);
    void main_menu();
    void showScheduleOfStudent(int studentUpNumber); // Consult the schedule of a given student (ex: "202025232")
    void showScheduleOfClass(); // Consult the schedule of a given class (ex: "L.EIC001", "1LEIC02")
    void showStudentsOfYear(); // Consult the students within a given year (ex: "1")
    void showStudentsOfUC(); // Consult the students within a given UC (ex: "L.EIC001")
    void showStudentsOfClass(); // Consult the students within a given class (ex: "L.EIC001", "1LEIC01")
    void showStudentsWithNClasses(); // Consult the number of students registered in at least N UCs (ex: "7")
    void showClassOccupation(); // Consult the class occupation (ex: "L.EIC001", "1LEIC02")
    void showYearOccupation(); // Consult the year occupation (ex: "1")
    void showUCOccupation(); // Consult the UC occupation (ex: "L.EIC001")
    void showUCWithNumberOfStudents(); // Consult the UCs with the greatest number of students
    void make_request(int studentUpNumber);

private:
    Tasks task = Tasks("classes.csv", "classes_per_uc.csv", "students_classes.csv");
    static bool sortUCByName(const pair<string, int>&p1,const pair<string, int>&p2);
    static bool sortByIncreaseNumberOfStudents(const pair<string, int>&p1,const pair<string, int>&p2);
    static bool sortByDecreaseNumberOfStudents(const pair<string, int>&p1,const pair<string, int>&p2);
    static bool sortStudentsByName(const Student& s1, const Student& s2);
    static bool sortStudentsByCode(const Student& s1, const Student& s2);

    void printResultUC(unordered_map<string, int>);
    void printResultStudents(list<Student>result);

    void join_uc(int studentUpNumber);

    void leave_uc(int studentUpNumber);

    void switch_ucs(int studentUpNumber);

    void join_class(int studentUpNumber);

    void leave_class(int studentUpNumber);

    void switch_classes(int studentUpNumber);

    std::queue<Request>& requestsQueue;

    void student_menu(int studentUpNumber);

    void admin_menu();

    void processNextRequest();

    void processAllRequests();

    std::string students_file;

    void undo_request(int studentUpNumber);

    std::queue<Request>& processedRequestsQueue;

    void revert_changes();
};


#endif //UNTITLED1_MENU_H
