ARDA_Stud_Manager

ARDA_Stud_Manager is a local cross-platform Qt application for managing students, groups, grades, and schedules. All data is stored locally — no database or internet connection required.
Features

    Student, group, and teacher management

    Schedule and academic module creation

    Grade and exam tracking

    Local file-based data storage

    Password hashing with SHA256

    Qt Widgets-based GUI

    Data serialization and deserialization

    Fully offline usage

Technologies

    C++11/17

    Qt 6 qwidget

    CMake

    Cross-platform: Windows, Linux

Build & Run

Make sure Qt and CMake are installed and available in your system path.

git clone https://github.com/Gerakl1123/ARDA_Stud_Manager
cd ARDA_Stud_Manager
mkdir build
cd build
cmake ..
make
./ARDA_Stud_Manager

Demo

Demo videos are available in the ARDA/demo video/ folder.
Development Status

Some menus (lesson plans, file manager) are under development.
The project is currently undergoing a major code refactor — updates will pause for 1–2 weeks.

Work in progress:

    Full rewrite of Contest and Student Manager classes

    UI and logic separation

    Bug fixes and optimization

Follow updates here: Telegram Channel
Latest Changes

24.07.2025

    Fixed bug with student sorting and saving

    Merged file saving grid into main sorting grid

18.07.2025

    Added two new menus

    Refactored UI, logic moved out of widgets

Known Issues

    Issue when adding many students to an existing notebook and saving after sorting (fixed 24.07.2025)

License

Licensed under CC BY-NC 4.0.
Free for non-commercial use with attribution.

Author: Gerakl1123
