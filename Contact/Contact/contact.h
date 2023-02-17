#pragma once

#include<iostream>
using namespace std;

#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 50
#define DELFAULT_SZ 3
//#define MAX 1000


struct PeoInfo {
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};


//通讯录类型
struct Contact {
	struct PeoInfo* data;  //存放一个信息
	int size;  //记录当前已经有的元素个数
	int capacity;  //记录最大容量
};

enum Function {
	EXIT,
	ADD,
	DELETE,
	SEARCH,
	MODIFY,
	SHOW,
	SAVE,
};

//声明函数
void InitContact(struct Contact* p);

void AddContact(struct Contact* p);

void ShowContact(struct Contact* p);

void DelContact(struct Contact* p);

void SearchContact(struct Contact* p);

void ModifyContact(struct Contact* p);

void DestoryContact(struct Contact* p);

void SaveContact(struct Contact* p);

void LoadContact(struct Contact* p);