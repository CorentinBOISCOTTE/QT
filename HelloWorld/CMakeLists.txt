cmake_minimum_required(VERSION 3.29.0)

# --------------------------------------- #
#              FIND PACKAGES              #
# --------------------------------------- #
# Output directories
set(OUTPUT_DIR_BASE "${CMAKE_SOURCE_DIR}/Builds/${CMAKE_CXX_COMPILER_ID}")

message(STATUS "[${PROJECT_NAME}]: Base output directory: ${OUTPUT_DIR_BASE}")

# Use generator expressions directly in output variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR_BASE}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR_BASE}/$<CONFIG>/libs")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR_BASE}/$<CONFIG>/libs")

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

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#---------------------------------------#
#				SOURCES					#
#---------------------------------------#
file(GLOB_RECURSE HW_SOURCES "Code/src/*.cpp")

add_executable(HelloWorld ${HW_SOURCES})

target_link_libraries(HelloWorld PRIVATE Qt6::Widgets)

target_include_directories(HelloWorld PRIVATE "Code/include")

#---------------------------------------#
#                COMPILE MODE           #
#---------------------------------------#
target_compile_features(HelloWorld PUBLIC cxx_std_23)

if (MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    target_compile_options(HelloWorld PUBLIC /W4 /WX)
else ()
    target_compile_options(HelloWorld PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif ()

# Build position independent code.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable C and C++ compiler extensions.
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)