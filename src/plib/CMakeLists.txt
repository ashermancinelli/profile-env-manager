add_library(plib OBJECT profile.cpp)
target_include_directories(plib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../utils
  )
target_link_libraries(plib PRIVATE nlohmann_json::nlohmann_json)
