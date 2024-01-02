
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

char* find_leks(char arr[], int size) {
    string leksema = "";
    char* dop = new char[size];
    for (int i = 0; i < size; i++) {
        dop[i] = '0';
    }
    cout << dop << endl;
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        leksema = "";
        while (arr[i] != '0' &&
            arr[i] != '1' &&
            arr[i] != '2' &&
            arr[i] != '3' &&
            arr[i] != '4' &&
            arr[i] != '5' &&
            arr[i] != '6' &&
            arr[i] != '7' &&
            arr[i] != '8' &&
            arr[i] != '9' &&
            i < size) {
            leksema += arr[i];
            i++;
        }
        if (leksema != "") {
            cout << leksema << endl;
            int k = 0;
            for (int j = cnt; j < leksema.length() + cnt; j++) {
                dop[j] = leksema[k];
                k++;
            }
            dop[leksema.length() + cnt] = ' ';
            cnt += (leksema.length() + 1);
        }
    }
    return dop;
}
void do_work(wchar_t* argv) {
    wstring ws(argv);
    string str(ws.begin(), ws.end());
    cout << str << endl;
}
int main(int argc, char* argv[]) {

    /*int size = atoi(argv[0]);
    char* arr = find_leks(*argv, size);
    for (int i = 1; i < size + 1; i++) {
        arr[i - 1] = *argv[i];
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i];
    }
    cout << endl;*/
    //do_work(argv);
    cout << argc << endl;
    cout << "Press any key to continue";
    _getch();
    return 0;
}