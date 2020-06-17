#include "Record.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Record::setId()
{
    int id;
    string str;
    fstream file;
    file.open("idRecord.txt", fstream::out | fstream::in);
    ifstream temp;
    while (!file.eof())
    {
        getline(file, str);
        id = atoi(str.c_str());
    }
    ++id;
    file.close();
    file.open("idRecord.txt", fstream::out | fstream::in);
    file << id;
    file.close();
    return id;
}
void Record::create(int ID)
{
    cin.ignore(10, '\n');
    cout << "\n    ��'�: "; cin >> name;
    cout << "   �������: "; cin >> surname;
    cout << "   �� �������: "; cin >> patronymic;
    cout << "   ����� �������� "; cin >> phone;
    idWorker = getWorker();
    setService();
    if (ID != 0)
        id = ID;
    else
        id = setId();
}

void Record::setService()
{

    cin.ignore(10, '\n');
    cout << "   ������� �������: \n";
    cout << "   1:������� ��������\n";
    cout << "   2:������ �� �������\n";
    cout << "   3:������� ��������\n";
    cout << "   4:������������ ���������\n";
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
                cout << "   ������� �����. ������ �� ���" << endl;
            }

        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "   ������� �����. ������ �� ���" << endl;
        }
    } while (!valid);

    switch (input)
    {
    case 1:
        service = Hairdressing�ervices;
        break;
    case 2:
        service = ManicureaAdPedicure;
        break;
    case 3:
        service = CosmeticProcedures;
        break;
    case 4:
        service = MakeupServices;
        break;
    default:

        break;
    }
}

void Record::getService(int variant)
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
        cout << "   unknow\n";
        break;
    }
}

int Record::idValid()
{
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "   ������� �����. ������ �� ���" << endl;
        }
    } while (!valid);
    return input;
}

int Record::getWorker()
{
    Worker worker;
    ifstream ifile;
    int id;
    ifile.open("Worker.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    int ok = 0;
    int n;
    while (ok != 1)
    {
        cout << "   ������ id ����������: ";
       id= idValid();
        for (int i = 0; i < worker.count(); i++)
        {
            ifile.seekg(i * sizeof(Worker));
            ifile.read(reinterpret_cast<char*>(&worker), sizeof(Worker));
            n = worker.getId();
            if (id == n)
            {
                ok = 1;
                return worker.getId();
            }
        }
        cout << "\n ���������� � ����� id ����. ������ �� ���\n";
    }
}

void Record::showData()
{
    cout << "   id : " << id << endl;
    cout << "   ��'�: " << name << endl;
    cout << "   �������: " << surname << endl;
    cout << "   �� �������: " << patronymic << endl;
    cout << "   ����� ��������: " << phone << endl;
    cout << "   �������:"; getService(service);
    cout << "   id ����������: " << idWorker;


}

void Record::read(int pn)
{
    ifstream ifile;
    ifile.open("Record.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(pn * sizeof(Record));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}

void Record::write()
{
    ofstream ofile;
    ofile.open("Record.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

int Record::count()
{
    ifstream ifile;
    ifile.open("Record.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    return (int)ifile.tellg() / sizeof(Record);
    ifile.close();
}


int Record::search(int variant)
{
    if (variant == 0)
        return 0;
    Record record;
    ifstream ifile;
    char str[40];
    ifile.open("Record.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "\n    ������ ��� ��� ������: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(Record));
        ifile.read(reinterpret_cast<char*>(&record), sizeof(Record));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, record.name))
            {
                record.showData();
            }
            break;

        case 2:
            if (0 == strcmp(str, record.surname))
            {
                record.showData();
            }
            break;
        case 3:
            if (0 == strcmp(str, record.patronymic))
            {
                record.showData();
            }
            break;
        case 4:
            if (0 == strcmp(str, record.phone))
            {
                record.showData();
            }
            break;
        case 5:
            if (atoi(str) == record.service)
            {
                record.showData();
            }
            break;
        case 6:
            if ((int)str == record.idWorker)
            {
                record.showData();
            }
        case 7:
            if ((int)str == record.id)
            {
                record.showData();
            }
            break;
        default:
            cout << "   ������� �����. ������ �� ���\n";
            break;
        }
    }
    ifile.close();
}


void Record::deleteData()
{
    bool del = false;
    Record record;
    int str;
    cout << "   ������ ����� ��������� ��� ���������: ";
    cin >> str;
    ifstream file;
    file.open("Record.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&record), sizeof(Record));
    while (!file.eof())
    {

        if (record.id != str)
        {
            temp.write(reinterpret_cast<char*>(&record), sizeof(Record));
        }

        else
        {
            del = true;
        }
        file.read(reinterpret_cast<char*>(&record), sizeof(Record));
    }
    temp.close();
    file.close();
    if (remove("Record.dat") != 0)
    {
        cout << "\n    �������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "Record.dat") != 0)
    {
        cout << "\n    �������. ���� ��������� �������������\n";
    }
    if (del == true)
        cout << "\n    ����� ��������\n";
    else
        cout << "\n    �� ������� �������� ����. ��������� �� ���.\n";
}

void Record::editData()
{
    bool edit = false;
    Record record;
    int str;
    cout << "   ������ id ��� �����������: ";
    cin >> str;
    ifstream file;
    file.open("Record.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&record), sizeof(Record));
    while (!file.eof())
    {

        if (record.id != str)
        {
            temp.write(reinterpret_cast<char*>(&record), sizeof(Record));
        }

        else
        {
            record.showData();
            record.create(record.id);
            temp.write(reinterpret_cast<char*>(&record), sizeof(Record));
            edit = true;
        }
        file.read(reinterpret_cast<char*>(&record), sizeof(Record));
    }
    temp.close();
    file.close();
    if (remove("Record.dat") != 0)
    {
        cout << "\n    �������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "Record.dat") != 0)
    {
        cout << "\n    �������. ���� ��������� �������������\n";
    }
    if (edit == true)
        cout << "\n    ����� ������\n";
    else
        cout << "\n    ������� ��� ��� ������ ��������� �� ���.\n";
}
