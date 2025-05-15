To-Do List Manager with Task Prioritization
A console-based To-Do List Manager developed in C++ that helps users efficiently manage and prioritize daily tasks using object-oriented programming principles. This project leverages data structures like priority queues along with custom sorting logic to rank tasks by urgency and importance, helping users stay organized and focused.

## Features
Task Prioritization: Automatically ranks tasks based on urgency and importance using priority queues.
Category-based Filtering: Easily filter tasks by categories such as Work, Personal, Study, etc.
Due Date Management: View and manage tasks according to their due dates.
File Handling: Save and load tasks from files to preserve data between sessions.
Console Interface: Simple, intuitive command-line interface for quick task management.
Object-Oriented Design: Modular and maintainable codebase following OOP concepts.

## Technologies Used
Language: C++
Concepts: Object-Oriented Programming (Classes, Inheritance, Encapsulation)
Data Structures: Priority Queue, Vectors
File Handling: Reading and writing tasks to files for persistent storage.

## Usage
Clone the repository:

```bash
git clone https://github.com/himanshi742/To-Do-List-Manager.git
```
Compile the project:
```bash
g++ main.cpp -o todo_manager

```
Run the executable:
```bash
./todo_manager
```
Follow the on-screen menu to add, view, filter, or delete tasks.

## How It Works
1.Tasks are stored as objects containing details like title, description, category, priority, and due date.
2.A priority queue sorts tasks, ensuring the most urgent and important ones are displayed first.
3.Users can filter tasks based on category or due date to focus on specific task groups.
4.All task data is saved to and loaded from a file, allowing persistent task management across sessions.

## Contributing
Contributions are welcome! Feel free to fork the repo and submit pull requests to add new features or improve existing functionality.
