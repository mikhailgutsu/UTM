#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include "windows.h"

class ThreadGroup {
public:
    ThreadGroup(const std::string& name) : groupName(name), maxPriority(10) {}

    void setMaxPriority(int priority) {
        maxPriority = priority;
    }

    void list() const {
        std::cout << "Thread Group: " << groupName << ", Max Priority: " << maxPriority << std::endl;
        for (const auto& t : threads) {
            if (t.joinable()) {
                std::cout << "  Thread: " << t.get_id() << std::endl;
            }
        }
    }

    void addThread(std::thread&& t, int priority) {
        threads.push_back(std::move(t));
        priorities.push_back(priority);
    }

    void startAllThreads() {
        for (auto& t : threads) {
            if (t.joinable()) {
                t.join();  
            }
        }
    }

    void showPriorities() const {
        std::cout << "Group: " << groupName << " Priorities: ";
        for (int p : priorities) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }

private:
    std::string groupName;
    int maxPriority;
    std::vector<std::thread> threads;
    std::vector<int> priorities; 
};

void threadTask(const std::string& name, int priority) {
    std::cout << "Thread " << name << " with priority " << priority << " is running." << std::endl;
}

int main() {

    ThreadGroup sys("Main");

    ThreadGroup g1("G1");

    ThreadGroup g3("G3");

    g3.addThread(std::thread(threadTask, "Thf", 3), 3);
    g3.addThread(std::thread(threadTask, "Thb", 7), 7);
    g3.addThread(std::thread(threadTask, "Thc", 3), 3);
    g3.addThread(std::thread(threadTask, "Thd", 3), 3);

    g3.showPriorities();
    g3.list();

    g1.addThread(std::thread(threadTask, "ThA", 3), 3);
    g1.list();

    g1.list();
    g1.showPriorities();

    ThreadGroup g2("G2");

    g2.addThread(std::thread(threadTask, "Th8", 3), 3);
    g2.addThread(std::thread(threadTask, "Th9", 4), 4);
    g2.addThread(std::thread(threadTask, "Th3", 3), 3);
    g2.list();

    sys.addThread(std::thread(threadTask, "Th1", 3), 3);
    sys.addThread(std::thread(threadTask, "Th2", 3), 3);

    sys.list();
    sys.showPriorities();

    std::cout << "Starting all threads:" << std::endl;

    sys.startAllThreads();
    g1.startAllThreads();
    g2.startAllThreads();
    g3.startAllThreads();

    system("pause");

    return 0;
}
