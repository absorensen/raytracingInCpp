#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void writeColor(std::ostream& out, color pixelColor, int const samplesPerPixel) {
    double red{ pixelColor.x() };
    double green{ pixelColor.y() };
    double blue{ pixelColor.z() };

    double const scale{ 1.0 / static_cast<double>(samplesPerPixel) };
    red   = sqrt(scale * red);
    green = sqrt(scale * green);
    blue  = sqrt(scale * blue);


    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256.0 * clamp(red,   0.0, 0.999999)) << ' '
        << static_cast<int>(256.0 * clamp(green, 0.0, 0.999999)) << ' '
        << static_cast<int>(256.0 * clamp(blue,  0.0, 0.999999)) << '\n';

}

#endif