/******************************************************************************

13. Write a Tracer class where its constructor prints a string and its destructor prints a string. 
	Give the strings as constructor arguments.
	Use it to see where RAII management objects will do their job 
	(i.e., experiment with Tracers as local objects, member objects, global objects, objects allocated by new, etc.). 
	Then add a copy constructor and a copy assignment so that you can use Tracer objects to see when copying is done.

******************************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>


// error() simply disguises throws:
inline void error(const std::string& s)
{
	throw std::runtime_error(s);
}

class Tracer {
	
public:
	std::string name;

	Tracer() : name{ "0" } { out("constructor", "0"); }		  // default constructor
	Tracer(const std::string& n) : name{ n } { out("constructor", n); }		      // 1 param constructor
	Tracer(const Tracer& t) : name{ t.name } { out("copy constructor", t.name); } // copy constructor
	Tracer& operator=(const Tracer& t) {						// copy assignement
		out("copy assignement", t.name);
		name = t.name;
		return *this;
	}
	~Tracer() { out("destructor", "0"); }	//destructor
	void out(const std::string& s, const std::string& nv) 
	{ 
		std::cerr << this << "->" << s << " " << name << " (" << nv << ")" << "\n"; 
	}
};
     
 Tracer global{ "global" };


void f() {
	Tracer mf{ "m_f" };
}

int main()
{
	try
	{
		
		f();
		Tracer tc{ "main" };		
		Tracer tc1{ tc };
		tc = Tracer{ "main2" };
		tc1 = tc;

		Tracer* tp = new Tracer{ "new" };
		delete tp;
	
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;           //write error message
	}


   char c;
   std::cin >> c;

}



