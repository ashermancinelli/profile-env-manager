add_library(utils OBJECT utils.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(utils
  PUBLIC
  plib
  nlohmann_json::nlohmann_json)
