
#include "contact.h"


void InitContact(struct Contact* p) {

	p->data = (struct PeoInfo*)malloc(DELFAULT_SZ * sizeof(struct PeoInfo));
	if (p->data == NULL) {
		return;
	}

	p->size = 0;
	p->capacity = DELFAULT_SZ;

	//把文件中已经存放的的通讯录中的信息加载到通讯录中
	LoadContact(p);

	/*memset(p->data, 0, sizeof(p->data));
	p->size = 0;*/
}

void CheckCapacity(struct Contact* p);

void LoadContact(struct Contact* p) {
	struct PeoInfo buf = {0};
	FILE* pfRead = fopen("contact.txt", "rb");
	if (pfRead == NULL) {
		printf("LoadContact: %s\n", strerror(errno));
		return;
	}
	while (fread(&buf,sizeof(struct PeoInfo),1,pfRead)) {
		CheckCapacity(p);
		p->data[p->size] = buf;
		p->size++;
	}

	fclose(pfRead);
	pfRead = NULL;
}

void CheckCapacity(struct Contact* p) {
	if (p->size == p->capacity) {
		struct PeoInfo* ptr = (struct PeoInfo*)realloc(p->data, (p->capacity + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL) {
			p->data = ptr;
			p->capacity += 2;
			printf("扩容成功\n");
		}
		else {
			printf("扩容失败\n");
		}
	

	}


}

void AddContact(struct Contact* p) {

	 CheckCapacity(p);

	 printf("请输入姓名：");
	 scanf("%s", p->data[p->size].name);
	 printf("请输入性别：");
	 scanf("%s", p->data[p->size].sex);
	 printf("请输入年龄：");
	 scanf("%d", &(p->data[p->size].age));
	 printf("请输入tele：");
	 scanf("%s", p->data[p->size].tele);
	 printf("请输入地址：");
	 scanf("%s", p->data[p->size].addr);
	 p->size++;
	 printf("添加成功\n");


	/*if (p->size == MAX) {
		printf("通讯录已满，无法添加\n");
	}
	else {
		printf("请输入姓名：");
		scanf("%s", p->data[p->size].name);
		printf("请输入性别：");
		scanf("%s", p->data[p->size].sex);
		printf("请输入年龄：");
		scanf("%d", &(p->data[p->size].age));
		printf("请输入tele：");
		scanf("%s", p->data[p->size].tele);
		printf("请输入地址：");
		scanf("%s", p->data[p->size].addr);
		p->size++;
		printf("添加成功\n");
	}*/
}

void ShowContact(struct Contact* p) {
	if (p->data == 0) {
		printf("该通讯录没有用户\n");
	}
	else {
		int i = 0;
		printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "电话", "地址");
		for (i = 0; i < p->size; i++) {
			printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n",
				p->data[i].name, 
				p->data[i].sex, 
				p->data[i].age, 
				p->data[i].tele, 
				p->data[i].addr);
			
		}
	}
}

int FindByName(struct Contact* p, char name[]) {
	int i = 0;
	for (i = 0; i < p->size; i++)
	{
		if (0 == strcmp(p->data[i].name, name)) {
			return i;
		}
	}
	return -1;
}

void DelContact(struct Contact* p) {
	int j = 0;
	char name[MAX_NAME];
	printf("请输入要删除的联系人姓名：");
	scanf("%s", name);
	//判断删除联系人的位置
	//返回-1，没有该联系人
	//返回i，
	int pos = FindByName(p, name);
	if (pos == -1) {
		printf("没有该联系人！\n");
	}
	else {
		for (j = pos; j < p->size - 1; j++) {
			p->data[j] = p->data[j + 1];
		}
		p->size--;
		printf("删除成功！\n");
	}
}

void SearchContact(struct Contact* p) {
	int i = 0;
	char name[MAX_NAME];
	printf("请输入要查找的联系人姓名：");
	scanf("%s", name);
	//判断删除联系人的位置
	//返回-1，没有该联系人
	//返回i，
	int pos = FindByName(p, name);
	if (pos == -1) {
		printf("没有该联系人！\n");
	}
	else {
		printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "电话", "地址");
		printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n",
			p->data[pos].name,
			p->data[pos].sex,
			p->data[pos].age,
			p->data[pos].tele,
			p->data[pos].addr);
	}
}

void ModifyContact(struct Contact* p) {
	int i = 0;
	char name[MAX_NAME];
	printf("请输入要修改的联系人姓名：");
	scanf("%s", name);
	//判断删除联系人的位置
	//返回-1，没有该联系人
	//返回i，
	int pos = FindByName(p, name);
	if (pos == -1) {
		printf("没有该联系人！\n");

	}
	else {
		printf("请输入姓名：");
		scanf("%s", p->data[pos].name);
		printf("请输入性别：");
		scanf("%s", p->data[pos].sex);
		printf("请输入年龄：");
		scanf("%d", &(p->data[pos].age));
		printf("请输入tele：");
		scanf("%s", p->data[pos].tele);
		printf("请输入地址：");
		scanf("%s", p->data[pos].addr);
		printf("修改成功！\n");
	}
}

void DestoryContact(struct Contact* p) {
	free(p->data);
	p->data = NULL;
}

void SaveContact(struct Contact* p) {
	FILE* pfWrite = fopen("contact.txt", "wb");
	if (pfWrite == NULL) {
		printf("%s\n", strerror(errno));
		return;
	}
	int i = 0;
	for (i = 0; i < p->size; i++) {
		fwrite(&(p->data[i]), sizeof(struct PeoInfo), 1, pfWrite);
	}

	fclose(pfWrite);
	pfWrite = NULL;
}