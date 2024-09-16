cmake_minimum_required(VERSION 3.9)

project(Browser)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)


option(MyHTML_BUILD_WITHOUT_THREADS "Build without POSIX Threads" ON)
option(MyCORE_BUILD_WITHOUT_THREADS "Build MyCORE without POSIX Threads" ON)
option(MyHTML_BUILD_SHARED "Build shared library" OFF)
option(MyHTML_BUILD_STATIC "Build static library" ON)
option(MyHTML_INSTALL_HEADER "Install header files" OFF)
add_subdirectory(libs/myhtml)

add_executable(Browser main.cpp
               inc/Browser/Thickness.h
               inc/Browser/Color.h
               inc/Browser/TextSize.h
               inc/Browser/StyleProperty.h
               inc/Browser/Style.h
               inc/Browser/Elements/PageElement.h
               src/PageElement.cpp
               inc/Browser/Renderer.h
               src/Renderer.cpp
               inc/Browser/Tools.h
               inc/Browser/Document.h
               src/Document.cpp
               inc/Browser/FontDescription.h
               inc/Browser/Elements/TextElement.h
               inc/Browser/DisplayType.h
               inc/Browser/Rect.h
               src/TextElement.cpp
               inc/Browser/StyleFactory.h
               src/StyleFactory.cpp
               inc/Browser/Cursor.h
               inc/Browser/BoxedValue.h
               inc/Browser/BoxedValue.inl
               src/Style.cpp
               inc/Browser/Point.h)

target_include_directories(Browser PRIVATE inc/ libs/ libs/myhtml/include/)
target_link_libraries(Browser PRIVATE SDL2::SDL2 d2d1 dwrite myhtml_static wininet)

configure_file(${CMAKE_SOURCE_DIR}/web.html ${CMAKE_BINARY_DIR}/web.html COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/default.css ${CMAKE_BINARY_DIR}/default.css COPYONLY)