#pragma once
#include "Human.h"
#include "Worker.h"
enum Service
{
	Hairdressing€ervices = 1,
	ManicureaAdPedicure,
	CosmeticProcedures,
	MakeupServices
};
class Record : public Human
{
private:
	int id;
	Service service;
	Worker worker;
	char phone[13];
	int idWorker;
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
	int getWorker();
	void setService();
	void getService(int);
	int idValid();
};

