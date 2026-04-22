/*
 ╔══════════════════════════════════════════════════════════════╗
 ║          SMART TO-DO LIST — OOP Project in C++               ║
 ║          Subject : Object Oriented Design & Programming      ║
 ║          Concepts: Encapsulation, Abstraction, Composition   ║
 ╚══════════════════════════════════════════════════════════════╝
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <chrono>
#include <thread>

using namespace std;

// ─────────────────────────────────────────────────
//  ANSI COLOR CODES
// ─────────────────────────────────────────────────
const string RESET   = "\033[0m";
const string BOLD    = "\033[1m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN    = "\033[36m";

// ─────────────────────────────────────────────────
//  UTILITY: ASCII UI Helpers
// ─────────────────────────────────────────────────

void printLine(int len = 62) {
    cout << CYAN;
    for (int i = 0; i < len; i++) cout << "═";
    cout << RESET << "\n";
}

void printHeader() {
    cout << "\n";
    cout << CYAN << BOLD;
    cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    cout << "  ║" << MAGENTA << "  ████████╗ ██████╗ ██████╗  ██████╗                    " << CYAN << "║\n";
    cout << "  ║" << MAGENTA << "     ██╔══╝██╔═══██╗██╔══██╗██╔═══██╗                   " << CYAN << "║\n";
    cout << "  ║" << MAGENTA << "     ██║   ██║   ██║██║  ██║██║   ██║                   " << CYAN << "║\n";
    cout << "  ║" << MAGENTA << "     ██║   ██║   ██║██║  ██║██║   ██║                   " << CYAN << "║\n";
    cout << "  ║" << MAGENTA << "     ██║   ╚██████╔╝██████╔╝╚██████╔╝                   " << CYAN << "║\n";
    cout << "  ║" << MAGENTA << "     ╚═╝    ╚═════╝ ╚═════╝  ╚═════╝                    " << CYAN << "║\n";
    cout << "  ║" << YELLOW << "          S M A R T   T O - D O   L I S T               " << CYAN << "║\n";
    cout << "  ║" << GREEN << "              OOP Project  ·  C++                       " << CYAN << "║\n";
    cout << "  ╚══════════════════════════════════════════════════════════╝\n";
    cout << RESET << "\n";
}

void printSuccess(const string& msg) {
    cout << GREEN << BOLD << "  ✔  " << msg << RESET << "\n";
}

void printError(const string& msg) {
    cout << RED << BOLD << "  ✘  " << msg << RESET << "\n";
}

void printInfo(const string& msg) {
    cout << BLUE << BOLD << "  ℹ  " << msg << RESET << "\n";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\n  Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string padRight(string s, size_t width) {
    if (s.length() < width) s.append(width - s.length(), ' ');
    return s;
}

// ─────────────────────────────────────────────────
//  ENUM: Category
// ─────────────────────────────────────────────────
enum class Category {
    GENERAL,
    WORK,
    PERSONAL,
    STUDY,
    HEALTH
};

string categoryToString(Category c) {
    switch (c) {
        case Category::WORK:     return "Work";
        case Category::PERSONAL: return "Personal";
        case Category::STUDY:    return "Study";
        case Category::HEALTH:   return "Health";
        default:                 return "General";
    }
}

Category stringToCategory(const string& s) {
    if (s == "Work")     return Category::WORK;
    if (s == "Personal") return Category::PERSONAL;
    if (s == "Study")    return Category::STUDY;
    if (s == "Health")   return Category::HEALTH;
    return Category::GENERAL;
}

// ─────────────────────────────────────────────────
//  CLASS: Task
//  Encapsulates a single to-do item
// ─────────────────────────────────────────────────
class Task {
private:
    static int idCounter;   // class-level ID counter
    int         id;
    string      title;
    string      description;
    int         priority;   // 1=High, 2=Medium, 3=Low
    bool        isCompleted;
    string      deadline;
    Category    category;
    string      createdAt;

    // Helper: get current timestamp
    string getCurrentTime() {
        time_t now = time(nullptr);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
        return string(buf);
    }

public:
    // ── Constructor ──────────────────────────────
    Task(const string& title,
         int priority,
         const string& description = "",
         const string& deadline    = "N/A",
         Category category         = Category::GENERAL)
        : id(++idCounter),
          title(title),
          description(description),
          priority(priority),
          isCompleted(false),
          deadline(deadline),
          category(category)
    {
        createdAt = getCurrentTime();
    }

    // ── Constructor for loading from file ────────
    Task(int id, const string& title, const string& description,
         int priority, bool isCompleted, const string& deadline,
         const string& category, const string& createdAt)
        : id(id),
          title(title),
          description(description),
          priority(priority),
          isCompleted(isCompleted),
          deadline(deadline),
          category(stringToCategory(category)),
          createdAt(createdAt)
    {
        if (id >= idCounter) idCounter = id + 1;
    }

    // ── Getters (Encapsulation) ──────────────────
    int         getId()          const { return id; }
    string      getTitle()       const { return title; }
    string      getDescription() const { return description; }
    int         getPriority()    const { return priority; }
    bool        getIsCompleted() const { return isCompleted; }
    string      getDeadline()    const { return deadline; }
    Category    getCategory()    const { return category; }
    string      getCreatedAt()   const { return createdAt; }

    // ── Setters ──────────────────────────────────
    void setTitle(const string& t)       { title = t; }
    void setDescription(const string& d) { description = d; }
    void setPriority(int p)              { priority = p; }
    void setDeadline(const string& d)    { deadline = d; }
    void setCategory(Category c)         { category = c; }

    // ── Mark as Completed ────────────────────────
    void markCompleted() {
        isCompleted = true;
    }

    void markPending() {
        isCompleted = false;
    }

    // ── Check if Overdue ─────────────────────────
    bool isOverdue() const {
        if (isCompleted || deadline == "N/A") return false;
        time_t now = time(nullptr);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
        string today(buf);
        return deadline < today;
    }

    // ── Priority String (No ANSI) ────────────────
    string priorityStr() const {
        if (priority == 1) return "[!!!] HIGH";
        if (priority == 2) return "[ ! ] MEDIUM";
        return               "[   ] LOW";
    }

    // ── Status String (No ANSI) ──────────────────
    string statusStr() const {
        return isCompleted ? "[✔]" : "[ ]";
    }

    // ── Display a single task row ─────────────────
    void displayTask(int index = -1) const {
        string idx = (index >= 0) ? to_string(index + 1) + "." : "  ";
        
        string statusCol = isCompleted ? GREEN : CYAN;
        string priCol = (priority == 1) ? RED : (priority == 2) ? YELLOW : GREEN;
        string catCol = MAGENTA;
        string overdueTag = isOverdue() ? (RED + BOLD + " [OVERDUE]" + RESET) : "";

        cout << CYAN << "  │ " << RESET 
             << padRight(idx, 3) << " "
             << statusCol << padRight(statusStr(), 3) << RESET << "  "
             << padRight(title.substr(0, 26), 26) << " "
             << priCol << padRight(priorityStr(), 12) << RESET << " "
             << catCol << padRight(categoryToString(category).substr(0, 9), 9) << RESET
             << overdueTag;
        
        // Print right border properly aligned by padding the rest
        int overdueLen = isOverdue() ? 10 : 0;
        int remaining = 11 - overdueLen; // Adjust based on total width 
        if (remaining > 0) cout << string(remaining, ' ');
        cout << CYAN << "│\n" << RESET;
    }

    // ── Display full task details ─────────────────
    void displayFull() const {
        string statusCol = isCompleted ? GREEN : YELLOW;
        string priCol = (priority == 1) ? RED : (priority == 2) ? YELLOW : GREEN;
        string overdueTag = isOverdue() ? (RED + BOLD + " [OVERDUE!]" + RESET) : "";

        cout << "\n";
        cout << CYAN << "  ┌─────────────────────────────────────────────────────┐\n";
        cout << "  │" << RESET << BOLD << "           TASK DETAILS                              " << CYAN << "│\n";
        cout << "  ├─────────────────────────────────────────────────────┤\n";
        cout << "  │" << RESET << "  ID          : " << padRight(to_string(id), 36) << CYAN << "│\n";
        cout << "  │" << RESET << "  Title       : " << padRight(title.substr(0,35), 36) << CYAN << "│\n";
        cout << "  │" << RESET << "  Description : " << padRight(description.empty() ? "—" : description.substr(0,35), 36) << CYAN << "│\n";
        cout << "  │" << RESET << "  Priority    : " << priCol << padRight(priorityStr(), 36) << CYAN << "│\n";
        cout << "  │" << RESET << "  Category    : " << MAGENTA << padRight(categoryToString(category), 36) << CYAN << "│\n";
        cout << "  │" << RESET << "  Status      : " << statusCol << padRight(isCompleted ? "✔ Completed" : "○ Pending", 36) << CYAN << "│\n";
        
        string deadLinePad = deadline;
        if (isOverdue()) deadLinePad += " [OVERDUE]";
        
        cout << "  │" << RESET << "  Deadline    : " << (isOverdue() ? RED : RESET) << padRight(deadLinePad, 36) << CYAN << "│\n";
        cout << "  │" << RESET << "  Created At  : " << padRight(createdAt, 36) << CYAN << "│\n";
        cout << "  └─────────────────────────────────────────────────────┘\n" << RESET;
    }

    // ── Serialize to CSV line ─────────────────────
    string serialize() const {
        return to_string(id) + "|" +
               title + "|" +
               description + "|" +
               to_string(priority) + "|" +
               (isCompleted ? "1" : "0") + "|" +
               deadline + "|" +
               categoryToString(category) + "|" +
               createdAt;
    }
};

// Initialize static member
int Task::idCounter = 0;

// ─────────────────────────────────────────────────
//  CLASS: TaskManager
//  Manages the full collection of tasks
// ─────────────────────────────────────────────────
class TaskManager {
private:
    vector<Task> tasks;
    string       saveFile;

    // ── Find task index by ID ─────────────────────
    int findById(int id) const {
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (tasks[i].getId() == id) return i;
        }
        return -1;
    }

    // ── Validate priority input ───────────────────
    bool validPriority(int p) const {
        return (p >= 1 && p <= 3);
    }

public:
    // ── Constructor ──────────────────────────────
    TaskManager(const string& file = "tasks.dat") : saveFile(file) {
        loadFromFile();
    }

    // ── Destructor ───────────────────────────────
    ~TaskManager() {
        saveToFile();
    }

    // ── Add Task ─────────────────────────────────
    void addTask() {
        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────┐\n";
        cout << "  │               ADD NEW TASK                          │\n";
        cout << "  └─────────────────────────────────────────────────────┘\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Title
        string title;
        cout << "  Title       : ";
        getline(cin, title);
        if (title.empty()) {
            printError("Title cannot be empty.");
            return;
        }

        // Description
        string desc;
        cout << "  Description : ";
        getline(cin, desc);

        // Priority
        int priority;
        cout << "  Priority    : [1] High  [2] Medium  [3] Low  → ";
        cin >> priority;
        if (!validPriority(priority)) {
            printError("Invalid priority. Defaulting to Low.");
            priority = 3;
        }

        // Deadline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string deadline;
        cout << "  Deadline    : (YYYY-MM-DD or N/A) → ";
        getline(cin, deadline);
        if (deadline.empty()) deadline = "N/A";

        // Category
        cout << "  Category    : [1] General  [2] Work  [3] Personal  [4] Study  [5] Health → ";
        int catChoice;
        cin >> catChoice;
        Category cat = Category::GENERAL;
        switch (catChoice) {
            case 2: cat = Category::WORK;     break;
            case 3: cat = Category::PERSONAL; break;
            case 4: cat = Category::STUDY;    break;
            case 5: cat = Category::HEALTH;   break;
            default: cat = Category::GENERAL; break;
        }

        tasks.emplace_back(title, priority, desc, deadline, cat);
        saveToFile();
        printSuccess("Task \"" + title + "\" added successfully!");
    }

    // ── Remove Task ───────────────────────────────
    void removeTask() {
        if (tasks.empty()) {
            printError("No tasks to remove.");
            return;
        }
        displayTasks();

        cout << "\n  Enter Task ID to delete → ";
        int id;
        cin >> id;

        int idx = findById(id);
        if (idx == -1) {
            printError("Task ID not found.");
            return;
        }

        string removedTitle = tasks[idx].getTitle();

        cout << "  Confirm delete \"" << removedTitle << "\"? [y/n] → ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            tasks.erase(tasks.begin() + idx);
            saveToFile();
            printSuccess("Task \"" + removedTitle + "\" removed.");
        } else {
            printInfo("Delete cancelled.");
        }
    }

    // ── Mark Task Completed ───────────────────────
    void markTaskCompleted() {
        if (tasks.empty()) {
            printError("No tasks available.");
            return;
        }
        displayPendingTasks();

        cout << "\n  Enter Task ID to mark complete → ";
        int id;
        cin >> id;

        int idx = findById(id);
        if (idx == -1) {
            printError("Task ID not found.");
            return;
        }

        if (tasks[idx].getIsCompleted()) {
            printInfo("Task is already completed.");
            return;
        }

        tasks[idx].markCompleted();
        saveToFile();
        printSuccess("Task \"" + tasks[idx].getTitle() + "\" marked as completed! ✔");
    }

    // ── Mark Task Pending ─────────────────────────
    void markTaskPending() {
        if (tasks.empty()) {
            printError("No tasks available.");
            return;
        }
        displayCompletedTasks();

        cout << "\n  Enter Task ID to mark as pending → ";
        int id;
        cin >> id;

        int idx = findById(id);
        if (idx == -1) {
            printError("Task ID not found.");
            return;
        }

        tasks[idx].markPending();
        saveToFile();
        printInfo("Task \"" + tasks[idx].getTitle() + "\" marked as pending.");
    }

    // ── Display All Tasks ─────────────────────────
    void displayTasks() const {
        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
        cout << "  │                     ALL TASKS                               │\n";
        cout << "  ├───┬───────────────────────────────┬──────────────┬──────────┤\n";
        cout << "  │ # │ Title                         │ Priority     │ Category │\n";
        cout << "  ├───┼───────────────────────────────┼──────────────┼──────────┤\n";

        if (tasks.empty()) {
            cout << "  │           No tasks found. Add one to get started!           │\n";
        } else {
            for (int i = 0; i < (int)tasks.size(); i++) {
                tasks[i].displayTask(i);
            }
        }

        cout << "  └─────────────────────────────────────────────────────────────┘\n";
        cout << "  Total: " << tasks.size() << " task(s)  |  "
             << "Completed: " << countCompleted() << "  |  "
             << "Pending: " << (tasks.size() - countCompleted()) << "\n";
    }

    // ── Display Pending Only ──────────────────────
    void displayPendingTasks() const {
        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
        cout << "  │                   PENDING TASKS                             │\n";
        cout << "  ├───┬───────────────────────────────┬──────────────┬──────────┤\n";
        cout << "  │ # │ Title                         │ Priority     │ Category │\n";
        cout << "  ├───┼───────────────────────────────┼──────────────┼──────────┤\n";

        int count = 0;
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (!tasks[i].getIsCompleted()) {
                tasks[i].displayTask(count);
                count++;
            }
        }

        if (count == 0) {
            cout << "  │          No pending tasks! You're all caught up. ✔          │\n";
        }

        cout << "  └─────────────────────────────────────────────────────────────┘\n";
    }

    // ── Display Completed Only ────────────────────
    void displayCompletedTasks() const {
        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
        cout << "  │                  COMPLETED TASKS                            │\n";
        cout << "  ├───┬───────────────────────────────┬──────────────┬──────────┤\n";
        cout << "  │ # │ Title                         │ Priority     │ Category │\n";
        cout << "  ├───┼───────────────────────────────┼──────────────┼──────────┤\n";

        int count = 0;
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (tasks[i].getIsCompleted()) {
                tasks[i].displayTask(count);
                count++;
            }
        }

        if (count == 0) {
            cout << "  │           No completed tasks yet. Keep going!               │\n";
        }

        cout << "  └─────────────────────────────────────────────────────────────┘\n";
    }

    // ── View Task Details ─────────────────────────
    void viewTaskDetails() const {
        if (tasks.empty()) {
            printError("No tasks available.");
            return;
        }
        displayTasks();

        cout << "\n  Enter Task ID for details → ";
        int id;
        cin >> id;

        int idx = findById(id);
        if (idx == -1) {
            printError("Task ID not found.");
            return;
        }

        tasks[idx].displayFull();
    }

    // ── Edit Task ─────────────────────────────────
    void editTask() {
        if (tasks.empty()) {
            printError("No tasks to edit.");
            return;
        }
        displayTasks();

        cout << "\n  Enter Task ID to edit → ";
        int id;
        cin >> id;

        int idx = findById(id);
        if (idx == -1) {
            printError("Task ID not found.");
            return;
        }

        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────┐\n";
        cout << "  │  EDIT TASK (press ENTER to keep current value)      │\n";
        cout << "  └─────────────────────────────────────────────────────┘\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string input;

        cout << "  Title       [" << tasks[idx].getTitle() << "] : ";
        getline(cin, input);
        if (!input.empty()) tasks[idx].setTitle(input);

        cout << "  Description [" << tasks[idx].getDescription() << "] : ";
        getline(cin, input);
        if (!input.empty()) tasks[idx].setDescription(input);

        cout << "  Priority    [" << tasks[idx].getPriority() << "] (1/2/3) : ";
        getline(cin, input);
        if (!input.empty()) {
            int p = stoi(input);
            if (validPriority(p)) tasks[idx].setPriority(p);
        }

        cout << "  Deadline    [" << tasks[idx].getDeadline() << "] : ";
        getline(cin, input);
        if (!input.empty()) tasks[idx].setDeadline(input);

        saveToFile();
        printSuccess("Task updated successfully.");
    }

    // ── Sort by Priority ──────────────────────────
    void sortByPriority() {
        if (tasks.empty()) {
            printError("No tasks to sort.");
            return;
        }

        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.getPriority() < b.getPriority();
        });

        saveToFile();
        printSuccess("Tasks sorted by priority (High → Low).");
        displayTasks();
    }

    // ── Sort by Status ────────────────────────────
    void sortByStatus() {
        if (tasks.empty()) {
            printError("No tasks to sort.");
            return;
        }

        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return (!a.getIsCompleted()) > (!b.getIsCompleted());
        });

        saveToFile();
        printSuccess("Tasks sorted: Pending first.");
        displayTasks();
    }

    // ── Search Tasks ──────────────────────────────
    void searchTasks() const {
        if (tasks.empty()) {
            printError("No tasks available.");
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Search keyword → ";
        string keyword;
        getline(cin, keyword);

        // Convert to lowercase for case-insensitive search
        string kw = keyword;
        transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
        cout << "  │              SEARCH RESULTS for: " << left << setw(27) << keyword << " │\n";
        cout << "  ├───┬───────────────────────────────┬──────────────┬──────────┤\n";
        cout << "  │ # │ Title                         │ Priority     │ Category │\n";
        cout << "  ├───┼───────────────────────────────┼──────────────┼──────────┤\n";

        int count = 0;
        for (int i = 0; i < (int)tasks.size(); i++) {
            string t = tasks[i].getTitle();
            transform(t.begin(), t.end(), t.begin(), ::tolower);
            string d = tasks[i].getDescription();
            transform(d.begin(), d.end(), d.begin(), ::tolower);

            if (t.find(kw) != string::npos || d.find(kw) != string::npos) {
                tasks[i].displayTask(count);
                count++;
            }
        }

        if (count == 0) {
            cout << "  │           No tasks matched your search.                     │\n";
        }

        cout << "  └─────────────────────────────────────────────────────────────┘\n";
        cout << "  Found " << count << " result(s).\n";
    }

    // ── Filter by Category ────────────────────────
    void filterByCategory() const {
        cout << "\n  Category: [1] General  [2] Work  [3] Personal  [4] Study  [5] Health → ";
        int choice;
        cin >> choice;

        Category cat;
        switch (choice) {
            case 2: cat = Category::WORK;     break;
            case 3: cat = Category::PERSONAL; break;
            case 4: cat = Category::STUDY;    break;
            case 5: cat = Category::HEALTH;   break;
            default: cat = Category::GENERAL; break;
        }

        cout << "\n";
        cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
        cout << "  │          FILTERED BY: " << left << setw(38) << categoryToString(cat) << " │\n";
        cout << "  ├───┬───────────────────────────────┬──────────────┬──────────┤\n";
        cout << "  │ # │ Title                         │ Priority     │ Category │\n";
        cout << "  ├───┼───────────────────────────────┼──────────────┼──────────┤\n";

        int count = 0;
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (tasks[i].getCategory() == cat) {
                tasks[i].displayTask(count);
                count++;
            }
        }

        if (count == 0) {
            cout << "  │           No tasks in this category.                        │\n";
        }

        cout << "  └─────────────────────────────────────────────────────────────┘\n";
    }

    // ── Statistics Dashboard ──────────────────────
    void showStatistics() const {
        int total     = tasks.size();
        int completed = countCompleted();
        int pending   = total - completed;
        int high = 0, medium = 0, low = 0;
        int work = 0, personal = 0, study = 0, health = 0, general = 0;

        for (const auto& t : tasks) {
            if (t.getPriority() == 1) high++;
            else if (t.getPriority() == 2) medium++;
            else low++;

            switch (t.getCategory()) {
                case Category::WORK:     work++;     break;
                case Category::PERSONAL: personal++; break;
                case Category::STUDY:    study++;    break;
                case Category::HEALTH:   health++;   break;
                default:                 general++;  break;
            }
        }

        int pct = (total > 0) ? (completed * 100 / total) : 0;

        // Progress bar
        int barFill = pct / 5; // 20 chars wide
        string bar = string(barFill, '#') + string(20 - barFill, '.');

        cout << "\n";
        cout << "  ╔═════════════════════════════════════════════════════╗\n";
        cout << "  ║              STATISTICS  DASHBOARD                  ║\n";
        cout << "  ╠═════════════════════════════════════════════════════╣\n";
        cout << "  ║  Total Tasks    : " << left << setw(33) << total    << " ║\n";
        cout << "  ║  Completed      : " << setw(33) << completed        << " ║\n";
        cout << "  ║  Pending        : " << setw(33) << pending          << " ║\n";
        cout << "  ╠═════════════════════════════════════════════════════╣\n";
        cout << "  ║  Progress  [" << bar << "] " << setw(3) << pct << "%  ║\n";
        cout << "  ╠═════════════════════════════════════════════════════╣\n";
        cout << "  ║  Priority Breakdown:                                ║\n";
        cout << "  ║    [!!!] High    : " << setw(33) << high            << " ║\n";
        cout << "  ║    [ ! ] Medium  : " << setw(33) << medium          << " ║\n";
        cout << "  ║    [   ] Low     : " << setw(33) << low             << " ║\n";
        cout << "  ╠═════════════════════════════════════════════════════╣\n";
        cout << "  ║  Category Breakdown:                                ║\n";
        cout << "  ║    General       : " << setw(33) << general         << " ║\n";
        cout << "  ║    Work          : " << setw(33) << work            << " ║\n";
        cout << "  ║    Personal      : " << setw(33) << personal        << " ║\n";
        cout << "  ║    Study         : " << setw(33) << study           << " ║\n";
        cout << "  ║    Health        : " << setw(33) << health          << " ║\n";
        cout << "  ╚═════════════════════════════════════════════════════╝\n";
    }

    // ── Clear All Completed ───────────────────────
    void clearCompleted() {
        int before = tasks.size();
        tasks.erase(
            remove_if(tasks.begin(), tasks.end(),
                      [](const Task& t) { return t.getIsCompleted(); }),
            tasks.end()
        );
        int removed = before - tasks.size();
        saveToFile();
        if (removed > 0)
            printSuccess(to_string(removed) + " completed task(s) removed.");
        else
            printInfo("No completed tasks to remove.");
    }

    // ── Count Completed ───────────────────────────
    int countCompleted() const {
        int c = 0;
        for (const auto& t : tasks) if (t.getIsCompleted()) c++;
        return c;
    }

    // ── Duplicate Task ────────────────────────────
    void duplicateTask() {
        if (tasks.empty()) {
            printError("No tasks available to duplicate.");
            return;
        }
        displayTasks();

        cout << "\n  Enter Task ID to duplicate → ";
        int id;
        cin >> id;

        int idx = findById(id);
        if (idx == -1) {
            printError("Task ID not found.");
            return;
        }

        const Task& t = tasks[idx];
        // Create new task with same details
        tasks.emplace_back(t.getTitle() + " (Copy)", t.getPriority(), t.getDescription(), t.getDeadline(), t.getCategory());
        saveToFile();
        printSuccess("Task duplicated successfully!");
    }

    // ── Export Tasks ──────────────────────────────
    void exportTasks() const {
        if (tasks.empty()) {
            printError("No tasks to export.");
            return;
        }

        string filename = "export.txt";
        ofstream file(filename);
        if (!file.is_open()) {
            printError("Could not open file for exporting.");
            return;
        }

        file << "SMART TO-DO LIST - EXPORTED TASKS\n";
        file << "=================================\n\n";

        for (const auto& t : tasks) {
            file << "Task: " << t.getTitle() << "\n";
            file << "Description: " << (t.getDescription().empty() ? "N/A" : t.getDescription()) << "\n";
            file << "Status: " << (t.getIsCompleted() ? "Completed" : "Pending") << "\n";
            file << "Priority: " << t.priorityStr() << "\n";
            file << "Category: " << categoryToString(t.getCategory()) << "\n";
            file << "Deadline: " << t.getDeadline() << "\n";
            file << "---------------------------------\n";
        }

        file.close();
        printSuccess("Tasks exported to " + filename + " !");
    }

    // ── Pomodoro Timer ────────────────────────────
    void pomodoroTimer() {
        cout << "\n";
        cout << CYAN << "  ┌─────────────────────────────────────────────────────┐\n";
        cout << "  │" << RESET << BOLD << "              POMODORO TIMER                         " << CYAN << "│\n";
        cout << "  └─────────────────────────────────────────────────────┘\n" << RESET;
        
        cout << "  [1] 25 min Focus\n";
        cout << "  [2] 5 min Break\n";
        cout << "  [3] Custom Minutes\n";
        cout << "  [0] Cancel\n";
        cout << "  → Enter choice: ";
        
        int choice;
        cin >> choice;
        int minutes = 0;
        
        if (choice == 1) minutes = 25;
        else if (choice == 2) minutes = 5;
        else if (choice == 3) {
            cout << "  Enter minutes: ";
            cin >> minutes;
        } else {
            printInfo("Pomodoro cancelled.");
            return;
        }

        if (minutes <= 0) {
            printError("Invalid minutes.");
            return;
        }

        int totalSeconds = minutes * 60;
        clearScreen();

        for (int s = totalSeconds; s > 0; --s) {
            int m_left = s / 60;
            int s_left = s % 60;

            cout << "\r  " << MAGENTA << "⏳ Time Remaining: " << BOLD 
                 << setfill('0') << setw(2) << m_left << ":" 
                 << setfill('0') << setw(2) << s_left << RESET << setfill(' ') 
                 << "  (Press Ctrl+C to abort)    " << flush;

            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << "\n";
        cout << "\a"; // system bell
        printSuccess("Time's up! Great job!");
    }

    // ── Save to File ──────────────────────────────
    void saveToFile() const {
        ofstream file(saveFile);
        if (!file.is_open()) {
            return; // silently fail (file saving is optional)
        }
        for (const auto& t : tasks) {
            file << t.serialize() << "\n";
        }
        file.close();
    }

    // ── Load from File ────────────────────────────
    void loadFromFile() {
        ifstream file(saveFile);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            istringstream ss(line);
            string token;
            vector<string> fields;

            while (getline(ss, token, '|')) {
                fields.push_back(token);
            }

            if (fields.size() < 8) continue;

            int    id          = stoi(fields[0]);
            string title       = fields[1];
            string desc        = fields[2];
            int    priority    = stoi(fields[3]);
            bool   completed   = (fields[4] == "1");
            string deadline    = fields[5];
            string category    = fields[6];
            string createdAt   = fields[7];

            tasks.emplace_back(id, title, desc, priority, completed, deadline, category, createdAt);
        }
        file.close();
    }
};

// ─────────────────────────────────────────────────
//  FUNCTION: Display Main Menu
// ─────────────────────────────────────────────────
void displayMenu() {
    cout << "\n";
    cout << CYAN << "  ┌─────────────────────────────────────────────────────┐\n";
    cout << "  │" << RESET << BOLD << "                     M A I N   M E N U               " << CYAN << "│\n";
    cout << "  ├────────┬────────────────────────────────────────────┤\n";
    cout << "  │" << YELLOW << "  TASK  " << CYAN << "│  [1] Add Task                              │\n";
    cout << "  │        │  [2] View All Tasks                        │\n";
    cout << "  │        │  [3] View Task Details                     │\n";
    cout << "  │        │  [4] Edit Task                             │\n";
    cout << "  │        │  [5] Delete Task                           │\n";
    cout << "  │        │  [16] Duplicate Task                       │\n";
    cout << "  ├────────┼────────────────────────────────────────────┤\n";
    cout << "  │" << GREEN << " STATUS " << CYAN << "│  [6] Mark Task as Completed                │\n";
    cout << "  │        │  [7] Mark Task as Pending                  │\n";
    cout << "  │        │  [8] View Completed Tasks                  │\n";
    cout << "  │        │  [9] View Pending Tasks                    │\n";
    cout << "  ├────────┼────────────────────────────────────────────┤\n";
    cout << "  │" << MAGENTA << "  SORT  " << CYAN << "│  [10] Sort by Priority                     │\n";
    cout << "  │        │  [11] Sort by Status                       │\n";
    cout << "  ├────────┼────────────────────────────────────────────┤\n";
    cout << "  │" << BLUE << " FILTER " << CYAN << "│  [12] Search Tasks                         │\n";
    cout << "  │        │  [13] Filter by Category                   │\n";
    cout << "  ├────────┼────────────────────────────────────────────┤\n";
    cout << "  │" << RED << "  MISC  " << CYAN << "│  [14] Statistics Dashboard                 │\n";
    cout << "  │        │  [15] Clear All Completed Tasks            │\n";
    cout << "  │        │  [17] Export Tasks to File                 │\n";
    cout << "  │        │  [18] Pomodoro Timer                       │\n";
    cout << "  │        │  [0]  Exit                                 │\n";
    cout << "  └────────┴────────────────────────────────────────────┘\n" << RESET;
    cout << "  → Enter choice: ";
}

// ─────────────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────────────
int main() {
    TaskManager manager("tasks.dat");

    printHeader();
    printInfo("Tasks are auto-saved to  tasks.dat");
    printInfo("Type a number from the menu and press ENTER.\n");

    int choice;

    while (true) {
        displayMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Invalid input. Please enter a number.");
            continue;
        }

        cout << "\n";
        printLine();

        switch (choice) {
            case 1:  manager.addTask();            break;
            case 2:  manager.displayTasks();       break;
            case 3:  manager.viewTaskDetails();    break;
            case 4:  manager.editTask();           break;
            case 5:  manager.removeTask();         break;
            case 6:  manager.markTaskCompleted();  break;
            case 7:  manager.markTaskPending();    break;
            case 8:  manager.displayCompletedTasks(); break;
            case 9:  manager.displayPendingTasks(); break;
            case 10: manager.sortByPriority();     break;
            case 11: manager.sortByStatus();       break;
            case 12: manager.searchTasks();        break;
            case 13: manager.filterByCategory();   break;
            case 14: manager.showStatistics();     break;
            case 15: manager.clearCompleted();     break;
            case 16: manager.duplicateTask();      break;
            case 17: manager.exportTasks();        break;
            case 18: manager.pomodoroTimer();      break;
            case 0:
                cout << "\n";
                cout << CYAN << BOLD;
                cout << "  ╔══════════════════════════════════════════════════════════╗\n";
                cout << "  ║      Thanks for using Smart To-Do List!  Goodbye!        ║\n";
                cout << "  ╚══════════════════════════════════════════════════════════╝\n\n" << RESET;
                return 0;
            default:
                printError("Invalid choice. Please try again.");
        }

        pauseScreen();
    }

    return 0;
}
