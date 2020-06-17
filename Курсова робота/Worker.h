#pragma once
#include "Human.h"
enum Position
{
    hairdresser=1,
    masterOfManicure,
    MakeUpArtist,
    beautician
};
class Worker : public Human
{
private:
    int id;
    Position position;
public:
    virtual void create(int) override;
    virtual void showData() override;
    void read(int pn);
    void write();
    static int count();
    int search(int variant);
    void deleteData();
    void editData();
    int setId();
    void setPosition();
    void getPosition(int);
    int getId();
};

