#include <iostream>
#include "helper.h"
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;

int main()
{

	mpz_t n, r, mod, one, powr, gcd;
	mpz_init_set_ui(n, INT_MAX);
    bool is;
    clock_t t1 = clock(), t2;
    is = aksLnPserial(n);
    t2 = clock() - t1;
    if(is)
        cout << endl << "Serial time is " << (float)(t2)/CLOCKS_PER_SEC;
    else
        cout << endl << "No serial time is " << (float)(t2) / CLOCKS_PER_SEC;

    t1 = clock();
    is = aksLnPparallel(n);
    t2 = clock() - t1;
    if (is)
        cout << endl << "Serial time is " << (float)(t2) / CLOCKS_PER_SEC;
    else
        cout << endl << "No serial time is " << (float)(t2) / CLOCKS_PER_SEC;
	
	return 0;
}
