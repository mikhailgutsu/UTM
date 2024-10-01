#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstdlib>
#include <ctime>

std::queue<int> depot; // The depot (shared buffer)
std::mutex mtx;        // Mutex for synchronization
std::condition_variable cv_produce, cv_consume;
const int D = 7;       // Maximum size of the depot
const int Z = 4;       // Number of objects each consumer consumes
const int X = 2;       // Number of items produced per iteration
const std::vector<int> odd_numbers = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}; // Odd numbers

// Producer function
void producer(int id) {
    std::srand(std::time(nullptr) + id); 
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_produce.wait(lock, [] { return depot.size() < D; }); // Wait until there's space in the depot

        // Produce X odd numbers
        for (int i = 0; i < X; ++i) {
            int object = odd_numbers[std::rand() % odd_numbers.size()];
            depot.push(object);
            std::cout << "Producer " << id << " produced: " << object << std::endl;
        }

        cv_consume.notify_all(); // Notify consumers
        if (depot.size() == D) {
            std::cout << "Depot is full!" << std::endl;
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
    }
}

// Consumer function
void consumer(int id) {
    int consumed_count = 0;
    while (consumed_count < Z) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consume.wait(lock, [] { return !depot.empty(); }); // Wait until there is something to consume

        // Consume object
        int object = depot.front();
        depot.pop();
        consumed_count++;
        std::cout << "Consumer " << id << " consumed: " << object << std::endl;

        cv_produce.notify_all(); // Notify producers
        if (depot.empty()) {
            std::cout << "Depot is empty!" << std::endl;
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
    }

    std::cout << "Consumer " << id << " finished consuming " << Z << " objects." << std::endl;
}

int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Create 4 producers
    for (int i = 0; i < 4; ++i) {
        producers.emplace_back(producer, i + 1);
    }

    // Create 4 consumers
    for (int i = 0; i < 4; ++i) {
        consumers.emplace_back(consumer, i + 1);
    }

    // Join threads (wait for them to finish)
    for (auto& p : producers) {
        p.join();
    }

    for (auto& c : consumers) {
        c.join();
    }

    return 0;
}
