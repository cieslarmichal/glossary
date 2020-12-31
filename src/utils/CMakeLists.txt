set(SOURCES
        src/HtmlTagsDeleter.cpp
        src/DefaultFileAccess.cpp
        src/StringHelper.cpp
        src/GetProjectPath.cpp
        src/GetExecutablePath.cpp
        src/FileAccessFactory.cpp
        src/DefaultFileAccessFactory.cpp
        src/FileExtensionsFilter.cpp
        src/FilenamePathFilter.cpp
        src/RandomNumberMersenneTwisterGenerator.cpp
        src/SupportedThreadsCalculator.cpp
        include/utils/StlOperators.h
        )

set(UT_SOURCES
        src/HtmlTagsDeleterTest.cpp
        src/DefaultFileAccessTest.cpp
        src/StringHelperTest.cpp
        src/GetExecutablePathTest.cpp
        src/GetProjectPathTest.cpp
        src/ThreadSafeQueueTest.cpp
        src/FileExtensionsFilterTest.cpp
        src/FilenamePathFilterTest.cpp
        src/RandomNumberMersenneTwisterGeneratorTest.cpp
        )


add_library(utils ${SOURCES})
add_executable(utilsUT ${SOURCES} ${UT_SOURCES})

target_include_directories(utils
        PUBLIC "include"
        PRIVATE "include/utils"
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(utilsUT PRIVATE
        "include"
        "include/utils"
        ${Boost_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        )

target_link_libraries(utils PUBLIC)

target_link_libraries(utilsUT PRIVATE
        gtest_main
        )

target_compile_options(utils PUBLIC ${FLAGS})
target_compile_options(utilsUT PUBLIC ${FLAGS})

add_test(utilsUT utilsUT --gtest_color=yes)
