set(SOURCES
        src/DefaultWordsDescriptionsDb.cpp
        src/WordsDescriptionsMemoryStorage.cpp
        src/WordsDescriptionsPersistentStorage.cpp
        src/WordsDescriptionsJsonSerializer.cpp
        src/DescriptionSerializer.cpp
        src/WordsDescriptionsDbFactory.cpp
        src/DefaultWordsDescriptionsDbFactory.cpp
        )

set(UT_SOURCES
        src/DefaultWordsDescriptionsDbTest.cpp
        src/WordsDescriptionsMemoryStorageTest.cpp
        src/WordsDescriptionsPersistentStorageTest.cpp
        src/WordsDescriptionsJsonSerializerTest.cpp
        src/DescriptionSerializerTest.cpp)

add_library(wordsDescriptionsDb ${SOURCES})
add_executable(wordsDescriptionsDbUT ${UT_SOURCES})

target_include_directories(wordsDescriptionsDb PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/wordsDescriptionsDb")
target_include_directories(wordsDescriptionsDbUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/wordsDescriptionsDb")

target_link_libraries(wordsDescriptionsDb PRIVATE utils)
target_link_libraries(wordsDescriptionsDbUT PRIVATE gtest_main gmock wordsDescriptionsDb utils)

target_compile_options(wordsDescriptionsDb PUBLIC ${FLAGS})
target_compile_options(wordsDescriptionsDbUT PUBLIC -Wall -Wextra -Werror)

add_test(wordsDescriptionsDbUT wordsDescriptionsDbUT --gtest_color=yes)

