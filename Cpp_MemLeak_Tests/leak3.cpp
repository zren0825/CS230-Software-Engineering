#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sys/timeb.h>
#include <cstring>
#include <chrono>
using namespace std;

class memObj
{
public:
        memObj();
        ~memObj();

private:
        char    *data;
};

memObj::memObj()
{
        data = new char[100];
}

memObj::~memObj()
{
        delete [] data;
}
 
int main(){
        cout << "Leak 3 test: delete array is used instead of delete [] array." << endl; 
	cout << "NB: The BBB requires 8 bytes overhead for pointer arrays  therefore definitely lost = No. pointers in array * 4bytes + 8bytes (In this case 48 bytes) " << endl;
        cout << "Expected output:" << endl;
        cout << "definitely lost: 48 bytes in 1 blocks" << endl;
        cout << "indirectly lost: 900 bytes in 9 blocks" << endl;
        cout << "  possibly lost: 0 bytes in 0 blocks" << endl;
        cout << "still reachable: 0 bytes in 0 blocks"<< endl;
        cout << "     suppressed: 0 bytes in 0 blocks" << endl;

	auto start = chrono::high_resolution_clock::now();
        memObj  *array;
        array = new memObj[10];
        delete array;
        //delete [] array;

	auto finish = chrono::high_resolution_clock::now();
	cout << "Runtime: " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns" << endl;
	return 0;
}

