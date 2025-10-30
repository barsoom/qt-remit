cmake_minimum_required(VERSION 3.16)

project(qt-remit VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets WebChannel)
qt_standard_project_setup()

qt_add_executable(qt-remit
    githubview.cpp
    constants.cpp
    mainwindow.cpp
    remitview.cpp
    settings.cpp
    clipboardbridge.cpp
    main.cpp
)

target_link_libraries(qt-remit PRIVATE Qt6::Widgets Qt6::WebEngineWidgets Qt6::WebChannel)

set_target_properties(qt-remit PROPERTIES
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)
