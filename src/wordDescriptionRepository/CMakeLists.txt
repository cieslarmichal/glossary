set(SOURCES
        src/DefaultWordDescriptionRepository.cpp
        src/WordsDescriptionsMemoryStorage.cpp
        src/WordsDescriptionsPersistentStorage.cpp
        src/WordsDescriptionsJsonSerializer.cpp
        src/WordDescriptionRepositoryFactory.cpp
        src/DefaultWordDescriptionRepositoryFactory.cpp
        )

set(UT_SOURCES
        src/DefaultWordDescriptionRepositoryTest.cpp
        src/WordsDescriptionsMemoryStorageTest.cpp
        src/WordsDescriptionsPersistentStorageTest.cpp
        src/WordsDescriptionsJsonSerializerTest.cpp
        )

add_library(wordDescriptionRepository ${SOURCES})
add_executable(wordDescriptionRepositoryUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(wordDescriptionRepositoryUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(wordDescriptionRepository
        PUBLIC
        "include"
        PRIVATE
        "include/wordDescriptionRepository"
        ${Boost_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        )
target_include_directories(wordDescriptionRepositoryUT
        PRIVATE
        "include"
        "include/wordDescriptionRepository"
        ${Boost_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        )

target_link_libraries(wordDescriptionRepository PUBLIC utils)
target_link_libraries(wordDescriptionRepositoryUT PRIVATE
        gmock_main
        gtest
        utils
        )

target_compile_options(wordDescriptionRepository PUBLIC ${FLAGS})
target_compile_options(wordDescriptionRepositoryUT PUBLIC)

add_test(wordDescriptionRepositoryUT wordDescriptionRepositoryUT --gtest_color=yes)

