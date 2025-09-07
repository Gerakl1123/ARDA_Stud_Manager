cmake_minimum_required(VERSION 3.16)

project(Student_Manager_ARDA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Xml Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml Core Gui)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
find_package(Qt6 REQUIRED COMPONENTS Core)


include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/includeWindow
)


file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SRCWINDOW_FILES "${CMAKE_SOURCE_DIR}/srcWindow/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/includeWindow/*.h")
file(GLOB_RECURSE HEADER_FILES_2 "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE UI_FILES "${CMAKE_SOURCE_DIR}/ui/*.ui")
set(MAIN_FILE main.cpp)

set(PROJECT_SOURCES
    ${SRC_FILES}
    ${SRCWINDOW_FILES}
    ${HEADER_FILES}
    ${HEADER_FILES_2}
    ${UI_FILES}
    ${MAIN_FILE}
)

qt_add_executable(ARDA
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    academicrecordwindow.h academicrecordwindow.cpp academicrecordwindow.ui
    accountingassessments.h accountingassessments.cpp accountingassessments.ui


    IODataHandler.h IODataHandler.cpp
    recordbook.h recordbook.cpp recordbook.ui
    confrimdialog.h confrimdialog.cpp confrimdialog.ui
    project.h project.cpp project.ui
    texpanel.h texpanel.cpp texpanel.ui
    coursework.h coursework.cpp coursework.ui
    icons.qrc
    JsonKeys.h
    diploma.h diploma.cpp diploma.ui
    CurrentVersionApplication.h
    updatechecker.h updatechecker.cpp
    parserjsonnetwork.h parserjsonnetwork.cpp
    Data.h Data.cpp
    clearcash.h clearcash.cpp
    passport.h passport.cpp
    extradata.h extradata.cpp
    admin.h admin.cpp admin.ui
    settingsbinder.h settingsbinder.cpp
    ModeSerelization.h



)



target_link_libraries(ARDA
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Xml
)
target_link_libraries(ARDA
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
)
target_link_libraries(ARDA PRIVATE Qt6::Network)
target_link_libraries(ARDA PRIVATE Qt6::Core)


set_target_properties(ARDA PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ARDA
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ARDA)
endif()
