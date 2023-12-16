#include "iostream"
#include "fstream"

void PrintString(char arr[], unsigned short n) {
    std::wcout << "String of length " << n << ": ";
    for (unsigned short i = 0; i < n; i++) {
        std::wcout << char(arr[i]) << "";
    }
    std::wcout << "\n";
}


int main() {
    setlocale(LC_ALL, "Rus");
    /*
     * ПОМЕНЯЙТЕ ДИРЕКТОРИИ!!!!!!!
     */
    // Бывают кракозябли в итоговом файле (если в нём кодировка не ANSI)
    unsigned short encryption_on;
    unsigned short key;

    std::wcout << L"1 - Шифруем. 0 - дешифруем. \n";
    std::wcin >> encryption_on;
    std::wcout << L"Введите ключ шифра (0-65535) \n";
    std::wcin >> key;

    // у меня exe-шник в папке поэтому ../
    char text[] = R"(../text.txt)";  // Текст для шифрования
    char text_out[] = R"(../encrypted.txt)";  // Текст вывода шифрованного текста
//    char text[] = R"(../encrypted.txt)";  // Текст для дешифрования
//    char text_out[] = R"(../decrypted.txt)";  // Текст вывода дешифрованного текста

    std::ifstream in(text);
    std::ofstream out(text_out);
    char abc[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя:;.,?! ";

    if (!in.is_open()) {
        std::wcerr << L"Файл не найден" << std::endl;
        return -100;
    }

    char encrypted_abc[73];  // Шифруем словарь (один раз посчитали сдвиг для каждого элемента алфавита и можем пользоваться сколько хотим)
    for (unsigned short i = 0; i < 73; i++) {
        encrypted_abc[i] = abc[(i + key) % 73];
    }

    PrintString(abc, 73); // Полученный сдвиг алфавита
    PrintString(encrypted_abc, 73);

    char current_symbol; // Буква слова, которую шифруем

    if (encryption_on) {
        while (!in.eof()) {  // Цикл шифровки в файл
            char s;
            bool k;
            bool in_abc = false;
            k = bool(in.get(s));
            /* ↑ Объяснение: при посимвольном чтении последний символ будет использован дважды. Но при втором чтении булево значение ifstream.get будет уже ложным
             * EOF can be false even after we have successfully read what will be the last character.
             * We will then try to read again, and this time get will fail, and not overwrite the existing value of char, so it still holds previous one
             */
            if (!k) {break;} // При чтении не получили символа (т.е. дошли до конца текста)

            for (unsigned short j = 0; j < 73; j++) {
                if (s == abc[j]) {
                    current_symbol = encrypted_abc[j];
                    in_abc = true;
                    break;
                }
            }
            if (!in_abc) {current_symbol = s;} // Любой другой случай (буквы других алфавитов и иные спец. символы)

            out << current_symbol;
        }
    } else {
        while (!in.eof()) {  // Цикл дешифровки в файл
            char s;
            bool k;
            bool in_abc = false;
            k = bool(in.get(s));
            if (!k) { break; }

            for (unsigned short j = 0; j < 73; j++) {
                if (s == encrypted_abc[j]) {
                    current_symbol = abc[j];
                    in_abc = true;
                    break;
                }
            }
            if (!in_abc) { current_symbol = s; }

            out << current_symbol;
        }
    }
    return 0;
}