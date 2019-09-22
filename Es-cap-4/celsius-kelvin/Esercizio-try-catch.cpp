// Esercizio-try-catch.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//  
// Esercizio per convertire gradi da celsius a kelvin e viceversa
// Alessandro Screm release 1.0 01-09-2019


#include "pch.h"
#include <iostream>
#include "std_lib_facilities.h"

//converte gradi celsius in kelvin
//precondizioni: -273,15 < c > 1000
//postcondizioni:ritorna un valore positivo in gradi kelvin
double ctok(double c)
{
	constexpr double delta_ck = 273.15;
	constexpr double min = -delta_ck;
	constexpr double max = 1000;

	if (c < min || c > max) error("ctok() precondition");

	double k = c + delta_ck;
	return k;
}

//converte gradi kelvin in celsius 
//precondizioni: 0 < k > 1000
//postcondizioni:ritorna il valore  in gradi celsius
double ktoc(double k)
{
	constexpr double delta_ck = 273.15;
	constexpr double min = 0;
	constexpr double max = 1000;

	if (k < min || k > max) error("ktoc() precondition");

	double c = k - delta_ck;
	return c;
}



int main()
{
	try {
		double c = 0;
		char g = ' ';
		double res = 0;

		cout << "Converte gradi da celsius in kelvin e viceversa\n";
		cout << "iserisci valore seguito da c oppure k\n";

		cin >> c >> g;
		if (!cin) error("main() valore input invalido");
		
		switch (g) {
		case 'c':
			res = ctok(c);
			cout << res << " kelvin \n";
			return 0;
		case 'k':
			res = ktoc(c);
			cout << res << " celsius \n";
			return 0;
		}
		error("main() simbolo non valido");
	}


	catch(exception& e){
		cerr << "error: " << e.what() << "\n";
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		return 2;
	}
}
