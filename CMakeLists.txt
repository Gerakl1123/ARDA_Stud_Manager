
cmake_minimum_required(VERSION 3.16)

project(Student_Manager_ARDA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE PROJECT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(PROJECT_SOURCES
    ${PROJECT_SRC_FILES}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    authregwindow.cpp
    authregwindow.h
windowsmanagerstudent.cpp
windowsmanagerstudent.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    qt_add_executable(Student_Manager_ARDA
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        authregwindow.h authregwindow.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Student_Manager_ARDA APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Student_Manager_ARDA SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Student_Manager_ARDA
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Student_Manager_ARDA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Student_Manager_ARDA PRIVATE Qt6::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Student_Manager_ARDA)
endif()
set_target_properties(Student_Manager_ARDA PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Student_Manager_ARDA
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Student_Manager_ARDA)
endif()
