#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class TaskManager {
private:
    std::vector<Task> tasks;
    std::string filename;
    int nextId;

    void updateNextId() {
        nextId = 1;
        for (const auto& t : tasks) {
            if (t.getId() >= nextId)
                nextId = t.getId() + 1;
        }
    }

public:
    TaskManager(const std::string& filename = "tasks.txt")
        : filename(filename), nextId(1) {
        load();
    }

    void load() {
        tasks.clear();
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                tasks.push_back(Task::deserialize(line));
            }
        }
        file.close();
        updateNextId();
    }

    void save() const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not save to " << filename << "\n";
            return;
        }
        for (const auto& t : tasks) {
            file << t.serialize() << "\n";
        }
        file.close();
    }

    void addTask(const std::string& description) {
        tasks.emplace_back(nextId++, description);
        save();
        std::cout << "Task added successfully.\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks found.\n";
            return;
        }

        std::cout << "\n"
                  << std::string(70, '-') << "\n"
                  << " ID  | Status    | Description              | Timestamps\n"
                  << std::string(70, '-') << "\n";

        for (const auto& t : tasks) {
            std::cout << " " << std::left << std::setw(4) << t.getId()
                      << "| " << std::setw(10) << t.statusLabel()
                      << "| " << std::setw(25) << t.getDescription().substr(0, 24)
                      << "| Created: " << t.getCreatedAt();
            if (t.isCompleted()) {
                std::cout << "\n      |           |                          "
                          << "| Done:    " << t.getCompletedAt();
            }
            std::cout << "\n";
        }
        std::cout << std::string(70, '-') << "\n";
    }

    bool markComplete(int id) {
        for (auto& t : tasks) {
            if (t.getId() == id) {
                if (t.isCompleted()) {
                    std::cout << "Task is already marked as done.\n";
                    return false;
                }
                t.markComplete();
                save();
                std::cout << "Task " << id << " marked as complete.\n";
                return true;
            }
        }
        std::cout << "Task with ID " << id << " not found.\n";
        return false;
    }

    bool deleteTask(int id) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [id](const Task& t) { return t.getId() == id; });

        if (it != tasks.end()) {
            std::cout << "Deleted task: " << it->getDescription() << "\n";
            tasks.erase(it);
            save();
            return true;
        }
        std::cout << "Task with ID " << id << " not found.\n";
        return false;
    }

    int totalTasks() const { return static_cast<int>(tasks.size()); }

    int completedTasks() const {
        return static_cast<int>(std::count_if(tasks.begin(), tasks.end(),
            [](const Task& t) { return t.isCompleted(); }));
    }
};

#endif
