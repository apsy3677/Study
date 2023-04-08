#pragma once
#include <string>
//#include<string>
using namespace std;

class Book
{
public:
	std::string name;
	std::string authorName;
	int year;
	int price;
	string isbn;

public:
	Book(string name, string authorName, int year, int price, string isbn);
};

