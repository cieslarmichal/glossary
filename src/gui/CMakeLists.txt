
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
        src/MainWindow.cpp Main.cpp)

add_executable(gui ${SOURCES})

target_link_libraries(gui PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets glossary)

target_compile_options(gui PUBLIC ${FLAGS})
