# CMakeList.txt : CMake project for Kubrick, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Kubrick 
"kubrick.cpp" 
"kubrick.hpp" 
"stb_image.h" 
"stb_image_write.h" 
"vec3.hpp" 
"color.hpp"
"ray.hpp" 
"hittable.hpp" 
"sphere.hpp" 
"hittableList.hpp" 
"utility.hpp"
)

# TODO: Add tests and install targets if needed.
