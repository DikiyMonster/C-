#include <iostream>

using namespace std;

int* twoSum(int* nums, int numsSize, int target)
{
	
	for(int i = 0; i < numsSize; ++i)
	{
		for (int j = i + 1; j < numsSize; ++j)
		{
			
			if(nums[i]+nums[j] == target)
			{
				int* result = new int[2];
				result[0] = j;
				result[1] = i;
				return result;
			}
		}	
		
	}
	int* result = new int[2];
    result[0] = 0;
    result[1] = 0;
    return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	int nums[] = {1,2,3,4};
	int target = 5;
	int* result = twoSum(nums, sizeof(nums)/ sizeof(nums[0]), target);
	
	if(result[0] != 0 || result[1] != 0)
	{
		cout << "Индексы двух чисел, сумма которых равна целевому показателю " << target << " : ";
		cout << result[0] << " и " << result[1] << endl;
		
		delete[] result;
	}
	else
	{
		cout << "Решение не найдено"<< endl;
		delete[] result;	
	}
	
	return 0;
}
