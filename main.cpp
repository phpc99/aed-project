#include <iostream>
#include <queue>
#include "Menu.h"
#include "Request.h"
/**
 * @brief The main function for the program.
 *
 * This function initializes a queue of requests, creates a Menu object,
 * and calls the main menu function to start the program.
 * Exception handling is implemented to catch and display any exceptions that may occur.
 *
 * @return 0 on successful execution.
 *
 * @throws std::exception If an exception is caught during program execution,
 * it will be displayed using cout.
 *
 */
int main() {

    try{
        std::queue<Request> requestsQueue;
        std::queue<Request> processedRequestsQueue;
        Menu menu(requestsQueue, processedRequestsQueue);
        menu.main_menu();
    } catch(exception& e){
        cout << e.what() << endl;
    }

    return 0;
}