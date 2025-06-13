# Olal cryptocurrency

install vcpkg as mentioned online.

Define UserMakeUserPresets.json

```
{
    "version": 4,
    "configurePresets": [
        {
            "name": "default",
            "inherits": "vcpkg",
            "environment": {
                "VCPKG_ROOT": "/path/to/folder/of/vcpkg"
            }
        }
    ]
}
```

- `brew install ninja autoconf automake libtool autoconf-archive`
- `brew install pkg-config`

Then to build the project

First preset: 

- `cmake --preset=default`
- `cmake --build build`

# CMake config

bitsery provides CMake targets:

  # this is heuristically generated, and may not be correct
  find_package(Bitsery CONFIG REQUIRED)
  target_link_libraries(main PRIVATE Bitsery::bitsery)

sqlite3 provides pkgconfig bindings.
sqlite3 provides CMake targets:

    find_package(unofficial-sqlite3 CONFIG REQUIRED)
    target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)

openssl is compatible with built-in CMake targets:

  find_package(OpenSSL REQUIRED)
  target_link_libraries(main PRIVATE OpenSSL::SSL)
  target_link_libraries(main PRIVATE OpenSSL::Crypto)

The package fmt provides CMake targets:

    find_package(fmt CONFIG REQUIRED)
    target_link_libraries(main PRIVATE fmt::fmt)

    # Or use the header-only version
    find_package(fmt CONFIG REQUIRED)
    target_link_libraries(main PRIVATE fmt::fmt-header-only)

The package gtest is compatible with built-in CMake targets:

    enable_testing()
    
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
    
    add_test(AllTestsInMain main)

libsodium provides CMake targets:

  # this is heuristically generated, and may not be correct
  find_package(unofficial-sodium CONFIG REQUIRED)
  target_link_libraries(main PRIVATE unofficial-sodium::sodium)

libsodium provides pkg-config modules:

  # A modern and easy-to-use crypto library
  libsodium

luajit provides pkg-config modules:

  # Just-in-time compiler for Lua
  luajit

The package spdlog provides CMake targets:

    find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(main PRIVATE spdlog::spdlog)

    # Or use the header-only version
    find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(main PRIVATE spdlog::spdlog_header_only)

liboqs provides CMake targets:

  # this is heuristically generated, and may not be correct
  find_package(liboqs CONFIG REQUIRED)
  target_link_libraries(main PRIVATE OQS::oqs)

liboqs provides pkg-config modules:

  # Library for quantum-safe cryptographic algorithms
  liboqs


# Additional

- Would you like to break out a SmartContractVM C++ class to better encapsulate Lua interaction? 
- Would you like the .cpp implementations for Account and Transaction?
- Want me to scaffold unit tests?
- Shall we begin wiring this up with Lua smart contract hooks?

When $a \ne 0$, there are two solutions to $(ax^2 + bx + c = 0)$ and they are
$$ x = {-b \pm \sqrt{b^2-4ac} \over 2a} $$