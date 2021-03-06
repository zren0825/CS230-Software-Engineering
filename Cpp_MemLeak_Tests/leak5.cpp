#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sys/timeb.h>
#include <chrono>
using namespace std;

void createLeak()
{
	char **memptrarr; 
	memptrarr = new char *[2];
	memptrarr[0] = new char [100];
	memptrarr[1] = new char [24];

	//delete [] memptrarr; 
	//delete [] *memptrptr;
}
 
int main(){
	cout << "Leak 5 test: Testing pointer to pointer memory allocation" << endl;
	cout << "Char pointers require 4 bytes for BBB architecture therefore 8 bytes are definitely lost" << endl;
	cout << "Expected output:" << endl;
        cout << "definitely lost: 8 bytes in 1 blocks" << endl;
        cout << "indirectly lost: 124 bytes in 2 blocks" << endl;
        cout << "  possibly lost: 0 bytes in 0 blocks" << endl;
        cout << "still reachable: 0 bytes in 0 blocks"<< endl;
        cout << "     suppressed: 0 bytes in 0 blocks" << endl;
	auto start = chrono::high_resolution_clock::now();
	createLeak();
	auto finish = chrono::high_resolution_clock::now();
	cout << "Runtime: " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns" << endl;
	return 0;
}

