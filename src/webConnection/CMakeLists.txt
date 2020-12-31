set(SOURCES
        src/CurlHttpHandler.cpp
        src/HttpHandlerFactory.cpp
        src/DefaultHttpHandlerFactory.cpp)

set(UT_SOURCES
        src/CurlHttpHandlerTest.cpp)

add_library(webConnection ${SOURCES})
add_executable(webConnectionUT ${SOURCES} ${UT_SOURCES})

target_include_directories(webConnection
        PUBLIC
        "include"
        PRIVATE
        "include/webConnection"
        ${CURL_INCLUDE_DIR}
        )
target_include_directories(webConnectionUT
        PRIVATE
        "include"
        "include/webConnection"
        ${GTEST_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        )

target_link_libraries(webConnection
        PUBLIC
        libcurl
        utils
        )
target_link_libraries(webConnectionUT
        PUBLIC
        libcurl
        gtest_main
        utils
        )

target_compile_options(webConnection PUBLIC ${FLAGS})
target_compile_options(webConnectionUT PUBLIC ${FLAGS})

add_test(webConnectionUT webConnectionUT --gtest_color=yes)
