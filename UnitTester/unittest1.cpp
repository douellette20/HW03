#include "stdafx.h"
#include "CppUnitTest.h"
#include "readint.h"
#include <fstream>
#include <iostream>
//using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTester
{		
	TEST_CLASS(ReadIntTest)
	{
	public:
		
		TEST_METHOD(TestCase1)
		{
			// Open a file stream to read the file zeroinput.txt
			std::ifstream ss("..\\UnitTester\\zeroinput.txt");

			//Check if file stream successfully opened
			if (ss.fail())
				throw int(-1);

			// replace cin read buffer with read buffer from the file stream
			std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
			
			// Perform the read_int() test
			// cin will read from file and not keyboard
			// expected value returned is 0
			Assert::AreEqual(read_int("My prompt: ", -3, 3), 0);

			// Restore cin to original state
			std::cin.rdbuf(orig_cin);

			// Close file stream
			ss.close();
		}

		TEST_METHOD(TestCase2)
		{
			auto func = []()
			{
				read_int("My prompt: ", 5, 1);
			};

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(TestCase3)
		{
			std::ifstream ss("..\\UnitTester\\valuesoutsiderange.txt");

			if (ss.fail())
				throw int(-1);

			std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());


			Assert::AreEqual(read_int("My prompt: ", 0, 4), 3);

			std::cin.rdbuf(orig_cin);

			ss.close();
		}

		TEST_METHOD(TestCase4)
		{
			auto func = []()
			{
				read_int("My prompt: ", 0, 0);
			};

			Assert::ExpectException<std::invalid_argument>(func);
		}

	};
}