cmake_minimum_required(VERSION 3.16)

project(Student_Manager_ARDA VERSION 0.1 LANGUAGES CXX)

# Enable Qt automatic tools
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_SOURCE_DIR}/ui
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


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
    resource.qrc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Student_Manager_ARDA
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        include/Contest.h
        src/Contest.cpp
        include/AttestatContest.h
        src/AttestatContest.cpp
        include/TopBallContest.h
        src/TopBallContest.cpp
        include/ManagerStudent.h
        src/ManagerStudent.cpp
    )
else()
    if(ANDROID)
        add_library(Student_Manager_ARDA SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Student_Manager_ARDA
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(Student_Manager_ARDA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


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
