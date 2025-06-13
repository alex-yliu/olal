cmake_minimum_required(VERSION 3.22)
project(olal_core)

# Allow multiple build targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/")
find_package(PkgConfig REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)
find_package(liboqs CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(Bitsery CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

pkg_check_modules(LUAJIT REQUIRED luajit)

# foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
# string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/bin)
# endforeach()

# Source files
file(GLOB_RECURSE SRC src/**.cpp)

# Shared library
add_library(olal_core SHARED ${SRC})
target_include_directories(olal_core PUBLIC
    ${LUAJIT_INCLUDE_DIRS}
)
target_link_directories(olal_core PUBLIC
    ${LUAJIT_LIBRARY_DIRS}
)
target_link_libraries(olal_core PUBLIC
    fmt::fmt-header-only
    spdlog::spdlog_header_only
    Boost::boost
    unofficial-sodium::sodium
    OQS::oqs
    OpenSSL::SSL
    OpenSSL::Crypto
    ${LUAJIT_LIBRARIES}
    unofficial::sqlite3::sqlite3
    Bitsery::bitsery
)

# Executable
add_executable(olal_cli ${SRC})
target_link_libraries(olal_cli PRIVATE olal_core)

# WASM target
# if(EMSCRIPTEN)
# set(CMAKE_EXECUTABLE_SUFFIX ".html")
# add_executable(olal_web ${SRC})
# target_link_libraries(olal_web PRIVATE
# fmt::fmt
# spdlog::spdlog
# Boost::boost
# libsodium::libsodium
# luajit::luajit
# SQLite::SQLite3
# Bitsery::bitsery
# )
# set_target_properties(olal_web PROPERTIES
# LINK_FLAGS "--bind -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME=createCryptoModule -s ALLOW_MEMORY_GROWTH=1"
# )
# endif()

# enable_testing()
# file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

# add_executable(olal_tests ${TEST_SOURCES})
# target_link_libraries(olal_tests
# olal_core
# GTest::gtest
# GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(olal_tests)
