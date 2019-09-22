// Esercizio-try-catch.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//  
// Esercizio per convertire gradi da celsius a fahrenheit e viceversa
// Alessandro Screm release 1.0 01-09-2019


#include "pch.h"
#include <iostream>
#include "std_lib_facilities.h"


//converte gradi celsius in fahrenheit 
//precondizioni: -1000 < c > 1000
//postcondizioni:ritorna il valore  in gradi fahrenheit
double ctof(double c)
{
	constexpr double min = -1000;
	constexpr double max = 1000;

	if (c < min || c > max) error("ctof() precondition");
	double f = (((double)9 / 5) * c) + 32;
	return f;
}
//converte gradi celsius in fahrenheit 
//precondizioni: -1000 < c > 1000
//postcondizioni:ritorna il valore  in gradi fahrenheit
double ftoc(double f)
{
	constexpr double min = -1000;
	constexpr double max = 1000;

	if (f < min || f > max) error("ctof() precondition");
	double c = ((f - 32) / ((double)9 / 5)); 
	return c;
}



int main()
{
	try {
		double temp = 0;
		char scala = ' ';
		double res = 0;

		cout << "Converte gradi da celsius in fahrenheit e viceversa\n";
		cout << "iserisci valore seguito da c oppure f\n";

		cin >> temp >> scala;
		if (!cin) error("main() valore input invalido");
		
		switch (scala) {
		case 'c':
			res = ctof(temp);
			cout << res << " fahrenheit \n";
			return 0;
		case 'f':
			res = ftoc(temp);
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
