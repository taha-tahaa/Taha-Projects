#include "ip.h"
#include <iostream>
#include <stddef.h>
#include "string.h"

const int MAX_INTERVAL = 256;
const int BITS_NUM = 32;
const int BYTES = 8;
const int DOTS_SIZE = 3;
const int SLASH_SIZE = 1;
const int ERROR = -1;
const int SPLTIP_NUM = 4;
const int TRUE = 1;
const int FALSE = 0;
const int TWO = 2;
const int ONE = 1;

ip::ip(String p) : my_field(p) {
    // Initialize IP array with error values
    for (int i = 0; i < SPLTIP_NUM; i++) {
        this->IP[i] = ERROR;
    }
    this->bits_num = 0;
}

int Bits_ToCheck(int check_bits, int value) {
    int aux = value;
    for (int i = 0; i < (BYTES - check_bits); i++) {
        aux = aux / TWO;
    }
    return aux;
}

bool ip::match(String input) {
    size_t len;
    bool value = false;
    String *aux_split;

    input.split("=, ", &aux_split, &len);
    if (!len) {
        delete[] aux_split;
        return false;
    }

    for (size_t i = 0; i < len; i += 2) {
        if (my_field.equals(aux_split[i])) {
            String valueToMatch = aux_split[i + 1].trim();
            char delimiter_dots[] = ".";
            int check_bits = this->bits_num;
            String *dots;
            valueToMatch.split(delimiter_dots, &dots, &len);

            if (check_bits == 0) {
                delete[] dots;
                delete[] aux_split;
                return true;
            }

            int j = 0;
            while (check_bits > 0) {
                if (check_bits >= BYTES && dots[j].to_integer() != this->IP[j]) {
                    delete[] dots;
                    delete[] aux_split;
                    return false;
                }

                if (check_bits < BYTES &&
                    (Bits_ToCheck(check_bits, dots[j].to_integer()) !=
                     Bits_ToCheck(check_bits, this->IP[j]))) {
                    delete[] dots;
                    delete[] aux_split;
                    return false;
                }

                check_bits -= BYTES;
                j++;
            }

            delete[] dots;
            delete[] aux_split;
            return true;
        }
    }

    delete[] aux_split;
    return value;
}

bool ip::set_value(String packet) {
    char delimiter_dots[] = ".";
    char delimiter_slash[] = "/";
    String *dots;
    String *slash;
    size_t dots_num = DOTS_SIZE;
    size_t slash_num = SLASH_SIZE;
    packet.split(delimiter_slash, &slash, &slash_num);
    packet.split(delimiter_dots, &dots, &dots_num);

    for (int i = 0; i < (int)dots_num; i++) {
        // Check if each octet is within the valid range
        if (dots[i].to_integer() > MAX_INTERVAL || dots[i].to_integer() < 0) {
            delete[] dots;
            delete[] slash;
            return FALSE;
        }
    }

    // Check if the provided bits value is within the valid range
    if (slash[ONE].to_integer() > BITS_NUM || slash[ONE].to_integer() < 0) {
        delete[] dots;
        delete[] slash;
        return FALSE;
    }

    this->bits_num = slash[ONE].to_integer();

    // Store the IP address octets in the IP array
    for (int i = 0; i < (int)dots_num; i++) {
        this->IP[i] = dots[i].to_integer();
    }

    delete[] dots;
    delete[] slash;
    return TRUE;
}
