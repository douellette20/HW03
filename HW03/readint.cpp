#include "readint.h"
#include <stdexcept>
#include <iostream>
using namespace std;

int read_int(const string &prompt, int low, int high)
{
	std::cin.exceptions(ios_base::failbit);
	// Throws an exception if the range is invalid
	if (low > high)
		throw invalid_argument("Invalid range");
	int num = 0;
	// Keeps looping through until no errors are thrown and therefore a value is returned
	while (true)
	{
		try
		{
			std::cout << prompt;
			cin >> num;
			if (num < low || num > high)
				throw range_error("The value entered is out of range");
			return num;
		}
		catch(ios_base::failure& ex)
		{
			cout << "Bad numeric string -- try again\n";
			// Reset the error flag
			cin.clear();
			// Skip the input line
			cin.ignore(numeric_limits<int>::max(), '\n');
		}
		catch(range_error& ex)
		{
			cerr << "Range error exception occurred\n";
			cerr << ex.what() << endl;
		}
	}
}