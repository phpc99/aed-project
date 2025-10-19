#include "Request.h"

#include <utility>
/**
 * @class Request
 * @brief Represents a request made by a student.
 */
Request::Request(RequestType type, int studentUpNumber, std::string  UCCode, std::string  classCode, std::string  newUCCode, std::string  newClassCode)
        : type(type), studentUpNumber(studentUpNumber), UCCode(std::move(UCCode)), classCode(std::move(classCode)), newUCCode(std::move(newUCCode)), newClassCode(std::move(newClassCode)) {}

RequestType Request::getType() const {
    return type;
}

int Request::getStudentUpNumber() const {
    return studentUpNumber;
}

std::string Request::getUCCode() const {
    return UCCode;
}

std::string Request::getClassCode() const {
    return classCode;
}

std::string Request::getNewUCCode() const {
    return newUCCode;
}

std::string Request::getNewClassCode() const {
    return newClassCode;
}

