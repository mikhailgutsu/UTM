#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

// Функция для вывода текста с задержкой в 100 мс между символами
void printWithDelay(const string& text) {
    for (char c : text) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}

// Первый поток: вычисление суммы произведений чисел на нечётных позициях по два элемента
void thread1() {
    cout << "Starting Thread 1" << endl;
    printWithDelay("Conditia 1 din tabelul 3");
    
    int sum = 0;
    for (int i = 19; i <= 119; i += 2) {  // Диапазон [19, 119]
        if (i + 1 <= 119) {
            sum += i * (i + 1);
        }
    }
    
    cout << "Suma produselor numerelor pe pozitii impare (inceput): " << sum << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Prenumele studentului");
}

// Второй поток: вычисление суммы произведений чисел на нечётных позициях по два элемента с конца диапазона
void thread2() {
    cout << "Starting Thread 2" << endl;
    printWithDelay("Conditia 2 din tabelul 3");

    int sum = 0;
    for (int i = 106; i >= 6; i -= 2) {  // Диапазон [6, 106]
        if (i - 1 >= 6) {
            sum += i * (i - 1);
        }
    }

    cout << "Suma produselor numerelor pe pozitii impare (sfarsit): " << sum << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Numele studentului");
}

// Третий поток: проход по диапазону от начала интервала [654, 1278]
void thread3() {
    cout << "Starting Thread 3" << endl;
    printWithDelay("Conditia 3 din tabelul 3");

    for (int i = 654; i <= 1278; i++) {
        cout << i << " ";
    }
    cout << endl;

    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Denumirea disciplinei");
}

// Четвертый поток: проход по диапазону от конца интервала [123, 908]
void thread4() {
    cout << "Starting Thread 4" << endl;
    printWithDelay("Conditia 4 din tabelul 3");

    for (int i = 908; i >= 123; i--) {
        cout << i << " ";
    }
    cout << endl;

    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Grupa");
}

int main() {
    // Запуск четырёх потоков
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);
    thread t4(thread4);

    // Ожидание завершения всех потоков
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
