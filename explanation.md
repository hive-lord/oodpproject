# C++ Keywords and Library Terms Used

This reference explains the main C++ keywords, standard library types, and common functions used in this project. It focuses on terms a beginner might want to understand while reading project.cpp.

## Core C++ Keywords
- class: Defines a new user-defined type with data and functions.
- public: Section of a class accessible from outside.
- private: Section of a class only accessible inside the class.
- const: Marks values or functions as not modifying state. Examples: const methods or const references.
- static: A variable shared by all instances of a class, or a function with internal linkage (not used here for functions).
- enum class: Strongly typed enumeration scoped inside its name.
- return: Exits a function and optionally returns a value.
- if, else, switch, case, default: Control flow for conditional logic.
- for, while: Looping constructs.
- break, continue: Control loop execution (break exits, continue skips to next iteration).
- true, false: Boolean literals.
- nullptr: Null pointer literal (not used, but common in modern C++).
- new, delete: Dynamic memory operators (not used in this code).
-
## Basic Types and Aliases
- int: Integer type used for IDs, menu choices, and counters.
- bool: Boolean type used for completion status.
- string: std::string, a dynamic string class for text.
- size_t: Unsigned size type used for string sizes and indexing.
- vector: std::vector, a dynamic array container.
-
## I/O and Stream Terms
- cout: Standard output stream used to print text to the terminal.
- cin: Standard input stream used to read user input.
- endl: Inserts a newline and flushes the output stream (not used here, but common).
- flush: Forces buffered output to be written immediately.
- getline: Reads an entire line from input into a string.
- istream, ostream: Base stream types (not used directly but behind cin/cout).
-
## Common Operators and Syntax
- <<: Stream insertion operator for output.
- >>: Stream extraction operator for input.
- ==, !=, <, >, <=, >=: Comparison operators.
- =: Assignment operator.
- +, -, *, /, %: Arithmetic operators.
- ++, --: Increment and decrement.
- &&, ||, !: Logical operators.
- ?: Ternary operator (used in a few short expressions).
- :: Scope resolution operator, used for std:: and class members.
-
## Standard Library Headers Used
- iostream: Provides cin, cout, and stream I/O.
- vector: Provides std::vector.
- string: Provides std::string.
- algorithm: Provides sort, transform, remove_if.
- fstream: Provides file streams ifstream and ofstream.
- sstream: Provides string streams (istringstream).
- iomanip: Provides setw, setfill for formatted output.
- ctime: Provides time, localtime, strftime.
- limits: Provides numeric_limits for input flushing.
- chrono: Provides time durations for sleeping.
- thread: Provides std::this_thread::sleep_for.
-
## Common Functions and Methods Used
- time: Returns the current time as time_t.
- localtime: Converts time_t to local time components.
- strftime: Formats a time into a string.
- numeric_limits<streamsize>::max(): Used to ignore the rest of the input line.
- transform: Applies a function to each element (used to lowercase strings).
- sort: Sorts a container range.
- remove_if: Removes elements matching a predicate (used before erase).
-
## Stream and File Types
- ifstream: Input file stream used to read tasks.dat.
- ofstream: Output file stream used to write tasks.dat and export.txt.
- istringstream: Reads tokens from a string (used to split lines).
-
## Formatting Helpers
- setw: Sets the width of the next output field.
- setfill: Sets the fill character for padded output.
-
## String and Character Details
- substr: Extracts part of a string.
- append: Adds characters to the end of a string.
- to_string: Converts numbers to strings.
-
## Application-Specific Names
- Task: The class representing a single to-do item.
- TaskManager: The class managing the list of tasks and user actions.
- Category: The enum class for task categories.
-
If you want a glossary that also includes each function in project.cpp with a plain-English definition, say the word and I will add it.