# To-Do List Console Application

A simple command-line to-do list manager written in C++. Tasks are persisted to a local file so they survive between sessions.

## Features

- **Add tasks** with automatic ID assignment and timestamp tracking
- **View tasks** in a formatted table with status, description, and timestamps
- **Mark tasks as complete** with completion timestamp recorded
- **Delete tasks** by ID
- **Persistent storage** — tasks are saved to `tasks.txt` and loaded on startup
- **Input validation** — handles invalid/non-numeric input gracefully

## Project Structure

```
todo list/
├── main.cpp          # Entry point, menu loop, and user interaction
├── Task.h            # Task class with serialization/deserialization
├── TaskManager.h     # TaskManager class handling CRUD and file I/O
├── tasks.txt         # Data file (auto-created on first save)
└── README.md
```

## Build & Run

### Using g++ (MinGW / GCC)

```bash
g++ -o todoapp main.cpp -std=c++17
./todoapp
```

### Using MSVC (Developer Command Prompt)

```bash
cl /EHsc /std:c++17 main.cpp /Fe:todoapp.exe
todoapp.exe
```

## Usage

```
Welcome to the To-Do List App!
Loaded 1 task(s) from file.

========== TO-DO LIST ==========
 1. Add Task
 2. View Tasks
 3. Mark Task as Complete
 4. Delete Task
 5. Exit
================================
Choose an option:
```

Select an option by entering its number. When adding a task, type the description and press Enter. To mark complete or delete, enter the task ID shown in the task list.

## Data Format

Tasks are stored in `tasks.txt` as pipe-delimited lines:

```
id|description|completed(0/1)|createdAt|completedAt
```

## Requirements

- C++17 compatible compiler (g++ 7+, MSVC 2017+, clang 5+)
