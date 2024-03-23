#include <iostream>
#include "port.h"

port::port() : range1(MIN_RANGE), range2(MAX_RANGE), dst_src("") {
    // Default constructor
    // Initialize the port range to the minimum and maximum values
    // Set dst_src to an empty string or a default value
}

port::port(String value) {
    dst_src = value;
    range1 = MIN_RANGE;
    range2 = MAX_RANGE;
}

bool port::set_value(String value){
    value.trim();
    int past_range1 = range1;
    int past_range2 = range2;

    String *hyphen;
    size_t hyphen_size;

    value.split("-=", &hyphen, &hyphen_size);
    String r1 = hyphen[0].trim();
    String r2 = hyphen[1].trim();
    range1 = r1.to_integer();
    range2 = r2.to_integer();

    delete[] hyphen;

    if (!(range1 <= range2 && range1 >= MIN_RANGE && range2 <= MAX_RANGE)) {
        // Invalid range, restore previous values
        range1 = past_range1;
        range2 = past_range2;
        return false;
    }

    return true;
}

bool port::match(String packet) {
    if (packet.equals("")) {
        return false;
    }

    packet.trim();
    const char* delimiters = ",=";
    String* substrings;
    size_t size = 0;
    packet.split(delimiters, &substrings, &size);

    for (size_t i = 0; i < size; i++) {
        substrings[i].trim();
    }

    bool found_dst_src = false;
    bool within_range = false;

    for (size_t i = 0; i < size - 1; i += 2) {
        if (substrings[i].trim().equals(dst_src)) {
            found_dst_src = true;
            String port_values = substrings[i + 1].trim();
            int port = port_values.to_integer();
            if (port >= range1 && port <= range2) {
                within_range = true;
                break;
            }
        }
    }

    delete[] substrings;

    return found_dst_src && within_range;
}
