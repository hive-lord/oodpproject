# Smart To-Do List (C++) Documentation

## Overview
This is a terminal-based smart to-do list written in C++. The project demonstrates OOP concepts like encapsulation, abstraction, and composition by modeling tasks in a dedicated class and managing them through a TaskManager. The interface is built with ASCII art and ANSI color codes.

## Goals and OOP Concepts
- Encapsulation: Task fields are private with getters and setters.
- Abstraction: TaskManager exposes high-level actions (add, remove, search) while hiding storage details.
- Composition: TaskManager owns a collection of Task objects.

## Key Features
- Create, edit, delete, duplicate, and view tasks.
- Mark tasks as completed or pending.
- Sort tasks by priority or status.
- Search tasks by keyword and filter by category.
- Show statistics with a progress bar.
- Export tasks to a text file.
- Pomodoro timer.
- Automatic persistence to a data file.

## Project Structure
- project.cpp: Main source file containing all classes, functions, and the program entry point.
- tasks.dat: Data file used for persistence (created at runtime).
- export.txt: Optional export file (created when exporting).

## Core Types and Their Roles

### enum class Category
Represents task categories:
- GENERAL, WORK, PERSONAL, STUDY, HEALTH

Helper functions:
- categoryToString(Category): Converts a category to a display label.
- stringToCategory(string): Parses a label back into the enum.

### class Task
Encapsulates a single to-do item and its metadata.

Private data:
- id: Unique numeric ID. Auto-incremented across tasks.
- title, description: Task text.
- priority: 1 (High), 2 (Medium), 3 (Low).
- isCompleted: Completion flag.
- deadline: Stored as a string in YYYY-MM-DD or N/A.
- category: Category enum.
- createdAt: Timestamp in YYYY-MM-DD HH:MM.

Behavior and methods:
- getCurrentTime(): Builds a timestamp using the local clock.
- isOverdue(): Compares deadline (YYYY-MM-DD) with the current date. Returns true if the task is pending and the deadline is earlier than today.
- priorityStr(): Formats priority as text, used in tables and exports.
- statusStr(): Returns a completion marker for list views.
- displayTask(): Renders a single row with colorized status, priority, category, and an overdue tag.
- displayFull(): Renders a full-width detail card with all fields.
- serialize(): Produces a pipe-delimited line for saving to disk.

Constructors:
- Standard constructor: Used when creating a new task from user input.
- Load constructor: Used when loading tasks from the data file and synchronizing the global ID counter.

### class TaskManager
Owns the list of tasks and implements all user actions.

Private data:
- tasks: Vector of Task objects.
- saveFile: Data file name, defaults to tasks.dat.

Key helpers:
- findById(int): Finds the index of a task by ID.
- validPriority(int): Ensures a priority is between 1 and 3.

User actions:
- addTask(): Captures user input and creates a new task.
- removeTask(): Deletes a task by ID with confirmation.
- markTaskCompleted(), markTaskPending(): Toggles completion state.
- displayTasks(), displayPendingTasks(), displayCompletedTasks(): Render task lists.
- viewTaskDetails(): Shows full details by ID.
- editTask(): Edits title, description, priority, and deadline.
- sortByPriority(): Orders tasks by priority (High to Low).
- sortByStatus(): Orders tasks so pending items appear first.
- searchTasks(): Case-insensitive search on title and description.
- filterByCategory(): Shows tasks for a single category.
- showStatistics(): Prints aggregate counts and a progress bar.
- clearCompleted(): Bulk removes completed tasks.
- duplicateTask(): Copies an existing task, appending " (Copy)" to the title.
- exportTasks(): Writes tasks to export.txt for sharing.
- pomodoroTimer(): Runs a countdown timer with a bell at the end.

Persistence:
- saveToFile(): Writes each task using Task::serialize().
- loadFromFile(): Reads tasks from the data file on startup.

## User Interface and Display Details
The UI relies on ANSI escape codes for color and style. Core helpers include:
- printHeader(), printLine(): Draw banners and separators.
- printSuccess(), printError(), printInfo(): Colorized status messages.
- clearScreen(), pauseScreen(): Simple UX helpers.
- padRight(): Keeps text aligned in columns.

Display formatting and truncation:
- List view titles are truncated to 26 characters.
- Categories are truncated to 9 characters.
- Full detail view truncates title and description to 35 characters.
- Overdue items display a tagged warning in list and detail views.

Note about IDs vs list numbering:
- The table shows a row number (index), not the internal task ID.
- Actions such as delete, edit, and mark complete ask for a task ID.
- To see the ID, use the task details view.

## Input Handling and Validation
The program mixes formatted input (cin >>) and line input (getline). It uses cin.ignore to clear the newline before reading a full line. Validation rules include:
- Title must not be empty.
- Priority must be 1, 2, or 3 (defaults to Low if invalid).
- Deadline can be YYYY-MM-DD or N/A. Empty input becomes N/A.
- Invalid menu input is handled by clearing the stream and re-prompting.

## Function Reference (Detailed)
This section explains each function, including inputs, outputs, and side effects.

### Global UI and Utility Helpers
- `printLine(int len = 62)`: Prints a cyan horizontal line of the given length. Side effect: writes to stdout.
- `printHeader()`: Prints the ASCII banner and title. Side effect: writes to stdout.
- `printSuccess(const string& msg)`: Prints a green success message with an icon. Side effect: writes to stdout.
- `printError(const string& msg)`: Prints a red error message with an icon. Side effect: writes to stdout.
- `printInfo(const string& msg)`: Prints a blue info message with an icon. Side effect: writes to stdout.
- `clearScreen()`: Clears the console using `system("cls")` on Windows or `system("clear")` elsewhere. Side effect: runs a shell command.
- `pauseScreen()`: Waits for the user to press ENTER. It clears the input buffer and then blocks on `cin.get()`. Side effect: consumes input.
- `padRight(string s, size_t width)`: Returns a new string padded with spaces to the given width. No I/O.

### Category Helpers
- `categoryToString(Category c)`: Maps a category enum to its label (Work, Personal, Study, Health, General).
- `stringToCategory(const string& s)`: Maps a label to the enum. Unknown strings default to `GENERAL`.

### Task Methods

Constructors and internal helpers:
- `Task(const string& title, int priority, const string& description = "", const string& deadline = "N/A", Category category = Category::GENERAL)`: Creates a new task, increments the static ID counter, sets `isCompleted` to false, and stores the current timestamp.
- `Task(int id, const string& title, const string& description, int priority, bool isCompleted, const string& deadline, const string& category, const string& createdAt)`: Builds a task from a saved record and updates the global ID counter if needed.
- `getCurrentTime()`: Returns the current local time formatted as YYYY-MM-DD HH:MM. Used by the constructor.

Getters:
- `getId()`, `getTitle()`, `getDescription()`, `getPriority()`, `getIsCompleted()`, `getDeadline()`, `getCategory()`, `getCreatedAt()`: Return the corresponding field with no side effects.

Setters and status updates:
- `setTitle(const string& t)`, `setDescription(const string& d)`, `setPriority(int p)`, `setDeadline(const string& d)`, `setCategory(Category c)`: Update individual fields.
- `markCompleted()`: Sets `isCompleted` to true.
- `markPending()`: Sets `isCompleted` to false.

Formatting and state checks:
- `isOverdue()`: Returns true when the task is pending and the deadline string is earlier than today. This comparison assumes the YYYY-MM-DD format.
- `priorityStr()`: Returns a fixed label for the priority level, used in list views and exports.
- `statusStr()`: Returns a short status marker for list views.

Display and serialization:
- `displayTask(int index = -1)`: Prints a single row in a table view. It uses `index` for list numbering and truncates title and category to fit columns. It adds an overdue tag when needed. Side effect: writes to stdout.
- `displayFull()`: Prints a detailed card with all fields and a highlighted overdue label. Side effect: writes to stdout.
- `serialize()`: Returns a pipe-delimited representation of the task used for saving.

### TaskManager Methods

Construction and helpers:
- `TaskManager(const string& file = "tasks.dat")`: Sets the save file path and loads existing tasks.
- `~TaskManager()`: Saves all tasks to the data file on program exit.
- `findById(int id)`: Private helper that returns the index of a task by ID, or -1 if not found.
- `validPriority(int p)`: Private helper that returns true for values 1 through 3.

Task creation and removal:
- `addTask()`: Prompts the user for fields, validates title and priority, normalizes empty deadlines to N/A, and appends a new Task. Saves the file afterward.
- `removeTask()`: Shows all tasks, asks for an ID, confirms deletion, and removes the task. Saves the file afterward.
- `duplicateTask()`: Copies a task by ID, appends " (Copy)" to the title, and saves.

Status changes:
- `markTaskCompleted()`: Shows pending tasks, asks for an ID, and marks the task as completed if possible. Saves afterward.
- `markTaskPending()`: Shows completed tasks, asks for an ID, and marks the task as pending. Saves afterward.

Display and detail views:
- `displayTasks()`: Prints the full table of tasks and a totals footer. Uses `countCompleted()` for summary.
- `displayPendingTasks()`: Prints only pending tasks and shows a friendly message if none exist.
- `displayCompletedTasks()`: Prints only completed tasks and shows a friendly message if none exist.
- `viewTaskDetails()`: Prompts for an ID and prints the full detail card for that task.

Editing and sorting:
- `editTask()`: Prompts for an ID, then allows the user to update title, description, priority, and deadline. Empty input keeps the current value. Saves afterward.
- `sortByPriority()`: Sorts tasks by priority (1 high to 3 low), saves, and reprints the list.
- `sortByStatus()`: Sorts tasks so pending tasks appear first, saves, and reprints the list.

Search, filter, and stats:
- `searchTasks()`: Prompts for a keyword and runs a case-insensitive search on title and description. Prints matching results and a count.
- `filterByCategory()`: Prompts for a category and prints only matching tasks.
- `showStatistics()`: Computes totals, completion percentage, priority counts, and category counts, then prints a dashboard with a progress bar.

Bulk actions and counts:
- `clearCompleted()`: Removes all completed tasks using `remove_if` and saves the result.
- `countCompleted()`: Returns the number of completed tasks by scanning the list.

Export and time utilities:
- `exportTasks()`: Writes a human-readable summary to export.txt. If the file cannot be opened, it prints an error.
- `pomodoroTimer()`: Prompts for a preset or custom duration and runs a blocking countdown with a 1-second sleep loop. It clears the screen before running and rings a bell when complete.

Persistence:
- `saveToFile()`: Writes tasks to the save file using `serialize()`. If the file cannot be opened, it silently returns.
- `loadFromFile()`: Reads the save file line-by-line, splits on the pipe character, and constructs tasks from valid rows.

### Menu and Entry Point
- `displayMenu()`: Prints the main menu with all available commands and a prompt.
- `main()`: Initializes `TaskManager`, prints the banner, and loops on the menu. It validates numeric input, dispatches each command, and exits cleanly with a goodbye message.

## Data File Format (tasks.dat)
Each line is a single task, pipe-delimited:

```
id|title|description|priority|isCompleted|deadline|category|createdAt
```

Field notes:
- id is an integer, unique per task.
- priority is 1, 2, or 3.
- isCompleted is 1 or 0.
- deadline is YYYY-MM-DD or N/A.
- createdAt is YYYY-MM-DD HH:MM.

Limitations of this format:
- The pipe character is not escaped, so it should not appear inside fields.
- Newlines are not escaped, so multi-line descriptions are not supported.

## Program Flow (main)
1. Create a TaskManager (loads tasks.dat).
2. Display the banner and instructions.
3. Show the main menu in a loop.
4. Dispatch the chosen action to TaskManager.
5. Pause for user input and return to the menu.

## Menu Map
- [1] Add Task
- [2] View All Tasks
- [3] View Task Details
- [4] Edit Task
- [5] Delete Task
- [6] Mark Task as Completed
- [7] Mark Task as Pending
- [8] View Completed Tasks
- [9] View Pending Tasks
- [10] Sort by Priority
- [11] Sort by Status
- [12] Search Tasks
- [13] Filter by Category
- [14] Statistics Dashboard
- [15] Clear All Completed Tasks
- [16] Duplicate Task
- [17] Export Tasks to File
- [18] Pomodoro Timer
- [0] Exit

## Build and Run
Example using g++:

```bash
g++ -std=c++17 -O2 -o project project.cpp
./project
```

Notes:
- The data file is created in the current working directory.
- If the executable is run from a different folder, it will create a new tasks.dat there.

## Complexity (High-Level)
- Add, edit, delete, search, and filter operations are O(n) due to linear scans.
- Sorting is O(n log n).
- File load and save are O(n).

## Known Limitations
- Deadlines are compared as strings, so they must be formatted as YYYY-MM-DD to behave correctly.
- The UI uses ANSI escape codes and may not render colors on all terminals.
- Tasks are stored in a plain text file without escaping, so the pipe character is not supported inside text fields.
- The list view displays row numbers, not IDs, which can be confusing when asked for a task ID.
- The Pomodoro timer blocks the program until it completes or the process is interrupted.

## Extension Ideas
- Validate and parse dates with a real date library.
- Show task IDs in list views.
- Add recurring tasks.
- Add import from CSV.
- Store tasks in JSON for stronger structure and escaping.
