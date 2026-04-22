# Smart To-Do List (C++ OOP Project)

A terminal-based **Smart To-Do List Manager** built using **C++** for the subject **Object Oriented Design & Programming (OODP)**.
This project demonstrates important OOP concepts such as **Encapsulation, Abstraction, Composition, File Handling, and Modular Design**. 

---

## Features

### Task Management

* Add new tasks
* Edit existing tasks
* Delete tasks
* Duplicate tasks
* View task details

### Task Status

* Mark tasks as completed
* Mark tasks as pending
* View completed tasks
* View pending tasks

### Sorting & Filtering

* Sort tasks by priority
* Sort tasks by completion status
* Search tasks using keywords
* Filter tasks by category

### Productivity Tools

* Statistics dashboard
* Pomodoro timer
* Export tasks to text file

### Data Persistence

* Auto-saves tasks to `tasks.dat`
* Loads saved tasks on startup

---

## OOP Concepts Used

### Encapsulation

The `Task` class stores task details as private members and uses getters/setters.

```cpp
private:
    string title;
    int priority;
    bool isCompleted;
```

### Abstraction

Complex operations are hidden behind simple methods such as:

```cpp
addTask()
removeTask()
saveToFile()
markTaskCompleted()
```

### Composition

The `TaskManager` class manages multiple `Task` objects.

```cpp
vector<Task> tasks;
```

### Constructor & Destructor

Used for initialization and automatic saving.

```cpp
TaskManager() { loadFromFile(); }
~TaskManager() { saveToFile(); }
```

---

## Project Structure

```text
oodpproject/
│── main.cpp
│── tasks.dat
│── export.txt
│── README.md
```

---

## Categories

* General
* Work
* Personal
* Study
* Health

---

## Priority Levels

| Level | Meaning |
| ----- | ------- |
| 1     | High    |
| 2     | Medium  |
| 3     | Low     |

---

## How to Compile and Run

### Linux / macOS

```bash
g++ main.cpp -o todo
./todo
```

### Windows (MinGW)

```bash
g++ main.cpp -o todo.exe
todo.exe
```

---

## Sample Menu

```text
[1] Add Task
[2] View All Tasks
[3] View Task Details
[4] Edit Task
[5] Delete Task
...
[18] Pomodoro Timer
[0] Exit
```

---

## File Storage

Tasks are stored in:

```text
tasks.dat
```

The file is automatically updated whenever changes are made.

---

## Suggested UML Diagrams

### 1. Class Diagram

Classes:

* `Task`
* `TaskManager`

### 2. Use Case Diagram

Actor:

* User

Use Cases:

* Add Task
* Delete Task
* Complete Task
* Search Task
* Export Tasks

### 3. Activity Diagram

```text
Start
 ↓
Display Menu
 ↓
Select Option
 ↓
Perform Action
 ↓
Return to Menu
 ↓
Exit
```

---

## Future Enhancements

* GUI version using Qt
* Notifications and reminders
* Deadline alerts
* Multi-user login system
* Cloud sync

---

## Author

**Hitesh**
B.Tech CSE (Data Science)
SRM University

---

## Subject

**Object Oriented Design & Programming (OODP)**
