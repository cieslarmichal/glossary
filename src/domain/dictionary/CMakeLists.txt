set(SOURCES
        src/repository/DefaultDictionaryRepository.cpp
        src/repository/DictionaryMemoryStorage.cpp
        src/repository/DictionaryPersistentStorage.cpp
        src/serialization/DictionaryJsonSerializer.cpp
        src/csvFileReading/DictionaryWordsCsvFileReader.cpp
        src/csvFileReading/DictionaryWordsCsvFileContentValidator.cpp
        src/DictionaryServiceFactory.cpp
        src/DefaultDictionaryServiceFactory.cpp
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
        src/WordDescriptionRepositoryFactory.cpp
        src/DefaultWordDescriptionRepositoryFactory.cpp
        src/DefaultWordDescriptionDownloader.cpp
        src/WordDescriptionDownloaderFactory.cpp
        src/DefaultWordDescriptionDownloaderFactory.cpp
        src/WordsApiJsonResponseDeserializer.cpp
        src/WordsApiResponseFetcher.cpp
        )

set(UT_SOURCES
        src/repository/DefaultDictionaryRepositoryTest.cpp
        src/repository/DictionaryMemoryStorageTest.cpp
        src/repository/DictionaryPersistentStorageTest.cpp
        src/serialization/DictionaryJsonSerializerTest.cpp
        src/csvFileReading/DictionaryWordsCsvFileReaderTest.cpp
        src/csvFileReading/DictionaryWordsCsvFileContentValidatorTest.cpp
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
        src/DefaultWordDescriptionDownloaderTest.cpp
        src/WordsApiJsonResponseDeserializerTest.cpp
        src/WordsApiResponseFetcherTest.cpp
        )

add_library(dictionary ${SOURCES})
add_executable(dictionaryUT ${SOURCES} ${UT_SOURCES})

target_include_directories(dictionary
        PUBLIC "include"
        PRIVATE
        ${JSON_INCLUDE_DIR}
        "src"
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(dictionaryUT PRIVATE
        "include"
        "src"
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