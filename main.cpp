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
//    char text[] = R"(../text.txt)";  // Текст для шифрования
    char text[] = R"(../666.txt)";  // Текст для дешифрования
    char text_out[] = R"(../7777.txt)";  // Текст вывода (вопросами нельзя назвать файл, поэтому 7ки)
//    char text_out[] = R"(../666.txt)";  // Текст вывода (вопросами нельзя назвать файл, поэтому 7ки)
    unsigned short encryption_on;
    unsigned short key;

    std::wcout << L"1 - Шифруем. 0 - дешифруем. \n";
    std::wcin >> encryption_on;
    std::wcout << L"Введите ключ шифра (0-65535) \n";
    std::wcin >> key;

    std::wifstream in(text);
    std::wofstream out(text_out);
//    out >> std::noskipws();
    wchar_t abc[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя:;.,?! ";
    wchar_t ABC[] = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ:;.,?! ";

    if (!in.is_open()) {
        std::wcerr << L"Файл не найден" << std::endl;
        return -100;
    }

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

    if (encryption_on) {
        while (!in.eof()) {  // Цикл шифровки в файл
            wchar_t s;
            bool k;
            k = bool(in.get(s));
            if (!k) {break;}
            if (LowerCase(s)) {  // Используем алфавит с нижним регистром для шифрования букв нижнего регистра и спец. символов
                for (unsigned short j = 0; j < 40; j++) {
                    if (s == abc[j]) {
                        current_symbol = encrypted_abc[j];
                        break;
                    }
                }
            } else if (CapitalCase(s)) { // Используем алфавит с верхним регистром для шифрования букв верхнего регистра
                for (unsigned short j = 0; j < 40; j++) {
                    if (s == ABC[j]) {
                        current_symbol = encrypted_ABC[j];
                        break;
                    }
                }
            }
            else {current_symbol = s;} // Любой другой случай (буквы других алфавитов и иные спец. символы)
            out << current_symbol;
        }
    } else {
        while (!in.eof()) {  // Цикл дешифровки в файл
            wchar_t s;
            bool k;
            k = bool(in.get(s));
            if (!k) {break;}
            if (CapitalCase(s)) {
                for (unsigned short j = 0; j < 40; j++) {
                    if (s == encrypted_ABC[j]) {
                        current_symbol = ABC[j];
                        break;
                    }
                }
            } else if (LowerCase(s)) {
                for (unsigned short j = 0; j < 40; j++) {
                    if (s == encrypted_abc[j]) {
                        current_symbol = abc[j];
                        break;
                    }
                }
            }
            else {current_symbol = s;}
            out << current_symbol;
        }
    }
    return 0;
}