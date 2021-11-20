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
"camera.hpp" 
"material.hpp"
)

target_compile_definitions(Kubrick PRIVATE NDEBUG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
if(CMAKE_BUILD_TYPE MATCHES "Release" OR CMAKE_BUILD_TYPE MATCHES "ReleaseWithDebInfo")
	# Optimization options for C/C++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Ob2 /Ot /Oi /Gy /MP")
	# Optimization options for C/C++ Linkers
	set_property(TARGET Kubrick APPEND PROPERTY LINK_FLAGS "/OPT:REF /OPT:ICF")

	set_target_properties(Kubrick PROPERTIES COMPILE_FLAGS "$<$<CONFIG:Release>:/GL>")
	set_target_properties(Kubrick PROPERTIES LINK_FLAGS "$<$<CONFIG:Release>:/LTCG>")
	
	set_target_properties(Kubrick PROPERTIES COMPILE_FLAGS "/GL")
	set_target_properties(Kubrick PROPERTIES LINK_FLAGS "/LTCG")
endif(CMAKE_BUILD_TYPE MATCHES "Release" OR CMAKE_BUILD_TYPE MATCHES "ReleaseWithDebInfo")
endif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

# TODO: Add tests and install targets if needed.
