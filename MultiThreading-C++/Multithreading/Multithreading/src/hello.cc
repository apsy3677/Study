// First program with std::thread
#pragma once

#include <iostream>
#include <thread>

#include "hello_functor.cc"
// #include "hello_lamda.cc"

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, hello Thread!\n";
}

int main() {
	// Create an std::thread object
	// Pass the entry point function to the constructor

	std::cout << "Hello, Main Thread!\n";
	std::thread thr1(hello);
	// Create an object of the functor class
	Hello hello;

	// Pass the functor object to std::thread's constructor
	std::thread thr2( hello );

	// Use a lambda expression as the thread's entry point
 	std::thread thr([]() {
 		std::cout << "Hello, Lambda Thread!\n";
 	});

 	thr2.join();
	// Wait for the thread to complete
	thr1.join();

 	// Wait for the thread to complete
 	thr.join();
}