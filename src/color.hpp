#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

#include <string>
#include <cstring>
#include <cmath>

struct Color {
    int red;
    int green;
    int blue;
    int alpha;

    Color(std::string colorStr);
    Color(int red, int green, int blue, int alpha);

private:
    int enforceInterval(int value);
};

#endif
