#include "simple_base64.h"
#include <string>

std::string simple_base64::decode(const std::string& input) {
    static const std::string chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    std::string result;
    int val = 0, valb = -8;
    
    for (unsigned char c : input) {
        if (chars.find(c) == std::string::npos) continue;
        val = (val << 6) + chars.find(c);
        valb += 6;
        if (valb >= 0) {
            result.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return result;
}
