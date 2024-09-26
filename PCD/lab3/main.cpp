#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

using namespace std;

mutex mtx;

void printWithDelay(const string& text) {
    lock_guard<mutex> lock(mtx);  
    for (char c : text) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}

void thread1() {
    cout << "Starting Thread 1" << endl;
    printWithDelay("Conditia 1 din tabelul 3");
    
    int sum = 0;
    for (int i = 19; i <= 119; i += 2) { // [19, 119]
        if (i + 1 <= 119) {
            sum += i * (i + 1);
        }
    }
    
    {
        lock_guard<mutex> lock(mtx); 
        cout << "Suma produselor numerelor pe pozitii impare (inceput): " << sum << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Prenumele studentului - Gutu");
}

void thread2() {
    cout << "Starting Thread 2" << endl;
    printWithDelay("Conditia 2 din tabelul 3");

    int sum = 0;
    for (int i = 106; i >= 6; i -= 2) {  // [6, 106]
        if (i - 1 >= 6) {
            sum += i * (i - 1);
        }
    }

    {
        lock_guard<mutex> lock(mtx);  
        cout << "Suma produselor numerelor pe pozitii impare (sfarsit): " << sum << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Numele studentului - Mihai");
}


void thread3() {
    cout << "Starting Thread 3" << endl;
    printWithDelay("Conditia 3 din tabelul 3");

    {
        lock_guard<mutex> lock(mtx);  
        for (int i = 654; i <= 1278; i++) { // [654, 1278]
            cout << i << " ";
        }
        cout << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Denumirea disciplinei - PCD");
}

void thread4() {
    cout << "Starting Thread 4" << endl;
    printWithDelay("Conditia 4 din tabelul 3");

    {
        lock_guard<mutex> lock(mtx);  
        for (int i = 908; i >= 123; i--) { // [123, 908]
            cout << i << " ";
        }
        cout << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(1000));
    printWithDelay("Grupa - CR-211FR");
}

int main() {
    
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);
    thread t4(thread4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
