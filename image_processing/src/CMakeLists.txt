# Add library target
add_library(detect_faces SHARED facefinder.cpp)

target_link_libraries(detect_faces PRIVATE ${OpenCV_LIBS})

# Include directories
target_include_directories(detect_faces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
