add_library(plib profile.cpp)
target_include_directories(plib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(plib PRIVATE nlohmann_json::nlohmann_json)
