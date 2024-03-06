#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

const int bufferSize = 1;
atomic<int> buffer(0);

void writer(int id) 
{
    for (int i = 0; i < 5; ++i) 
    {
        buffer.store(i, memory_order_relaxed);
        cout << "Писатель " << id << " пишет: " << i << endl;
    }
}

void reader(int id) 
{
    for (int i = 0; i < 5; ++i) 
    {
        int value = buffer.load(memory_order_relaxed);
        cout << "Читатель " << id << " читает: " << value << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    vector<thread> threads;

    for (int i = 0; i < 2; ++i)
    {
        threads.push_back(thread(writer, i));
    }

    for (int i = 0; i < 2; ++i)
    {
        threads.push_back(thread(reader, i));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
