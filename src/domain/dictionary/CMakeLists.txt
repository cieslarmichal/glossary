set(SOURCES
        src/repositories/DefaultDictionaryRepository.cpp
        src/repositories/DictionaryMemoryStorage.cpp
        src/repositories/DictionaryPersistentStorage.cpp
        src/serializers/DictionaryJsonSerializer.cpp
        src/DictionaryWordsCsvReader.cpp
        src/DefaultDictionaryWordRandomizer.cpp
        src/DefaultDictionaryService.cpp
        src/DictionaryNameSelector.cpp
        src/DictionaryFinder.cpp
        src/DictionaryWordAccumulator.cpp
        src/DefaultDictionaryNamesRetriever.cpp
        src/DefaultDictionaryWordsRetriever.cpp
        src/DefaultRandomDictionaryWordRetriever.cpp
        src/DictionaryObserverService.cpp
        src/WordsDictionaryMembershipFinder.cpp
        src/DefaultWordDescriptionRepository.cpp
        src/WordsDescriptionsMemoryStorage.cpp
        src/WordsDescriptionsPersistentStorage.cpp
        src/WordsDescriptionsJsonSerializer.cpp
        src/clients/WordsApiClientImpl.cpp
        )

set(UT_SOURCES
        src/repositories/DefaultDictionaryRepositoryTest.cpp
        src/repositories/DictionaryMemoryStorageTest.cpp
        src/repositories/DictionaryPersistentStorageTest.cpp
        src/serializers/DictionaryJsonSerializerTest.cpp
        src/DictionaryWordsCsvReaderTest.cpp
        src/DefaultDictionaryWordRandomizerTest.cpp
        src/DefaultDictionaryServiceTest.cpp
        src/DictionaryNameSelectorTest.cpp
        src/DictionaryFinderTest.cpp
        src/DictionaryWordAccumulatorTest.cpp
        src/DefaultDictionaryNamesRetrieverTest.cpp
        src/DefaultDictionaryWordsRetrieverTest.cpp
        src/DefaultRandomDictionaryWordRetrieverTest.cpp
        src/DictionaryObserverServiceTest.cpp
        src/WordsDictionaryMembershipFinderTest.cpp
        src/DefaultWordDescriptionRepositoryTest.cpp
        src/WordsDescriptionsMemoryStorageTest.cpp
        src/WordsDescriptionsPersistentStorageTest.cpp
        src/WordsDescriptionsJsonSerializerTest.cpp
        src/clients/WordsApiClientImplTest.cpp
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
