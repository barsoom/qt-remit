cmake_minimum_required(VERSION 3.16)

project(qt-remit VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets WebChannel)
qt_standard_project_setup()

set(MACOSX_BUNDLE_ICON_FILE qt-remit.icns)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/qt-remit.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

qt_add_executable(qt-remit
    githubview.cpp
    constants.cpp
    mainwindow.cpp
    remitview.cpp
    settings.cpp
    clipboardbridge.cpp
    main.cpp
    ${app_icon_macos}
)

target_link_libraries(qt-remit PRIVATE Qt6::Widgets Qt6::WebEngineWidgets Qt6::WebChannel)

set_target_properties(qt-remit PROPERTIES
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)

target_compile_definitions( ${PROJECT_NAME} PRIVATE __clang_major__=18)
