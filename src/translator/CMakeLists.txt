set(SOURCES
        src/DefaultTranslator.cpp
        src/TranslationJsonDeserializer.cpp
        src/TranslationYandexRequestFormatter.cpp
        src/TranslatorFactory.cpp
        src/DefaultTranslatorFactory.cpp)

set(UT_SOURCES
        src/DefaultTranslatorTest.cpp
        src/TranslationJsonDeserializerTest.cpp
        src/TranslationYandexRequestFormatterTest.cpp)

add_library(translator ${SOURCES})
add_executable(translatorUT ${UT_SOURCES})

target_include_directories(translator PUBLIC "include" PRIVATE ${JSON_INCLUDE_DIR} "include/translator")
target_include_directories(translatorUT PRIVATE "include" "include/translator" ${JSON_INCLUDE_DIR})

target_link_libraries(translator PUBLIC webConnection PRIVATE utils)
target_link_libraries(translatorUT PRIVATE gtest_main gmock utils webConnection translator)

target_compile_options(translator PUBLIC ${FLAGS})
target_compile_options(translatorUT PUBLIC -Wall -Wextra -Werror)

add_test(translatorUT translatorUT --gtest_color=yes)
