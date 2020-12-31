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
        include/dictionaryService/DictionaryServiceApi.h)

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
        )

add_library(dictionaryService ${SOURCES})
add_executable(dictionaryServiceUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(dictionaryServiceUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(dictionaryService
        PUBLIC "include"
        PRIVATE
        ${JSON_INCLUDE_DIR}
        "include/dictionaryService"
        "src/"
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(dictionaryServiceUT PRIVATE
        "include"
        "include/dictionaryService"
        "src/"
        ${JSON_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(dictionaryService PUBLIC utils)
target_link_libraries(dictionaryServiceUT PRIVATE
        gmock_main
        gtest
        utils
        )

target_compile_options(dictionaryService PUBLIC ${FLAGS})
target_compile_options(dictionaryServiceUT PUBLIC)

add_test(dictionaryServiceUT dictionaryServiceUT --gtest_color=yes)
