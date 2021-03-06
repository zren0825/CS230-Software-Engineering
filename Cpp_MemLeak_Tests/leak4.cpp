#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sys/timeb.h>
#include <cstring>
#include <chrono>
using namespace std;

class MemLeak
{
public:
        MemLeak();

        ~MemLeak();

        void createMemLeak(char *p_memptr);

private:
        char    *memptr;
};

MemLeak::MemLeak()
{
        memptr = NULL;
}

MemLeak::~MemLeak()
{
        if (memptr != NULL)
                delete [] memptr;
}

void MemLeak::createMemLeak(char        *p_memptr)
{
        if (memptr != NULL)
        {
                delete [] memptr;
                memptr = NULL;
        }

        size_t  len;

        len = strlen(p_memptr);
        memptr = new char [len + 1];
        if (memptr != NULL)
        {
                strcpy(memptr, p_memptr);
        }
        memptr++;
}


 
int main(){
        cout << "Leak 4 test: Interior pointer test. A pointer is assigned to a memory block and then incremented by one" << endl;
	cout << "NB: The program should fail when run independantly ie without valgrind" << endl;
        cout << "Expected output:" << endl;
        cout << "definitely lost: 8 bytes in 1 blocks" << endl;
        cout << "indirectly lost: 0 bytes in 0 blocks" << endl;
        cout << "  possibly lost: 0 bytes in 0 blocks" << endl;
        cout << "still reachable: 0 bytes in 0 blocks"<< endl;
        cout << "     suppressed: 0 bytes in 0 blocks" << endl;
        auto start = chrono::high_resolution_clock::now();
	MemLeak m;
        m.createMemLeak("Foo Bar");
	auto finish = chrono::high_resolution_clock::now();
	cout << "Runtime: " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns" << endl;
	return 0;
}

