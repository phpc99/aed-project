//
// Created by pedro on 28/10/2023.
//

#include <climits>
#include <queue>
#include "Menu.h"
#include "Request.h"

using namespace std;
/**
 * @brief Constructor for the Menu class.
 *
 * This constructor initializes a Menu object and prompts the user if they want to change files.
 * If the user chooses to change files, it prompts for new file names for 'classes,' 'classes_per_uc,' and 'students_classes.'
 * The Tasks object is then recreated with the new filenames, and the requestsQueue is reset.
 *
 * @param rq A reference to the queue of requests.
 *
 */
Menu::Menu(std::queue<Request> &rq, queue<Request> &prq)
        : requestsQueue(rq), processedRequestsQueue(prq) {

    char choice;
    cout << "Do you want to change the files? [Y/N]:";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        string file1, file2, file3;

        cout << "Enter the name for 'classes' file (e.g., classes.csv):" << endl;
        cin >> file1;

        cout << "Enter the name for 'classes_per_uc' file (e.g., classes_per_uc.csv):" << endl;
        cin >> file2;

        cout << "Enter the name for 'students_classes' file (e.g., students_classes.csv):" << endl;
        cin >> file3;

        task = Tasks(file1, file2, file3); // Recreate the task object with new filenames
        rq = {};
        prq = {};

        students_file = file3;
    } else {
        students_file = "students_classes.csv";
    }
}
/**
 * @brief Displays the main menu for user login.
 *
 * This function prompts the user to sign in, allowing either an administrator login using 'admin'
 * or a student login using a valid student UP number. If the user is an administrator, it
 * navigates to the administrator menu. If the user is a student, it navigates to the student menu.
 * Invalid inputs are handled and appropriate messages are displayed.
 *
 * @note This function runs in an infinite loop until the program is manually terminated.
 */
void Menu::main_menu() {
    while (true) {
        cout << endl;
        cout << "|=============================================|\n"
             << "|                  Sign In                    |\n"
             << "|=============================================|\n"
             << "|  use 'admin' to log in as an administrator  |\n"
             << "|=============================================|\n"
             << "  Student UP Number: ";

        string input;
        cin >> input;
        if (input == "admin") {
            cout << "Administrator login successful." << endl;
            admin_menu();
        } else {
            stringstream ss(input);
            int studentUpNumber;
            if (ss >> studentUpNumber && ss.eof()) {
                if (task.studentExists(studentUpNumber)) {
                    cout << "Student with UP number " << studentUpNumber << " successfully logged in" << endl;
                    student_menu(studentUpNumber);
                } else {
                    cout << "Student with UP number " << studentUpNumber << " does not exist." << endl;
                }
            } else {
                cout << "Invalid input. Please enter a valid student UP number" << endl;
            }
        }
    }
}

/**
 * @brief Displays the menu for student-specific operations.
 *
 * This function presents a menu with various options for managing student-related information,
 * such as getting schedules, obtaining class and UC information, making requests, and more.
 * The user can choose an option, and the corresponding operation is performed. Invalid inputs are handled.
 *
 * @param studentUpNumber The UP number of the logged-in student.
 *
 * @note This function runs in an infinite loop until the user chooses to go back to the main menu.
 */
void Menu::student_menu(int studentUpNumber) {
    while (true) {
        cout << endl;
        cout << "|=============================================|\n"
                "|         Students Management System          |\n"
                "|=============================================|\n"
                "|  Get your schedule                      [1] |\n"
                "|  Get schedule from specific class       [2] |\n"
                "|  Get students from specific year        [3] |\n"
                "|  Get students from specific UC          [4] |\n"
                "|  Get students from specific class       [5] |\n"
                "|  Get students with N classes            [6] |\n"
                "|  Get specific class occupation          [7] |\n"
                "|  Get specific year occupation           [8] |\n"
                "|  Get specific UC occupation             [9] |\n"
                "|  Get UCs with the number of students   [10] |\n"
                "|  Make a request                        [11] |\n"
                "|  Go back                                [0] |\n"
                "|=============================================|\n";

        cout << endl;
        cout << "Please choose an option:";
        int option;
        cin >> option;
        cout << endl;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input" << endl;
            return;
        }

        switch (option) {
            case 0:
                return main_menu();
            case 1:
                showScheduleOfStudent(studentUpNumber);
                break;
            case 2:
                showScheduleOfClass();
                break;
            case 3:
                showStudentsOfYear();
                break;
            case 4:
                showStudentsOfUC();
                break;
            case 5:
                showStudentsOfClass();
                break;
            case 6:
                showStudentsWithNClasses();
                break;
            case 7:
                showClassOccupation();
                break;
            case 8:
                showYearOccupation();
                break;
            case 9:
                showUCOccupation();
                break;
            case 10:
                showUCWithNumberOfStudents();
                break;
            case 11:
                make_request(studentUpNumber);
                break;
            default:
                cout << "Invalid input" << endl;
        }
    }
}
/**
 * @brief Displays the schedule of a specific student.
 * @param studentUpNumber The UP number of the student whose schedule is to be displayed.
 */
void Menu::showScheduleOfStudent(int studentUpNumber) {
    cout << "Consulting schedule for student UP number: " << studentUpNumber << endl;
    list<Class> result = task.getScheduleOfStudent(studentUpNumber);
    result.sort();
    for (const auto &c: result) {
        cout << c << endl;
    }
}

void Menu::showScheduleOfClass() {
    // Consult the schedule of a given class
    cout << "Enter UC code:";
    string unitCode;
    cin >> unitCode;
    cout << "Enter class code:";
    string classCode;
    cin >> classCode;
    list<Class> result = task.getScheduleOfClass(unitCode, classCode);
    result.sort();
    for (const auto &c: result) {
        cout << c << endl;
    }
}

void Menu::showStudentsOfYear() {
    // Consult the students within a given year
    cout << "Enter year number:";
    int yearNumber;
    cin >> yearNumber;
    list<Student> result = task.getStudentsOfYear(yearNumber);
    printResultStudents(result);
}

void Menu::showStudentsOfUC() {
    // Consult the students within a given UC
    cout << "Enter UC code:";
    string unitCode;
    cin >> unitCode;
    list<Student> result = task.getStudentsOfUC(unitCode);
    printResultStudents(result);
}

void Menu::showStudentsOfClass() {
    // Consult the students within a given class
    cout << "Enter UC code:";
    string unitCode;
    cin >> unitCode;
    cout << "Enter class code:";
    string classCode;
    cin >> classCode;
    list<Student> result = task.getStudentsOfClass(unitCode, classCode);
    printResultStudents(result);
}

void Menu::showStudentsWithNClasses() {
    // Consult the number of students registered in at least N UCs
    cout << "Enter N:";
    int number;
    cin >> number;
    list<Student> result = task.getStudentsWithNClasses(number);
    printResultStudents(result);
}

void Menu::showClassOccupation() {
    // Consult the class occupation
    cout << "Enter UC code:";
    string unitCode;
    cin >> unitCode;
    cout << "Enter class code:";
    string classCode;
    cin >> classCode;
    list<Class> result = task.getScheduleOfClass(unitCode, classCode);
    cout << "Occupation of UC " << unitCode << " in class " << classCode << " is " << result.size() << endl;
}

void Menu::showYearOccupation() {
    // Consult the year occupation
    cout << "Enter year number:";
    int yearNumber;
    cin >> yearNumber;
    list<Student> result = task.getStudentsOfYear(yearNumber);
    cout << "Occupation of students in year " << yearNumber << " is " << result.size() << endl;
}

void Menu::showUCOccupation() {
    // Consult the UC occupation
    cout << "Enter UC code:";
    string unitCode;
    cin >> unitCode;
    list<Student> result = task.getStudentsOfUC(unitCode);
    cout << "Occupation of students in UC " << unitCode << " is " << result.size() << endl;
}
/**
 * @brief Displays the UCs with the greatest number of students.
 */
void Menu::showUCWithNumberOfStudents() {
    unordered_map<string, int> result = task.getUCOccupation();
    printResultUC(result);
}
/**
 * @brief Prints the results of UC occupation based on user-selected sorting method.
 * @param result An unordered_map containing UC codes as keys and the corresponding number of students as values.
 */
void Menu::printResultUC(unordered_map<string, int> result) {
    cout << endl;
    cout << "|==============================|\n"
            "|          Sort Method         |\n"
            "|==============================|\n"
            "|  By name                 [1] |\n"
            "|  By increasing order     [2] |\n"
            "|  By decreasing order     [3] |\n"
            "|==============================|\n";

    cout << endl;
    cout << "Please choose an option:";

    int sortChoice;
    cin >> sortChoice;
    cout << endl;

    vector<pair<string, int>> sortVector;
    for (auto i: result) {
        sortVector.push_back({i.first, i.second});
    }

    switch (sortChoice) {
        case 1:
            sort(sortVector.begin(), sortVector.end(), sortUCByName);
            break;
        case 2:
            sort(sortVector.begin(), sortVector.end(), sortByIncreaseNumberOfStudents);
            break;
        case 3:
            sort(sortVector.begin(), sortVector.end(), sortByDecreaseNumberOfStudents);
            break;
        default:
            cout << "Invalid input" << endl;
            main_menu();
    }
    for (const auto &c: sortVector) {
        cout << "The UC " << c.first << " has " << c.second << " students" << endl;
    }
}
/**
 * @brief Prints the results of student information based on user-selected sorting method.
 * @param result A list of Student objects containing the search results.
 */
void Menu::printResultStudents(list<Student> result) {

    cout << endl;
    cout << "|========================|\n"
            "|       Sort Method      |\n"
            "|========================|\n"
            "|  By name           [1] |\n"
            "|  By UP code        [2] |\n"
            "|========================|\n";

    cout << endl;
    cout << "Please choose an option:";

    int sortChoice;
    cin >> sortChoice;
    cout << endl;

    switch (sortChoice) {
        case 1:
            result.sort(sortStudentsByName);
            break;
        case 2:
            result.sort(sortStudentsByCode);
            break;
        default:
            cout << "Invalid input" << endl;
            main_menu();

    }
    cout << "Found " << result.size() << " students" << endl << endl;

    for (const auto &c: result) {
        cout << c << endl;
    }
}

bool Menu::sortStudentsByName(const Student &s1, const Student &s2) {
    if (s1.getName() < s2.getName()) return true;
    return false;
}

bool Menu::sortUCByName(const pair<string, int> &p1, const pair<string, int> &p2) {
    if (p1.first < p2.first) return true;
    return false;
}

bool Menu::sortByIncreaseNumberOfStudents(const pair<string, int> &p1, const pair<string, int> &p2) {
    if (p1.second < p2.second) return true;
    return false;
}

bool Menu::sortByDecreaseNumberOfStudents(const pair<string, int> &p1, const pair<string, int> &p2) {
    if (p1.second > p2.second) return true;
    return false;
}

bool Menu::sortStudentsByCode(const Student &s1, const Student &s2) {
    if (s1.getUP() < s2.getUP()) return true;
    return false;
}

/**
 * @brief Handles registration requests for a student.
 *
 * This function presents a menu of registration options for a student, including joining or leaving UCs
 * and classes, switching between UCs and classes, and returning to the main menu. It continuously prompts
 * the user for input until they choose to go back to the main menu.
 *
 * @param studentUpNumber The UP number of the student making the requests.
 */
void Menu::make_request(int studentUpNumber) {
    while (true) {
        cout << endl;
        cout << "|==============================|\n"
                "|    Registration Requests     |\n"
                "|==============================|\n"
                "|    Join UC               [1] |\n"
                "|    Leave UC              [2] |\n"
                "|    Switch UC's           [3] |\n"
                "|    Join Class            [4] |\n"
                "|    Leave Class           [5] |\n"
                "|    Switch Classes        [6] |\n"
                "|    Undo latest request   [7] |\n"
                "|    Go Back               [0] |\n"
                "|==============================|\n";
        cout << endl;
        cout << "Please choose an option:";
        int requestTypeNum;
        cin >> requestTypeNum;
        cout << endl;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input. Please try again." << endl;
        } else {
            switch (requestTypeNum) {
                case 0:
                    return; // Go back to the main menu
                case 1:
                    join_uc(studentUpNumber);
                    break;
                case 2:
                    leave_uc(studentUpNumber);
                    break;
                case 3:
                    switch_ucs(studentUpNumber);
                    break;
                case 4:
                    join_class(studentUpNumber);
                    break;
                case 5:
                    leave_class(studentUpNumber);
                    break;
                case 6:
                    switch_classes(studentUpNumber);
                    break;
                case 7:
                    undo_request(studentUpNumber);
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        }
    }
}

/**
 * @brief Initiates a request for a student to join a specific UC.
 *
 * This function prompts the user to enter the UC code they want to join, creates a corresponding request,
 * and adds it to the registration requests queue for further processing.
 * @details Time Complexity: O(1)
 * @param studentUpNumber The UP number of the student initiating the request.
 */
void Menu::join_uc(int studentUpNumber) {
    cout << "Your UP student number: " << studentUpNumber << endl;
    cout << "Please enter the UC code you want to join: ";
    string UCCode;
    cin >> UCCode;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input. Please enter a valid UC code." << endl;
        return;
    }
    Request joinUCRequest(RequestType::ADD_UC, studentUpNumber, UCCode);
    requestsQueue.push(joinUCRequest);
    std::cout << "Request added successfully!" << std::endl;
}

/**
 * @brief Initiates a request for a student to leave a specific UC.
 *
 * This function prompts the user to enter the UC code they want to leave,
 * creates a corresponding request, and adds it to the registration requests queue for further processing.
 * @details Time Complexity: O(1)
 * @param studentUpNumber The UP number of the student initiating the request.
 */
void Menu::leave_uc(int studentUpNumber) {
    cout << "Your UP student number: " << studentUpNumber << endl;

    cout << "Please enter the UC code you want to leave: ";
    string UCCode;
    cin >> UCCode;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input. Please enter a valid UC code." << endl;
        return;
    }
    Request leaveUCRequest(RequestType::REMOVE_UC, studentUpNumber, UCCode);
    requestsQueue.push(leaveUCRequest);
    std::cout << "Request added successfully!" << std::endl;
}

/**
 * @brief Initiates a request for a student to switch from one UC to another.
 *
 * This function prompts the user to enter the UC codes they want to leave and join,
 * creates a corresponding request, and adds it to the registration requests queue for further processing.
 * @details Time Complexity: O(1)
 * @param studentUpNumber The UP number of the student initiating the request.
 */
void Menu::switch_ucs(int studentUpNumber) {
    cout << "Your UP student number: " << studentUpNumber << endl;

    cout << "Please enter the UC code you want to leave: ";
    string oldUCCode;
    cin >> oldUCCode;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input. Please enter a valid UC code." << endl;
        return;
    }

    cout << "Please enter the UC code you want to join: ";
    string newUCCode;
    cin >> newUCCode;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input. Please enter a valid UC code." << endl;
        return;
    }
    // Create a request of type SWITCH_UC and add it to the requests queue
    Request switchUCsRequest(RequestType::SWITCH_UC, studentUpNumber, oldUCCode, "", newUCCode);
    requestsQueue.push(switchUCsRequest);
    std::cout << "Request added successfully!" << std::endl;
}

//Request to join a class
void Menu::join_class(int studentUpNumber) {
    cout << "Your UP student number: " << studentUpNumber << endl;

    cout << "Please enter the UC code of the class you want to join: ";
    string UCCode;
    cin >> UCCode;

    cout << "Please enter the class code you want to join: ";
    string classCode;
    cin >> classCode;
    cout << endl;

    Request joinClassRequest(RequestType::ADD_CLASS, studentUpNumber, UCCode, classCode);
    requestsQueue.push(joinClassRequest);
    std::cout << "Request added successfully!" << std::endl;
}

//Request to leave a class
void Menu::leave_class(int studentUpNumber) {
    cout << "Your UP student number: " << studentUpNumber << endl;

    cout << "Please enter the UC code of the class you want to leave: ";
    string UCCode;
    cin >> UCCode;

    cout << "Please enter the class code you want to leave: ";
    string classCode;
    cin >> classCode;
    cout << endl;

    Request leaveClassRequest(RequestType::REMOVE_CLASS, studentUpNumber, UCCode, classCode);
    requestsQueue.push(leaveClassRequest);
    std::cout << "Request added successfully!" << std::endl;
}

//Request to switch classes
void Menu::switch_classes(int studentUpNumber) {
    cout << "Your UP student number: " << studentUpNumber << endl;

    cout << "Please enter the UC code in which you want to switch classes: ";
    string UCCode;
    cin >> UCCode;

    cout << "Please enter the class code you want to leave: ";
    string oldClassCode;
    cin >> oldClassCode;
    cout << endl;

    cout << "Please enter the class code you want to join: ";
    string newClassCode;
    cin >> newClassCode;

    Request switchClassesRequest(RequestType::SWITCH_CLASS, studentUpNumber, UCCode, oldClassCode, "", newClassCode);
    requestsQueue.push(switchClassesRequest);
    std::cout << "Request added successfully!" << std::endl;
}

/**
 * @brief Undoes the latest registration request made by a specific student.
 *
 * This function checks if the provided student UP number matches the UP number of the student
 * who made the latest request in the queue. If the conditions are met, the latest request is
 * removed from the queue, effectively undoing the registration action.
 *
 * @param studentUpNumber The UP number of the student attempting to undo the latest request.
 */
void Menu::undo_request(int studentUpNumber) {
    if (studentUpNumber == requestsQueue.front().getStudentUpNumber() && !requestsQueue.empty()) {
        requestsQueue.pop();
        cout << "Latest request undone successfully!" << endl;
    } else {
        cout << "You have no requests." << endl;
    }
}

/**
 * @brief Admin menu for managing student registration requests.
 *
 * This function presents an admin menu with options to process the next request, process all requests,
 * revert changes, or exit the system. The admin can choose an option by entering the corresponding number.
 * The function continues to prompt the admin until they choose to exit the system.
 */
void Menu::admin_menu() {
    while (true) {
        cout << endl;
        cout << "|=============================================|\n"
                "|     Students Management System - Admin      |\n"
                "|=============================================|\n"
                "|  Process next request                   [1] |\n"
                "|  Process all requests                   [2] |\n"
                "|  Revert changes                         [3] |\n"
                "|  Exit                                   [0] |\n"
                "|=============================================|\n";

        cout << endl;
        cout << "Please choose an option:";
        int option;
        cin >> option;
        cout << endl;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input" << endl;
            return;
        }

        switch (option) {
            case 0:
                exit(0);
            case 1:
                processNextRequest();
                break;
            case 2:
                processAllRequests();
                break;
            case 3:
                revert_changes();
                break;
            default:
                cout << "Invalid input" << endl;
        }
    }
}

/**
 * @brief Processes the next registration request in the queue.
 * @details Time Complexity: O(n)
 * This function retrieves the next registration request from the queue and processes it based on its type.
 * The processing includes adding or removing students from UCs or classes, switching UCs or classes, and updating
 * the student file accordingly. The processed requests are moved to the processedRequestsQueue for reference.
 * After processing, a success message is displayed.
 */
void Menu::processNextRequest() {
    if (requestsQueue.empty()) {
        std::cout << "No requests to process." << std::endl;
        return;
    }

    Request request = requestsQueue.front();
    requestsQueue.pop();

    // Process the request
    std::cout << "Processing request from student " << request.getStudentUpNumber() << " ..." << std::endl;

    // Implement the logic for each request type
    switch (request.getType()) {
        //Rules for adding a UC
        case RequestType::ADD_UC: {
            // Add the student to the UC
            std::size_t numOfUCs = task.getNumberOfUCs(request.getStudentUpNumber());
            if (task.isUCInStudentSchedule(request.getStudentUpNumber(), request.getUCCode())) {
                std::cout << "Student is already enrolled in " << request.getUCCode() << "." << std::endl;
                break;
            }

            if (numOfUCs + 1 > 7) {
                std::cout << "Student cannot add UC. Already enrolled in 7 UCs." << std::endl;

            } else {
                list<string> availableClasses = task.getAvailableUCClasses(request.getStudentUpNumber(),request.getUCCode(), "");
                size_t numAvailableClasses = availableClasses.size();
                if (numAvailableClasses == 0) {
                    std::cout << "Student has no compatible classes for the requested UC." << std::endl;

                } else if (numAvailableClasses == 1) {
                    std::cout << "1 available class found. Adding student to class " << availableClasses.front() << std::endl;
                    std::string studentName = task.getStudentName(request.getStudentUpNumber());
                    std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + availableClasses.front();
                    task.appendToFile(students_file, line);
                    processedRequestsQueue.push(request);

                } else {
                    std::cout << numAvailableClasses<< " multiple available classes found. Student joined UC without class." << std::endl;
                    std::string studentName = task.getStudentName(request.getStudentUpNumber());
                    std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + "";
                    task.appendToFile(students_file, line);
                    processedRequestsQueue.push(request);

                }
            }
            break;
        }

        //Rules for removing a UC
        case RequestType::REMOVE_UC: {
            if (!task.isUCInStudentSchedule(request.getStudentUpNumber(), request.getUCCode())) {
                std::cout << "Student is not enrolled in " << request.getUCCode() << "." << std::endl;
                break;
            }
            std::cout << "Removing student from UC " << request.getUCCode() << " ..." << std::endl;
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode();
            task.removeFromFile(students_file, line);
            processedRequestsQueue.push(request);
            break;
        }

        //Rules for switching UCs
        case RequestType::SWITCH_UC: {
            if (!task.isUCInStudentSchedule(request.getStudentUpNumber(), request.getUCCode())) {
                std::cout << "Student is not enrolled in " << request.getUCCode() << "." << std::endl;
                break;
            }
            if (task.isUCInStudentSchedule(request.getStudentUpNumber(), request.getNewUCCode())) {
                std::cout << "Student is already enrolled in " << request.getUCCode() << "." << std::endl;
                break;
            }
            list<string> availableClasses = task.getAvailableUCClasses(request.getStudentUpNumber(),
                                                                       request.getNewUCCode(), request.getUCCode());
            size_t numAvailableClasses = availableClasses.size();
            if (numAvailableClasses == 0) {
                std::cout << "Student has no compatible classes for the requested UC." << std::endl;

            } else if (numAvailableClasses == 1) {
                std::cout << "1 available class found. Switching student to class " << availableClasses.front() << std::endl;
                std::string studentName = task.getStudentName(request.getStudentUpNumber());
                std::string lineToDelete = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode();
                task.removeFromFile(students_file, lineToDelete);
                std::string lineToAdd = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getNewUCCode() + "," + availableClasses.front();
                task.appendToFile(students_file, lineToAdd);
                processedRequestsQueue.push(request);

            } else {
                std::cout << numAvailableClasses << " multiple available classes found. Student switched to UC without class." << std::endl;
                std::string studentName = task.getStudentName(request.getStudentUpNumber());
                std::string lineToDelete = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode();
                task.removeFromFile(students_file, lineToDelete);
                std::string lineToAdd = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getNewUCCode() + "," + "";
                task.appendToFile(students_file, lineToAdd);
                processedRequestsQueue.push(request);
            }
            break;
        }

        //Rules for adding a class
        case RequestType::ADD_CLASS: {
            const int studentUpNumber = request.getStudentUpNumber();
            const std::string &UCCode = request.getUCCode();
            const std::string &classCode = request.getClassCode();
            std::size_t numOfUCs = task.getNumberOfUCs(request.getStudentUpNumber());

            if (task.isClassInStudentSchedule(studentUpNumber, UCCode, classCode)) {
                std::cout << "Student is already enrolled in class " << classCode << " for UC " << UCCode << std::endl;
                break;

            } else if (task.isUCInStudentSchedule(studentUpNumber, UCCode) && task.isClassInStudentSchedule(studentUpNumber, UCCode, "") &&  task.checkClassAvailability(studentUpNumber, UCCode, classCode, "", "")) {
                std::cout << "Adding student to Class " << classCode << " for UC " << UCCode << " ..." << std::endl;
                std::string studentName = task.getStudentName(request.getStudentUpNumber());
                std::string lineToDelete = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode();
                task.removeFromFile(students_file, lineToDelete);
                std::string lineToAdd = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
                task.appendToFile(students_file, lineToAdd);
                processedRequestsQueue.push(request);
                break;

            } else if (task.isUCInStudentSchedule(studentUpNumber, UCCode) && !task.isClassInStudentSchedule(studentUpNumber, UCCode, "")) {
                std::cout << "Student is already enrolled in another class for UC " << UCCode << std::endl;
                break;

            } else if (!task.checkClassAvailability(studentUpNumber, UCCode, classCode, "", "") || numOfUCs + 1 > 7) {
                std::cout << "Class " << classCode << " in UC " << UCCode << " is not available for the student." << std::endl;
                break;

            } else {
                std::cout << "Adding student to Class " << classCode << " for UC " << UCCode << " ..." << std::endl;
                std::string studentName = task.getStudentName(request.getStudentUpNumber());
                std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
                task.appendToFile(students_file, line);
                processedRequestsQueue.push(request);
            }
            break;
        }

        //Rules for removing a class
        case RequestType::REMOVE_CLASS: {
            if (!task.isClassInStudentSchedule(request.getStudentUpNumber(), request.getUCCode(),
                                               request.getClassCode())) {
                std::cout << "Student is not enrolled in class " << request.getClassCode() << " for UC "
                          << request.getUCCode() << "." << std::endl;
                break;
            }
            std::cout << "Removing student from Class" << request.getUCCode() << " for UC " << request.getClassCode()
                      << " ..." << std::endl;
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
            task.removeFromFile(students_file, line);
            processedRequestsQueue.push(request);
            break;
        }

        //Rules for switching classes
        case RequestType::SWITCH_CLASS: {
            const int studentUpNumber = request.getStudentUpNumber();
            const std::string &UCCode = request.getUCCode();
            const std::string &classCode = request.getClassCode();
            const std::string &newClassCode = request.getNewClassCode();

            if (task.isClassInStudentSchedule(studentUpNumber, UCCode, newClassCode)) {
                std::cout << "Student is already enrolled in class " << newClassCode << " for UC " << UCCode
                          << std::endl;
                break;
            } else if (!task.isClassInStudentSchedule(studentUpNumber, UCCode, classCode)) {
                std::cout << "Student is not enrolled in class " << classCode << " for UC " << UCCode << std::endl;
                break;
            } else if (!task.checkClassAvailability(studentUpNumber, UCCode, newClassCode, "", classCode)) {
                std::cout << "Class " << newClassCode << " in UC " << UCCode << " is not available for the student."
                          << std::endl;
                break;
            } else {
                std::cout << "Adding student to Class " << newClassCode << " for UC " << UCCode << " ..." << std::endl;

                std::string studentName = task.getStudentName(request.getStudentUpNumber());
                std::string lineToDelete = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
                task.removeFromFile(students_file, lineToDelete);
                std::string linetoAdd = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getNewClassCode();
                task.appendToFile(students_file, linetoAdd);
                processedRequestsQueue.push(request);
            }
            break;
        }
    }
    std::cout << "Request processed successfully!" << std::endl;
}

/**
 * @brief Process all requests in the queue.
 *
 * This function processes all pending requests in the requestsQueue by repeatedly
 * calling the processNextRequest function until the queue is empty.
 * Each request is processed individually, and the overall processing status is
 * displayed. The function provides feedback on the number of requests processed
 * and informs when all requests have been handled.
 */
void Menu::processAllRequests() {
    if (requestsQueue.empty()) {
        cout << "The request queue is empty. There are no requests to process." << endl;
        return;
    }

    cout << "Processing all requests...\n" << endl;

    int requestCount = 0;
    while (!requestsQueue.empty()) {
        cout << "\nProcessing request #" << ++requestCount << "..." << endl;
        processNextRequest();
    }

    cout << "All requests have been processed." << endl;
}

/**
 * @brief Revert the changes made by the last processed request.
 *
 * This function reverts the changes made by the last processed request stored
 * in the processedRequestsQueue. It identifies the type of the last processed
 * request and performs the necessary actions to undo the changes.
 *
 * The supported request types include:
 * - ADD_UC: Removes the student from the added UC.
 * - REMOVE_UC: Adds the student back to the removed UC.
 * - SWITCH_UC: Reverts the student's switch from the new UC to the old UC.
 * - ADD_CLASS: Removes the student from the added class.
 * - REMOVE_CLASS: Adds the student back to the removed class.
 * - SWITCH_CLASS: Reverts the student's switch from the new class to the old class.
 */
void Menu::revert_changes() {
    if (processedRequestsQueue.empty()) {
        std::cout << "No requests to process." << std::endl;
        return;
    }

    Request request = processedRequestsQueue.front();
    processedRequestsQueue.pop();

    switch (request.getType()) {
        case RequestType::ADD_UC : {
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode();
            task.removeFromFile(students_file, line);
            break;
        }
        case RequestType::REMOVE_UC : {
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode();
            task.appendToFile(students_file, line);
            break;
        }
        case RequestType::SWITCH_UC:{
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string lineToDelete = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getNewUCCode();
            task.removeFromFile(students_file, lineToDelete);
            std::string lineToAdd = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + "";
            task.appendToFile(students_file, lineToAdd);
            break;
        }
        case RequestType::ADD_CLASS:{
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
            task.removeFromFile(students_file, line);
            break;
        }
        case RequestType::REMOVE_CLASS:{
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string line = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
            task.appendToFile(students_file, line);
            break;
        }
        case RequestType::SWITCH_CLASS:{
            std::string studentName = task.getStudentName(request.getStudentUpNumber());
            std::string lineToDelete = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getNewClassCode();
            task.removeFromFile(students_file, lineToDelete);
            std::string lineToAdd = std::to_string(request.getStudentUpNumber()) + "," + studentName + "," + request.getUCCode() + "," + request.getClassCode();
            task.appendToFile(students_file, lineToAdd);
            break;
        }
    }
    cout << "Last processed request has been reverted successfully!" << endl;
}
