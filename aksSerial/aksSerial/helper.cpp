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
 * 4> 28/10/2015: *Changes in getOrder(), addition of new parameter logN2,
 *                 gcd calculation step was removed as it was redundant and
 *		           was not required.
 *                 *Addition and implentation of gcdExists() funtion
 * 5> 29/10/2015: *Changes in getMinR(), change in return type
 * 6> 31/10/2015: *Rectified a bug in gcdExists()
 * 7> 1/11/2015:  *Addition of reduceExponents() function
 *		          *Addition of congruenceExists() function
 * 8> 5/11/2015: *Addition of a separate test.cpp file
 * 9> 18/11/2015: *Addition of compatibility fix for linux
 *10> 27/11/2015: *Addition of defination of aksLnP()
 *11> 12/12/2015: *Addition of defination of ParallelWork() functor
 *12> 12/12/2015: *Modified aksLnP() to aksLnPserial()
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
 *		r (mpz_t) - the number for modulus
 *		logN2 (mpz_t) - the max limit for k
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

	mpz_t one,	// the value 1 in mpz_t
	      powr;	// for storing n^k
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
 * return : void
 *
 * Implementation - Start from r = 3 and get k corresponding to current r
 * value. Loop unti suitable k is found at some suitable r such that
 * k > log2^2(n)
 */
void getMinR(mpz_t r, const mpz_t number)
{
	#ifdef PRINTFUNC
	std::cout << "\n>>Entered getMinR()";
	#endif

	mpz_t one,
	      k,	// for k
	      logN2,	// for log2^2(n)
	      logN5,
	      gcd;	// for gcd

	int lgN = mpz_sizeinbase(number, 2);
	int lgN2 = pow(lgN, 2);			// logN2 = ceil(log2^2(n))
	char clgN2[LOGSIZE];

    #ifdef LINUX
    sprintf(clgN2, "%d", lgN2);
    #else
	_itoa_s(lgN2, clgN2, 10);
	#endif
    mpz_init_set_str(logN2, clgN2, 10);	// logN2  =log2^2(n)

	int lgN5 = pow(lgN, 5);			// logN5 = ceil(log2^5(n))
	char clgN5[LOGSIZE];
    #ifdef LINUX
    sprintf(clgN5, "%d", lgN5);
    #else
	_itoa_s(lgN5, clgN5, 10);
    #endif
	mpz_init_set_str(logN5, clgN5, 10);	// logN5  =log2^5(n)

	mpz_init_set_str(r, "3", 10);		// r = 3
	mpz_init_set_str(gcd, "1", 10);
	mpz_init_set_str(one, "1", 10);		// 1 in mpz_t

	#ifdef PRINTVALS
	gmp_printf("\nNumber : %Zd, r : %Zd, logN2 : %Zd, gcd : %Zd, one : %Zd\nIterations:", number, r, logN2, gcd, one);
	#endif

	while (mpz_cmp(r, logN5) < 0)	// while(r < log2^5(n))
	{
		
		mpz_gcd(gcd, r, number);
		if (mpz_cmp(gcd, one) != 0)	// not prime
		{
			#ifdef PRINTVALS
			gmp_printf("\nGCD found != 1, and = %Zd", gcd, k);
			#endif
			
			mpz_add(r, r, one);	// r += 1
			continue;
		}
		
		getOrder(k, number, r, logN2);

		#ifdef PRINTVALS
		gmp_printf("\n%Zd\) Number : %Zd, r : %Zd, gcd : %Zd, k : %Zd", r, number, r, gcd, k);
		#endif

		if (mpz_cmp(k, logN2) > 0)
		{
			return;
		}

		mpz_add(r, r, one);	// r += 1
	}
}

//-------------------------------------------------------------------------//

/*
* gcdExists() - This function checks if 1 < (a, n) < n for a <=r
*
* parameters : number (mpz_t) - the number to be tested
*              r (mpz_t) - the value of r
* return : if gcd exists or not (bool) - true if exist and false otherwise
*
* Implementation: #TODO complete it
*/
bool gcdExists(const mpz_t number, const mpz_t r)
{
	#ifdef PRINTFUNC
	std::cout << "\n>>Entered gcdExists()";
	#endif
	
	mpz_t one,	// the value 1 in mpz_t
		  gcd,	// to store gcd
		  a;	// loop counter

	mpz_init_set_str(gcd, "1", 10);	// initialize gcd to 1
	mpz_init_set_str(one, "1", 10);	// initialize one to 1
	mpz_init_set_str(a, "2", 10);	// initialize a to 2

	while (mpz_cmp(a, r) <= 0)		// while(a < r)
	{
		mpz_gcd(gcd, a, number);

		#ifdef PRINTVALS
		gmp_printf("\n%Zd\) a : %Zd, gcd : %Zd", a, a, gcd);
		#endif

		if (mpz_cmp(gcd, one) != 0)	// if(gcd != 1)
		{
			mpz_clears(gcd, one, a, NULL);
			return true;			// exists
		}
		
		mpz_add(a, a, one); // a += 1
	}

	return false;	// does not exist
}

//-------------------------------------------------------------------------//

/*
* reduceExponents() - This function reduces the exponents mod r
*
* parameters : poly (ZZ_pX) - the polynomial
*              r (ZZ) - the value of r
* return : void
* 
* Implementation : #TODO complete it
*/
void reduceExponents(ZZ_pX &p, const ZZ &r)
{
	#ifdef PRINTFUNC
	std::cout << "\n>>Entered reduceExponents()";
	#endif
	
	long i = deg(p);
	long rl;
	long i_mod_r;
	ZZ_p c;			// value of current (high-order) coefficient
	ZZ_p newc;		// value to put into new (low-order) coefficient

	// But we need R as a long!
	// WARNING: Truncates without checking length first.
	conv(rl, r);

	while (i >= rl) 
	{
		c = coeff(p, i);
		if (!IsZero(c)) 
		{
			i_mod_r = i % rl;

			newc = coeff(p, i_mod_r);	// Add the value of the high-order coefficient to that of the
			add(newc, newc, c);		// equivalent (mod r) low-order coefficient

			// Update the value of the low-order coefficient and clear the high-order one
			SetCoeff(p, i % rl, newc);
			SetCoeff(p, i, 0);
		}
		i--;
	}
}

//-------------------------------------------------------------------------//

// Defination of ParallelWork() functor's function call operator
void ParallelWork::operator () (int start, int end)
{
    ZZ_p::init(number);
    long al;
    for (int a = start; a <= end; a++)
    {
        conv(al, a);
        SetCoeff(base, 1, 1);
        SetCoeff(base, 0, al);

        // Perform the exponentiation  (x + 1)^n
        left = 1;

        for (long u = bitLength; u != 0; u--)
        {
            sqr(left, left);

            if (bit(number, u - 1) == 1)
            {
                mul(left, left, base);
            }
            reduceExponents(left, r);
        }

        // Build the right side and perform the final comparison
        rem(nModR, number, r);
        leadingCoeff = trunc_long(nModR, 32);
        SetCoeff(right, 0, al);
        SetCoeff(right, leadingCoeff, 1);

        if (left != right)
        {
            *isPrime = false;   // does't exist
        }
    }
}

/*
* congruenceExists() - This function checks if (X + a)^n iseqv to (X^n + a)
* mod(X^r - 1, n).
*
* parameters : number (mpz_t) - the number to be tested
*              r (mpz_t) - the value of r
* return : if congruence exists or not (bool) - true if exist and false otherwise
* 
* Implementation: #TODO complete it
*/
bool congruenceExists(const mpz_t gnumber, const mpz_t gr)
{
	#ifdef PRINTFUNC
	std::cout << "\n>>Entered congruenceExists()";
	#endif

	char cNumber[NSIZE],    // char rep of n
	     cR[NSIZE];         // and r
    
	gmp_sprintf(cNumber, "%Zd", gnumber);
	gmp_sprintf(cR, "%Zd", gr);

	ZZ number = conv<ZZ>(cNumber);
	ZZ r = conv<ZZ>(cR);

	ZZ_p::init(number);

	ZZ nModR;
	ZZ_pX left;
	ZZ_pX right;
	long leadCoeff;
	bool isPrime;
	long bitLength;
	ZZ_pX base;
	long aMax;

	long sqrtRlogN;
	long logN = NumBits(number);

  	// Find sqrt(r) * log(n)
	conv(sqrtRlogN, r);
	sqrtRlogN = sqrt(sqrtRlogN);
	sqrtRlogN *= logN;

	bitLength = NumBits(number);
	aMax = floor(sqrtRlogN);
	isPrime = true;

    // Initialize and call the function
	ParallelWork pFunct(bitLength, leadCoeff,
                        base, left, right,
                        nModR, number, r, &isPrime);
    pFunct(1, aMax);
	
	return isPrime ; // exists
}

//-------------------------------------------------------------------------//

/*
* aksLnPserial() - This function runs the aks algorithm improved by Lenstra and Pomerance
*
* parameters : number (mpz_t) - the number to be tested
* return : if prime or not (bool) - true if prime and false otherwise
*
* Implementation: This funciton implements the Lenstra and Pomerance improved AKS algorithm
*/
bool aksLnPserial(const mpz_t number)
{
     #ifdef PRINTFUNC
     std::cout << "\n>>Entered congruenceExists()";
     #endif
    
     /* Don't check here for the time being
     // Check for small primes
     char cNumber[NSIZE];
     int iNumber;
     gmp_sprintf(cNumber, "%Zd", number);
     iNumber = atoi(cNumber);
     if(iNumber == 2 || iNumber == 3 || iNumber == 5 || iNumber == 7 || iNumber == 11 ||
        iNumber == 13 || iNumber == 17 || iNumber == 19 || iNumber == 23 || iNumber == 29)
        return true;
     */

     mpz_t r;       // r value

     // Check for perfect power
     if (isPower(number))
     {
         #ifdef PRINTVALS
         cout << "Not prime because perfect power";
         #endif

         return false;  // composite
     }

     // get value of r
     getMinR(r, number);

     // check for GCD
     if (gcdExists(number, r))
     {
         #ifdef PRINTVALS
         cout << "Not prime because gcd present";
         #endif

         return false;  // composite
     }

     // check if number <= r
     if (mpz_cmp(r, number) >= 0)
     {
         #ifdef PRINTVALS
         cout << "Not prime because r >= n";
         #endif
         
         return false;  // composite, condition in algorithm
     }

     // check for congruence
     if (!congruenceExists(number, r))
     {
         #ifdef PRINTVALS
         cout << "Not prime because congruence does not exists";
         #endif
         
         return false;  // composite
     }

     // passed all tests, so prime
     return true;
}
