#include <Windows.h>
#include <process.h>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct myData {
    int* arr_;
    int size_;
    int max_negative;
    myData(int size) {
        size_ = size;
        arr_ = new int[size];
        for (int i = 0; i < size; i++) {
            cout << "Enter " << i << "th element of array: ";
            cin >> arr_[i];
        }
        max_negative = INT_MAX;
    }
};
 
 
void WINAPI option_1(LPVOID data) {
    for (int i = 0; i < ((myData*)data)->size_; i++) {
        if (((myData*)data)->arr_[i] < 0) {
            ((myData*)data)->max_negative = max(((myData*)data)->max_negative, ((myData*)data)->arr_[i]);
        }
    }
    cout << "The max element of negative elements is " << ((myData*)data)->max_negative << endl;
 
}
 
unsigned __stdcall option_2(void* data) {
    for (int i = 0; i < ((myData*)data)->size_; i++) {
        if (((myData*)data)->arr_[i] < 0) {
            ((myData*)data)->max_negative = max(((myData*)data)->max_negative, ((myData*)data)->arr_[i]);
        }
    }
    cout << "The max element of negative elements is " << ((myData*)data)->max_negative << endl;
    return 0;
}
 
int main() {
    HANDLE workerThread;
    DWORD IDWorkerThread;
 
    cout << "Enter size of array: ";
    int size; cin >> size;
 
    auto param = new myData(size);
    int time;
    cout << "Enter time stop time (s): ";
    cin >> time;
 
    // workerThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)option_1, (LPVOID)param, 0, &IDWorkerThread);
    workerThread = (HANDLE)_beginthreadex(NULL, 0, &option_2, (void*)param, 0, (unsigned int*)&IDWorkerThread);
 
    if (workerThread == NULL) {
        return GetLastError();
    }
    SuspendThread(workerThread); // приостановить
    Sleep(time * 1000); // подождать
    ResumeThread(workerThread); // возобновить
    if (WaitForSingleObject(workerThread, INFINITE) != WAIT_OBJECT_0)
    {
        cout << "Wait for single object failed." << endl;
    }
    else {
        cout << "Result: " << param->max_negative << endl;
    }
    CloseHandle(workerThread);
    return 0;
