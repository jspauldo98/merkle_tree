#include <stdio.h>
#include "pMT.cpp"
#include "bTREE.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>	// to covert string to int
using namespace std;
int main(int argc, char **argv)
{
	pMT tester(1);
    string data, time;
    ifstream myfile ("my_test.txt");
    if (myfile.is_open())
    {
      while ( myfile >> data >> time)
      {
      	istringstream buffer(time);
      	int time_val = 0;
      	buffer >> time_val;
        cout << tester.insert(data, time_val) << endl;
      }
      myfile.close();
    }
    else cout << "Unable to open file";

    cout << "***************************************************************************" << endl;
    cout << "*****************pMT 1*****************************************************"<< endl;
    cout << "***************************************************************************" << endl;
    cout << tester << endl;

    pMT tester2(1);
    string data1, time1;
    ifstream myfile2 ("my_test.txt");
    if (myfile2.is_open())
    {
      while ( myfile2 >> data1 >> time1)
      {
      	istringstream buffer(time1);
      	int time_val = 0;
      	buffer >> time_val;
        cout << tester2.insert(data1, time_val) << endl;
      }
      myfile2.close();
    }
    else cout << "Unable to open file";
    // tester2.insert("jhsbfkjhskj", 7009);


    cout << "***************************************************************************" << endl;
    cout << "*****************pMT 2*****************************************************"<< endl;
    cout << "***************************************************************************" << endl;
    cout << tester2 << endl;

    cout << "***************************************************************************" << endl;
    cout << "*****************differnece*****************************************************"<< endl;
    cout << "***************************************************************************" << endl;

     cout << (tester ^ tester2) << endl;

	return 0;
}
