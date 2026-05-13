cmake_minimum_required(VERSION 3.16)

# set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-15)
# set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-15)

project(TerminalUI)

set(CMAKE_CXX_STANDARD 20)

# FTXUI (still using FetchContent is fine)
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG dfe9318009c9767256af692d506cf7f646d400e6
)

FetchContent_MakeAvailable(ftxui)

# Disable building tests, examples, and apps to save TONS of time
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)

# OpenCV (MANUAL ADD)
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/opencv)

add_subdirectory(opencv)

add_executable(main test2.cpp)

target_include_directories(main PRIVATE 
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/opencv

   ${CMAKE_SOURCE_DIR}/opencv/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/core/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/imgproc/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/imgcodecs/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/highgui/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/videoio/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/video/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/calib3d/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/features2d/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/objdetect/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/dnn/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/ml/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/flann/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/photo/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/stitching/include
    ${CMAKE_SOURCE_DIR}/opencv/modules/gapi/include
)

# 3. Link (ensure names match the internal OpenCV targets)
target_link_libraries(main PRIVATE
    ftxui::screen ftxui::dom ftxui::component

    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
    opencv_videoio
    opencv_video
    opencv_calib3d
    opencv_features2d
    opencv_objdetect
    opencv_dnn
    opencv_ml
    opencv_flann
    opencv_photo
    opencv_stitching
)