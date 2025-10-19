#include "Class.h"
/**
 * @brief Constructor for the Class class.
 *
 * This constructor initializes the Class object based on the provided input line,
 * which is expected to be formatted with comma-separated values representing
 * ClassCode, UCCode, Weekday, Start, Duration, and Type.
 * @details Time Complexity: O(n)
 * @param input_line The input line containing comma-separated values.
 */
Class::Class(const string &input_line) {
    string feel;
    istringstream input(input_line);
    getline(input, feel, ','); // ClassCode
    classCode = feel;
    getline(input, feel, ','); // UcCode
    UCCode = feel;
    getline(input, feel, ','); // Weekday
    weekday = feel;
    getline(input, feel, ','); // Start
    start_lesson = stof(feel);
    getline(input, feel, ','); // Duration
    duration = stof(feel);
    getline(input, feel, ','); // Type
    type = feel;
}

ostream &operator<<(ostream &out, const Class &c) {
    // Extract hour and minute from start_lesson
    int start_hour = (int) (c.getStartLesson());
    int start_minute = (int) ((c.getStartLesson() - start_hour) * 60);

    float end_of_lesson = c.getStartLesson() + c.getDuration();
    int end_hour = (int) (end_of_lesson);
    int end_minute = (int) ((end_of_lesson - end_hour) * 60);

    out << '[' << c.getUcCode() << ';' << c.getClassCode() << "] " << c.getWeekday()
        << " " << start_hour << ":" << setw(2) << setfill('0') << start_minute
        << " - " << end_hour << ":" << setw(2) << setfill('0') << end_minute;
    return out;
}

int Class::getYear(string ClassCode) {
    if (ClassCode[0] == '1') return 1;
    if (ClassCode[0] == '2') return 2;
    if (ClassCode[0] == '3') return 3;
    return -1;
}
/**
 * @brief Checks if this Class overlaps with another Class.
 *
 * This function determines whether the current Class object overlaps with another Class
 * object based on their weekday, start time, and duration.
 *
 * @param other The other Class object to be compare with.
 * @return True if there is an overlap, false otherwise.
 *
 * @note The time complexity of this function is O(1).
 */
bool Class::overlapsWith(const Class& other) const {
    if(weekday != other.weekday) return false;
    float end_lesson = start_lesson + duration;
    float other_end_lesson = other.start_lesson + other.duration;

    return (start_lesson < other_end_lesson) && (end_lesson > other.start_lesson);
}
/**
 * @brief Overloaded less-than operator for the Class class.
 *
 * This operator compares two Class objects based on their weekday and start lesson.
 * @details Time Complexity: O(1)
 * @param right The Class object on the right side of the comparison.
 * 
 * @return True if the current object starts sooner than the right object, false otherwise.
 */
bool Class::operator<(const Class &right) {
    if (map_weekday[weekday] < map_weekday[right.weekday]) return true;
    else if (map_weekday[weekday] > map_weekday[right.weekday]) return false;
    else if (start_lesson < right.getStartLesson()) return true;
    return false;
}
