cmake_minimum_required(VERSION 3.16)

project(ARDA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Xml
    Core
    Gui
    PrintSupport
    Network
    Sql

)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
    main.cpp

    mainwindow.h
    mainwindow.cpp
    mainwindow.ui


    confrimdialog.h
    confrimdialog.cpp
    confrimdialog.ui




    CurrentVersionApplication.h

    updatechecker.h
    updatechecker.cpp

    parserjson.h
    parserjson.cpp

    clearcash.h
    clearcash.cpp

    admin.h
    admin.cpp
    admin.ui

    settingsbinder.h
    settingsbinder.cpp

    ModeSerelization.h


    builderform.h
    builderform.cpp
    # student core
    StudentManagerCore/addstudentdialog.h
    StudentManagerCore/addstudentdialog.cpp
    StudentManagerCore/addstudentdialog.ui

    StudentManagerCore/sortstudentdialog.h
    StudentManagerCore/sortstudentdialog.cpp
    StudentManagerCore/sortstudentdialog.ui

    StudentManagerCore/deletestudentdialog.h
    StudentManagerCore/deletestudentdialog.cpp
    StudentManagerCore/deletestudentdialog.ui

    StudentManagerCore/findstudentdialog.h
    StudentManagerCore/findstudentdialog.cpp
    StudentManagerCore/findstudentdialog.ui

    StudentManagerCore/priviewstudentdialog.h
    StudentManagerCore/priviewstudentdialog.cpp
    StudentManagerCore/priviewstudentdialog.ui

    StudentManagerCore/studentdataservice.cpp
    StudentManagerCore/studentdataservice.h
    StudentManagerCore/studentdataservice.ui


    StudentManagerCore/ManagerStudent.cpp
    StudentManagerCore/ManagerStudent.h

    StudentManagerCore/Student.h
    StudentManagerCore/Student.cpp

#end student

    #DataCore
    ManagerDataCore/addfullinfostudent.h
    ManagerDataCore/addfullinfostudent.cpp
    ManagerDataCore/addfullinfostudent.ui

    ManagerDataCore/passportdialog.h
    ManagerDataCore/passportdialog.cpp
    ManagerDataCore/passportdialog.ui

    ManagerDataCore/extradatadialog.h
    ManagerDataCore/extradatadialog.cpp
    ManagerDataCore/extradatadialog.ui

    ManagerDataCore/Data.h
    ManagerDataCore/Data.cpp

    ManagerDataCore/passport.h
    ManagerDataCore/passport.cpp

    ManagerDataCore/extradata.h
    ManagerDataCore/extradata.cpp


 #end DataCore

    findobjectjson.h
    findobjectjson.cpp
    findobjectjson.ui

    ModeValidator.h

    Logger.h
    Logger.cpp

    AuthUser.cpp
    AuthUser.h

    Validator.cpp
    Validator.h

    FileChooicer.h
    FileChooicer.cpp

    authregwindow.cpp
    authregwindow.h

    Serializer.cpp
    Serializer.h

    icons.qrc
    JsonKeys.h

    Loader.cpp
    Loader.h

    LogicOperation.cpp
    LogicOperation.h


    #LessonsCore

    LessonsCore/academicrecordwindow.h
    LessonsCore/academicrecordwindow.cpp
    LessonsCore/academicrecordwindow.ui

    LessonsCore/accountingassessments.h
    LessonsCore/accountingassessments.cpp
    LessonsCore/accountingassessments.ui


    LessonsCore/recordbook.h
    LessonsCore/recordbook.cpp
    LessonsCore/recordbook.ui


    LessonsCore/texpanel.h
    LessonsCore/texpanel.cpp
    LessonsCore/texpanel.ui


    LessonsCore/coursework.h
    LessonsCore/coursework.cpp
    LessonsCore/coursework.ui


    LessonsCore/diploma.h
    LessonsCore/diploma.cpp
    LessonsCore/diploma.ui

    LessonsCore/project.h
    LessonsCore/project.cpp
    LessonsCore/project.ui


    #end LessonsCore


    #IO CORE
    IOCore/iodatabasehandler.h
    IOCore/iodatabasehandler.cpp
    IOCore/IODataHandler.h
    IOCore/IODataHandler.cpp

    #END IO

    #constest core
    ContestCore/TopBallContest.cpp
    ContestCore/TopBallContest.h

    ContestCore/StudentWriterResult.h
    ContestCore/StudentWriterResult.cpp

    ContestCore/dialogcontest.cpp
    ContestCore/dialogcontest.h
    ContestCore/dialogcontest.ui


    ContestCore/contestwindow.cpp
    ContestCore/contestwindow.h
    ContestCore/contestwindow.ui

    ContestCore/ContestResult.h
    ContestCore/ContestManager.cpp
    ContestCore/ContestManager.h

    ContestCore/AttestatContest.cpp
    ContestCore/AttestatContest.h

    ContestCore/Contest.h
    #end contest
    ardaeditorform.h ardaeditorform.cpp ardaeditorform.ui


    #FileCore
    FileManagerCore/createfiledialog.h FileManagerCore/createfiledialog.cpp FileManagerCore/createfiledialog.ui
    FileManagerCore/movefile.h FileManagerCore/movefile.cpp FileManagerCore/movefile.ui
    FileManagerCore/apfs.h FileManagerCore/apfs.cpp FileManagerCore/apfs.ui

    FileManagerCore/addedobjectfiles.h
    FileManagerCore/addedobjectfiles.cpp
    FileManagerCore/addedobjectfiles.ui

    FileManagerCore/backup.h
    FileManagerCore/backup.cpp
    FileManagerCore/backup.ui
    FileManagerCore/managerfs.h
    FileManagerCore/managerfs.cpp
    FileManagerCore/managerfs.ui

    FileManagerCore/filemanagerdialog.ui

    FileManagerCore/filemanagerdialog.h
    FileManagerCore/filemanagerdialog.cpp
    # end fileCore

    #Notific core
    NotificationCORE/assignmentplanner.h NotificationCORE/assignmentplanner.cpp NotificationCORE/assignmentplanner.ui
    NotificationCORE/addwork.h NotificationCORE/addwork.cpp NotificationCORE/addwork.ui
    NotificationCORE/priviewworks.h NotificationCORE/priviewworks.cpp NotificationCORE/priviewworks.ui
    NotificationCORE/notificationmanager.h NotificationCORE/notificationmanager.cpp NotificationCORE/notificationmanager.ui
    NotificationCORE/telegramnotifier.h NotificationCORE/telegramnotifier.cpp
    # Notific edn


    tablemanager.h tablemanager.cpp
    xorstr.h
)



qt_add_executable(ARDA
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    Delete.png
    dataeditor.h dataeditor.cpp dataeditor.ui
    dynamiccreateformeditordatajson.h dynamiccreateformeditordatajson.cpp

    #Scheudle start
    add_lesson_schedule_dialog.h add_lesson_schedule_dialog.cpp add_lesson_schedule_dialog.ui

    dataschedule.h dataschedule.cpp
    addlessontimeform.h addlessontimeform.cpp addlessontimeform.ui
    addcabinetsdialog.h addcabinetsdialog.cpp addcabinetsdialog.ui
    addnameteachersform.h addnameteachersform.cpp addnameteachersform.ui
    schedulebuilderform.h schedulebuilderform.cpp schedulebuilderform.ui
    primarydatascheudlemanagerform.h primarydatascheudlemanagerform.cpp primarydatascheudlemanagerform.ui
    addlessonnameform.h addlessonnameform.cpp addlessonnameform.ui
    scheduledataservice.h scheduledataservice.cpp
    schedulejsonparser.h schedulejsonparser.cpp
    #end scheudle
    passportdatajsonparser.h passportdatajsonparser.cpp
    scheduleioservice.h scheduleioservice.cpp





)

target_link_libraries(ARDA
    PRIVATE
        Qt6::Widgets
        Qt6::Xml
        Qt6::Core
        Qt6::Gui
        Qt6::PrintSupport
        Qt6::Network
        Qt6::Sql

)

qt_import_plugins(ARDA)

target_link_libraries(ARDA PRIVATE Qt6::Core)
target_link_libraries(ARDA PRIVATE Qt6::Core)
target_link_libraries(ARDA PRIVATE Qt6::Core)
target_link_libraries(ARDA PRIVATE Qt6::Core)
target_link_libraries(ARDA PRIVATE Qt6::Core)
target_link_libraries(ARDA PRIVATE Qt6::Core)
target_compile_options(ARDA PRIVATE -fpermissive)

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

if(WIN32)
    set(CMAKE_SYSTEM_VERSION 10.0.17763)
    set(CMAKE_SYSTEM_VERSION 6.2)

    add_compile_definitions(_WIN32_WINNT=0x0A00)
    add_compile_definitions(NTDDI_VERSION=0x0A000006)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ARDA)
endif()
