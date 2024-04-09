cmake_minimum_required(VERSION 3.10)
project(face_detection_library)

# Set the target platform and architecture
set(ANDROID_PLATFORM android-24 CACHE STRING "ANDROID_PLATFORM")
#message("ANDROID_PLATFORM: ${ANDROID_PLATFORM}")
set(ANDROID_ARCH arm64-v8a)  # Adjust the architecture as needed (e.g., arm64-v8a, x86, x86_64)

# Set additional Android-specific options
set(ANDROID_ABI ${ANDROID_ARCH} CACHE STRING "Target Android ABI")

set(ANDROID_STL c++_shared)
set(ANDROID_CPP_FEATURES rtti exceptions)

# Set path to Android NDK (replace with your actual NDK path)
set(ANDROID_NDK /Users/robevans/Library/Android/sdk/ndk/26.2.11394342)

# Set the path to the Android toolchain file
set(ANDROID_TOOLCHAIN_FILE ${ANDROID_NDK}/build/cmake/android.toolchain.cmake)

set(OpenCV_DIR "/Users/robevans/dev/3rd party/opencv_${ANDROID_ARCH}")

find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add subdirectory containing source code
add_subdirectory(src)

# Set output directory for shared libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/${ANDROID_ARCH} CACHE STRING "cmake libs directory")

# Set library type to shared
set(BUILD_SHARED_LIBS ON)

message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")