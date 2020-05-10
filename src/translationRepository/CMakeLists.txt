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
add_executable(translationRepositoryUT ${UT_SOURCES})

target_include_directories(translationRepository
        PUBLIC "include"
        PRIVATE ${JSON_INCLUDE_DIR} "include/translationRepository"
        )
target_include_directories(translationRepositoryUT PRIVATE
        "include"
        ${INTERNAL_LIBS_INCLUDE_PATH}
        ${JSON_INCLUDE_DIR}
        "include/translationRepository"
        )

target_link_libraries(translationRepository PUBLIC utils)
target_link_libraries(translationRepositoryUT PRIVATE
        gtest_main
        gmock
        utils 
        translationRepository
        )

target_compile_options(translationRepository PUBLIC ${FLAGS})
target_compile_options(translationRepositoryUT PUBLIC -Wall -Wextra -Werror)

add_test(translationRepositoryUT translationRepositoryUT --gtest_color=yes)
