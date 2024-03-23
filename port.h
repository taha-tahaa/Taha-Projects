#ifndef PORT_H
#define PORT_H

#define MAX_RANGE 65535
#define MIN_RANGE 0

#include "generic-field.h"
#include "string.h"
#include <iostream>
class port : public GenericField {
    String dst_src="";
    int range1=MIN_RANGE;
    int range2=MAX_RANGE;

public:
    /**
    * @brief Default constructor. Initializes port range to minimum and
    *      maximum values.  Sets dst_src to an empty string or a default value.
    */
    port();

    /**
     * @brief Constructor that initializes the port range to the minimum and
     *    maximum values.    Sets dst_src to the provided value.
     * @param value The value to set for dst_src.
     */
    port(String value);

    /**
     * @brief Sets the value of the port range and dst_src based on the
     * provided value.
     * @param value The value to set for the port range and dst_src.
     * @return True if the value was successfully set and within range,
     * False otherwise.
     */
    bool set_value(String value);

    /**
     * @brief Checks if the provided packet matches the port range and dst_src.
     * @param packet The packet to match against.
     * @return True if the packet matches the port range and dst_src,
     * False otherwise.
     */
    bool match(String packet);
 };

#endif /* PORT_H_ */
