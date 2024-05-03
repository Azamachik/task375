#include "task1.h"
#include "task2.h"
using namespace task1;
using namespace task2;
int main() {
    int task_number;
    bool exit {false};
    while (!exit) {
    cout << "Select a number of task (1, 2) or 0 (to exit): ";
    cin >> task_number;
    switch (task_number) {
        case 1:
            task259();
            break;
        case 2:
            task375();
            break;
        case 0:
            exit = true;
            break;
        default:
            cout << "Try again!";
            break;
    }
    }
    return 0;
}
