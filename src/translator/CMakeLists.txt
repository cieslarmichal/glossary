set(SOURCES
        src/DefaultTranslator.cpp
        src/GoogleTranslateApiJsonResponseDeserializer.cpp
        src/GoogleTranslateApiRequestFormatter.cpp
        src/TranslatorFactory.cpp
        src/DefaultTranslatorFactory.cpp
        )

set(UT_SOURCES
        src/DefaultTranslatorTest.cpp
        src/GoogleTranslateApiJsonResponseDeserializerTest.cpp
        src/GoogleTranslateApiRequestFormatterTest.cpp
        )

add_library(translator ${SOURCES})
add_executable(translatorUT ${SOURCES} ${UT_SOURCES})

target_compile_definitions(translatorUT PUBLIC -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(translator
        PUBLIC "include"
        PRIVATE
        "include/translator"
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )
target_include_directories(translatorUT PRIVATE
        "include"
        "include/translator"
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(translator
        PUBLIC webConnection
        PRIVATE utils
        )
target_link_libraries(translatorUT PRIVATE
        gmock_main
        gtest
        utils
        webConnection
        )

target_compile_options(translator PUBLIC ${FLAGS})
target_compile_options(translatorUT PUBLIC)

add_test(translatorUT translatorUT --gtest_color=yes)
