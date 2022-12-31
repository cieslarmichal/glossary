find_package(Qt5Charts)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
        src/view/GuessTab.cpp
        src/view/DictionariesTab.cpp
        src/view/CheckWordDescriptionTab.cpp
        src/view/TranslatorTab.cpp
        src/view/StatisticsTab.cpp
        src/view/WelcomeTab.cpp
        src/view/AboutDialog.cpp
        src/view/AddDictionaryDialog.cpp
        src/view/AddDictionaryWordDialog.cpp
        src/view/WordDescriptionDialog.cpp
        src/view/WordDescriptionFormatter.cpp
        src/view/DictionaryFormatter.cpp
        src/view/DictionaryWordAccumulator.cpp
        src/view/FormattedDictionariesStorage.cpp
        src/viewManager/CheckWordDescriptionTabViewManager.cpp
        src/viewManager/GuessTabViewManager.cpp
        src/viewManager/DictionariesTabViewManager.cpp
        src/viewManager/TranslatorTabViewManager.cpp
        src/viewManager/StatisticsTabViewManager.cpp
        src/viewManager/WelcomeTabViewManager.cpp
        src/view/MainView.cpp
        src/model/GlossaryAdapter.cpp
        src/Gui.cpp
        )

set(UT_SOURCES
        src/view/WordDescriptionFormatterTest.cpp
        src/view/DictionaryFormatterTest.cpp
        src/view/FormattedDictionariesStorageTest.cpp
        src/view/DictionaryWordAccumulatorTest.cpp
        )

add_executable(gui ${SOURCES} Main.cpp)
add_executable(guiUT ${UT_SOURCES} ${SOURCES})

target_include_directories(gui PUBLIC "src/")
target_include_directories(guiUT PUBLIC "src/")

target_link_libraries(gui PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        glossary
        translation
        statistics
        dictionary
        fileSystem
        )
target_link_libraries(guiUT PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        gmock_main
        gtest
        glossary
        translation
        statistics
        dictionary
        fileSystem
        )

target_compile_options(gui PUBLIC ${FLAGS})
target_compile_options(guiUT PUBLIC)

add_test(guiUT guiUT --gtest_color=yes)
