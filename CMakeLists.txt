cmake_minimum_required(VERSION 3.10)
project(Norden)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-g") 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/lib)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo cairomm-1.0)
pkg_check_modules(PANGO REQUIRED pango pangomm-1.4)

add_executable(Norden ${SOURCES})

target_link_libraries(Norden ${CAIRO_LIBRARIES} ${PANGO_LIBRARIES} SDL2 GL GLEW)

target_include_directories(Norden PRIVATE ${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

target_compile_options(Norden PRIVATE ${CAIRO_CFLAGS_OTHER} ${PANGO_CFLAGS_OTHER})
