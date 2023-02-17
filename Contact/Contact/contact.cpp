
#include "contact.h"


void InitContact(struct Contact* p) {

	p->data = (struct PeoInfo*)malloc(DELFAULT_SZ * sizeof(struct PeoInfo));
	if (p->data == NULL) {
		return;
	}

	p->size = 0;
	p->capacity = DELFAULT_SZ;

	//���ļ����Ѿ���ŵĵ�ͨѶ¼�е���Ϣ���ص�ͨѶ¼��
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
			printf("���ݳɹ�\n");
		}
		else {
			printf("����ʧ��\n");
		}
	

	}


}

void AddContact(struct Contact* p) {

	 CheckCapacity(p);

	 printf("������������");
	 scanf("%s", p->data[p->size].name);
	 printf("�������Ա�");
	 scanf("%s", p->data[p->size].sex);
	 printf("���������䣺");
	 scanf("%d", &(p->data[p->size].age));
	 printf("������tele��");
	 scanf("%s", p->data[p->size].tele);
	 printf("�������ַ��");
	 scanf("%s", p->data[p->size].addr);
	 p->size++;
	 printf("��ӳɹ�\n");


	/*if (p->size == MAX) {
		printf("ͨѶ¼�������޷����\n");
	}
	else {
		printf("������������");
		scanf("%s", p->data[p->size].name);
		printf("�������Ա�");
		scanf("%s", p->data[p->size].sex);
		printf("���������䣺");
		scanf("%d", &(p->data[p->size].age));
		printf("������tele��");
		scanf("%s", p->data[p->size].tele);
		printf("�������ַ��");
		scanf("%s", p->data[p->size].addr);
		p->size++;
		printf("��ӳɹ�\n");
	}*/
}

void ShowContact(struct Contact* p) {
	if (p->data == 0) {
		printf("��ͨѶ¼û���û�\n");
	}
	else {
		int i = 0;
		printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n", "����", "�Ա�", "����", "�绰", "��ַ");
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
	printf("������Ҫɾ������ϵ��������");
	scanf("%s", name);
	//�ж�ɾ����ϵ�˵�λ��
	//����-1��û�и���ϵ��
	//����i��
	int pos = FindByName(p, name);
	if (pos == -1) {
		printf("û�и���ϵ�ˣ�\n");
	}
	else {
		for (j = pos; j < p->size - 1; j++) {
			p->data[j] = p->data[j + 1];
		}
		p->size--;
		printf("ɾ���ɹ���\n");
	}
}

void SearchContact(struct Contact* p) {
	int i = 0;
	char name[MAX_NAME];
	printf("������Ҫ���ҵ���ϵ��������");
	scanf("%s", name);
	//�ж�ɾ����ϵ�˵�λ��
	//����-1��û�и���ϵ��
	//����i��
	int pos = FindByName(p, name);
	if (pos == -1) {
		printf("û�и���ϵ�ˣ�\n");
	}
	else {
		printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n", "����", "�Ա�", "����", "�绰", "��ַ");
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
	printf("������Ҫ�޸ĵ���ϵ��������");
	scanf("%s", name);
	//�ж�ɾ����ϵ�˵�λ��
	//����-1��û�и���ϵ��
	//����i��
	int pos = FindByName(p, name);
	if (pos == -1) {
		printf("û�и���ϵ�ˣ�\n");

	}
	else {
		printf("������������");
		scanf("%s", p->data[pos].name);
		printf("�������Ա�");
		scanf("%s", p->data[pos].sex);
		printf("���������䣺");
		scanf("%d", &(p->data[pos].age));
		printf("������tele��");
		scanf("%s", p->data[pos].tele);
		printf("�������ַ��");
		scanf("%s", p->data[pos].addr);
		printf("�޸ĳɹ���\n");
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