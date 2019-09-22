// equazioni-quadratiche.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
// calcola equazioni a*xexp2+b*x+c=0
// Alessandro Screm 01-09-2019 versione 1.0
// esercizio per utilizzo try catch

#include "pch.h"
#include <iostream>
#include "std_lib_facilities.h"

struct res
{
	double x1;
	double x2;

};
// Calcola il valore di x dell equazione:a*xexp2+b*x+c=0
// formula x = (-b +-sqrt(bexp2-4ac)/2a
// precondizioni: a > 0 , (bexp2 -4ac) > 0
// poscondizioni: ritorna il valore di x
res eq2grado(double a, double b, double c)
{
	res X;
	double root = ((b*b) - (4 * a*c));
	if (a <= 0 || root <= 0) error("eq2grado() l' equazione non ha radice reale!\n");

	X.x1 = (((-b) + (sqrt(root))) / (2 * a));
	X.x2 = (((-b) - (sqrt(root))) / (2 * a));
	return X;
}

int main()
{
	double a = 0;
	double b = 0;
	double c = 0;
	res X;

	cout << "Calcola il calore dell espressione quadratica a*xexp2+b*x+c=0\n";
	cout << "Inserici le variabili: \n";
	
	try
	{
		cout << "a = ";
		cin >> a;
		if (!cin) error("main() Valore input invalido");

		cout << "b = ";
		cin >> b;
		if (!cin) error("main() Valore input invalido");

		cout << "c = ";
		cin >> c;
		if (!cin) error("main() Valore input invalido");

		X = eq2grado(a, b, c);
		cout << "risultati: \n";
		cout << "x = " << X.x1 << "\n";
		cout << "x = " << X.x2 << "\n";

		return 0;

	}
	catch (const std::exception& e)
	{
		cerr << "Error: " << e.what() << "\n";

	}
	catch (...)
	{
		cerr << "Oops: unknown exception!\n";
	}

}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
