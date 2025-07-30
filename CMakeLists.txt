cmake_minimum_required(VERSION 3.29.0 FATAL_ERROR)

project(QT-tests VERSION 1.0.0 LANGUAGES CXX)

find_program(QT_QMAKE_EXECUTABLE qmake)

if(QT_QMAKE_EXECUTABLE)
    message(STATUS "qmake found: ${QT_QMAKE_EXECUTABLE}")
    
    execute_process(
        COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PREFIX
        OUTPUT_VARIABLE QT_INSTALL_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    list(APPEND CMAKE_PREFIX_PATH "${QT_INSTALL_PREFIX}/lib/cmake")
    message(STATUS "Qt installed here: ${QT_INSTALL_PREFIX}")
else()
    message(WARNING "qmake was not found in the PATH. Qt will not be automatically detected.")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(HelloWorld)