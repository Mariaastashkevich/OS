
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
  //  wchar_t lpszAppName[] = L"C:\\Users\\user\\Desktop\\Laba_2_os\\Debug\\Child.exe";
    wchar_t lpszAppName[] = L"Child.exe";
    STARTUPINFO si; // вид главного окна
    PROCESS_INFORMATION piApp; 

    ZeroMemory(&si, sizeof(STARTUPINFO)); 
    si.cb = sizeof(STARTUPINFO); 
    si.lpTitle = (LPWSTR)L"Child----";
    wcout << args;

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
    
    WaitForSingleObject(piApp.hProcess, INFINITE);
    
    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);
}



