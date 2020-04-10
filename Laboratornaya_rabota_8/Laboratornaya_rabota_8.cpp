#include <iostream>
#include <Windows.h>
#include <string>
#include "App.h"
#using <System.dll>
#using <system.dll> 
using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace std;

class ListApplications 
{
	App *head;
	int size;
public:
	ListApplications () {
		head = NULL;
		size = 0;
	}
	void AddApplication(App ap) 
	{
		App *apl = new App();
		strcpy_s(apl->name, ap.name);
		strcpy_s(apl->prouzvod, ap.prouzvod);
		apl->razmer = ap.razmer;
		apl->zena = ap.zena;
		if (!head)
		{
			head = apl;
			size++;
			return;
		}
		else
		{
			App* cur = head;
			App* previ = NULL;
			while (cur)
			{
				if ((strcmp(cur->name, apl->name) == 0) && (strcmp(cur->prouzvod, apl->prouzvod)) && (cur->razmer == apl->razmer) && (cur->zena == apl->zena))
				{
					String^ str = gcnew String("Такой элемент уже есть в списке");
					throw str;
				}
				else if (((strcmp(cur->name, apl->name) > 0) && (!cur->prev)) || ((strcmp(cur->name, apl->name) == 0) && (strcmp(cur->prouzvod, apl->prouzvod) >= 0) && (!cur->prev)))
				{
					apl->next = cur;
					cur->prev = apl;
					head = apl;
					size++;
					return;
				}
				else if (((strcmp(cur->name, apl->name) < 0) && (!cur->next)) || ((strcmp(cur->name, apl->name) == 0) && (strcmp(cur->prouzvod, apl->prouzvod) <= 0) && (!cur->next)))
				{
					apl->prev = cur;
					cur->next = apl;
					size++;
					return;
				}
				else
				{
					if ((strcmp(cur->name, apl->name) < 0) || ((strcmp(cur->name, apl->name) == 0) && (strcmp(cur->prouzvod, apl->prouzvod) < 0)))
					{
						previ = cur;
						cur = cur->next;
						continue;
					}
					if ((strcmp(cur->name, apl->name) > 0) || ((strcmp(cur->name, apl->name) == 0) && (strcmp(cur->prouzvod, apl->prouzvod) >= 0)))
					{
						previ->next = apl;
						apl->next = cur;
						cur->prev = apl;
						apl->prev = previ;
						size++;
						return;
					}
				}
			}
		}
	}
	void RemoveIndexApp(int index)
	{
		if ((index > size)&&(index <= 0))
		{
			String^ str = gcnew String("Элемент с таким индексом не существует");
			throw str;
		}
		if ((index == 1) && (!head->next))
		{
			head = NULL;
			delete head;
			size = 0;
			return;
		}
		if ((index == 1) && (head->next))
		{
			App *tmp = head;
			head = head->next;
			head->prev = NULL;
			delete tmp;
			size--;
			return;
		}
		if (index == size)
		{
			App *cur = head, *tmp;
			while (cur->next)
			{
				cur = cur->next;
			}
			tmp = cur;
			cur = cur->prev;
			cur->next = NULL;
			tmp = NULL;
			delete tmp;
			size--;
			return;
		}
		App *cur = head, *tmp;
		for (int i = 1; i < index - 1; i++)
		{
			cur = cur->next;
		}
		tmp = cur->next;
		cur->next = tmp->next;
		cur = tmp->next;
		cur->prev = tmp->prev;
		tmp = NULL;
		delete tmp;
		size--;
	}
	App GetIndexApp(int index)
	{
		if (index > size)
		{
			String^ str = gcnew String("Элемент с таким индексом не существует");
			throw str;
		}
		App *cur = head;
		for (int i = 0; i < index; i++)
		{
			if (i == index - 1)
				break;
			cur = cur->next;
		}
		App help;
		strcpy_s(help.name, cur->name);
		strcpy_s(help.prouzvod, cur->prouzvod);
		help.razmer = cur->razmer;
		help.zena = cur->zena;
		return help;
	}
	int* CheckAvailApp(char *s, int &isize)
	{
		if (!size)
		{
			String^ str = gcnew String("Список пуст!");
			throw str;
		}
		App *cur = head;
		int i = 0;
		while (cur)
		{
			if (strcmp(cur->name, s) == 0)
			{
				isize++;
			}
			cur = cur->next;
			i++;
		}
		if (!isize) 
		{ 
			int *e = new int[1];
			isize++;
			e[0] = -1;
			return e;
		}
		cur = head;
		int in = 0;
		i = 0;
		int *imass = new int[isize];
		while (cur)
		{
			in++;
			if (strcmp(cur->name, s) == 0)
			{
				imass[i] = in;
				i++;
			}
			cur = cur->next;
		}
		return imass;
	}
	char** UniqueNames(int &usize)
	{
		if (!size)
		{
			String^ str = gcnew String("Список пуст!");
			throw str;
		}
		char **allnames = new char*[size];
		for (int i = 0; i < size; i++)
			allnames[i] = new char[100];
		App *cur = head;
		int k = 0;
		while (cur)
		{
			strcpy_s(allnames[k], 100, cur->prouzvod);
			cur = cur->next;
			k++;
		}
		bool f = true;
		for (int i = 0; i < size; i++)
		{
			f = true;
			for (int j = 0; j < size; j++)
			{
				if (i == j)
					continue;
				if (strcmp(allnames[i], allnames[j]) == 0)
					f = false;
			}
			if (f)
				usize++;
		}
		char **uniqnames = new char*[usize];
		for (int i = 0; i < usize; i++)
			uniqnames[i] = new char[100];
		cur = head;
		k = 0;
		for (int i = 0; i < size; i++)
		{
			f = true;
			for (int j = 0; j < size; j++)
			{
				if (i == j)
					continue;
				if (strcmp(allnames[i], allnames[j]) == 0)
					f = false;
			}
			if (f)
			{
				strcpy_s(uniqnames[k], 100, allnames[i]);
				k++;
			}
		}
		return uniqnames;
	}
	char** NamesWithoutRepeat(int &usize)
	{
		if (!size)
		{
			String^ str = gcnew String("Список пуст!");
			throw str;
		}
		char **allnames = new char*[size];
		for (int i = 0; i < size; i++)
			allnames[i] = new char[100];
		App *cur = head;
		int k = 0;
		while (cur)
		{
			strcpy_s(allnames[k], 100, cur->prouzvod);
			cur = cur->next;
			k++;
		}
		bool f = true;
		for (int i = 1; i < size; i++)
		{
			f = true;
			for (int j = i - 1; j >= 0; j--)
			{
				if (strcmp(allnames[i], allnames[j]) == 0)
				{
					f = true;
					break;
				}
				else
					f = false;
			}
			if (!f)
				usize++;
		}
		char **uniqnames = new char*[usize + 1];
		for (int i = 0; i <= usize; i++)
			uniqnames[i] = new char[100];
		strcpy_s(uniqnames[0], 100, allnames[0]);
		k = 1;
		for (int i = 1; i < size; i++)
		{
			f = true;
			for (int j = i - 1; j >= 0; j--)
			{
				if (strcmp(allnames[i], allnames[j]) == 0)
				{
					f = true;
					break;
				}
				else
					f = false;
			}
			if (!f)
			{
				strcpy_s(uniqnames[k], 100, allnames[i]);
				k++;
			}
		}
		return uniqnames;
	}
	void PrintListApplications()
	{
		if (!size)
		{
			String^ str = gcnew String("Список пуст!");
			throw str;
		}
		App *cur = head;
		while (cur)
		{
			cout << cur->name << ", " << cur->prouzvod << ", " << cur->razmer << ", " << cur->zena << endl;
			cur = cur->next;
		}
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ListApplications lA = ListApplications();
	int n;
	cout << "Введите количество программ: ";
	try
	{
		cin >> n;
		cin.ignore();
		if (n <= 0) throw 3;
	}
	catch (int i)
	{
		EventLog^ myLog = gcnew EventLog();
		myLog->Source = "MySource";
		myLog->WriteEntry("Некорректное число программ");
		cout << "Некорректное число программ" << endl;
		return 1;
	}
	App *Applications = new App[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Введите наименование программы " << i + 1 << ": ";
		cin.getline(Applications[i].name, 99);
		cout << "Введите наименование производителя программы " << i + 1 << ": ";
		cin.getline(Applications[i].prouzvod, 99);
		char buf[100] = "";
		cout << "Введите размер на диске для программы (в Гб) " << i + 1 << ": ";
		cin >> Applications[i].razmer;
		cin.ignore();
		try
		{
			if (Applications[i].razmer <= 0) throw 1;
		}
		catch (int a)
		{
			EventLog^ myLog = gcnew EventLog();
			myLog->Source = "MySource";
			myLog->WriteEntry("\"Размер на диске\" не может иметь такое значение");
			cout << "\"Размер на диске\" не может иметь такое значение" << endl;
			return 1;
		}
		cout << "Введите цену прогаммы (в рублях) " << i + 1 << ": ";
		cin >> Applications[i].zena;
		cin.ignore();
		try
		{
			if (Applications[i].zena < 0) throw 1;
		}
		catch (int a)
		{
			EventLog^ myLog = gcnew EventLog();
			myLog->Source = "MySource";
			myLog->WriteEntry("\"Цена программы\" не может иметь такое значение");
			cout << "\"Цена программы\" не может иметь такое значение" << endl;
			return 1;
		}
	}
	try
	{
		for (int i = 0; i < n; i++)
		{
			lA.AddApplication(Applications[i]);
		}

		lA.PrintListApplications();

		App help = lA.GetIndexApp(2);
		cout << "Наименование программы: " << help.name << "\nПроизводитель: " << help.prouzvod << "\nРазмер на диске(ГБ): " << help.razmer << "\nЦена(руб): " << help.zena << "\n";
		
		char str[100];
		int us = 0;
		cout << "Введине название программы для поиска: ";
		cin.getline(str, 99);
		int *indexmass = lA.CheckAvailApp(str, us);
		for (int i = 0; i < us; i++)
		{
			cout << indexmass[i] << " ";
		}
		cout << endl;

		us = 0;
		char** unique = lA.UniqueNames(us);
		for (int i = 0; i < us; i++)
		{
			cout << unique[i] << endl;
		}
		cout << endl;

		us = 0;
		char** unames = lA.NamesWithoutRepeat(us);
		for (int i = 0; i < us + 1; i++)
		{
			cout << unames[i] << endl;
		}
		cout << endl;

		lA.RemoveIndexApp(n);
		lA.RemoveIndexApp(n - 2);
		lA.RemoveIndexApp(1);

		lA.PrintListApplications();
	}
	catch (String^ s)
	{
		EventLog^ myLog = gcnew EventLog();
		myLog->Source = "MySource";
		myLog->WriteEntry(s);
		return 1;
	}
	return 0;
}