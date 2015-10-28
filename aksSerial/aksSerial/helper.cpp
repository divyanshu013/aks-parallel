/*
 * Major Project - Parallel implementation of AKS Algorithm
 * This source file contains the definations of the functions that will be
 * used for implementing the steps of AKS algorithm. The corresponding
 * prototypes are present in helper.h file.
 * You are expected to adhere to the coding standards.
 *
 * Changelog:
 * 1> 19/10/2015: Addition of isPower() funtion
 * 2> 20/10/2015: Addition of getMinR() function
 * 3> 26/10/2015: Implemented getMinR() function
 * 4> 28/10/2015: Changes in getOrder(), addition of new parameter logN2
 */

#include "helper.h"


/*
 * isPower() - This function checks if given number is a perfect power or not
 *
 * parameters : mpz_t - the number to be tested
 * return : bool - true if perfect power, else not
 * 
 * Implementation - It is currently implemented using the library funtion
 * from MPIR as it provides a very fast implementaion. But the implementation
 * is libale to change.
 */
bool isPower(const mpz_t number)
{
	#ifdef PRINTFUNC
	std::cout << "\n>>Entered isPower()";
	#endif
	#ifdef PRINTVALS
	gmp_printf("\nNumber : %Zd", number);
	#endif
	
	// return true if number is a perfect power
	return (mpz_perfect_power_p(number) > 0 ? true : false);
}

//-------------------------------------------------------------------------//

/*
 * getOrder() - This function finds k such that given r ? N, n ? Z with
 * (n, r) = 1, such that n^k = 1
 *
 * parameters : k (mpz_t) - the value of k is stored in this var
 *              number (mpz_t) - the number to be tested
 *			    r (mpz_t) - the number for modulus
 *				logN2 (mpz_t) - the max limit for k
 * return : void
 *
 * Implementation - It is implemented currently using the MPIR libray funtion
 * for the modular exponentiation as it provides a very fast implementation.
 */
void getOrder(mpz_t k, const mpz_t number, const mpz_t r, const mpz_t logN2)
{
	#ifdef PRINTFUNC
	std::cout << "\n\n>>Entered getOrder()";
	#endif
	#ifdef PRINTVALS
	gmp_printf("\nIn getOrder() Number : %Zd, r : %Zd", number, r);
	#endif
	
	mpz_t one,						// the value 1 in mpz_t
		  powr;						// for storing n^k
		  //nModR,
		  //kModR;

	mpz_init_set_str(k, "1", 10);	// initialize k to 1
	mpz_init_set_str(one, "1", 10);	// initialize one to 1
	//mpz_init_set_str(nModR, "0", 10);	
	//mpz_init_set_str(kModR, "0", 10);	
	mpz_init_set(powr, number);		// initialize to given number

	while (true)
	{
		//mpz_mod(nModR, number, r);
		//mpz_mod(kModR, k, r);
		mpz_powm(powr, number, k, r); // n^k mod r
		//mpz_powm(powr, nModR, kModR, r); // n^k mod r
		   		   
		#ifdef PRINTVALS
		gmp_printf("\nK : %Zd, powr : %Zd, log2N %Zd", k, powr, logN2);
		#endif

		if (mpz_cmp(powr, one) == 0)  // is powr == 1
		{
			#ifdef PRINTVALS
			std::cout << std::endl;
			#endif
			
			mpz_clears(one, powr, NULL);
			return;
		}
		else
			mpz_add(k, k, one);
	}
}

//-------------------------------------------------------------------------//

/*
 * getMinR() - This function finds min r such that given r ? N, n ? Z with
 * (n, r) = 1, with some smallest number k such that n^k = 1 (mod r) and
 * k > log^2(n).
 * 
 * parameters : r (mpz_t) - the value of min r is stored in this var
 *              number (mpz_t) - the number to be tested
 * return : if co-prime or not (bool) - true if r and number are co-prime
 *
 * Implementation - Start from r = 3 and get k corresponding to current r
 * value. Loop unti suitable k is found at some suitable r such that
 * k > log2^2(n)
 */
bool getMinR(mpz_t r, const mpz_t number)
{
	#ifdef PRINTFUNC
	std::cout << "\n>>Entered getMinR()";
	#endif
	
	mpz_t one,
		  k,		// for k
		  logN2,	// for log2^2(n)
		  gcd;		// for gcd
	
	int lgN2 = pow(mpz_sizeinbase(number, 2), 2);	// logN2 = ceil(log2^2(n))
	char clgN2[10];
	_itoa_s(lgN2, clgN2, 10);

	mpz_init_set_str(r, "3", 10);		// r = 3
	mpz_init_set_str(logN2, clgN2, 10);	// logN2  =log2^2(n)
	mpz_init_set_str(gcd, "1", 10);
	mpz_init_set_str(one, "1", 10);		// 1 in mpz_t

	#ifdef PRINTVALS
	gmp_printf("\nNumber : %Zd, r : %Zd, logN2 : %Zd, gcd : %Zd, one : %Zd\nIterations:", number, r, logN2, gcd, one);
	#endif

	while (mpz_cmp(r, number) < 0)	// while(r < n)
	{
		mpz_gcd(gcd, r, number);
		if (mpz_cmp(gcd, one) != 0)	// not prime
		{
			#ifdef PRINTVALS
			gmp_printf("\nGCD found != 1, and = %Zd", gcd, k);
			#endif
			
			mpz_clears(r, logN2, gcd, one, NULL);
			return false;
		}

		getOrder(k, number, r, logN2);

		#ifdef PRINTVALS
		gmp_printf("\n%Zd\) Number : %Zd, r : %Zd, gcd : %Zd, k : %Zd",r , number, r, gcd, k);
		#endif

		if (mpz_cmp(k, logN2) > 0)
		{
			return true;
		}
		
		mpz_add(r, r, one);		// r += 1
	}

	// reached n, so return false as no suitable r could be found
	return false;
}