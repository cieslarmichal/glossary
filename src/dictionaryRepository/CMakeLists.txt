set(SOURCES
        src/DefaultDictionaryRepository.cpp
        src/DictionaryWordsCSVFileReader.cpp
        src/DictionaryMemoryStorage.cpp
        src/DictionaryPersistentStorage.cpp
        src/DictionaryJsonSerializer.cpp
        src/DictionaryRepositoryFactory.cpp
        src/DefaultDictionaryRepositoryFactory.cpp
        src/DictionaryWordsCSVFileContentValidator.cpp
        )

set(UT_SOURCES
        src/DefaultDictionaryRepositoryTest.cpp
        src/DictionaryWordsCSVFileReaderTest.cpp
        src/DictionaryMemoryStorageTest.cpp
        src/DictionaryPersistentStorageTest.cpp
        src/DictionaryJsonSerializerTest.cpp
        src/DictionaryWordsCSVFileContentValidatorTest.cpp
        )

add_library(dictionaryRepository ${SOURCES})
add_executable(dictionaryRepositoryUT ${UT_SOURCES})

target_include_directories(dictionaryRepository PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/dictionaryRepository")
target_include_directories(dictionaryRepositoryUT PRIVATE "include" ${INTERNAL_LIBS_INCLUDE_PATH} ${JSON_INCLUDE_DIR} "include/dictionaryRepository")

target_link_libraries(dictionaryRepository PRIVATE utils)
target_link_libraries(dictionaryRepositoryUT PRIVATE gtest_main gmock dictionaryRepository utils)

target_compile_options(dictionaryRepository PUBLIC ${FLAGS})
target_compile_options(dictionaryRepositoryUT PUBLIC -Wall -Wextra -Werror)

add_test(dictionaryRepositoryUT dictionaryRepositoryUT --gtest_color=yes)
