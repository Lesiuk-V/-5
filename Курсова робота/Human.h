#pragma once
class Human
{
protected:
    char  name[40];
    char surname[40];
    char patronymic[40];
    char dateOfBirth[11];
    char phone[14];
public:
    virtual void create(int) = 0;
    virtual void showData() = 0;
};

