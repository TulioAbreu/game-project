#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

#include <string>
#include <cstring>
#include <cmath>

std::string toUpperCase(std::string str) {
    std::string result (str);
    for (auto& c : result) c = toupper(c);
    return result;
}

inline int hexChar2dec(char ch) {
    switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return ((int) ch) - '0';
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
    }
    return -1;
}

int hex2dec(std::string value) {
    const char* hexStr = toUpperCase(value).c_str();
    const size_t hexStrLength = strlen(hexStr);

    int sum = 0;
    for (size_t i = 0, expoent = hexStrLength - 1; i < hexStrLength; ++i, --expoent) {
        int value = hexChar2dec(hexStr[i]);
        sum += value * pow(16, expoent);
    }

    return sum;
}

struct Color {
private:
    int enforceInterval(int value) {
        if (value < 0) return 0;
        if (value > 255) return 255;
        return value;
    }
public:
    int red;
    int green;
    int blue;
    int alpha;

    Color(std::string colorStr) {
        if (colorStr.size() <= 0) { 
            red = green = blue = alpha = 0;
            return; 
        }

        if (colorStr[0] == '#') {
            colorStr.erase(0, 1);
        }
        const size_t colorStrSize = colorStr.size();
        int charsPerNumber = floor(colorStrSize / 3.f);
        bool hasAlpha = (fmod(colorStrSize, 3.f) != 0);
        red   = hex2dec(colorStr.substr(0*charsPerNumber, charsPerNumber));
        green = hex2dec(colorStr.substr(1*charsPerNumber, charsPerNumber));
        blue  = hex2dec(colorStr.substr(2*charsPerNumber, charsPerNumber));
        alpha = (hasAlpha) ? hex2dec(colorStr.substr(3*charsPerNumber, charsPerNumber)) : 255;
        red = enforceInterval(red);
        green = enforceInterval(green);
        blue = enforceInterval(blue);
        alpha = enforceInterval(alpha);
    }

    Color(int red, int green, int blue, int alpha = 255) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }
};

#endif
