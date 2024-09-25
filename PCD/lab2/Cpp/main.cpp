#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

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

    void addThread(std::thread&& t) {
        threads.push_back(std::move(t));
    }

    void startAllThreads() {
        for (auto& t : threads) {
            if (t.joinable()) {
                t.join(); 
            }
        }
    }

private:
    std::string groupName;
    int maxPriority;
    std::vector<std::thread> threads;
};

void threadTask(const std::string& name) {
    std::cout << "Thread " << name << " is running." << std::endl;
}

int main() {
    ThreadGroup sys("sys");
    sys.list();
    sys.setMaxPriority(9);
    sys.list();

    ThreadGroup g1("g1");
    g1.setMaxPriority(10);

    g1.addThread(std::thread(threadTask, "A"));
    g1.list();

    g1.setMaxPriority(8);
    g1.setMaxPriority(10);
    g1.list();

    g1.addThread(std::thread(threadTask, "B"));
    g1.list();

    g1.setMaxPriority(3);
    g1.addThread(std::thread(threadTask, "C"));
    g1.list();

    ThreadGroup g2("g2");
    g2.list();
    g2.setMaxPriority(10);
    g2.list();

    for (int i = 0; i < 5; ++i) {
        g2.addThread(std::thread(threadTask, std::to_string(i)));
    }

    sys.list();
    std::cout << "Starting all threads:" << std::endl;

    sys.startAllThreads();
    g1.startAllThreads();
    g2.startAllThreads();

    return 0;
}
