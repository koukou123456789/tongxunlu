#include "contact.h"


void menu() {
	printf("*********************************\n");
	printf("**** 1.add        2.delete ******\n");
	printf("**** 3.search     4.modify   ****\n");
	printf("**** 5.show       6.save     ****\n");
	printf("**** 0.exit                  ****\n");
	printf("*********************************\n");
}

int main() {
	int input = 0;


	//����ͨѶ¼��
	struct Contact con;
	InitContact(&con);

	do
	{
		menu();
		printf("��ѡ��");
		scanf("%d", &input);
		switch (input) {
		case ADD:
			AddContact(&con);
			break;
		case DELETE:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SAVE:
			SaveContact(&con);
			break;
		case EXIT:
			printf("�˳�ͨѶ¼��\n");
			DestoryContact(&con);
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
}


