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
        )

add_library(dictionaryService ${SOURCES})
add_executable(dictionaryServiceUT ${UT_SOURCES})

target_include_directories(dictionaryService PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/dictionaryService" "src/")
target_include_directories(dictionaryServiceUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/dictionaryService" "src/")

target_link_libraries(dictionaryService PRIVATE utils)
target_link_libraries(dictionaryServiceUT PRIVATE gtest_main gmock dictionaryService utils)

target_compile_options(dictionaryService PUBLIC ${FLAGS})
target_compile_options(dictionaryServiceUT PUBLIC -Wall -Wextra -Werror)

add_test(dictionaryServiceUT dictionaryServiceUT --gtest_color=yes)
