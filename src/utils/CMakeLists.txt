set(SOURCES
        src/HtmlTagsDeleter.cpp
        src/FileAccessImpl.cpp
        src/StringHelper.cpp)

set(UT_SOURCES
        src/HtmlTagsDeleterTest.cpp
        src/FileAccessImplTest.cpp
        src/StringHelperTest.cpp)


add_library(utils ${SOURCES})
add_executable(utilsUT ${UT_SOURCES} ${SOURCES})

target_include_directories(utils PUBLIC "include" PRIVATE "include/utils")
target_include_directories(utilsUT PRIVATE "include" "include/utils")

target_link_libraries(utilsUT PRIVATE gtest_main gmock)

target_compile_options(utils PUBLIC ${FLAGS})
target_compile_options(utilsUT PUBLIC -Wall -Wextra -Werror)

add_test(utilsUT ${EXECUTABLE_OUTPUT_PATH}/utilsUT --gtest_color=yes)
