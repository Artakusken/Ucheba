#include <iostream>
#include <vector>

void PrintVector(std::vector<unsigned short> v, unsigned short start = 0, unsigned short end = 0) {
    if (!end) {
        end = v.size();
    }
    std::cout << "vector: ";
    for (unsigned short i = start; i != end; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

int main() {
//     8 ВАРИАНТ. ЯКИМОВ АРТЁМ. 3 ГРУППА 6 ПОДГРУППА ПМИ
//     ДЗ 10 "Знакомство с std::vector"
//  Найдите информацию о том, как устроен массив переменной длины std::vector и продемонстрируйте работу с ним.
//
//      1. За счет каких средств языка С++ получается изменять длину массива std::vector?
//      2. Что такое capacity и чем оно отличается от size? Что делает shrink_to_fit, resize, reserve?
//      3. Что обозначают знаки < и > при создании std::vector?
//      4. Продемонстрируйте работу push_back, erase, insert, clear.
//      5. В чем отличие функции at и []? И почему в С++ сделали именно так?
//
//	Для демонстрации можете считать, что вам дана последовательность целых чисел длины n (n < 10^4)


    // пункты 1, 3, 4
    std::vector<unsigned short> v;  // Объявление класса вектора: шаблон_вектора<тип данных> название

    v.push_back(1); // Добаление значения в конец вектора
    PrintVector(v);

    v.erase(v.begin());  // Удаление значения по индексу
    PrintVector(v);

    v.insert(v.begin(), 1); // Внесение значения в вектор по индексу
    v.insert(v.begin(), 2);
    PrintVector(v);

    v.pop_back(); // Удаление значения в конце списка
    PrintVector(v);

    v.clear(); // Очищение вектора
    PrintVector(v);
    std::cout << std::endl;

    // пункт 2
    for (unsigned short i = 0; i < 12; i++) {v.push_back(i);}
    PrintVector(v);
    std::cout << std::endl;

    std::cout << "default size and capacity" << std::endl;
    std::cout << v.size() << " <- size " << std::endl;  // Размер вектора (кол-во элементов в векторе)
    std::cout << v.capacity() << " <- capacity " << std::endl;  // Зарезервированная память для вектора (для более эффективного добавления новых элементов)

    v.shrink_to_fit(); // Урезание зарезервированной память до такой, которая достаточна для текущего количества элементов
    std::cout << "a shrink has happened" << std::endl;
    std::cout << v.size() << " <- size " << std::endl;
    std::cout << v.capacity() << " <- capacity " << std::endl;
    PrintVector(v);

    v.resize(20); // Увеличение/урезание размера вектора до опр. значения (новые элементы - дефолтное значение типа )
    std::cout << "a resize has happened, value 20" << std::endl;
    std::cout << v.size() << " <- size " << std::endl;
    std::cout << v.capacity() << " <- capacity " << std::endl;
    PrintVector(v);

    v.reserve(30); // Резервация памяти для меньшего количества реаллокаций
    std::cout << "a reservation has happened, value 30" << std::endl;
    std::cout << v.size() << " <- size " << std::endl;
    std::cout << v.capacity() << " <- capacity " << std::endl;
    PrintVector(v);

    // пункт 5
    std::cout << "call 50th index of vector" << std::endl;  // Вызовем участок незарезервированной памяти
    std::cout << v[18] << " [index] " << std::endl;  // Обычный вызов просто залезет в память
    std::cout << v.at(25) << " at(index) " << std::endl;  // Вызов через at даст исключение 'std::out_of_range' при индексе превышающем size
    return 0;
}