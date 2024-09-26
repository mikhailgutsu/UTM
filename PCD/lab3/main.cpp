#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

const int SIZE = 100;
int counter = 0;
vector<int> b(SIZE);
vector<int> a;

int pairone = 0;
int pairtwo = 0;

void straightThread() {
    int result = 0;
    cout << "Starting Thread 1" << endl;
    for (int i = 0; i < counter; i += 4) {
        this_thread::sleep_for(chrono::milliseconds(100));

        if ((i + 4) >= counter) {
            continue;
        } else {
            pairone = a[i] + a[i + 1];
            pairtwo = a[i + 2] + a[i + 3];
            result = pairone + pairtwo;
            cout << "Current value for Thread 1 is: " << pairone << " + " << pairtwo << " = " << result << endl;
        }
    }
    cout << "1: Name" << endl;
}

void reverseThread() {
    int result = 0;
    cout << "Starting Thread 2" << endl;
    for (int i = counter - 1; i >= 0; i -= 4) {
        this_thread::sleep_for(chrono::milliseconds(100));

        if ((i - 4) <= 0) {
            continue;
        } else {
            pairone = a[i] + a[i - 1];
            pairtwo = a[i - 2] + a[i - 3];
            result = pairone + pairtwo;
            cout << "Current value for Thread 2 is: " << pairone << " + " << pairtwo << " = " << result << endl;
        }
    }
    cout << "2: Surname" << endl;
}

void straightIntervalThread() {
    cout << "Starting Thread 4" << endl;
    for (int i = 200; i <= 300; ++i) {
        cout << i << " ";
    }
    cout << endl;
    cout << "4: Group" << endl;
}

void reverseIntervalThread() {
    cout << "Starting Thread 3" << endl;
    for (int i = 1000; i <= 1100; ++i) {
        cout << i << " ";
    }
    cout << endl;
    cout << "3: P C D" << endl;
}

int main() {
    cout << "Printing Array: " << endl;
    for (int i = 0; i < SIZE; ++i) {
        b[i] = rand() % 100 + 16; // Random values between 16 and 115
        cout << b[i] << " ";
        if (i == 50) {
            cout << b[i] << " ";
        }
        if (i == 99) {
            cout << endl;
        }
        if (b[i] % 2 == 0) {
            ++counter;
        }
    }

    a.resize(counter);
    int k = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (b[i] % 2 == 0) {
            a[k++] = b[i];
        }
    }

    thread first(straightThread);
    thread second(reverseThread);
    thread third(reverseIntervalThread);
    thread fourth(straightIntervalThread);

    first.join();
    second.join();
    third.join();
    fourth.join();

    return 0;
}
