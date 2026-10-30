# Course Progress Manager (C++)

A menu-driven C++ console application for managing courses, student enrolments and learning progress.

## Features
- Add courses with a unique course ID, title and instructor.
- Enrol students in courses.
- List courses and enrolled students.
- Track progress as a percentage (0–100).
- Remove an enrolment.
- Calculate average progress and show the top three students.
- Prevent duplicate course IDs and duplicate student enrolments in a course.
- Validate numeric menu, ID and progress input.

## Requirements
A C++17-compatible compiler, such as GCC or MinGW-w64.

## Compile

Windows Command Prompt (MinGW):
```cmd
g++ -std=c++17 -Wall -Wextra -pedantic course_progress_manager.cpp -o course_progress_manager.exe
```

Linux:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic course_progress_manager.cpp -o course_progress_manager
```

## Run
Windows: `course_progress_manager.exe`

Linux: `./course_progress_manager`

## Data storage
Courses and students are stored in memory using `unordered_map`, `list` and `map`. **Data resets when the program exits.** File or database persistence is a possible future improvement.
