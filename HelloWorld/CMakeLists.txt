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

#---------------------------------------#
#				SOURCES					#
#---------------------------------------#
file(GLOB_RECURSE HW_SOURCES "Code/src/*.cpp")

add_executable(HelloWorld ${HW_SOURCES})

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