set(SOURCES
        src/CurlHttpClient.cpp
        src/HttpClientFactory.cpp
        src/DefaultHttpClientFactory.cpp)

set(UT_SOURCES
        src/CurlHttpClientTest.cpp)

add_library(httpClient ${SOURCES})
add_executable(httpClientUT ${SOURCES} ${UT_SOURCES})

target_include_directories(httpClient
        PUBLIC
        "include"
        PRIVATE
        "include/httpClient"
        ${CURL_INCLUDE_DIR}
        )
target_include_directories(httpClientUT
        PRIVATE
        "include"
        "include/httpClient"
        ${GTEST_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        )

target_link_libraries(httpClient
        PUBLIC
        libcurl
        utils
        )
target_link_libraries(httpClientUT
        PUBLIC
        libcurl
        gtest_main
        utils
        )

target_compile_options(httpClient PUBLIC ${FLAGS})
target_compile_options(httpClientUT PUBLIC ${FLAGS})

add_test(httpClientUT httpClientUT --gtest_color=yes)
