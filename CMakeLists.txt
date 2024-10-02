project(mnasm)
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.29)
set(CMAKE_CXX_STANDARD 17)

add_executable(mnasm
    src/main.cpp
    src/server/server.cpp
)

target_link_libraries(mnasm curl)
