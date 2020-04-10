#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>


typedef struct chsystem//chat_system的缩写
{
	char name[15];//姓名
	char tel[20];//手机
	char tecent[15];//qq号码
	char email[20];//邮箱
}cs;//通讯录结构体

typedef struct pcs
{
	cs chat;
	pcs* next;
}*ptcs;//通讯录节点
ptcs head = (ptcs)malloc(sizeof(pcs));//在函数外只能进行变量定义与初始化，并不能进行操作
//操作只能在函数体内进行

int menu_select()//功能选择框
{
	char c;
	do
	{
		system("cls");
		printf("\n\t\t**********通讯录管理系统**********\n");
		printf("\t\t^*****************^-^**************^\n");
		printf("\t\t|           1.添加联系人           |\n");
		printf("\t\t|           2.查询联系人           |\n");
		printf("\t\t|           3.删除联系人           |\n");
		printf("\t\t|           4.修改联系人信息       |\n");
		printf("\t\t|           5.输出联系人列表       |\n");
		printf("\t\t|           6.排序                 |\n");
		printf("\t\t|           7.写入文件             |\n");
		printf("\t\t|           8.读取文件             |\n");
		printf("\t\t|           9.通话记录             |\n");
		printf("\t\t|           0.退出                 |\n");
		printf("\t\t|**********************************|\n");
		printf("\t\t请您选择(0-9):");
		c = getchar();
	} while (c < '0' || c>'9');//检查输入是否符合规范
	return(c - '0');//这里稍微复杂化了，c只要定义为int型，最后直接返回c就行了
}

int cala(char* p)//计算字符串长度
{
	int i, n = 0;
	for (i = 0; p[i] != '\0'; i++)n++;
	return n;
}

int Addpeo()//添加联系人
{
	int t, n, a;
	char flag = 'y';
	ptcs p = head, q;
	while (p->next)p = p->next;
	while (flag != 'n' && flag != 'N')
	{
		q = (ptcs)malloc(sizeof(pcs));
		p->next = q;
		p = q;
		q->next = NULL;
		printf("\n\t\t请输入:\n");
		printf("\t\t姓名:");//输入姓名
		scanf("\t\t%s", q->chat.name);
		printf("\t\t手机号码:");//输入手机号
		scanf("\t\t%s", q->chat.tel);
		do
		{
			n = 0;
			if (cala(q->chat.tel) != 11)
			{
				n = 1;
				printf("\t\t您输入的手机号码格式不存在,请重新输入:");
				scanf("\t\t%s", q->chat.tel);
			}
			else
			{
				for (t = 0; t < 11; t++)
				{
					if (q->chat.tel[t] < '0' || q->chat.tel[t]>'9')
					{
						n = 1;
						printf("\t\t您输入的手机号码格式不合理,请重新输入:");
						scanf("\t\t%s", q->chat.tel);
						break;
					}
				}
			}
		} while (n);
		printf("\t\tQQ号:");//输入QQ号
		scanf("\t\t%s", q->chat.tecent);
		do
		{
			n = 0;
			if (cala(q->chat.tecent) > 10)
			{
				n = 1;
				printf("\t\t您输入的QQ号码格式不存在,请重新输入:");
				scanf("\t\t%s", q->chat.tecent);
			}
			else
			{
				for (t = 0; t < 10; t++)
				{
					if (q->chat.tecent[t] < '0' || q->chat.tecent[t]>'9')
					{
						n = 1;
						printf("\t\t您输入的QQ号码格式不合理,请重新输入:");
						scanf("\t\t%s", q->chat.tecent);
						break;
					}
				}
			}
		} while (n);
		printf("\t\t电子邮箱:");//输入邮箱
		scanf("\t\t%s", q->chat.email);
		do
		{
			a = 0;
			for (t = 0; q->chat.email[t] != '\0'; t++)
			{
				if (q->chat.email[t] == '@')
					a++;
			}
			if (a != 1)
			{
				printf("\t\t输入的邮箱不合理，请重新输入:");
				scanf("\t\t%s", q->chat.email);
			}
		} while (a != 1);
		printf("\n\t\t是否继续添加?(Y/N)");
		scanf("\t\t%c", &flag);
	}
	return 0;
}

int watch_over()//查询联系人
{
	int m, n;
	char flag = 'y';
	ptcs p = head->next;
	while (flag != 'n' && flag != 'N')
	{
		printf("\n\t\t*************查询方式*************\n");
		printf("\t\t^*****************^-^**************^\n");
		printf("\t\t|            1.查找姓名            |\n");
		printf("\t\t|            2.查找手机号          |\n");
		printf("\t\t|            3.查找QQ号码          |\n");
		printf("\t\t|            4.返回                |\n");
		printf("\t\t|**********************************|\n");
		printf("\n\t\t请选择查询方式:");
		scanf("\t\t%d", &m);//选择查询方式
		do
		{
			n = 0;
			if (m != 1 && m != 2 && m != 3 && m != 4)
			{
				n = 1;
				printf("\t\t您输入的查询方式不存在,请重新输入:");
				scanf("\t\t%d", &m);//选择查询方式
			}
		} while (n);
		if (!p)
		{
			printf("\t\t该通讯录为空!\n");
			return 0;
		}
		if (1 == m)
		{
			char nm[15];
			p = head->next;
			printf("\t\t请输入您要查询的联系人:");
			scanf("\t\t%s", nm);
			while (p != NULL && strcmp(p->chat.name, nm) != 0)p = p->next;
			if (!p)
			{
				printf("\t\t您要查询的联系人不存在!\n");
				printf("\t\t是否继续查询?(Y/N)");
				scanf("\t\t%c", &flag);
				return 0;
			}
			printf("\t\t手机号码:%s\n", p->chat.tel);
			printf("\t\tqq号:%s\n", p->chat.tecent);
			printf("\t\t电子邮箱:%s\n", p->chat.email);
		}
		if (2 == m)
		{
			char te[20];
			p = head->next;
			printf("\t\t请输入您要查询的手机号码:");
			scanf("\t\t%s", te);
			while (p != NULL && strcmp(p->chat.tel, te) != 0)p = p->next;
			if (!p)
			{
				printf("\t\t您要查询的联系人不存在!\n");
				printf("\t\t是否继续查询?(Y/N)");
				scanf("\t\t%c", &flag);
				return 0;
			}
			printf("\t\t姓名:%s\n", p->chat.name);
			printf("\t\tqq号:%s\n", p->chat.tecent);
			printf("\t\t电子邮箱:%s\n", p->chat.email);
		}
		if (3 == m)
		{
			char qq[15];
			p = head->next;
			printf("\t\t请输入您要查询的qq号:");
			scanf("\t\t%s", qq);
			while (p != NULL && strcmp(p->chat.tecent, qq) != 0)p = p->next;
			if (!p)
			{
				printf("\t\t您要查询的联系人不存在!\n");
				printf("\t\t是否继续查询?(Y/N)");
				scanf("\t\t%c", &flag);
				return 0;
			}
			printf("\t\t姓名:%s\n", p->chat.name);
			printf("\t\t手机号:%s\n", p->chat.tecent);
			printf("\t\t电子邮箱:%s\n", p->chat.email);
		}
		if (4 == m)return 0;
		printf("\t\t是否继续查询?(Y/N)");
		scanf("\t\t%c", &flag);
	}
	return 0;
}

int Delete()//删除个人信息
{
	char nm[20];
	char flag = 'y';
	ptcs p = head->next, bh, pre;
	if (!p)
	{
		printf("\t\t该通讯录为空!\n");
		return 0;
	}
	while (flag != 'n' && flag != 'N')
	{
		p = head->next;
		printf("\t\t请输入您要删除的联系人姓名:");
		scanf("\t\t%s", nm);
		while (p != NULL && strcmp(p->chat.name, nm) != 0)
		{
			pre = p;
			p = p->next;
		}
		if (!p)
		{
			printf("\t\t该联系人不存在!\n");
			printf("\t\t是否继续删除?(Y/N)");
			scanf("\t\t%c", &flag);
			return 0;
		}
		bh = p->next;
		if (p == head->next)head->next = bh;
		else pre->next = bh;
		printf("\t\t该联系人已删除!\n");
		printf("\t\t是否继续删除?(Y/N)");
		scanf("\t\t%c", &flag);
	}
	return 0;
}

int changeall(ptcs p)//修改某一联系人的所有信息
{
	int a, n, t;
	printf("\t\t姓名:");//输入姓名
	scanf("\t\t%s", p->chat.name);
	printf("\t\t手机号码:");//输入手机号
	scanf("\t\t%s", p->chat.tel);
	do
	{
		n = 0;
		if (cala(p->chat.tel) != 11)
		{
			n = 1;
			printf("\t\t您输入的手机号码格式不存在,请重新输入:");
			scanf("\t\t%s", p->chat.tel);
		}
		else
		{
			for (t = 0; t < 11; t++)
			{
				if (p->chat.tel[t] < '0' || p->chat.tel[t]>'9')
				{
					n = 1;
					printf("\t\t您输入的手机号码格式不合理,请重新输入:");
					scanf("\t\t%s", p->chat.tel);
					break;
				}
			}
		}
	} while (n);
	printf("\t\tQQ号:");//输入QQ号
	scanf("\t\t%s", p->chat.tecent);
	do
	{
		n = 0;
		if (cala(p->chat.tecent) != 10)
		{
			n = 1;
			printf("\t\t您输入的QQ号码格式不存在,请重新输入:");
			scanf("\t\t%s", p->chat.tecent);
		}
		else
		{
			for (t = 0; t < 10; t++)
			{
				if (p->chat.tecent[t] < '0' || p->chat.tecent[t]>'9')
				{
					n = 1;
					printf("\t\t您输入的QQ号码格式不合理,请重新输入:");
					scanf("\t\t%s", p->chat.tecent);
					break;
				}
			}
		}
	} while (n);
	printf("\t\t电子邮箱:");//输入邮箱
	scanf("\t\t%s", p->chat.email);
	do
	{
		a = 0;
		for (t = 0; p->chat.email[t] != '\0'; t++)
		{
			if (p->chat.email[t] == '@')
				a++;
		}
		if (a != 1)
		{
			printf("\t\t输入的邮箱不合理，请重新输入:");
			scanf("\t\t%s", p->chat.email);
		}
	} while (a != 1);
	return 0;
}

int changetel(ptcs p)//修改手机号内容
{
	int n, t;
	scanf("\t\t%s", p->chat.tel);
	do
	{
		n = 0;
		if (cala(p->chat.tel) != 11)
		{
			n = 1;
			printf("\t\t您输入的手机号码格式不存在,请重新输入:");
			scanf("\t\t%s", p->chat.tel);
		}
		else
		{
			for (t = 0; t < 11; t++)
			{
				if (p->chat.tel[t] < '0' || p->chat.tel[t]>'9')
				{
					n = 1;
					printf("\t\t您输入的手机号码格式不合理,请重新输入:");
					scanf("\t\t%s", p->chat.tel);
					break;
				}
			}
		}
	} while (n);
	return 0;
}

int changeQQ(ptcs p)//修改QQ号码
{
	int n, t;
	scanf("%s", p->chat.tecent);
	do
	{
		n = 0;
		if (cala(p->chat.tecent) != 10)
		{
			n = 1;
			printf("\t\t您输入的QQ号码格式不存在,请重新输入:");
			scanf("\t\t%s", p->chat.tecent);
		}
		else
		{
			for (t = 0; t < 10; t++)
			{
				if (p->chat.tecent[t] < '0' || p->chat.tecent[t]>'9')
				{
					n = 1;
					printf("\t\t您输入的QQ号码格式不合理,请重新输入:");
					scanf("\t\t%s", p->chat.tecent);
					break;
				}
			}
		}
	} while (n);
	return 0;
}

int changeEmail(ptcs p)//修改电子邮箱
{
	int t, a;
	scanf("\t\t%s", p->chat.email);
	do
	{
		a = 0;
		for (t = 0; p->chat.email[t] != '\0'; t++)
		{
			if (p->chat.email[t] == '@')
				a++;
		}
		if (a != 1)
		{
			printf("\t\t输入的邮箱不合理，请重新输入:");
			scanf("\t\t%s", p->chat.email);
		}
	} while (a == 1);
	return 0;
}

int change()//修改联系人信息
{
	char nm[20], flag = 'y';
	int m, n;
	ptcs p = head->next;
	if (!p)
	{
		printf("\t\t该通讯录为空!\n");
		return 0;
	}
	while (flag != 'n' && flag != 'N')
	{
		p = head->next;
		printf("\n\t\t*******hello!请输入您要修改的内容*******\n");
		printf("\t\t^*****************^-^**************^\n");
		printf("\t\t|              1.联系人            |\n");
		printf("\t\t|              2.手机号码          |\n");
		printf("\t\t|              3.QQ号              |\n");
		printf("\t\t|              4.电子邮箱          |\n");
		printf("\t\t|              5.返回              |\n");
		printf("\t\t|**********************************|\n");
		printf("\n\t\t请输入您要修改的内容:");
		scanf("\t\t%d", &m);
		do
		{
			n = 0;
			if (m != 1 && m != 2 && m != 3 && m != 4 && m != 5)
			{
				n = 1;
				printf("\t\t您输入的修改内容不存在,请重新输入:");
				scanf("\t\t%d", &m);//选择修改内容
			}
		} while (n);
		if (5 == m)return 0;
		printf("\t\t请输入您想修改信息的联系人的姓名:");
		scanf("\t\t%s", nm);
		while (p != NULL && strcmp(p->chat.name, nm) != 0)p = p->next;
		if (!p)
		{
			printf("\t\t该联系人不存在!\n");
			return 0;
		}
		if (1 == m)
		{
			printf("\t\t请输入您的修改:\n");
			changeall(p);
		}
		if (2 == m)
		{
			printf("\t\t请输入%s的手机号码:", p->chat.name);
			changetel(p);
		}
		if (3 == m)
		{
			printf("\t\t请输入%s的QQ号:", p->chat.name);
			changeQQ(p);
		}
		if (4 == m)
		{
			printf("\t\t请输入%s的电子邮箱:", p->chat.name);
			changeEmail(p);
		}
		printf("\t\t是否继续修改?(Y/N)");
		scanf("\t\t%c", &flag);
	}
	return 0;
}

int display()//输出通讯录列表
{
	ptcs p = head->next;
	if (!p)
	{
		printf("\t\t该通讯录为空!\n");
		return 0;
	}
	printf("\n\t\t******************************通讯录列表******************************\n");
	printf("\t\t姓名\t\t手机号码\tQQ号码\t\t电子邮箱\n");
	printf("\t\t**********************************************************************\n");
	while (p)
	{
		printf("\t\t%-16s%-16s%-16s%-20s\n", p->chat.name, p->chat.tel, p->chat.tecent, p->chat.email);
		p = p->next;
		printf("\t\t**********************************************************************\n");
	}
	return 0;
}

int cacu(ptcs p)//计算链表的长度
{
	int n = 0;
	while (p)
	{
		p = p->next;
		n++;
	}
	return n;
}

int arrange()//对通讯录进行排序,这里本人用冒泡法排序,稍微有些繁琐
{
	int i, n;
	ptcs pre = head, p = head->next, k, q;
	if (!p)
	{
		printf("\t\t该通讯录为空!\n");
		return 0;
	}
	n = cacu(p);
	for (i = 0; i < n - 1; i++)
	{
		for (p = head->next, pre = head; p->next->next != NULL; pre = p, p = p->next);
		{
			k = p->next;
			q = k->next;
			if (strcmp(p->chat.name, k->chat.name) > 0)
			{
				pre->next = k;
				k->next = p;
				p->next = q;
				p = k;
			}
		}
	}
	display();
	return 0;
}

int write()//将数据写入文件
{
	ptcs p = head->next;
	FILE* fp;
	char filename[30];
	if (!p)
	{
		printf("\t\t该通讯录为空!");
		return 0;
	}
	printf("\t\t写入到文件!\n");
	printf("\t\t请输入所写入的文件名:");
	scanf("\t\t%s", filename);
	if ((fp = fopen(filename, "a+")) == NULL)
	{
		printf("\t\t无法打开文件!\n");
		system("pause");
		return 0;
	}
	fprintf(fp, "******************************通讯录列表******************************\n");
	fprintf(fp, "姓名\t\t手机号码\tQQ号码\t\t电子邮箱\n");
	fprintf(fp, "**********************************************************************\n");
	while (p)
	{
		fprintf(fp, "%-16s%-16s%-16s%-20s\n", p->chat.name, p->chat.tel, p->chat.tecent, p->chat.email);
		p = p->next;
		fprintf(fp, "**********************************************************************\n");
	}
	fprintf(fp, "\n******************************共%d个联系人******************************\n", cacu(head->next));
	fclose(fp);                                         //关闭文件   
	printf("\t\t写入成功!\n");
	return 0;
}

int read()//读取文件
{
	char str[100]; char filename[30];
	FILE* fp;
	printf("\t\t读取文件!\n");
	printf("\t\t请输入所写入的文件名:");
	scanf("\t\t%s", filename);
	if ((fp = fopen(filename, "a+")) == NULL)
	{
		printf("\t\t无法打开文件!\n");
		system("pause");
		return 0;
	}
	while ((fgets(str, 100, fp)) != NULL)
	{
		printf("\t\t%s", str);
	}
	return 0;
}

int call()//呼叫或被呼叫
{
	int n;
	ptcs p = head->next;
	srand((unsigned)time(NULL)); //用时间做种，每次产生随机数不一样
	n = rand() % (cacu(p) + 5) + 1;
	return n;
}

int save(int n, char* filename)//保存通话记
{
	FILE* fp;
	ptcs p = head->next;
	int i = 1;
	if ((fp = fopen(filename, "a+")) == NULL)
	{
		printf("\t\t通话记录将失去!\n");
		system("pause");
		return 0;
	}
	if (n <= cacu(p))
	{
		while (i < n)
		{
			p = p->next;
			i++;
		}
		fprintf(fp, "%-16s%-16s%-16s%-20s\n", p->chat.name, p->chat.tel, p->chat.tecent, p->chat.email);
		fprintf(fp, "**********************************************************************\n");
	}
	else fprintf(fp, "未知号码\n");
	fclose(fp); //关闭文件   
	return 0;
}

int chat_record()//通话记录
{
	int m, n, i;
	char flag = 'y';
	char cal[30] = "call.txt", caled[30] = "called.txt";
	while (flag != 'n' && flag != 'N')
	{
		printf("\t\t模拟通话开始!\n");
		printf("\t\t请选择通话类型(1.呼叫(call) OR 2.被呼叫(called)):");
		scanf("\t\t%d", &m);
		do
		{
			i = 0;
			if (m != 1 && m != 2)
			{
				i = 1;
				printf("\t\t您输入序号不在标准中,请重新输入:");
				scanf("\t\t%d", &m);//选择修改内容
			}
		} while (i);
		n = call();
		if (1 == m)
			save(n, cal);
		else if (2 == m)
			save(n, caled);
		printf("\t\t是否继续模拟?(Y/N)");
		scanf("\t\t%c", &flag);
	}
	return 0;
}

int main()
{
	/*head->next=NULL;
	system("cls");
	printf("\n\t\t**********通讯录管理系统**********\n");
	printf("\t\t┌-------------------------------┐\n");
	printf("\t\t│        1.添加联系人           │\n");
	printf("\t\t│        2.查询联系人           │\n");
	printf("\t\t│        3.删除联系人           │\n");
	printf("\t\t│        4.修改联系人信息       │\n");
	printf("\t\t│        5.输出联系人列表       │\n");
	printf("\t\t│        6.排序                 │\n");
	printf("\t\t│        7.写入文件             │\n");
	printf("\t\t│        8.读取文件             │\n");
	printf("\t\t│        9.通话记录             │\n");
	printf("\t\t│        0.退出                 │\n");
	printf("\t\t└-------------------------------┘\n");
	printf("\t\t请您选择(0-9):");
	printf("\n\t\t******************************通讯录列表******************************\n");
	printf("\t\t姓名\t\t手机号码\tQQ号码\t\t电子邮箱\n");*/
	head->next = NULL;
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			printf("\n\t\t添加记录到通讯录\n"); //添加记 录
			Addpeo();
			system("pause");
			break;
		case 2:
			printf("\n\t\t在通讯录中查找联系人\n");
			watch_over();
			system("pause");
			break;
		case 3:
			printf("\n\t\t从通讯录中删除联系人\n");
			Delete();
			system("pause");
			break;
		case 4:
			printf("\n\t\t修改通讯录中的信息\n");
			change();
			system("pause");
			break;
		case 5:
			printf("\n\t\t输出通讯录列表\n");
			display();
			system("pause");
			break;
		case 6:
			printf("\n\t\t排序\n");
			arrange();
			system("pause");
			break;
		case 7:
			printf("\n\t\t写入文件\n");
			write();
			system("pause");
			break;
		case 8:
			printf("\n\t\t读取文件\n");
			read();
			system("pause");
			break;
		case 9:
			printf("\n\t\t模拟通话\n");
			chat_record();
			system("pause");
			break;
		case 0:
			printf("\n\t\t谢谢使用，再见!\n");  //结束程序    
			printf("\n\t\t");
			system("pause");
			exit(0);
		}
	}
	return 0;
}