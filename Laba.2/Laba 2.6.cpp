//Параллельный алгоритм №4: последовательный перебор простых чисел
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

bool isPrime(int num) 
{
    if (num < 2) 
	{
        return false;
    }
    
    int sqrtNum = static_cast<int>(sqrt(num));
    for (int i = 2; i <= sqrtNum; ++i) 
	{
        if (num % i == 0) 
		{
            return false;
        }
    }

    return true;
}

void parallelPrimeSearch(int start, int end) 
{
    #pragma omp parallel for
    for (int num = start; num <= end; ++num) 
	{
        if (isPrime(num)) 
		{
            #pragma omp critical
            {
                cout << num << " ";
            }
        }
    }
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	
    int start = 50;
    int end = 150;

    cout << "Простые числа между " << start << " и " << end << " являются:\n";
    parallelPrimeSearch(start, end);

    return 0;
}
