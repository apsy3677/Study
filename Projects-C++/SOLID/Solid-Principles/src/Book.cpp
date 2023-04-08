#include "Book.h"

Book :: Book(string name, string authorName, int year, int price, string isbn) {
	this->name = name;
	this->authorName = authorName;
	this->year = year;
	this->price = price;
	this->isbn = isbn;
}