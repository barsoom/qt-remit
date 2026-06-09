cmake_minimum_required(VERSION 3.16)

project(qt-remit VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets WebChannel Test)
qt_standard_project_setup()

# Qt 6.9's FindWrapOpenGL.cmake unconditionally links the legacy AGL.framework on macOS. AGL still exists on the live filesystem (so CMake's find_library succeeds) but was removed from the macOS 26 SDK that the linker actually links against, causing "ld: framework 'AGL' not found". AGL has been unused since macOS 10.9, so we strip it from the interface.
if(APPLE AND TARGET WrapOpenGL::WrapOpenGL)
    get_target_property(_wrapopengl_libs WrapOpenGL::WrapOpenGL INTERFACE_LINK_LIBRARIES)
    if(_wrapopengl_libs)
        list(FILTER _wrapopengl_libs EXCLUDE REGEX "AGL")
        set_target_properties(WrapOpenGL::WrapOpenGL PROPERTIES INTERFACE_LINK_LIBRARIES "${_wrapopengl_libs}")
    endif()
endif()

set(CMAKE_AUTORCC ON)

add_executable(qt-remit)


# To add a new source or header file:
#   - Add .cpp files to the SOURCES list below.
#     Most C++ build systems need .cpp files to be listed explicitly.
#   - Add .h files to the HEADERS list below.
#     Qt's MOC (Meta-Object Compiler, the tool that makes signals/slots work) needs
#     all QObject-derived headers to be listed for it to generate the necessary
#     meta-object code.

# See https://cmake.org/cmake/help/latest/command/file.html#glob for why we're not using file(GLOB ...) 

set(SRC src)
set(INC include)

set(SOURCES
    ${SRC}/browserpane.cpp
    ${SRC}/clipboardbridge.cpp
    ${SRC}/constants.cpp
    ${SRC}/githubview.cpp
    ${SRC}/lastwindowstate.cpp
    ${SRC}/main.cpp
    ${SRC}/mainwindow.cpp
    ${SRC}/remitview.cpp
    ${SRC}/settings.cpp
    ${SRC}/settingsdialog.cpp
    ${SRC}/urlrouter.cpp
    resources/resources.qrc
)

set(HEADERS
    ${INC}/browserpane.h
    ${INC}/clipboardbridge.h
    ${INC}/constants.h
    ${INC}/githubview.h
    ${INC}/lastwindowstate.h
    ${INC}/mainwindow.h
    ${INC}/remitview.h
    ${INC}/settings.h
    ${INC}/settingsdialog.h
    ${INC}/urlrouter.h
)

target_sources(qt-remit PRIVATE ${SOURCES} ${HEADERS})

target_include_directories(qt-remit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(qt-remit PRIVATE Qt6::Widgets Qt6::WebEngineWidgets Qt6::WebChannel)

if(APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME "Qt-Remit")
    set(MACOSX_BUNDLE_ICON_FILE qt-remit.icns)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/qt-remit.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(qt-remit PRIVATE ${app_icon_macos})
    set_target_properties(qt-remit PROPERTIES MACOSX_BUNDLE ON)
endif()

if(WIN32)
    set(WIN_RC "${CMAKE_CURRENT_SOURCE_DIR}/resources/qt-remit.rc")
    target_sources(qt-remit PRIVATE ${WIN_RC})
    set_target_properties(qt-remit PROPERTIES WIN32_EXECUTABLE ON)
endif()

if(MSVC)
  # Current assumption is that msvc doesn't define __clang_major__, but QWebEngine assumes we're on clang because the chromium in it is built with clang.
  # This definition suppresses LSP warnings related to that.
  target_compile_definitions(qt-remit PRIVATE __clang_major__=18)
endif()

# Tests — no WebEngine dependency, so no display server required
enable_testing()
add_executable(qt-remit-tests)
target_sources(qt-remit-tests PRIVATE
    ${SRC}/urlrouter.cpp
    ${INC}/urlrouter.h
    tests/test_urlrouter.cpp
)
target_include_directories(qt-remit-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(qt-remit-tests PRIVATE Qt6::Core Qt6::Test)
add_test(NAME qt-remit-tests COMMAND qt-remit-tests)