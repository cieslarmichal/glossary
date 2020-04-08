set(SOURCES
        src/DefaultWordDescriptionRepository.cpp
        src/WordsDescriptionsMemoryStorage.cpp
        src/WordsDescriptionsPersistentStorage.cpp
        src/WordsDescriptionsJsonSerializer.cpp
        src/DescriptionSerializer.cpp
        src/WordDescriptionRepositoryFactory.cpp
        src/DefaultWordDescriptionRepositoryFactory.cpp
        )

set(UT_SOURCES
        src/DefaultWordDescriptionRepositoryTest.cpp
        src/WordsDescriptionsMemoryStorageTest.cpp
        src/WordsDescriptionsPersistentStorageTest.cpp
        src/WordsDescriptionsJsonSerializerTest.cpp
        src/DescriptionSerializerTest.cpp)

add_library(wordDescriptionRepository ${SOURCES})
add_executable(wordDescriptionRepositoryUT ${UT_SOURCES})

target_include_directories(wordDescriptionRepository PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/wordDescriptionRepository")
target_include_directories(wordDescriptionRepositoryUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/wordDescriptionRepository")

target_link_libraries(wordDescriptionRepository PUBLIC utils)
target_link_libraries(wordDescriptionRepositoryUT PRIVATE gtest_main gmock wordDescriptionRepository utils)

target_compile_options(wordDescriptionRepository PUBLIC ${FLAGS})
target_compile_options(wordDescriptionRepositoryUT PUBLIC -Wall -Wextra -Werror)

add_test(wordDescriptionRepositoryUT wordDescriptionRepositoryUT --gtest_color=yes)

