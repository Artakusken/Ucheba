#include "iostream"
#include "fstream"

unsigned short StrLen(wchar_t* str)
{
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void PrintString(wchar_t arr[], unsigned short n) {
    std::wcout << "String of length " << n << ": ";
    for (unsigned short i = 0; i < n; i++) {
        std::wcout << wchar_t(arr[i]) << "";
    }
    std::wcout << "\n";
}

unsigned short EqualsOneOfElements(wchar_t symbol) {
    wchar_t s[] = L":;.,?! ";
    for (unsigned short i = 0; i < StrLen(s); i++) {
        if (symbol == s[i]) {return true;}
    }
    return false;
}

bool CapitalCase(wchar_t symbol) {
    if ((symbol >= L'А' and symbol <= L'Я') or symbol == L'Ё') {
        return true;
    }
    return false;
}

bool LowerCase(wchar_t symbol) {  // Нижний регистр и символы
    if ((symbol >= L'а' and symbol <= L'я') or symbol == L'ё' or (EqualsOneOfElements(symbol))) {
        return true;
    }
    return false;
}


int main() {
    setlocale(LC_ALL, "Rus");
    /*
     * ПОМЕНЯЙТЕ ДИРЕКТОРИИ!!!!!!!
     */
    // Бывают кракозябли в итоговом файле (если в нём кодировка не ANSI)
    char text[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\text.txt)";  // Текст для шифрования
//    char text[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\encrypted text.txt)";  // Текст для дешифрования
    char text_out[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\7777.txt)";  // Текст вывода (вопросами нельзя назвать файл, поэтому 7ки)
    unsigned short encryption_on;
    unsigned short key;

    std::wcout << L"1 - Шифруем. 0 - дешифруем. \n";
    std::wcin >> encryption_on;
    std::wcout << L"Введите ключ шифра (0-65535) \n";
    std::wcin >> key;

    std::wifstream in(text, std::ios::in);
    std::wofstream out(text_out);
    wchar_t abc[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя:;.,?! ";
    wchar_t ABC[] = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ:;.,?! ";

    if (!in.is_open()) {
        std::wcerr << L"Файл не найден" << std::endl;
        return -100;
    }
    
//    std::cout << key << std::endl;
    wchar_t encrypted_abc[40];  // Шифруем словарь (один раз посчитали сдвиг для каждого элемента алфавита и можем пользоваться сколько хотим)
    for (unsigned short i = 0; i < 40; i++) {
        encrypted_abc[i] = abc[(i + key) % 40];
    }
    wchar_t encrypted_ABC[40];
    for (unsigned short i = 0; i < 40; i++) {
        encrypted_ABC[i] = ABC[(i + key) % 40];
    }

    PrintString(abc, 40); // Полученный сдвиг алфавита
    PrintString(ABC, 40);
    PrintString(encrypted_abc, 40);
    PrintString(encrypted_ABC, 40);

    wchar_t current_symbol; // Буква слова, которую шифруем
    unsigned short c = 0;  // Счётчик длины текста

    if (encryption_on) {
        while (!in.eof()) {  // Цикл шифровки в файл
            wchar_t word[40]{};
            wchar_t encrypted_word[41]{};
            in >> word;

            for (unsigned short i = 0; i < StrLen(word); i++) {
                current_symbol = word[i];
                if (LowerCase(current_symbol)) {  // Используем алфавит с нижним регистром для шифрования букв нижнего регистра и спец. символов
                    for (unsigned short j = 0; j < 40; j++) {
                        if (current_symbol == abc[j]) {
                            encrypted_word[i] = encrypted_abc[j];
                            break;
                        }
                    }
                } else if (CapitalCase(current_symbol)) { // Используем алфавит с верхним регистром для шифрования букв верхнего регистра
                    for (unsigned short j = 0; j < 40; j++) {
                        if (current_symbol == ABC[j]) {
                            encrypted_word[i] = encrypted_ABC[j];
                            break;
                        }
                    }
                }
                else {encrypted_word[i] = current_symbol;} // Любой другой случай (буквы других алфавитов и иные спец. символы)
            }
            encrypted_word[StrLen(encrypted_word)] = encrypted_abc[39];  // Добавление пробела. Wofstream срезает пробел на конце слова, здесь он восполняется сразу в зашифрованном виде
            out << encrypted_word;
        }
    } else {
        while (!in.eof()) {  // Цикл дешифровки в файл
            wchar_t word[20000]{};  // 20'000 На случай если пробелов вообще нет (например в зашифрованном тексте не было "!", а пробелы должными были получаться от воскл. знаков. Итог - текст остался без пробелов)
            // wofstream берёт по слову (набор символов от начала/пробела до пробела/конца)
            wchar_t decrypted_word[20001]{};
            in >> word;
            for (unsigned short i = 0; i < StrLen(word); i++) {
                current_symbol = word[i];
                if (CapitalCase(current_symbol)) {
                    for (unsigned short j = 0; j < 40; j++) {
                        if (current_symbol == encrypted_ABC[j]) {
                            decrypted_word[i] = ABC[j];
                            break;
                        }
                    }
                } else if (LowerCase(current_symbol)) {
                    for (unsigned short j = 0; j < 40; j++) {
                        if (current_symbol == encrypted_abc[j]) {
                            decrypted_word[i] = abc[j];
                            break;
                        }
                    }
                }
                else {decrypted_word[i] = current_symbol;};
            }
            decrypted_word[StrLen(decrypted_word)] = abc[39 - (key % 40)]; // Добавление изначального символа (тот что был заменён пробелом).
            // Wofstream срезает пробел на конце слова, и мы теряем букву, которая была шифрована в пробел. ↑Здесь она восполняется сразу в дешифрованном виде
            out << decrypted_word;
            c += StrLen(decrypted_word); // Счёт длины текста
        }
        out.seekp(c - 1, std::ios::beg);  // Отходим от конца текста
        out << L" ";  // "Стираем" лишнюю букву, которая образовалась в ходе восполнения последнего пробела (он впереди всего текста).
    }
    return 0;
}