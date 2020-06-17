#include "Worker.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int Worker::setId()
{
    int id;
    string str;
    fstream file;
    file.open("id.txt", fstream::out | fstream::in);
    ifstream temp;
    while (!file.eof())
    {
        getline(file, str);
        id = atoi(str.c_str());
    }
    ++id;
    file.close();
    file.open("id.txt", fstream::out | fstream::in);
    file << id;
    file.close();
    return id;
}

int Worker::getId()
{
    return id;
}

void Worker::create(int ID)
{
    cin.ignore(10, '\n');
    cout << "\n    Ім'я: "; cin >> name;
    cout << "   Прізвище: "; cin >> surname;
    cout << "   По батькові: "; cin >> patronymic;
    setPosition();
    cout << "   Дата народження(день.місяць.рік): "; cin >> dateOfBirth;
    cout << "   Номер телефону:"; cin >> phone;
    if (ID != 0)
        id = ID;
    else
        id = setId();
}
void Worker::showData()
{
    cout << "   id: " << id << endl;
    cout << "   Ім'я: " << name << endl;
    cout << "   Прізвище: " << surname << endl;
    cout << "   По батькові: " << patronymic << endl;
    cout << "   Посада: "; getPosition(position);
    cout << "   Дата народження(день.місяць.рік): " << dateOfBirth << endl;
    cout << "   Номер телефону:" << phone;
}
void Worker::read(int pn)
{
    ifstream ifile;
    ifile.open("Worker.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(pn * sizeof(Worker));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}
void Worker::write()
{
    ofstream ofile;
    ofile.open("Worker.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

int Worker::count()
{
    ifstream ifile;
    ifile.open("Worker.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    return (int)ifile.tellg() / sizeof(Worker);
    ifile.close();
}

void Worker::setPosition()
{

    cin.ignore(10, '\n');
    cout << "  виберіть професію: \n";
    cout << "   1:Перукар\n";
    cout << "   2:Майстер манікюру \n";
    cout << "   3:Візажист\n";
    cout << "   4:Косметолог\n";
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {

            if (input > 0 && input <= 4)
                valid = true;

            else
            {
                valid = false;
                cout << "Помилка вводу. Введіть ще раз" << endl;
            }

        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Помилка вводу. Введіть ще раз" << endl;
        }
    } while (!valid);

    switch (input)
    {
    case 1:
        position = hairdresser;
        break;
    case 2:
        position = masterOfManicure;
        break;
    case 3:
        position = MakeUpArtist;
        break;
    case 4:
        position = beautician;
        break;
    default:

        break;
    }
}

void Worker::getPosition(int variant)
{
    switch (variant)
    {
    case 1:
        cout << "   Послуги перукаря\n";
        break;
    case 2:
        cout << "   Манікюр та педикюр\n";
        break;
    case 3:
        cout << "   Послуги візажиста\n";
        break;
    case 4:
        cout << "   Косметологічні процедури\n";
        break;
    default:
        cout << "unknow\n";
        break;
    }
}

int Worker::search(int variant)
{
    if (variant == 0)
        return 0;
    Worker worker;
    ifstream ifile;
    char str[40];
    ifile.open("Worker.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "\nВведіть дані для пошуку: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(Worker));
        ifile.read(reinterpret_cast<char*>(&worker), sizeof(Worker));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, worker.name))
            {
                worker.showData();
            }
            break;

        case 2:
            if (0 == strcmp(str, worker.surname))
            {
                worker.showData();
            }
            break;
        case 3:
            if (0 == strcmp(str, worker.patronymic))
            {
                worker.showData();
            }
            break;
        case 4:

            if (atoi(str) == worker.position)
            {
                worker.showData();
            }
            break;
        case 5:
            if (0 == strcmp(str, worker.dateOfBirth))
            {
                worker.showData();
            }
            break;
        case 6:

            if (atoi(str) == worker.id)
            {
                worker.showData();
            }
            break;
        default:
            cout << "   Помилка вводу. Введіть ще раз\n";
            break;
        }
    }
    ifile.close();
}



void Worker::deleteData()
{
    bool del = false;
    Worker worker;
    int str;
    cout << "   Введіть id для видалення: ";
    cin >> str;
    ifstream file;
    file.open("Worker.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&worker), sizeof(Worker));
    while (!file.eof())
    {

        if (worker.id != str)
        {
            temp.write(reinterpret_cast<char*>(&worker), sizeof(Worker));
        }

        else
        {
            del = true;
        }
        file.read(reinterpret_cast<char*>(&worker), sizeof(Worker));
    }
    temp.close();
    file.close();
    if (remove("Worker.dat") != 0)
    {
        cout << "\nПомилка. Файл неможливо видалити\n";
    }
    if (rename("temp.dat", "Worker.dat") != 0)
    {
        cout << "\nПомилка. Файл неможливо перейменувати\n";
    }
    if (del == true)
        cout << "\nЗапис видалено\n";
    else
        cout << "\nНе вдалося видалити файл. Спробуйте ще раз.\n";
}

void Worker::editData()
{
    bool edit = false;
    Worker worker;
    int str;
    cout << "Введіть id для редагування: ";
    cin >> str;
    ifstream file;
    file.open("Worker.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&worker), sizeof(Worker));
    while (!file.eof())
    {

        if (worker.id != str)
        {
            temp.write(reinterpret_cast<char*>(&worker), sizeof(Worker));
        }

        else
        {
            worker.create(worker.id);
            temp.write(reinterpret_cast<char*>(&worker), sizeof(Worker));
            edit = true;
        }
        file.read(reinterpret_cast<char*>(&worker), sizeof(Worker));
    }
    temp.close();
    file.close();
    if (remove("Worker.dat") != 0)
    {
        cout << "\nПомилка. Файл неможливо видалити\n";
    }
    if (rename("temp.dat", "Worker.dat") != 0)
    {
        cout << "\nПомилка. Файл неможливо перейменувати\n";
    }
    if (edit == true)
        cout << "\nЗапис змінено\n";
    else
        cout << "\nПомилка при зміні запису спробуйте ще раз.\n";
}