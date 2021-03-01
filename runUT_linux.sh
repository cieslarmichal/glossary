env:
C_COMPILER=gcc-8
CXX_COMPILER=g++-8

mkdir build
cd build
env CC=${C_COMPILER} CXX=${CXX_COMPILER} cmake .. -DENABLE_COVERAGE:BOOL=TRUE -DCMAKE_BUILD_TYPE=DEBUG
echo "We have" `nproc` "cores here"
make
ctest -V
