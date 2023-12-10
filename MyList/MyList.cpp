#include <iostream>
#include <string>

#include "MyList.h"


class c
{
	int a;
	char b;
	friend std::ostream& operator << (std::ostream&, const c&);

public:
	c() {}
	c(int _a, char _b) : a(_a), b(_b) {}
	bool operator > (const c& another) const
	{
		return std::tie(a, b) > std::tie(another.a, another.b);
	}
};

std::ostream& operator << (std::ostream& stream, const c& instance)
{
	stream << "{ " << instance.a << ", " << instance.b << " }";
	return stream;
}

void test_str()
{
	MyList <std::string> l;
	for (int i = 0; i < 20; i++)
	{
		std::string s = "";
		for (int j = 0; j < 10; j++)
		{
			s += ((char)(97 + (rand() % 26)));
		}
		l.push_back(s);
	}

	MyList <std::string> ::MyIterator iter1, iter2;
	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << *iter1 << " ";
	std::cout << std::endl << std::endl;

	l.sort();

	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << *iter1 << " ";
	std::cout << std::endl << std::endl;

	iter1 = ++l.begin(), iter2 = --l.end();
	l.erase(iter1, iter2);
	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << *iter1 << " ";
	std::cout << std::endl << std::endl;

	iter1 = --l.end();
	l.insert(iter1, 5, "drftgy");
	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << *iter1 << " ";
	std::cout << std::endl << std::endl;
}

void test_class()
{
	MyList <c> l;
	for (int i = 0; i < 20; i++)
	{
		c example(rand() % 100, (char)('a' + (rand() % 26)));
		l.push_back(example);
	}

	MyList <c> ::MyIterator iter1, iter2;
	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << (*iter1) << " ";
	std::cout << std::endl << std::endl;

	l.sort();

	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << (*iter1) << " ";
	std::cout << std::endl << std::endl;

	iter1 = ++l.begin(), iter2 = --l.end();
	l.erase(iter1, iter2);
	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << (*iter1) << " ";
	std::cout << std::endl << std::endl;

	iter1 = --l.end();
	l.insert(iter1, 5, c(58465, 'p'));
	for (iter1 = l.begin(); iter1 != l.end(); ++iter1)
		std::cout << (*iter1) << " ";
	std::cout << std::endl << std::endl;
}

int main()
{
	MyList<int> x;
	x.push_back(54);
	MyList <MyList <int>> a;
	a.push_back(x);

	test_str();
	test_class();
}