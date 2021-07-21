#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>





using namespace std;

const int sname = 50;

struct Zavod
{

    int numberzavod; //НОМЕР ЗАВОДА
    char fiodir[sname]; //ФИО ДИРЕКТОРА
    char fioenerg[sname];//ФИО ГЛАВНОГО ЭНЕРГЕТИКА
    double planenergy;//Расход энергии по плану
    double factenergy;//Расход энергии фактически
    double otkloneniya = factenergy-planenergy; //отклонение фактического от планового;
    Zavod* next; // Указатель на следующий элемент
};

const int size_struct = sizeof(Zavod);

Zavod WriteStruct(const int& count)
{
    // Объявление и Инициализация
    Zavod zavod;

    //if(count !=0) 
    cin.get();
    cout << "[SYSTEM]: Добавление новой записи\n[SYSTEM]:";
      
       cout<<"Введите ФИО директора: ";

    cin.get(zavod.fiodir, sname);
    cout << "[SYSTEM]: Введите ФИО главного эергетика: ";
    cin.get();
    cin.get(zavod.fioenerg, sname);
    cout << "[SYSTEM]: Введите номер завод: "; cin >> zavod.numberzavod;

    cout << "[SYSTEM]: Введите расход эергии по плану: "; cin >> zavod.planenergy;

    cout << "[SYSTEM]: Введите расход эергии фактически: "; cin >> zavod.factenergy;

 


    return zavod;
}






Zavod* AddFirst(int& count, Zavod zavod, int mode) // Добавление первой записи. mode [0] - Не производится восстановление данных из файла [1] - Производится восстановление
{
    // Объявление и Инициализация
    Zavod* begin = 0;

    if (mode == 0) zavod = WriteStruct(count); // Заполнение структуры

    if (zavod.fiodir!=NULL)
    {
        begin = new Zavod; // Выделине памяти под элемент 

        *begin = zavod; // Присвоение значения элементу 

        begin->next = 0; // Следующий элемент после нашего 0 

        count++; // Инкремент количества записей

        if (mode == 0) // Если восстановления из файла не происходит
            cout << "[SYSTEM]: Новая запись: " << "\t|Номер завода " <<zavod.numberzavod<< "\t|ФИО директора: " << zavod.fiodir << "\t|ФИО главного энергетика: " << zavod.fioenerg << "\t| Фатк.эерегия: " << zavod.factenergy << "\t| По плану эергия: "
            << zavod.planenergy << "\t[создана]\n";
    }
    else cout << "[SYSTEM ERROR]: Вы ввели некорректные значения. Процедура отменена\n";

    return begin; // В качестве результата возвращаем ссылку на первый элемент  
}

Zavod* AddStructEnd(Zavod* end, int& count, Zavod zavod, int mode) // Добавление записи в конец mode [0] - Не производится восстановление данных из файла [1] - Производится восстановление
{
    // Объявление и Инициализация
    Zavod* new_zavod = 0;

    char ch = '+';

    while (ch == '+')
    {
        if (mode == 0) zavod = WriteStruct(count); // Заполнение структуры (если mode = 0, тогда не производится восстановление данных из файла

        if (zavod.planenergy > 0.0 && zavod.factenergy > 0.0)
        {
            new_zavod = new Zavod;

            *new_zavod = zavod;

            new_zavod->next = 0;

            end->next = new_zavod;

            end = new_zavod;

            count++; // Инкремент количества записей

            if (mode == 0) // Если восстановления из файла не происходит
            {
                cout << "[SYSTEM]: Новая запись: " << "\t|Номер завода " << zavod.numberzavod << "\t|ФИО директора: " << zavod.fiodir << "\t|ФИО главного энергетика: " << zavod.fioenerg << "\t| Фатк.эерегия: " << zavod.factenergy << "\t| По плану эергия: "
                    << zavod.planenergy << "\t[создана]\n";

                cout << "[SYSTEM]: Продолжить заполнение данных в очередь списка? [+] - ДА [AnyKey] - НЕТ\n[CONTINUE?]: "; cin >> ch;

                if (ch != '+') break;
            }
            else break; // Если восстановление из файла происходит, то просто пропускаем диалог о продолжении заполнения данных в очередь
        }
        else
        {
            cout << "[SYSTEM ERROR]: Вы ввели некорректные значения. Процедура отменена\n";

            break;
        }
    }

    return end; // вернуть измененное значение нашей основной очереди
}

void FileReader(Zavod** begin, Zavod** end, const char* fname, int& count) // Восстановление данных из файла
{
    FILE* freader = fopen(fname, "r");

    Zavod zavod;
    int n = 0; // Если n < 1 - то конец файла
    if (!freader) cout << "[SYSTEM]: Нет данных для восстановления\n";
    else // Если файл существует
    {
        cout << "[SYSTEM DATA RECOVERY]:\n\n";
        while (!feof(freader))
        {
            n = fread(&zavod, size_struct, 1, freader); // Буффер | Размер буффера | Количество читаемых данных | Поток

            if (n < 1) break; // Если n < 1 - то конец файла

            if (*begin) // Если очередь не пустая
                *end = AddStructEnd(*end, count, zavod, 1); // Добавить новые элементы в конец списка
            else // Если очередь пустая
            {
                *begin = AddFirst(count, zavod, 1); // Добовление первого элемента

                *end = *begin;
            }



        }

    }
}
void PrintStruct(const Zavod& zavod)
{
    cout << "[SYSTEM]: Новая запись: " << "\t|Номер завода " << zavod.numberzavod << "\t|ФИО директора: " << zavod.fiodir << "\t|ФИО главного энергетика: " << zavod.fioenerg << "\t| Фатк.эерегия: " << zavod.factenergy << "\t| По плану эергия: "
        << zavod.planenergy <<"\t Разница"<<zavod.factenergy-zavod.planenergy ;
}


void ViewList(Zavod* begin, const int& count)
{
    Zavod* temp = begin;

    if (count == 0) cout << "[SYSTEM ERROR]: Очередь пустая. Нечего показывать!\n";
    else
    {
        for (int i = 1; i <= count; i++)
        {
            cout << "---------------Запись завода  №" << i << "---------------\n";

            PrintStruct(*temp);

            cout << "\n---------------------------------------------------\n";

            temp = temp->next; // Перемещаем указатель на следующий элемент
        }
    }
}


void FileWriter(Zavod* begin, const char* fname, const int& count) // Запись данных в файл
{
    FILE* fwriter = fopen(fname, "w"); // Открытие бинарного файла для записи (содержимое очищается)

    Zavod* temp = begin;

    int i = 0; // Подсчет добавленных записей

    if (count == 0) cout << "[SYSTEM ERROR]: Очередь пустая. Нечего сохранять!\n";
    else
    {
        cout << "[SYSTEM]: Следующие записи были сохранены в файле:\n\n";
        for (i = 0; i < count; i++)
        {
            fwrite(temp, size_struct, 1, fwriter); // Запись данных в файл

            //fwriter << &temp;

            cout<<"\t| ФИО директора: " << temp->fiodir << "\t| ФИО энергетика: " << temp->fioenerg << "\t| Фактически энергии: " << temp->factenergy << "\t| По плану энергии: " << temp->planenergy << "\t[сохранен]\n";

            temp = temp->next; // Перемещаем указатель на следующий элемент
        }
        cout << endl;
    }
    fclose(fwriter);
}
enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};
void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void searchzavod(Zavod* begin , const int& count)
{

    Zavod* zavod = begin;
    int numberzavod1 = 0;
    cout << "Введите номер завода который вы хоите найти";
    cin >> numberzavod1;
    for (int i = 1;i <= count;i++)
    {
        if (numberzavod1 == zavod->numberzavod)
        {
            SetColor((ConsoleColor)4, (ConsoleColor)1);
            cout << "\t| ФИО директора: " << zavod->fiodir << "\t| ФИО энергетика: " <<zavod->fioenerg << "\t| Фактически энергии: " <<zavod->factenergy << "\t| По плану энергии: " << zavod->planenergy<<"\t| Разница:  "<<
                zavod->factenergy- zavod->planenergy;
            SetColor((ConsoleColor)15, (ConsoleColor)0);
            break; // Зачем ??
        }
        else
        {
            zavod = zavod->next;
        }
            
    }
}



int main()
{
    setlocale(LC_ALL, "Russian");
  
          
             //цвет текста  цвет фона 
       
   // HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | BACKGROUND_GREEN);
   // system("color 0F"); //тут два параметра 1 - цвет фона 2 - цвет текста .Меняет всю констоль
     // Инициализация
    Zavod* begin = 0, // Указатель на начало очереди
        * end = 0, // Указатель на конец очереди
        student; // Переменная структуры для передачи данных


    const char* fname = "main.txt"; // Имя файла (передается в функции)

    int count = 0; // Количество записей в списке

    int mode = 0; // Режим работы программы (меню)

    FileReader(&begin, &end, fname, count); // Восстановление данных (если имеются)

    cout << "[1] - Организация списка (добавление первого элемента)\n[2] - Добавить новые элементы в конец списка\n[3] - Очистить экран\n[4] - Показать список\n";
    cout << "[5] -Поиск по номеру завод\n[6] - Удалить весь список\n[7] - Сохранить данные в файл\n[666] - Выход\n";

    while (true)
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1:
            // Организация списка
            if (count > 0) // Если очередь не пустая
                cout << "[SYSTEM ERROR]: Организация списка уже была выполнена ранее! Вы можете добавить новые элементы в конец списка [2]\n";
            else // Если очередь пустая
            {
                begin = AddFirst(count, student, 0); // Добовление первого элемента

                end = begin;
            }
            break;
        case 2:
            if (count > 0) // Если очередь не пустая
                end = AddStructEnd(end, count, student, 0); // Добавить новые элементы в конец списка
            else // Очередь пустая
                cout << "[SYSTEM ERROR]: Организация списка еще не выполнена! Пожалуйста, выполните организацию списка [1]\n";
            break;
        case 3: // Очистить экран
            system("cls");
            cout << "[1] - Организация списка (добавление первого элемента)\n[2] - Добавить новые элементы в конец списка\n[3] - Очистить экран\n[4] - Показать список\n";
            cout << "[5] - Исключить последний элемент из списка\n[6] - Удалить весь список\n[7] - Сохранить данные в файл\n[666] - Выход\n";
            break;
        case 4: ViewList(begin, count); break; // Показать список

        case 5:searchzavod(begin , count);break;
                
        case 7: FileWriter(begin, fname, count); break; // Сохранить данные в файл
        case 666:
            if (count > 0)
            {
                cout << "[SYSTEM]: В очереди есть заполненные данные, Вы желаете их сохранить в файл?";
                cout << " [ПРЕДУПРЕЖДЕНИЕ!] - если файл уже существует, он будет перезаписан. Продолжить? [1] - ДА [AnyKey] - НЕТ\n[SAVE?]: ";
                cin >> mode;

                if (mode == 1) FileWriter(begin, fname, count); // Сохранить данные в файл
            }

          
            return 0;
            break;
        }
    }
    return 0;
}

    

