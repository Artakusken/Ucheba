#include "pseudo_string.hpp"
#include <iostream>

namespace ya
{
    PseudoString::PseudoString() {
            string = new char[1];
            string[0] = '\0';
            len = 0;
        };

    PseudoString::PseudoString(unsigned int length) {
//          std::cout << " con \n";
            string = new char[length + 1];
            string[length] = '\0';
            len = length;
        }

    PseudoString::PseudoString(const char* char_array) {
//            std::cout << " con \n";
            len = 0;
            while (char_array[len]) { // Узнаём размер переданной строки
                len++;
            }

            string = new char[len + 1]; // Аллоцируем память для строки и терм. нуля
            for (unsigned short i = 0; (i <= len); ++i) {  // передаём в память значения данной нам строки
                string[i] = char_array[i];
            };
            string[len] = '\0';  // добавляем терм. ноль
        }

    PseudoString::~PseudoString() {
//          std::cout << " des \n";
            delete[] string;
        }

    PseudoString::PseudoString(const PseudoString& other) : PseudoString(other.string) {}

//    PseudoString& PseudoString::operator=(PseudoString other) {
//        delete[] string;
//        len = other.len;
//        string = other.string;
//        return *this;
//    }
    PseudoString& PseudoString::operator=(PseudoString copy)
    {
//        std::cout << "Copy operator " << std::endl;
        Swap(copy);
        return *this;
    }

    char& PseudoString::operator[](int index) {
        if (index >= 0 and index < len) {
            return string[index];
        }
        else if (index >= (0 - len)) {
            return string[len + index];
        }
        throw std::invalid_argument("Incorrect index value");
    }

    PseudoString& PseudoString::operator+=(const PseudoString& other) {
        PseudoString temp(*this);
        delete[] string;
        string = new char[len + other.len];
        unsigned short c = 0;
        while (temp.string[c]) { // Запись старой строки
            string[c] = temp.string[c]; c++;
        }
        c = 0;
        while (other.string[c]) { // Запись её нового продолжения
            string[c + temp.len] = other.string[c]; c++;
        }
        len += other.len;
        string[len] = '\0';
        return *this;
    }

    PseudoString& PseudoString::operator+=(const char* other) {
        PseudoString temp(*this);
        delete[] string;
        unsigned short other_len = 0;
        while (other[other_len]) { // Узнаём размер переданной строки
            other_len++;
        }
        string = new char[len + other_len];
        unsigned short c = 0;
        while (temp.string[c]) { // Запись старой строки
            string[c] = temp.string[c]; c++;
        }
        c = 0;
        while (other[c]) { // Запись её нового продолжения
            string[c + temp.len] = other[c]; c++;
        }
        len += other_len;
        string[len] = '\0';
        return *this;
    }

    PseudoString PseudoString::operator+(const PseudoString& other) {
        PseudoString temp(*this);
        temp += other;
        return temp;
    }

    PseudoString PseudoString::operator+(const char* other) {
        PseudoString temp(*this);
        temp += other;
        return temp;
    }

    PseudoString& PseudoString::operator*=(const unsigned short n) {
        PseudoString temp(*this);
        delete[] string;
        string = new char[len * n];
        unsigned short c;
        for (unsigned short i = 0; i < n; i++) {
            c = 0;
            while (temp.string[c]) { // Запись старой строки
                string[c + (i * temp.len)] = temp.string[c];
                c++;
            }
        }
        len *= n;
        string[len] = '\0';
        return *this;
    }

    PseudoString PseudoString::operator*(const unsigned short n) {
        PseudoString temp(*this);
        temp *= n;
        return temp;
    }

    PseudoString PseudoString::Slice(int start, int end, int step) {
        // Корректировка аргументов и адаптация отриц. значений
        if (end < 0) {
            if (end > -len) {end = len + end;}
            else {end = -len;}
        }
        else if (end > len - 1) {end = len - 1;}

        if (start < 0)
        {
            if (start > -len) {start = len + start;}
            else {start = -len;}
        }

        if (abs(step) <= abs(end - start) and end and start < len) { // Доп. проверка некорректируемых аргументов
            if (start > end and step > 0) {return PseudoString();}  //
            int t;
            if (start < end and step < 0) {t = start, start = end, end = t;}

            unsigned int temp_len = (abs(end - start) + 1); // Подсчёт длины субстроки
            temp_len /= abs(step);
            if (temp_len % abs(step) != 0) { // Округление вверх
                temp_len++;
            }

            PseudoString temp(temp_len);

            for (unsigned short i = 0; (i < temp_len); i++) {  // передаём в память значения данной нам строки
                temp.string[i] = string[start + (i * step)];
            }
            return temp;
        }
        else { return PseudoString(); }
    }

    PseudoString PseudoString::Reversed() {
        return this->Slice(0, len - 1, -1);
    }

    void PseudoString::Reverse() {
        if (len) {
            unsigned int i = 0;
            unsigned int j = len - 1;
            char temp;
            while (i < j) {
                temp = string[i];
                string[i] = string[j];
                string[j] = temp;
                i++;
                j--;
            }
        }
    }

    unsigned int PseudoString::getLength() {
        return len;
    }

    void PseudoString::Print() {
        std::cout << string << "\n";
    }

    PseudoString operator+(const PseudoString& a, const PseudoString& other) {
        PseudoString temp(a);
        temp += other;
        return temp;
    };

    PseudoString operator+(const char* a, const PseudoString& other) {
        PseudoString temp(a);
        temp += other;
        return temp;
    };

    PseudoString operator*(const unsigned short n, const PseudoString& string) {
        PseudoString temp(string);
        temp *= n;
        return temp;
    };
};
