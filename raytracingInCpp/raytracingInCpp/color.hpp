#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void writeColor(std::ostream& out, color pixelColor, int const samplesPerPixel) {
    double red{ pixelColor.x() };
    double green{ pixelColor.y() };
    double blue{ pixelColor.z() };

    double const scale{ 1.0 / static_cast<double>(samplesPerPixel) };
    red   = 65536.0 * clamp(sqrt(scale * red), 0.0, 0.999999);
    green = 65536.0 * clamp(sqrt(scale * green), 0.0, 0.999999);
    blue  = 65536.0 * clamp(sqrt(scale * blue), 0.0, 0.999999);


    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(red) << ' '
        << static_cast<int>(green) << ' '
        << static_cast<int>(blue) << '\n';

}

#endif