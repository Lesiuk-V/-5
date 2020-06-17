#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "Record.h"
#include "Worker.h"
using namespace std;

void print_Worker_menu()
{
    system("cls");
    cout << "           Працівники\n" << endl;
    cout << "   1.  Додати дані" << endl;
    cout << "   2.  Переглянути всі дані  " << endl;
    cout << "   3.  Пошук" << endl;
    cout << "   4.  Редагування даних " << endl;
    cout << "   5.  Видалення даних " << endl;
    cout << "   6. Вихід" << endl;
    cout << "  ->";
}

void print_Record_menu()
{
    system("cls");
    cout << "              Записи \n" << endl;
    cout << "   1.  Додати данні" << endl;
    cout << "   2.  Переглянути данні" << endl;
    cout << "   3.  Пошук" << endl;
    cout << "   4.  Редагування даних" << endl;
    cout << "   5.  Видалення даних" << endl;
    cout << "   6. Вихід" << endl;
    cout << "  ->";
}

void print_menu()
{
    system("cls");
    cout << "            Салон краси\n" << endl;
    cout << "   1.  Працівники" << endl;
    cout << "   2.  Записи" << endl;
    cout << "   3. Вихід" << endl;
    cout << "  ->";
}

void printSearchRecordMenu()
{
    cout << "\n\nПошук за полем: \n";
    cout << "   1. Ім'я " << endl;
    cout << "   2. Прізвище" << endl;
    cout << "   3. По батькові" << endl;
    cout << "   4. Номер телефону" << endl;
    cout << "   5. Вид послуги(1:Послуги перукаря, 2:Манікюр та педикюр,3:Послуги візажиста,4:Косметологічні процедури)" << endl;
    cout << "   6. id працівника" << endl;
    cout << "   7. id запису" << endl;
    cout << "  ->";
}
void printSearchWorkerMenu()
{
    cout << "\n\nПошук за полем: \n";
    cout << "   1. Ім'я" << endl;
    cout << "   2. Прізвище" << endl;
    cout << "   3. По батькові" << endl;
    cout << "   4. Посада(Перукар-1, Майстер манікюру-2, Візажист-3, Косметолог-4)" << endl;
    cout << "   5. Дата народження" << endl;
    cout << "   6. id" << endl;
    cout << "   7. номер телефону" << endl;
    cout << "  ->";
}

int get_variant(int max) {
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
            if (input > 0 && input <= max)
                return input;
            else
            {
                valid = false;
                cout << "   Помилка вводу. Введіть ще раз" << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "   Помилка вводу. Введіть ще раз" << endl;
        }
    } while (!valid);
    return input;
}
int main()
{
    system("chcp 1251>nul");
    int variant;
    int searchVar;
    Worker worker;
    int n;
    Record record;
    do {
        print_menu();
        char ch;
        variant = get_variant(3);
        switch (variant)
        {
        case 1:

            do
            {
                print_Worker_menu();
                variant = get_variant(6);
                switch (variant)
                {
                case 1:

                    do
                    {

                        cout << "  Введіть дані працівника: ";
                        worker.create(0);
                        worker.write();
                        cout << "  Продовжити ввід?(т/н)?";
                        cin >> ch;
                    } while (ch == 'т');
                    break;
                case 2:
                    n = Worker::count();
                    cout << "  У файлі " << n << " працівник(ів)\n";
                    for (int j = 1; j < n + 1; j++)
                    {
                        cout << "\n Працівник " << j << endl;
                        worker.read(j - 1);
                        worker.showData();
                        cout << endl;
                    }
                    cout << endl;
                    break;
                case 3:
                    do
                    {
                        printSearchWorkerMenu();
                        searchVar = get_variant(7);
                        worker.search(searchVar);
                        break;
                        system("pause");
                    } while (searchVar != 7);
                    break;
                case 4:
                    worker.editData();
                    break;
                case 5:

                    worker.deleteData();
                    break;
                }
                if (variant != 6)
                    system("pause");
            } while (variant != 6);

            break;

        case 2:
            do
            {
                print_Record_menu();
                variant = get_variant(6);
                switch (variant)
                {
                case 1:
                    do
                    {
                        cout << "   Введіть дані запису: ";
                        record.create(0);
                        record.write();
                        cout << "   Породивжити(т/н)?";
                        cin >> ch;
                    } while (ch == 'т');
                    break;
                case 2:
                    n = Record::count();
                    cout << "   У файлі " << n << " записів";
                    for (int j = 1; j < n + 1; j++)
                    {
                        cout << "\n   Запис " << j << endl;
                        record.read(j - 1);
                        record.showData();
                        cout << endl;
                    }
                    cout << endl;
                    break;
                case 3:
                    do
                    {
                        printSearchRecordMenu();
                        searchVar = get_variant(7);
                        record.search(searchVar);
                        break;
                        system("pause");
                    } while (searchVar != 8);
                    break;
                case 4:
                    record.editData();
                    break;
                case 5:
                    record.deleteData();
                    break;
                }
                if (variant != 6)
                    system("pause");
            } while (variant != 6);
            break;
        }
        if (variant != 3)
            system("pause");
    } while (variant != 3);
    return 0;
}