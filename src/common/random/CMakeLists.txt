set(SOURCES
        src/RandomNumberMersenneTwisterGenerator.cpp
        src/RandomNumberGeneratorFactory.cpp
        )

add_library(random ${SOURCES})

target_include_directories(random
        PUBLIC "include"
        PRIVATE "include/random"
        )

target_compile_options(random PUBLIC ${FLAGS})
