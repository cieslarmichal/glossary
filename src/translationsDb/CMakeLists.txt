set(SOURCES
        src/TranslationsDbImpl.cpp
        src/TranslationsSerializerImpl.cpp
        src/TranslationsMemoryStorage.cpp
        src/TranslationsPersistentStorage.cpp
        src/TranslationsDbFactory.cpp
        src/TranslationsDbFactoryImpl.cpp)

set(UT_SOURCES
        src/TranslationsDbImplTest.cpp
        src/TranslationsSerializerImplTest.cpp
        src/TranslationsMemoryStorageTest.cpp
        src/TranslationsPersistentStorageTest.cpp)

add_library(translationsDb ${SOURCES})
add_executable(translationsDbUT ${UT_SOURCES} ${SOURCES})

target_include_directories(translationsDb PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/translationsDb")
target_include_directories(translationsDbUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/translationsDb")

target_link_libraries(translationsDb PRIVATE utils)
target_link_libraries(translationsDbUT PRIVATE gtest_main gmock utils)

target_compile_options(translationsDb PUBLIC ${FLAGS})
target_compile_options(translationsDbUT PUBLIC -Wall -Wextra -Werror)

add_test(translationsDbUT ${EXECUTABLE_OUTPUT_PATH}/translationsDbUT --gtest_color=yes)
