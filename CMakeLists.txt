project(mnasm)
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.29)
set(CMAKE_CXX_STANDARD 17)

add_executable(mnasm
    src/main.cpp
    src/server/server.cpp
    src/server/init.cpp
    src/getconf.cpp
    src/mnt.cpp
    src/getvar.cpp
    src/handler/mnt.cpp
    src/handler/chdir.cpp
    src/handler/fileio.cpp
    src/handler/sys.cpp
)

target_link_libraries(mnasm curl)
