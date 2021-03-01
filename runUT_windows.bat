mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_USE_OPENSSL=ON -Dgtest_force_shared_crt=ON CMAKE_PREFIX_PATH=C:\\Qt\\5.15.2\\msvc2019_64
cmake --build .
ctest -V