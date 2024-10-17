#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <stdexcept>  // для обработки исключений
#include <algorithm>  // для стандартных алгоритмов: replace_copy_if, stable_partition, find_if, swap_ranges, rotate
#include <iterator>   // для итераторов: istream_iterator, ostream_iterator
#include <cctype>     // для функции isdigit (проверка, является ли символ цифрой)
#include <limits>     // для numeric_limits (используется в случае необходимости сброса ввода)

using namespace std;

// Проверка на нечетное количество элементов
void checkOddSize(int size) {
    if (size % 2 == 0) {
        throw invalid_argument("Количество элементов должно быть нечетным.");
    }
}

// Задание 1: Удвоение значений первого, среднего и последнего элемента контейнера
template <typename Container>
void doubleFirstMiddleLast(Container& container) {
    checkOddSize(container.size());  // Проверка, что количество элементов нечетное

    auto first = container.begin();  // Итератор на первый элемент
    auto last = container.end();     // Итератор на конец контейнера (указатель за последним элементом)
    --last;  // Сдвигаем итератор на последний элемент контейнера

    auto middle = first;  // Инициализируем итератор для среднего элемента
    advance(middle, container.size() / 2);  // Смещаем итератор до среднего элемента

    // Удваиваем значения первого, среднего и последнего элементов
    *first *= 2;
    *middle *= 2;
    *last *= 2;
}

// Вывод содержимого контейнера на экран
template <typename Container>
void printContainer(const Container& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        cout << *it << " ";  // Выводим каждый элемент через пробел
    }
    cout << endl;  // Переход на новую строку после вывода всех элементов
}

// Задание 2: Вставка последних 5 элементов дека перед пятым с конца элементом списка
void insertDequeIntoList(deque<int>& D, list<int>& L) {
    if (D.size() < 5 || L.size() < 5) {
        throw invalid_argument("Оба контейнера должны содержать не менее 5 элементов.");
    }

    auto itL = L.end();
    advance(itL, -5);  // Сдвигаем итератор на 5 позиций назад от конца

    L.insert(itL, D.rbegin(), D.rbegin() + 5);  // Вставляем элементы
}

// Задание 3: Комбинирование двух списков в формате A1, B1, A2, B2, ..., AN, BN
void combineLists(list<int>& L1, list<int>& L2) {
    if (L1.size() != L2.size()) {
        throw invalid_argument("Оба списка должны содержать одинаковое количество элементов.");
    }

    list<int> result;  // Новый список для результата

    auto it1 = L1.begin();
    auto it2 = L2.begin();

    // Чередуем элементы из L1 и L2
    while (it1 != L1.end() && it2 != L2.end()) {
        result.push_back(*it1);  // Добавляем элемент из L1
        result.push_back(*it2);  // Добавляем элемент из L2
        ++it1;
        ++it2;
    }

    // Перезаписываем L2 с результатом
    L2 = result;
}

// Задание 4: Замена цифровых символов на подчеркивания
void replaceDigitsWithUnderscore() {
    while (true) {
        cout << "Введите набор символов (для завершения ввода нажмите Enter):" << endl;

        string input;
        getline(cin, input);  // Считываем строку целиком

        ostream_iterator<char> outputIt(cout, "");

        // Лямбда для проверки, является ли символ цифрой
        auto isDigit = [](char c) { return isdigit(c); };

        replace_copy_if(input.begin(), input.end(), outputIt, isDigit, '_');  // Замена цифр

        cout << "\nПродолжить ввод? (y/n): ";
        string choice;
        getline(cin, choice);

        if (choice == "n" || choice == "N") {
            break;
        } else if (choice != "y" && choice != "Y") {
            cout << "Неверный ввод. Пожалуйста, введите 'y' для продолжения или 'n' для завершения.\n";
        }
    }
}

// Задание 5: Вставка 0 после первого отрицательного и перед последним положительным
void insertZeroInList(list<int>& L) {
    auto firstNegative = find_if(L.begin(), L.end(), [](int x) { return x < 0; });
    if (firstNegative != L.end()) {
        L.insert(next(firstNegative), 0);  // Вставляем 0 после первого отрицательного
    }

    auto lastPositive = find_if(L.rbegin(), L.rend(), [](int x) { return x > 0; });
    if (lastPositive != L.rend()) {
        L.insert(lastPositive.base(), 0);  // Вставляем 0 перед последним положительным
    }

    cout << "Список после вставки нулей: ";
    printContainer(L);
}

// Задание 6: Поменять местами первую и вторую половину каждого списка
void swapAndRotateLists(list<int>& L1, list<int>& L2) {
    if (L1.size() % 2 != 0 || L2.size() % 2 != 0) {
        throw invalid_argument("Оба списка должны содержать четное количество элементов.");
    }

    auto midL1 = L1.begin();
    advance(midL1, L1.size() / 2);  // Середина списка L1
    swap_ranges(L1.begin(), midL1, midL1);  // Меняем местами половины

    auto midL2 = L2.begin();
    advance(midL2, L2.size() / 2);  // Середина списка L2
    rotate(L2.begin(), midL2, L2.end());  // Переставляем элементы

    cout << "L1 после swap_ranges: ";
    printContainer(L1);

    cout << "L2 после rotate: ";
    printContainer(L2);
}

// Функция для задания 1 (удвоение элементов)
void task1() {
    int n;
    cout << "Введите количество элементов в контейнерах для задания 1 (нечетное число, >= 3): ";
    cin >> n;
    checkOddSize(n);

    vector<int> V(n);
    deque<int> D(n);
    list<int> L(n);

    cout << "Введите элементы для вектора V: ";
    for (int i = 0; i < n; ++i) cin >> V[i];

    cout << "Введите элементы для дека D: ";
    for (int i = 0; i < n; ++i) cin >> D[i];

    cout << "Введите элементы для списка L: ";
    auto it = L.begin();
    for (int i = 0; i < n; ++i, ++it) cin >> *it;

    doubleFirstMiddleLast(V);
    doubleFirstMiddleLast(D);
    doubleFirstMiddleLast(L);

    cout << "Удвоенные элементы вектора: ";
    printContainer(V);

    cout << "Удвоенные элементы дека: ";
    printContainer(D);

    cout << "Удвоенные элементы списка: ";
    printContainer(L);
}

// Функция для задания 2 (вставка дека в список)
void task2() {
    int n;
    cout << "Введите количество элементов в деке D и списке L для задания 2 (не менее 5): ";
    cin >> n;
    if (n < 5) {
        throw invalid_argument("Оба контейнера должны содержать не менее 5 элементов.");
    }

    deque<int> D(n);
    list<int> L(n);

    cout << "Введите элементы для дека D: ";
    for (int i = 0; i < n; ++i) cin >> D[i];

    cout << "Введите элементы для списка L: ";
    auto it = L.begin();
    for (int i = 0; i < n; ++i, ++it) cin >> *it;

    insertDequeIntoList(D, L);

    cout << "Список после вставки: ";
    printContainer(L);
}

// Функция для задания 3 (комбинирование двух списков)
void task3() {
    int n;
    cout << "Введите количество элементов в списках L1 и L2 для задания 3: ";
    cin >> n;

    list<int> L1(n);
    list<int> L2(n);

    cout << "Введите элементы для списка L1: ";
    auto it1 = L1.begin();
    for (int i = 0; i < n; ++i, ++it1) cin >> *it1;

    cout << "Введите элементы для списка L2: ";
    auto it2 = L2.begin();
    for (int i = 0; i < n; ++i, ++it2) cin >> *it2;

    combineLists(L1, L2);

    cout << "L2 после комбинирования: ";
    printContainer(L2);
}

int main() {
    setlocale(LC_ALL, "Russian");

    int taskNumber;
    cout << "Выберите задание (1-6): ";
    cin >> taskNumber;

    switch (taskNumber) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            replaceDigitsWithUnderscore();
            break;
        case 5:
            {
                int n;
                cout << "Введите количество элементов в списке L для задания 5: ";
                cin >> n;

                list<int> L(n);
                cout << "Введите элементы для списка L: ";
                for (auto& elem : L) cin >> elem;

                insertZeroInList(L);
            }
            break;
        case 6:
            {
                int n;
                cout << "Введите количество элементов в списках L1 и L2 для задания 6 (четное число): ";
                cin >> n;

                list<int> L1(n);
                list<int> L2(n);

                cout << "Введите элементы для списка L1: ";
                for (auto& elem : L1) cin >> elem;

                cout << "Введите элементы для списка L2: ";
                for (auto& elem : L2) cin >> elem;

                swapAndRotateLists(L1, L2);
            }
            break;
        default:
            cout << "Неверный номер задания." << endl;
    }

    return 0;
}
