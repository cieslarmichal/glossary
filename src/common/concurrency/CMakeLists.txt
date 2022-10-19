set(SOURCES
        src/SupportedThreadsCalculator.cpp
        )

add_library(concurrency ${SOURCES})

target_include_directories(concurrency
        PUBLIC "include"
        PRIVATE "include/concurrency"
        )

target_compile_options(concurrency PUBLIC ${FLAGS})
