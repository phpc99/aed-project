#ifndef UNTITLED1_REQUEST_H
#define UNTITLED1_REQUEST_H

#include <string>
/**
 * @enum RequestType
 * @brief Represents the type of a request.
 */
enum class RequestType { ADD_UC, REMOVE_UC, SWITCH_UC, ADD_CLASS, REMOVE_CLASS, SWITCH_CLASS };

class Request {
public:
    Request(RequestType type, int studentUpNumber, std::string  UCCode, std::string  classCode = "", std::string  newUCCode = "", std::string  newClassCode = "");

    [[nodiscard]] RequestType getType() const;
    [[nodiscard]] int getStudentUpNumber() const;
    [[nodiscard]] std::string getUCCode() const;
    [[nodiscard]] std::string getClassCode() const;
    [[nodiscard]] std::string getNewUCCode() const;
    [[nodiscard]] std::string getNewClassCode() const;

private:
    RequestType type;
    int studentUpNumber;
    std::string UCCode;
    std::string classCode;
    std::string newUCCode;     // Optional, only needed for SWITCH requests
    std::string newClassCode;  // Optional, only needed for SWITCH requests
};

#endif //UNTITLED1_REQUEST_H
