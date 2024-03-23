#include "string.h"
#include <cstring>
#include <cctype>
#include <iostream>

String::String() {
    // Initialize an empty string with a null character
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

String::String(const String& str) {
    // Copy constructor: create a new string and copy the content
    length = str.length;
    data = new char[length + 1];
    std::strcpy(data, str.data);
}

String::String(const char* str) {
    // Constructor with a C-style string
    if (str == nullptr) {
        // If input is null, create an empty string
        length = 0;
        data = new char[1];
        data[0] = '\0';
    } else {
        // Copy the content of the C-style string
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }
}

String::~String() {
    // Destructor: deallocate memory
    delete[] data;
}

String& String::operator=(const String& str) {
    // Copy assignment operator: copy the content of another string
    if (this != &str) {
        delete[] data;
        length = str.length;
        data = new char[length + 1];
        std::strcpy(data, str.data);
    }
    return *this;
}

String& String::operator=(const char* str) {
    // Assignment operator with a C-style string
    if (data != str) {
        delete[] data;
        if (str == nullptr) {
            // If input is null, create an empty string
            length = 0;
            data = new char[1];
            data[0] = '\0';
        } else {
            // Copy the content of the C-style string
            length = std::strlen(str);
            data = new char[length + 1];
            std::strcpy(data, str);
        }
    }
    return *this;
}

bool String::equals(const String& rhs) const {
    // Compare two strings for equality
    if ((std::strcmp(data, rhs.data) != 0) || (length != rhs.length)) {
        return false;
    }
    return true;
}

bool String::equals(const char* rhs) const {
    // Compare the string with a C-style string for equality
    if (rhs == nullptr)
        return false;
    return (std::strcmp(data, rhs) == 0);
}

void String::split(const char* delimiters, String** output, size_t* size) const {
    if (data == nullptr) {
        // If the string is null, set output to null and size to 0
        *output = nullptr;
        *size = 0;
        return;
    }
    if (output == nullptr) {
        // If output is null, set size to 2 and return
        *size = 2;
        return;
    }
    if (delimiters == nullptr || size == nullptr) {
        // If delimiters or size is null, return without splitting
        return;
    }

    // Count the number of delimiters
    size_t delimiterCount = 0;
    const char* ptr = data;
    while (*ptr != '\0') {
        if (std::strchr(delimiters, *ptr) != nullptr) {
            delimiterCount++;
        }
        ptr++;
    }

    // Compute the number of substrings
    *size = delimiterCount + 1;

    // Allocate memory for the output array
    *output = new String[*size];

    const char* start = data;
    const char* end = data;
    size_t substringIndex = 0;

    while (*end != '\0' && substringIndex < *size) {
        if (std::strchr(delimiters, *end) != nullptr) {
            // Calculate the length of the substring
            size_t substringLength = end - start;
            if (substringLength > 0) {
                // Copy the substring to the output array
                char* substring = new char[substringLength + 1];
                std::strncpy(substring, start, substringLength);
                substring[substringLength] = '\0';

                (*output)[substringIndex++] = String(substring);

                delete[] substring;
            }
            start = end + 1;
        }
        end++;
    }

    // Handle the last substring if it's not empty
    size_t substringLength = end - start;
    if (substringLength > 0 && substringIndex < *size) {
        char* substring = new char[substringLength + 1];
        std::strncpy(substring, start, substringLength);
        substring[substringLength] = '\0';

        (*output)[substringIndex++] = String(substring);

        delete[] substring;
    }

    // If the last substring is empty, decrement the size
    if (end == data + std::strlen(data)) {
        *size = substringIndex;
    }
}

int String::to_integer() const {
    try {
        // Convert the string to an integer using std::stoi
        return std::stoi(data);
    } catch (const std::exception& e) {
        // Handle exception (e.g., return a default value or throw a custom exception)
        // For now, returning 0 as a placeholder
        return 0;
    }
}

String String::trim() const {
    const char* start = data;
    const char* end = data + std::strlen(data) - 1;

    // Skip leading whitespaces
    while (std::isspace(*start)) {
        start++;
    }

    // Skip trailing whitespaces
    while (end > start && std::isspace(*end)) {
        end--;
    }

    size_t trimmedLength = (end >= start) ? (end - start + 1) : 0;
    char* trimmedData = new char[trimmedLength + 1];
    std::memcpy(trimmedData, start, trimmedLength);
    trimmedData[trimmedLength] = '\0';

    String trimmedString(trimmedData);
    delete[] trimmedData;

    return trimmedString;
}
