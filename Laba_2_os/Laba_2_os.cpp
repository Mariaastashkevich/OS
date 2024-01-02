
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
    PROCESS_INFORMATION piApp; // Структура piApp типа PROCESS_INFORMATION содержит идентификаторы и дескрипторы нового создаваемого процесса и его главного потока. Мы не используем эти дескрипторы в нашей программе и поэтому закрываем их

    ZeroMemory(&si, sizeof(STARTUPINFO)); // перед запуском консольного процесса все поля структуры si типа STARTUPINFO должны заполняться нулями
    //si - адрес блока памяти
    // sizeof(STARTUPINFO) - длина блока памяти
    si.cb = sizeof(STARTUPINFO); 
    si.lpTitle = (LPWSTR)L"Child----";
    // тут установить высоту буфера для дочернего процесса
    wcout << args;
    // создаем новый консольный процесс

    if (!CreateProcessW((LPCWSTR)lpszAppName, args, nullptr, nullptr, FALSE,
        CREATE_NEW_CONSOLE, nullptr, nullptr, (LPSTARTUPINFO)&si, &piApp))
        /* lpszAppName - определяет строку с именем exe-файла, который будет запускаться при создании нового процесса
        // args -

         */
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
}



