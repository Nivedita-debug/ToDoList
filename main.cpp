#include "TaskManager.h"
#include <iostream>
#include <limits>

void printMenu() {
    std::cout << "\n========== TO-DO LIST ==========\n"
              << " 1. Add Task\n"
              << " 2. View Tasks\n"
              << " 3. Mark Task as Complete\n"
              << " 4. Delete Task\n"
              << " 5. Exit\n"
              << "================================\n"
              << "Choose an option: ";
}

int readInt() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

int main() {
    TaskManager manager("tasks.txt");

    std::cout << "Welcome to the To-Do List App!\n";
    std::cout << "Loaded " << manager.totalTasks() << " task(s) from file.\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt();

        switch (choice) {
        case 1: {
            std::cout << "Enter task description: ";
            std::string desc;
            std::getline(std::cin, desc);
            if (desc.empty()) {
                std::cout << "Description cannot be empty.\n";
            } else {
                manager.addTask(desc);
            }
            break;
        }
        case 2:
            manager.viewTasks();
            std::cout << "Summary: " << manager.completedTasks() << "/"
                      << manager.totalTasks() << " completed.\n";
            break;
        case 3: {
            manager.viewTasks();
            std::cout << "Enter task ID to mark complete: ";
            int id = readInt();
            manager.markComplete(id);
            break;
        }
        case 4: {
            manager.viewTasks();
            std::cout << "Enter task ID to delete: ";
            int id = readInt();
            manager.deleteTask(id);
            break;
        }
        case 5:
            running = false;
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid option. Please choose 1-5.\n";
        }
    }
    return 0;
}
