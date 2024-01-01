#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;
int main()
{
    wstring s;
    wcout << "Enter your string: ";
    wcin >> s;
    wstring size = to_wstring(s.length());
    size += L" " + s;
    wchar_t* args = _wcsdup(size.c_str());
    wchar_t lpszAppName[] = L"D:\\programming\\university\\algorithms\\MariaBigBrain_laba\\x64\\Debug\\Child.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    wcout << args;
    // создаем новый консольный процесс
    if (!CreateProcessW((LPCWSTR)lpszAppName, args, nullptr, nullptr, FALSE,
        CREATE_NEW_CONSOLE, nullptr, nullptr, (LPSTARTUPINFO)&si, &piApp))
    {
        _cputs("The new process is not created.\n");
        _cputs("Check a name of the process.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 0;
    }
    _cputs("The new process is created.\n");
    // ждем завершения созданного прцесса
    WaitForSingleObject(piApp.hProcess, INFINITE);
    // закрываем дескрипторы этого процесса в текущем процессе
    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);
    return 0;
}
