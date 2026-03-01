#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class Task {
private:
    int id;
    std::string description;
    bool completed;
    std::string createdAt;
    std::string completedAt;

    static std::string currentTimestamp() {
        std::time_t now = std::time(nullptr);
        std::tm* lt = std::localtime(&now);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt);
        return std::string(buf);
    }

public:
    Task() : id(0), completed(false) {}

    Task(int id, const std::string& description)
        : id(id), description(description), completed(false),
          createdAt(currentTimestamp()) {}

    Task(int id, const std::string& description, bool completed,
         const std::string& createdAt, const std::string& completedAt)
        : id(id), description(description), completed(completed),
          createdAt(createdAt), completedAt(completedAt) {}

    int getId() const { return id; }
    const std::string& getDescription() const { return description; }
    bool isCompleted() const { return completed; }
    const std::string& getCreatedAt() const { return createdAt; }
    const std::string& getCompletedAt() const { return completedAt; }

    void markComplete() {
        completed = true;
        completedAt = currentTimestamp();
    }

    std::string statusLabel() const {
        return completed ? "[Done]" : "[Pending]";
    }

    // Serialize to a single line: id|description|completed|createdAt|completedAt
    std::string serialize() const {
        return std::to_string(id) + "|" + description + "|" +
               (completed ? "1" : "0") + "|" + createdAt + "|" + completedAt;
    }

    // Deserialize from a single line
    static Task deserialize(const std::string& line) {
        std::istringstream ss(line);
        std::string token;
        int id;
        std::string desc, createdAt, completedAt;
        bool done;

        std::getline(ss, token, '|'); id = std::stoi(token);
        std::getline(ss, desc, '|');
        std::getline(ss, token, '|'); done = (token == "1");
        std::getline(ss, createdAt, '|');
        std::getline(ss, completedAt, '|');

        return Task(id, desc, done, createdAt, completedAt);
    }
};

#endif
