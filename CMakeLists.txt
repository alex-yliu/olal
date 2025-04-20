cmake_minimum_required(VERSION 3.22)
project(olal_core)

# Allow multiple build targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Conan setup
# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
# include(${CMAKE_BINARY_DIR}/conan_deps.cmake)
find_package(fmt REQUIRED)
find_package(libsodium REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(luajit REQUIRED)
find_package(GTest REQUIRED)
find_package(SQLite3 REQUIRED)

# Source files
file(GLOB_RECURSE SRC src/*.cpp)

# Shared library
add_library(olal_core SHARED ${SRC})
target_link_libraries(olal_core
    fmt::fmt
    spdlog::spdlog
    Boost::boost
    libsodium::libsodium
    OpenSSL::SSL
    OpenSSL::Crypto
    luajit::luajit
    SQLite::SQLite3
)

# Executable
add_executable(olal_cli ${SRC})
target_link_libraries(olal_cli PRIVATE olal_core)

# WASM target
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_executable(olal_web ${SRC})
    target_link_libraries(olal_web PRIVATE
        fmt::fmt
        spdlog::spdlog
        libsodium::libsodium
        luajit::luajit
        SQLite::SQLite3
    )
    set_target_properties(olal_web PROPERTIES
        LINK_FLAGS "--bind -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME=createCryptoModule -s ALLOW_MEMORY_GROWTH=1"
    )
endif()

enable_testing()
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_executable(olal_tests ${TEST_SOURCES})
target_link_libraries(olal_tests
    olal_core
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(olal_tests)
