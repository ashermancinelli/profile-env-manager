add_executable(profile main.cpp)
target_link_libraries(profile PRIVATE plib utils)
target_include_directories(profile PRIVATE ${PROJECT_SOURCE_DIR})
