# Olal cryptocurrency

Following are in the `build` folder.

- `rm -rf build && mkdir build`
- In root folder: `conan install . --output-folder=build --build=missing`
- `cd build`
- `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`
- `cmake --build .`
- `ctest --output-on-failure`


# Resources

- Autotools: https://opensource.com/article/19/7/introduction-gnu-autotools


# Additional

- Would you like to break out a SmartContractVM C++ class to better encapsulate Lua interaction? 

When $a \ne 0$, there are two solutions to $(ax^2 + bx + c = 0)$ and they are
$$ x = {-b \pm \sqrt{b^2-4ac} \over 2a} $$