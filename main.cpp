#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cctype>

using namespace std;


// Чтение файла
bool readFile(const string& filename, vector<string>& lines)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    return true;
}


// Подсчёт количества слов
int countWords(const vector<string>& lines)
{
    int count = 0;

    for (const string& line : lines)
    {
        bool insideWord = false;

        for (char c : line)
        {
            if (!isspace(static_cast<unsigned char>(c)))
            {
                if (!insideWord)
                {
                    count++;
                    insideWord = true;
                }
            }
            else
            {
                insideWord = false;
            }
        }
    }

    return count;
}


// Подсчёт общего количества символов
int countCharacters(const vector<string>& lines)
{
    int count = 0;

    for (const string& line : lines)
    {
        count += line.length();
    }

    return count;
}


// Поиск самой длинной строки
string findLongestLine(const vector<string>& lines)
{
    if (lines.empty())
    {
        return "";
    }

    string longest = lines[0];

    for (const string& line : lines)
    {
        if (line.length() > longest.length())
        {
            longest = line;
        }
    }

    return longest;
}


// Получение уникальных строк
vector<string> getUniqueLines(const vector<string>& lines)
{
    set<string> uniqueSet(lines.begin(), lines.end());

    return vector<string>(uniqueSet.begin(), uniqueSet.end());
}


// Сортировка строк без учёта регистра
vector<string> sortLines(const vector<string>& lines)
{
    vector<string> sortedLines = lines;

    sort(sortedLines.begin(), sortedLines.end(),
        [](const string& a, const string& b)
        {
            string lowerA = a;
            string lowerB = b;

            transform(lowerA.begin(), lowerA.end(), lowerA.begin(),
                [](unsigned char c)
                {
                    return tolower(c);
                });

            transform(lowerB.begin(), lowerB.end(), lowerB.begin(),
                [](unsigned char c)
                {
                    return tolower(c);
                });

            return lowerA < lowerB;
        });

    return sortedLines;
}


// Запись результатов
bool writeResults(
    const string& filename,
    const vector<string>& lines,
    const vector<string>& sortedLines,
    const vector<string>& uniqueLines)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    // Количество строк
    file << "Общее количество строк: "
         << lines.size() << "\n\n";


    // Самая длинная строка
    file << "Самая длинная строка:\n";

    if (!lines.empty())
    {
        file << findLongestLine(lines) << "\n";
    }
    else
    {
        file << "(файл пуст)\n";
    }

    file << "\n";


    // Отсортированные строки
    file << "Строки в алфавитном порядке:\n";

    for (size_t i = 0; i < sortedLines.size(); i++)
    {
        file << i + 1 << ". " << sortedLines[i] << "\n";
    }

    file << "\n";


    // Уникальные строки
    file << "Количество уникальных строк: "
         << uniqueLines.size() << "\n";

    file << "Уникальные строки:\n";

    for (size_t i = 0; i < uniqueLines.size(); i++)
    {
        file << i + 1 << ". " << uniqueLines[i] << "\n";
    }

    file << "\n";


    // Количество символов
    file << "Общее количество символов: "
         << countCharacters(lines) << "\n";


    // Количество слов
    file << "Общее количество слов: "
         << countWords(lines) << "\n";


    file.close();

    return true;
}


int main()
{
    const string inputFilename = "input.txt";
    const string outputFilename = "output.txt";

    vector<string> lines;


    // Проверяем и читаем input.txt
    if (!readFile(inputFilename, lines))
    {
        cout << "Ошибка: файл input.txt не найден или не может быть открыт."
             << endl;

        return 1;
    }


    // Сортировка
    vector<string> sortedLines = sortLines(lines);


    // Уникальные строки
    vector<string> uniqueLines = getUniqueLines(lines);


    // Запись результатов
    if (!writeResults(
        outputFilename,
        lines,
        sortedLines,
        uniqueLines))
    {
        cout << "Ошибка: не удалось создать или записать файл output.txt."
             << endl;

        return 1;
    }


    cout << "Обработка файла успешно завершена." << endl;
    cout << "Результаты записаны в output.txt." << endl;

    return 0;
}