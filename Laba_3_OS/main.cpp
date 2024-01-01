#include <iostream>
#include <windows.h>
#include <vector>
#include <process.h>
using namespace std;
CRITICAL_SECTION cs1;
int k;
long long sum;
HANDLE event_1 = CreateEvent(NULL, TRUE, FALSE, NULL);
HANDLE event_2 = CreateEvent(NULL, FALSE, FALSE, NULL);
DWORD WINAPI Work(LPVOID lpParam) {
 EnterCriticalSection(&cs1);
 vector<char>& a = *static_cast<vector<char>*>(lpParam);
 int j = 0;
 for (int i = 0; i < a.size(); i++) {
  if ((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z')) {
   swap(a[j], a[i]);
   j++;
  }
 }
 for (int i = j; i < a.size(); i++) {
  a[i] = ' ';
 }
 LeaveCriticalSection(&cs1);
 SetEvent(event_1);
}
DWORD WINAPI CountElement(LPVOID lpParam) {
 WaitForSingleObject(event_1, INFINITE);
 vector<char>& a = *static_cast<vector<char>*>(lpParam);
 int sum = 0;
 for (int i = 0; i < a.size(); i++) {
  if (a[i] == 'a' ||  a[i] == 'e' ||  a[i] == 'o' ||  a[i] == 'i' ||  a[i] == 'u') {
   sum += 1;
  }
 }
 SetEvent(event_2);
}
int main()
{
 k = 0;
 sum = 0;
 vector<char> v;
 setlocale(LC_ALL, "RUSSIAN");
 std::cout << "Введите размер массива: ";
 int n;
 std::cin >> n;
 std::cout << "Введите элементы: ";
 for (int i = 0; i < n; i++) {
  char elem;
  std::cin >> elem;
  v.push_back(elem);
 }
 
 std::cout << n << endl;
 for (auto x : v) {
  std::cout << x << " ";
 }
 std::cout << endl;
 InitializeCriticalSection(&cs1);
 HANDLE hThread1 = CreateThread(NULL, 0, Work, &v, NULL, NULL);
 HANDLE hThread2 = CreateThread(NULL, 0, CountElement, &v, NULL, NULL);
 std::cout << "Введите значение k: ";
 std::cin >> k;
 std::cout << endl;
 WaitForSingleObject(event_1, INFINITE);
 EnterCriticalSection(&cs1);
 std::cout << "Итоговый массив: ";
 for (int i = 0; i < k; i++) {
  std::cout << v[i] << " ";
 }
 std::cout << endl;
 LeaveCriticalSection(&cs1);
 WaitForSingleObject(event_2, INFINITE);
 std::cout << sum << endl;
 for (int i = k; i < v.size(); i++) {
  std::cout << v[i] << " ";
 }
 std::cout << endl;
 
}
