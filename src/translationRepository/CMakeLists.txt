set(SOURCES
        src/DefaultTranslationRepository.cpp
        src/TranslationsJsonSerializer.cpp
        src/TranslationsMemoryStorage.cpp
        src/TranslationsPersistentStorage.cpp
        src/TranslationRepositoryFactory.cpp
        src/DefaultTranslationRepositoryFactory.cpp)

set(UT_SOURCES
        src/DefaultTranslationRepositoryTest.cpp
        src/TranslationsJsonSerializerTest.cpp
        src/TranslationsMemoryStorageTest.cpp
        src/TranslationsPersistentStorageTest.cpp)

add_library(translationRepository ${SOURCES})
add_executable(translationRepositoryUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(translationRepositoryUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(translationRepository
        PUBLIC
        "include"
        PRIVATE
        "include/translationRepository"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(translationRepositoryUT PRIVATE
        "include"
        "include/translationRepository"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(translationRepository PUBLIC utils)
target_link_libraries(translationRepositoryUT PRIVATE
        gmock_main
        gtest
        utils
        )

target_compile_options(translationRepository PUBLIC ${FLAGS})
target_compile_options(translationRepositoryUT PUBLIC)

add_test(translationRepositoryUT translationRepositoryUT --gtest_color=yes)
