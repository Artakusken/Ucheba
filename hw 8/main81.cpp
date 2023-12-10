#include "iostream"
#include "fstream"

void print_array(short unsigned arr[], unsigned short n) {
    std::cout << "Array of length " << n << ": ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void print_string(wchar_t arr[], unsigned short n) {
    std::wcout << "String of length " << n << ": ";
    for (int i = 0; i < n; i++) {
        std::wcout << wchar_t(arr[i]) << "";
    }
    std::wcout << "\n";
}

unsigned short strlen(wchar_t* str)
{
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

unsigned short beatify_string_end(wchar_t* str) {
    unsigned short len = strlen(str);
    unsigned short end_index = 0;
    wchar_t ls = str[len - 1];  // last_symbol

    if (len > 3 and (ls == L'.' == str[len - 3])) { // word... case
        end_index = 3;
    } else if (len > 1 and (ls == L'.' or ls == L',' or ls == L':' or ls == ';' or ls == '!' or ls == '?')) {
        end_index = 1;
    }
    return end_index;
}

void slice_string(wchar_t* str, wchar_t* new_str, unsigned short start, unsigned short end, unsigned short len) {
    for (unsigned short i = start; i < end; i++) {
        new_str[i - start] = str[i];
    }
    new_str[len] = '\0';
}

// Поиск и подсчёт количества двух гласных симовол подряд в слове
int parse_for_glas(wchar_t s[50]) {
    int glas_pares = 0;
    const wchar_t glas[] = L"ёуеаоэяиюы";
    bool first_glas;
    bool second_glas;

    for (int i = 0; i < (strlen(s) - 1); i++) {
        first_glas =  false;
        second_glas = false;

        for (short j = 0; j < 10; j++) {
            if (int(s[i]) == int(glas[j])) { first_glas = true; }
            if (int(s[i + 1]) == int(glas[j])) { second_glas = true; }
            if (first_glas + second_glas == 2) {
                glas_pares++;
                break;
            }
        }
    }
    return glas_pares;
}

// Сравнение всех символов двух строк, если все символы одинаковы (и длина стоковой строки <= проверяемой) → строки равны
bool compare_lines(wchar_t* source_line, wchar_t* other_line) {
    unsigned short source_len = strlen(source_line);
    if (source_len > strlen(other_line)) { return false; }

    for (unsigned short i = 0; i < source_len; i++) {
        if (source_line[i] != other_line[i]) { return false; }
    }
    return true;
}

// Чтение исходного файла (по словам, в файле 1 строка - 1 слово), запись слова в новый файл только, если оно там не встретилось ранее
void delete_duplicates(char* new_filepath, char* filepath, unsigned short limit) {
    std::wifstream in(new_filepath);
    std::wofstream out(new_filepath);
    std::wifstream source_text(filepath);
    bool to_copy;

    while (!source_text.eof()) {  // Взятие слова из исходного файла
        wchar_t source_line[40];
        source_text >> source_line;
        to_copy = true;
        while (!in.eof()) {  // Проверка на совпадение и запись в новом файле
            wchar_t s[40];
            in >> s;
            if (compare_lines(source_line, s)) {
                to_copy = false;
                break;
            }
        }
        in.clear();
        in.seekg(0);
        if (to_copy) {
            out << source_line << std::endl;
            limit--;
        }
        if (!limit) {
            break;
        }
    }
}

int main() {
//    Дан файл, содержащий русский текст.
//    Найти в тексте N<=2000 слов, содержащих наибольшее количество сочетаний из двух гласных.
//    Записать найденные слова в текстовый файл в порядке невозрастания количества сочетаний.
//    Для каждого слова вывести также это количество. Все найденные слова должны быть разными!

    setlocale(LC_ALL, "Rus");
    /*
     * ПОМЕНЯЙТЕ ДИРЕКТОРИИ!!!!!!!
     */
    // Бывают кракозябли в итоговом файле (если в нём кодировка не ANSI)
    char text[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\input.txt)";
    char temp_file1[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\temp_words.txt)";
    char temp_file2[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\words with vowels pares.txt)";
    char final_words[] = R"(C:\Users\ARTEM\CLionProjects\Ucheba\words.txt)";
    unsigned short N;
    std::wcout << L"Введите число слов, которые надо вывести (не более 2 тыс.)" << std::endl;
    std::cin >> N;

    std::wifstream in(text);
    std::wofstream out(temp_file1); // Необработанные (со знаками на конце и цифрой в начале ← см. ниже) слова с парами гласных

    if (!in.is_open()) {
        std::wcerr << L"Файл не найден" << std::endl;
        return -100;
    }

    unsigned short glas_pares_count;
    unsigned short glas_pares_number;
    unsigned short vowels_count_list[5]{}; // Массив счётчиков количества 2 гласных подряд (1-5 пар подряд), с запасом

    while (!in.eof()) {  // Чтение и выделение из текста всех слов с 2 гласными подряд
        wchar_t word[40];
        in >> word;

        glas_pares_count = parse_for_glas(word);
        if (glas_pares_count) {
            vowels_count_list[glas_pares_count - 1]++; // -1 для нумерации с 1
            out << glas_pares_count << word << std::endl; // 1примернОЕ (1й символ - обозначение кол-ва пар в слове)
        }
    }

    print_array(vowels_count_list, 5);
    for (unsigned short i = 4; true; i--) {
        if (vowels_count_list[i]) {
            glas_pares_number = i + 1;
            break;
        }
    }
    out.close();

    std::wofstream out2(temp_file2);  // Обработанные слова с парами гласных (но возможны повторы)
    std::wifstream in2(temp_file1);
    unsigned short cur_word_vowels;

    while (glas_pares_number > 0) { // Чтение слов с парами гласных (Если есть слова с 3/2/1 парами гласных, то будет 3/2/1 циклов чтения)
        while (!in2.eof()) {
            wchar_t s[40];
            in2 >> s;
            cur_word_vowels = short(s[0] - 48);  // в utf-8 код "1" = 49, s[0] хранит кол-во пар гласных в слове правее цифры

            if (cur_word_vowels == glas_pares_number) { // Сначала обрабатываются слова с наибольшим кол-вом пар
                unsigned short end_index = beatify_string_end(s);  // Срез конца
                unsigned short start_index = 1;  // Убрать цифру в начале
                unsigned short new_len = strlen(s) - start_index - end_index;

                wchar_t final_str[new_len];
                slice_string(s, final_str, start_index, strlen(s) - end_index, new_len);
                out2 << final_str << std::endl;
            }
        }
        in2.clear();
        in2.seekg(0);
        glas_pares_number--;
    }
    // ↓ Итог. Удалить повторы и ограничить кол-во выводимых слов
    delete_duplicates(final_words, temp_file2, N);

    in2.close(); // Закрыть дабы удалить
    out2.close();
    remove(temp_file1);
    remove(temp_file2);
}
