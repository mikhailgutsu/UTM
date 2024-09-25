#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mutex>

#include "windows.h"

const int ARRAY_SIZE = 100;
int mas[ARRAY_SIZE];

// Мьютекс для синхронизации вывода в консоль
std::mutex mtx;

// Функция для первого потока: сумма чисел на нечетных позициях, начиная с начала
void sumOddFromStart(int thread_id) {
    int sum = 0;
    for (int i = 1; i < ARRAY_SIZE; i += 2) {
        sum += mas[i];
    }
    // Блокируем вывод в консоль
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << thread_id << " (from start) sum of odd positions = " << sum << std::endl;
}

// Функция для второго потока: сумма чисел на нечетных позициях, начиная с конца
void sumOddFromEnd(int thread_id) {
    int sum = 0;
    for (int i = ARRAY_SIZE - 1; i >= 0; i -= 2) {
        sum += mas[i];
    }
    // Блокируем вывод в консоль
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << thread_id << " (from end) sum of odd positions = " << sum << std::endl;
}

int main() {
    // Инициализация генератора случайных чисел
    std::srand(std::time(0));

    // Заполнение массива случайными числами от 0 до 100
    for (int i = 0; i < ARRAY_SIZE; i++) {
        mas[i] = std::rand() % 101;
    }

    // Создаем два потока
    std::thread t1(sumOddFromStart, 1);
    std::thread t2(sumOddFromEnd, 2);

    // Ожидаем завершения обоих потоков
    t1.join();
    t2.join();

    system("pause");

    return 0;
}
