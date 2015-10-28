#include <iostream>
#include "helper.h"
#include <cmath>
#include <cstring>
using namespace std;

int main()
{

	mpz_t n, r, mod, one, powr, gcd;
	char ip[100];
	cin >> ip;
	mpz_init_set_str(n, ip, 10);
	std::cout << "here " << mpz_sizeinbase(n, 2);
	
	int lgN2 = pow(mpz_sizeinbase(n, 2), 5);	// logN2 = ceil(log2^2(n))
	/*
	char clgN2[10];
	sprintf_s(clgN2, "%d", lgN2);

	cout << "here" << clgN2;
	mpz_set_str(mod, clgN2, 10); // logN2  =log2^2(n)
	 */ 



	mpz_init_set_str(mod, "49", 10);
	mpz_init_set_str(one, "1", 10);
	//int logN2 = ceil(pow(mpz_sizeinbase(n, 2) - 1, 2));
	//cout << "here";
	getMinR(r, n);
	//cout << "here";
	//cout << endl << logN2;
	
	/*
	mpz_init_set_str(k, "1", 10);
	
	mpz_init_set_str(one, "1", 10);
	mpz_t powr;
	mpz_init_set(powr, n);
	
	while (true)
	{
		mpz_powm(powr, n, k, mod);
		if (mpz_cmp(powr, one) == 0)
		{
			gmp_printf("\n Ok fine : %Zd", k);
			break;
		}
		else
			mpz_add(k, k, one);
		//gmp_printf("\n Ok: %Zd and powr %Zd", k, powr);
	}
	  */
	//mpz_clears(n, k, mod, one, powr, NULL	);
	mpz_invert(one, n, mod);
	//getOrder(k, n, mod);
	gmp_printf("\n Ok: %Zd and powr", one);
//	cout << "Found :" << found << " logn2 :" << lgN2;
	getchar();
	getchar();
	return 0;
}
