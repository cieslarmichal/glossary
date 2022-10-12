env:
C_COMPILER=gcc-8
CXX_COMPILER=g++-8

mkdir build
cd build || exit
env CC=${C_COMPILER} CXX=${CXX_COMPILER} cmake .. -DENABLE_COVERAGE:BOOL=TRUE -DCMAKE_BUILD_TYPE=DEBUG CMAKE_PREFIX_PATH=/home/michal/Qt5/5.15.2/gcc_64
echo "We have" $(nproc) "cores here"
make
ctest -V
