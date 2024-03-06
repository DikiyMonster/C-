//2. Add Two Numbers

#include <iostream>

using namespace std;

// Определение структуры узла связанного списка
struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Функция для сложения двух связанных чисел
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
    ListNode* dummyHead = new ListNode(0); // Создаем фиктивную голову для результата
    ListNode* current = dummyHead;
    int carry = 0; // Переменная для переноса разряда

    while (l1 || l2 || carry) 
	{
        int sum = carry; // Инициализируем сумму значением переноса

        if (l1) 
		{
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2) 
		{
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10; // Рассчитываем перенос для следующего разряда
        current->next = new ListNode(sum % 10); // Создаем новый узел с результатом
        current = current->next;
    }

    return dummyHead->next; // Возвращаем результат 
}

// Функция для отображения связанного списка (для тестирования)
void printList(ListNode* head) 
{
    ListNode* current = head;
    while (current) 
	{
        cout << current->val << " -> ";
        current = current->next;
    }
    cout << "nullptr" <<endl;
}

int main() {
    // Создаем два связанных числа
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    // Вызываем функцию сложения
    ListNode* result = addTwoNumbers(l1, l2);

    printList(result);

    return 0;
}
