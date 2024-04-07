#include <libk/string.h>
#include <libk/types.h>

// @brief string length
size_t strlen(const char* String) {
    size_t length = 0;
    while(String[length]) {
        length++;
    }
    return length;
}