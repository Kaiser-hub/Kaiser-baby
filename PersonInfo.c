#include<stdio.h>
#include<string.h>

#define Total 1024

//定义联系人的结构体，包含姓名和电话号码
typedef struct PersonInfo {
	char name[256];
	char sex[32];
	char age[32];
	char phone[256];
	char address[256];
}PersonInfo;

//定一个联系人界面的结构体，包含联系人总个数和有效个数
//[0,size)这个是有效元素，[size,Total)是无效元素
typedef struct AddressBook{
	PersonInfo person[Total];
	int size;
}AddressBook;

//初始化函数，把所有的联系人信息，先进性初始化
//这里的函数参数，使用了指针类型 ，原因有二
//1.结构体作为函数参数时，需要进行拷贝操作，而结构体一般占用的内存都比较大，参数写成指针类型，可以有效的减少拷贝开销
//2.初始化函数的内部需要修改结构体变量的内容，我们在函数内部修改，同时还要影响到外部，此时传指针，相当于输出型参数
void Init(AddressBook* addr) {
	addr->size = 0;
	for (int i = 0; i < Total; i++) {
		strcpy(addr->person[i].name, "");
		strcpy(addr->person[i].sex, "");
		strcpy(addr->person[i].age, "");
		strcpy(addr->person[i].phone, "");
		strcpy(addr->person[i].address, "");
	}
}

int Print() {
	printf("========================\n");
	printf("1.添加联系人\n");
	printf("2.删除指定联系人\n");
	printf("3.查找指定联系人\n");
	printf("4.修改指定联系人\n");
	printf("5.显示所有联系人\n");
	printf("6.清空所有联系人\n");
	printf("0.退出程序\n");
	printf("========================\n");
	printf("请输入您的选择\n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

//添加联系人函数
void AddPersonInfo(AddressBook* address_book) {
	printf("新增联系人!\n");
	PersonInfo* info = &address_book->person[address_book->size];
	printf("请输入新增联系人的姓名：\n");
	scanf("%s", info->name);
	printf("请输入新增联系人的性别：\n");
	scanf("%s", info->sex);
	printf("请输入新增联系人的年龄：\n");
	scanf("%s", info->age);
	printf("请输入新增联系人的电话号码：\n");
	scanf("%s", info->phone);
	printf("请输入新增联系人的住址：\n");
	scanf("%s", info->address);
	address_book->size++;
	printf("~~新增联系人成功！\n");
}

//删除指定联系人函数
void DelPersonInfo(AddressBook* address_book) {
	printf("删除指定联系人\n");
	if (address_book->size <= 0) {
		printf("通讯录为空，操作失败\n");
		return;
	}
	printf("请输入要删除联系人的序号:");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= address_book->size) {
		printf("您输入的序号违法，操作失败\n");
		return;
	}
	//获取最后一个元素
	PersonInfo* last_info = &address_book->person[address_book->size-1];
	//获取待删除的元素
	PersonInfo* delete_info = &address_book->person[id];
	*delete_info = *last_info;
	address_book->size--;
	printf("指定联系人删除成功！\n");
}

//查找指定联系人函数
void FindPersonInfo(AddressBook* address_book) {
	//假如查找的联系人存在重名情况，则显示所有重名的联系人
	printf("查找指定联系人\n");
	printf("请输入您想要查找联系人的姓名\n");
	char name[256] = { 0 };
	scanf("%s", name);
	for (int i = 0; i < address_book->size; i++) {
		PersonInfo* find_info = &address_book->person[i];
		if (strcmp(name, find_info->name) == 0) {
			printf("[%d] %s: %s, %s, %s, %s\n", i, find_info->name, find_info->sex, find_info->age, find_info->phone, find_info->address);
		}
	}
	printf("显示查找联系人如上\n");
}

//修改指定联系人函数
void ModifyPersonInfo(AddressBook* address_book) {
	printf("修改指定联系人信息\n");
	printf("请输入需要修改联系人的序号：\n");
	if (address_book->size <= 0) {
		printf("通讯录为空，操作失败\n");
		return;
	}
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= address_book->size) {
		printf("您输入的序号违法，操作失败\n");
		return;
	}
	PersonInfo* info = &address_book->person[id];
	printf("请输入修改后的信息(*表示此项不做修改)\n");
	printf("姓名：");
	char name[256] = { 0 };
	scanf("%s", name);
	if (strcmp(name, "*") != 0) {
		strcpy(info->name, name);
	}
	printf("性别：");
	char sex[32] = { 0 };
	scanf("%s", sex);
	if (strcmp(sex, "*") != 0) {
		strcpy(info->sex, sex);
	}
	printf("年龄：");
	char age[32] = { 0 };
	scanf("%s", age);
	if (strcmp(age, "*") != 0) {
		strcpy(info->age, age);
	}
	printf("电话：");
	char phone[256] = { 0 };
	scanf("%s", phone);
	if (strcmp(phone, "*") != 0) {
		strcpy(info->phone, phone);
	}
	printf("住址：");
	char address[256] = { 0 };
	scanf("%s", address);
	if (strcmp(address, "*") != 0) {
		strcpy(info->address, address);
	}
	printf("修改成功！\n");
}

//显示所有联系人函数
void ShowPersonInfo(AddressBook* address_book) {
	printf("显示所有联系人\n");
	//按姓名排序之后的顺序显示
	PersonInfo ret = { "\0" };
	for (int i = 0; i < address_book->size; i++) {
		PersonInfo* info = &address_book->person[i];
		for (int j = i + 1; j < address_book->size; j++) {
			PersonInfo* info1 = &address_book->person[j];
			if (strcmp(info->name, info1->name) > 0) {
				ret = *info;
				*info = *info1;
				*info1 = ret;
			}
		}
	}
	for (int a = 0; a < address_book->size; a++) {
		PersonInfo* info = &address_book->person[a];
		printf("[%d] %s: %s, %s, %s, %s\n", a, info->name, info->sex, info->age, info->phone, info->address);
	}
	printf("当前共显示%d条记录\n", address_book->size);
}

//清空所有联系人函数
void ClearPersonInfo(AddressBook* address_book) {
	printf("清空所有联系人\n");
	printf("您真的确定要清空所有联系人吗，Yes/No\n");
	char choice[32] = { 0 };
	scanf("%s", choice);
	if (strcmp(choice, "Yes") == 0 || strcmp(choice, "yes") == 0) {
		address_book->size = 0;
		printf("清空完毕！\n");
		return;
	}
	else {
		printf("清空操作已取消\n");
		return;
	}
}

int main() {
	AddressBook address_book;
	Init(&address_book);
	typedef void(*Func)(AddressBook*);
	Func func_table[] = {
		NULL,//这里加个NULL，是为了与函数Print()中的选项的序号对应上
		AddPersonInfo,
		DelPersonInfo,
		FindPersonInfo,
		ModifyPersonInfo,
		ShowPersonInfo,
		ClearPersonInfo
	};
	while (1) {
		int choice = Print();
		if (choice < 0 || choice >= sizeof(func_table) / sizeof(func_table[0])) {
			printf("您的输入不合法\n");
			continue;
		}
		if (choice == 0) {
			printf("再见！\n");
			break;
		}
		func_table[choice](&address_book);
	}
	return 0;
}
