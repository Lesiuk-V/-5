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
    cout << "\n    ��'�: "; cin >> name;
    cout << "   �������: "; cin >> surname;
    cout << "   �� �������: "; cin >> patronymic;
    setPosition();
    cout << "   ���� ����������(����.�����.��): "; cin >> dateOfBirth;
    cout << "   ����� ��������:"; cin >> phone;
    if (ID != 0)
        id = ID;
    else
        id = setId();
}
void Worker::showData()
{
    cout << "   id: " << id << endl;
    cout << "   ��'�: " << name << endl;
    cout << "   �������: " << surname << endl;
    cout << "   �� �������: " << patronymic << endl;
    cout << "   ������: "; getPosition(position);
    cout << "   ���� ����������(����.�����.��): " << dateOfBirth << endl;
    cout << "   ����� ��������:" << phone;
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
    cout << "  ������� �������: \n";
    cout << "   1:�������\n";
    cout << "   2:������� ������� \n";
    cout << "   3:³������\n";
    cout << "   4:����������\n";
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
                cout << "������� �����. ������ �� ���" << endl;
            }

        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������� �����. ������ �� ���" << endl;
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
        cout << "   ������� ��������\n";
        break;
    case 2:
        cout << "   ������ �� �������\n";
        break;
    case 3:
        cout << "   ������� ��������\n";
        break;
    case 4:
        cout << "   ������������ ���������\n";
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
    cout << "\n������ ��� ��� ������: ";
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
            cout << "   ������� �����. ������ �� ���\n";
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
    cout << "   ������ id ��� ���������: ";
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
        cout << "\n�������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "Worker.dat") != 0)
    {
        cout << "\n�������. ���� ��������� �������������\n";
    }
    if (del == true)
        cout << "\n����� ��������\n";
    else
        cout << "\n�� ������� �������� ����. ��������� �� ���.\n";
}

void Worker::editData()
{
    bool edit = false;
    Worker worker;
    int str;
    cout << "������ id ��� �����������: ";
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
        cout << "\n�������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "Worker.dat") != 0)
    {
        cout << "\n�������. ���� ��������� �������������\n";
    }
    if (edit == true)
        cout << "\n����� ������\n";
    else
        cout << "\n������� ��� ��� ������ ��������� �� ���.\n";
}