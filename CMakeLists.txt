cmake_minimum_required(VERSION 3.16)

project(Student_Manager_ARDA VERSION 0.1 LANGUAGES CXX)

# Enable Qt automatic tools
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/includeWindow
)

# Collect all source and header files
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SRCWINDOW_FILES "${CMAKE_SOURCE_DIR}/srcWindow/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/includeWindow/*.h")
file(GLOB_RECURSE HEADER_FILES_2 "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE UI_FILES "${CMAKE_SOURCE_DIR}/ui/*.ui")

# Main and resource files
set(MAIN_FILE main.cpp)
set(RESOURCE_FILE resource.qrc)

# Combine all sources
set(PROJECT_SOURCES
    ${SRC_FILES}
    ${SRCWINDOW_FILES}
    ${HEADER_FILES}
    ${HEADER_FILES_2}
    ${UI_FILES}
    ${MAIN_FILE}
    ${RESOURCE_FILE}
)

# One simple executable (no Android, no version check)
qt_add_executable(Student_Manager_ARDA
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    srcWindow/DynamicFormDialog.cpp
    includeWindow/DynamicFormDialog.h
    include/BuildForm.h
    src/BuildForm.cpp
    include/Serializer.h
    src/Serializer.cpp
    include/LogicOperation.h
    src/LogicOperation.cpp
    include/ContestCore/EgeContest.h
    src/CoreCppContest/EgeContest.cpp



)

# Link Qt libraries
target_link_libraries(Student_Manager_ARDA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Optional: macOS bundle metadata
set_target_properties(Student_Manager_ARDA PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install instructions
include(GNUInstallDirs)
install(TARGETS Student_Manager_ARDA
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Student_Manager_ARDA)
endif()
