
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    src/view/GuessTab.cpp
    src/view/DictionariesTab.cpp
    src/view/CheckWordDescriptionTab.cpp
    src/view/TranslatorTab.cpp
    src/view/StatisticsTab.cpp
    src/view/AboutDialog.cpp
    src/viewManager/CheckWordDescriptionTabViewManager.cpp
    src/viewManager/GuessTabViewManager.cpp
    src/viewManager/DictionariesTabViewManager.cpp
    src/viewManager/TranslatorTabViewManager.cpp
    src/viewManager/StatisticsTabViewManager.cpp
    src/MainViewCreator.cpp
    src/view/MainView.cpp
    Main.cpp
    )

add_executable(gui ${SOURCES})

target_include_directories(gui PUBLIC "src/")

target_link_libraries(gui PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets glossary)

target_compile_options(gui PUBLIC ${FLAGS})
