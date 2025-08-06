cmake_minimum_required(VERSION 3.16)

project(Student_Manager_ARDA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем необходимые модули Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Xml Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml Core Gui)

# Включаем свои include каталоги
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/includeWindow
)

# Собираем исходники и ui
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

# Создаем исполняемый файл
qt_add_executable(ARDA
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    academicrecordwindow.h academicrecordwindow.cpp academicrecordwindow.ui
    accountingassessments.h accountingassessments.cpp accountingassessments.ui
    DataHandler.h
    DataHandler.cpp
    StudentDataHandler.h
    StudentDataHandler.cpp
)

# Включаем include external (если там что-то кроме QXlsx всё ещё используется)
target_include_directories(ARDA PRIVATE
    ${CMAKE_SOURCE_DIR}/external
)

target_link_libraries(ARDA
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Xml
)

# Свойства для macOS и Windows
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
