#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int bufferSize = 1;
int buffer = 0;  

void writer(int id) {
    for (int i = 0; i < 5; ++i) 
	{
        
        buffer = i;
        cout << "Writer " << id << " wrote: " << i << endl;
    }
}

void reader(int id) {
    for (int i = 0; i < 5; ++i) 
	{
        
        cout << "Reader " << id << " read: " << buffer << endl;
    }
}

int main()
{
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
