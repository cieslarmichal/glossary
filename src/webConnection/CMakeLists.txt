set(SOURCES
        src/HttpHandlerImpl.cpp
        src/HttpHandlerFactory.cpp
        src/HttpHandlerFactoryImpl.cpp)

set(UT_SOURCES
        src/HttpHandlerTest.cpp)

add_library(webConnection ${SOURCES})
add_executable(webConnectionUT ${UT_SOURCES})

target_include_directories(webConnection PUBLIC "include" PRIVATE "include/webConnection")
target_include_directories(webConnectionUT PRIVATE "include" PRIVATE "include/webConnection")

target_link_libraries(webConnection PUBLIC -lcurl utils)
target_link_libraries(webConnectionUT PRIVATE gtest_main gmock webConnection)

target_compile_options(webConnection PUBLIC ${FLAGS})
target_compile_options(webConnectionUT PUBLIC -Wall -Wextra -Werror)

add_test(webConnectionUT webConnectionUT --gtest_color=yes)
