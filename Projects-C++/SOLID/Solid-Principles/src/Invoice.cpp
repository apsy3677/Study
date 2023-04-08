//#include<bits/stdc++.h>
#include "Book.h"
#include <memory>
#include <iostream>
#pragma once

using namespace std;

class Invoice
{
public:
	//Book* book;
	// use unique pointer

	unique_ptr<Book> book;

	int quantity;
	double discountRate;
	double taxRate;
	double total;

public:
	Invoice(Book* book, int quantity, double discountRate, double taxRate) {
		this->quantity = quantity;
		this->book = make_unique<Book>(book);
		this->discountRate = discountRate;
		this->taxRate = taxRate;
		this->total = this->calculateTotal();
	}
	double calculateTotal() {
		double price = (book->price - book->price*discountRate)*this->quantity;
		double pricewithTax = price * (1 + taxRate);
		return pricewithTax;
	}
	
	void save() {
		cout << " Save the Invoice to File ";
	}
	/*Invoice()
	{

	}*/

};

