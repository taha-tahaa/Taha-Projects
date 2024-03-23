#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"

const int SIZE=4;
class ip : public  GenericField
{
String my_field;
int IP[SIZE];
int bits_num;
/**
  * @brief Checks if the input matches the IP address field.
  * @param input The input string to match against.
  * @return True if the input matches the IP address field, False otherwise.
  */
 bool aux_match(String input);

public:
 /**
  * @brief Constructor that initializes the IP address field with the provided
  * value.
  * @param p The value to set for the IP address field.
  */
 ip(String p);

 /**
  * @brief Sets the value of the IP address field based on the provided packet.
  * @param packet The packet containing the IP address value.
  * @return True if the value was successfully set, False otherwise.
  */
 bool set_value(String packet);

 /**
  * @brief Checks if the provided value matches the IP address field.
  * @param value The value to match against.
  * @return True if the value matches the IP address field, False otherwise.
  */
 bool match(String value);
    
};

#endif 
