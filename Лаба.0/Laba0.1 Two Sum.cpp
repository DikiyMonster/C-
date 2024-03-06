// 1. Two Sum
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target)
 {
    unordered_map<int, int> numToIndex; // Сопоставляем число с индексом 

    for (int i = 0; i < nums.size(); ++i) 
	{
        int complement = target - nums[i];

        // Проверяем существует complement в контейнере
        if (numToIndex.find(complement) != numToIndex.end()) 
		{
            // Возвращает индексы 2 чисел 
            return {numToIndex[complement], i};
        }

        // Добавляем текущий номер и егу индекс в контейнер
        numToIndex[nums[i]] = i;
    }

    // Возвращаем пустой вектор 
    return {};
}

int main()
 {
 	
 	setlocale(LC_ALL, "Russian");
 	
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = twoSum(nums, target);

    if (result.size() == 2) 
	{
        cout << "Индексы двух чисел давющие в сумме: " << target << ": " << result[0] << ", " << result[1] << endl;
    } 
	else
	{
        cout << "Нет решение." << endl;
    }

    return 0;
}
