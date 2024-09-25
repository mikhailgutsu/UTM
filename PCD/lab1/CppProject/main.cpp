#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include "windows.h"

const int ARRAY_SIZE = 100;
int mas[ARRAY_SIZE];

std::mutex mtx;

void sumOddFromStart(int thread_id) {
    int sum = 0;
    for (int i = 1; i < ARRAY_SIZE; i += 2) {
        sum += mas[i];

        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << thread_id << " (from start): mas[" << i << "] = " << mas[i]
                  << ", Current sum = " << sum << std::endl;
    }
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << thread_id << " (from start) final sum of odd positions = " << sum << std::endl;
}

void sumOddFromEnd(int thread_id) {
    int sum = 0;
    for (int i = ARRAY_SIZE - 1; i >= 0; i -= 2) {
        sum += mas[i];

        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << thread_id << " (from end): mas[" << i << "] = " << mas[i]
                  << ", Current sum = " << sum << std::endl;
    }
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << thread_id << " (from end) final sum of odd positions = " << sum << std::endl;
}

int main() {

    std::srand(std::time(0));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        mas[i] = std::rand() % 101;
    }

    std::thread t1(sumOddFromStart, 1);
    std::thread t2(sumOddFromEnd, 2);

    t1.join();
    t2.join();

    system("pause");

    return 0;
}
