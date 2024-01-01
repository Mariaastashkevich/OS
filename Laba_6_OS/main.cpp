#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
mutex m1;
int k;
long long sum;
condition_variable cv1, cv2;
void Work(vector<char>& a) {
    unique_lock<mutex> lk(m1); 
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
    lk.unlock();
    cv1.notify_one();
}
void CountElement(vector<char>& a) {
    unique_lock<mutex> lk(m1);
    cv1.wait(lk);
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 'a' ||  a[i] == 'e' ||  a[i] == 'o' ||  a[i] == 'i' ||  a[i] == 'u' || a[i] == 'y') {
            sum += 1;
        }
    }
    lk.unlock();
    cv2.notify_one();
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
    vector<char> v2 = v;
    std::cout << n << endl;
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << endl;

    thread t1(Work, ref(v));
    thread t2(CountElement, ref(v));
    std::cout << "Введите значение k: ";
    std::cin >> k;
    std::cout << endl;

    cv1.notify_all();

    {
        std::unique_lock<std::mutex> lock(m1);
        cv2.wait(lock);
    }

    std::cout << "Итоговый массив: ";
    for (int i = 0; i < k; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << endl;




    std::cout << sum << endl;
    for (int i = k; i < v2.size(); i++) {
        std::cout << v2[i] << " ";
    }
    std::cout << endl;
    // дожидаемся завершения потоков
    t1.join();
    t2.join();
}
