set(SOURCES
        src/SupportedThreadsCalculator.cpp
        )

add_library(concurrency ${SOURCES})

target_include_directories(concurrency
        PUBLIC "include"
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(concurrency PUBLIC)

target_compile_options(concurrency PUBLIC ${FLAGS})
