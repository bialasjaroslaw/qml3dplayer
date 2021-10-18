cmake_minimum_required(VERSION 3.14)

project(QML3DVideoPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Multimedia 3DCore 3DRender REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        videoplayer.cpp
        videoplayer.h
        playervideosurface.cpp
        playervideosurface.h
        customtextureimage.cpp
        customtextureimage.h
        customtexture.cpp
        customtexture.h
        framedatagenerator.cpp
        framedatagenerator.h
        qml.qrc
)

if(ANDROID)
    add_library(QML3DVideoPlayer SHARED
        ${PROJECT_SOURCES}
    )
else()
    add_executable(QML3DVideoPlayer
      ${PROJECT_SOURCES}
    )
endif()

target_compile_definitions(QML3DVideoPlayer
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QML3DVideoPlayer
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Multimedia
  Qt${QT_VERSION_MAJOR}::3DCore
  Qt${QT_VERSION_MAJOR}::3DRender
)

