set(SOURCES
        src/WordsDescriptionsDbImpl.cpp
        src/WordsDescriptionsMemoryStorage.cpp
        src/WordsDescriptionsPersistentStorage.cpp
        src/WordsDescriptionsSerializerImpl.cpp
        src/DescriptionSerializer.cpp
        src/WordsDescriptionsDbFactory.cpp
        src/WordsDescriptionsDbFactoryImpl.cpp)

set(UT_SOURCES
        src/WordsDescriptionsDbImplTest.cpp
        src/WordsDescriptionsMemoryStorageTest.cpp
        src/WordsDescriptionsPersistentStorageTest.cpp
        src/WordsDescriptionsSerializerImplTest.cpp
        src/DescriptionSerializerTest.cpp)

add_library(wordsDescriptionsDb ${SOURCES})
add_executable(wordsDescriptionsDbUT ${UT_SOURCES})

target_include_directories(wordsDescriptionsDb PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/wordsDescriptionsDb" ${PLOG_INCLUDE_DIR})
target_include_directories(wordsDescriptionsDbUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/wordsDescriptionsDb")

target_link_libraries(wordsDescriptionsDb PRIVATE utils)
target_link_libraries(wordsDescriptionsDbUT PRIVATE gtest_main gmock wordsDescriptionsDb utils)

target_compile_options(wordsDescriptionsDb PUBLIC ${FLAGS})
target_compile_options(wordsDescriptionsDbUT PUBLIC -Wall -Wextra -Werror)

add_test(wordsDescriptionsDbUT wordsDescriptionsDbUT --gtest_color=yes)

