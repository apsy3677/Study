#include "Invoice.cpp"

class InvoicePrinter {
private:
	unique_ptr<Invoice> invoice;

public:
	InvoicePrinter(Invoice *invoice) {
		this->invoice = make_unique<Invoice>(invoice);
	}
	void print() {
		cout << "Invoice::" << endl;
		cout << this->invoice->quantity << "x" << this->invoice->book->name + " " << this->invoice->book->price << "$" << endl;
	}
};