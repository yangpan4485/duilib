# CMake root file for duilib related apps
#Date 2012-09-16
#Author: Qi Gao(monkgau@gmail.com)
#
#  CMake files for duilib
#  file for each app is under the related sub-dir
#

cmake_minimum_required(VERSION 3.6)

project(dui)

message(STATUS," CMake project files for duilib")

# this line is for UNICODE release,which is required by DuiDesigner 
add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output/bin)

# add each CMake file
add_subdirectory(duilib)
add_subdirectory(360SafeDemo)
add_subdirectory(FlashDemo)
# add_subdirectory(GameDemo)
add_subdirectory(ListDemo)
# add_subdirectory(MenuDemo) the sources in this project has error
# add_subdirectory(QQDemo)
add_subdirectory(RichListDemo)
