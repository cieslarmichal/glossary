set(SOURCES
        src/repositories/DefaultDictionaryRepository.cpp
        src/repositories/DictionaryMemoryStorage.cpp
        src/repositories/DictionaryPersistentStorage.cpp
        src/serializers/DictionaryJsonSerializer.cpp
        src/readers/DictionaryWordsCsvReaderImpl.cpp
        src/repositories/DefaultWordDescriptionRepository.cpp
        src/repositories/WordsDescriptionsMemoryStorage.cpp
        src/repositories/WordsDescriptionsPersistentStorage.cpp
        src/serializers/WordsDescriptionsJsonSerializer.cpp
        src/clients/WordsApiClientImpl.cpp
        src/queries/GetDictionaryQueryImpl.cpp
        src/queries/GetDictionariesQueryImpl.cpp
        src/queries/GetDictionariesNamesQueryImpl.cpp
        src/queries/GetDictionaryEnglishWordsQueryImpl.cpp
        src/queries/GetDictionariesEnglishWordsQueryImpl.cpp
        src/queries/GetRandomWordFromDictionaryQueryImpl.cpp
        src/queries/GetRandomWordFromDictionariesQueryImpl.cpp
        src/queries/GetWordDescriptionQueryImpl.cpp
        src/commands/CreateDictionaryCommandImpl.cpp
        src/commands/CreateDictionaryFromCsvFileCommandImpl.cpp
        src/commands/AddWordToDictionaryCommandImpl.cpp
        src/commands/RemoveWordFromDictionaryCommandImpl.cpp
        src/commands/UpdateWordTranslationInDictionaryCommandImpl.cpp
        )

set(UT_SOURCES
        src/repositories/DefaultDictionaryRepositoryTest.cpp
        src/repositories/DictionaryMemoryStorageTest.cpp
        src/repositories/DictionaryPersistentStorageTest.cpp
        src/serializers/DictionaryJsonSerializerTest.cpp
        src/readers/DictionaryWordsCsvReaderImplTest.cpp
        src/repositories/DefaultWordDescriptionRepositoryTest.cpp
        src/repositories/WordsDescriptionsMemoryStorageTest.cpp
        src/repositories/WordsDescriptionsPersistentStorageTest.cpp
        src/serializers/WordsDescriptionsJsonSerializerTest.cpp
        src/clients/WordsApiClientImplTest.cpp
        src/queries/GetDictionaryQueryImplTest.cpp
        src/queries/GetDictionariesQueryImplTest.cpp
        src/queries/GetDictionariesNamesQueryImplTest.cpp
        src/queries/GetDictionaryEnglishWordsQueryImplTest.cpp
        src/queries/GetDictionariesEnglishWordsQueryImplTest.cpp
        src/queries/GetRandomWordFromDictionaryQueryImplTest.cpp
        src/queries/GetRandomWordFromDictionariesQueryImplTest.cpp
        src/queries/GetWordDescriptionQueryImplTest.cpp
        src/commands/CreateDictionaryCommandImplTest.cpp
        src/commands/CreateDictionaryFromCsvFileCommandImplTest.cpp
        src/commands/AddWordToDictionaryCommandImplTest.cpp
        src/commands/RemoveWordFromDictionaryCommandImplTest.cpp
        src/commands/UpdateWordTranslationInDictionaryCommandImplTest.cpp
        )

add_library(dictionary ${SOURCES})
add_executable(dictionaryUT ${SOURCES} ${UT_SOURCES})

target_include_directories(dictionary
        PUBLIC
        "include"
        PRIVATE
        "include/dictionary"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(dictionaryUT PRIVATE
        "include/dictionary"
        ${JSON_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(dictionary PUBLIC
        fileSystem
        collection
        random
        httpClient
        fmt::fmt
        )
target_link_libraries(dictionaryUT PRIVATE
        gmock_main
        gtest
        fileSystem
        collection
        random
        httpClient
        fmt::fmt
        )

target_compile_options(dictionary PUBLIC ${FLAGS})
target_compile_options(dictionaryUT PUBLIC ${FLAGS})

add_test(dictionaryUT dictionaryUT --gtest_color=yes)
