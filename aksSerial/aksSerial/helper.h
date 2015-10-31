/*
 * Major Project - Parallel implementation of AKS Algorithm
 * This header file contains the prototypes of the functions that will be 
 * used for implementing the steps of AKS algorithm. The corresponding 
 * implementations are present in helper.cpp file.
 * You are expected to adhere to the coding standards.
 *
 * Changelog:
 * 1> 19/10/2015: Addition of isPower() function
 * 2> 20/10/2015: Addition of getOrder() function
 *                Addition of getMinR() function
 * 3> 28/10/2015: *Changes in getOrder(), addition of new parameter logN2
 *				  *Addition of gcdExists() function
 * 4> 29/10/2015: *Changes in getMinR(), change in return type
 * 5) 31/10/2015: *Addition of congruenceExists()
 */

#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <mpir.h>
#include <NTL/ZZ_pX.h>

#define PRINTFUNC		// Uncommnet it to know the entry/exit in functions
#define PRINTVALS		// Uncomment it to print values in funtions
#define LOGSIZE 200		// size of log buffer

/* 
 * isPower() - This function checks if given number is a perfect power or not
 *
 * parameters : number (mpz_t) - the number to be tested
 * return : bool - true if perfect power, else not
 *
 * Implementation - It is currently implemented using the library funtion
 * from MPIR as it provides a very fast implementaion. But the implementation
 * is libale to change.
 */
bool isPower(const mpz_t number);

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
 */
void getOrder(mpz_t k, const mpz_t number, const mpz_t r, const mpz_t logN2);

//-------------------------------------------------------------------------//

/*
 * getMinR() - This function finds min r such that given r ? N, n ? Z with
 * (n, r) = 1, with some smallest number k such that n^k = 1 (mod r) and
 * k > log^2(n). 
 * 
 * parameters : r (mpz_t) - the value of min r is stored in this var
 *              number (mpz_t) - the number to be tested
 * return : void
 */
void getMinR(mpz_t r, const mpz_t number);

//-------------------------------------------------------------------------//

/*
* gcdExists() - This function checks if 1 < (a, n) < n for a <=r
*
* parameters : number (mpz_t) - the number to be tested
*              r (mpz_t) - the value of r
* return : if gcd exists or not (bool) - true if exist and false otherwise
*/
bool gcdExists(const mpz_t number, const mpz_t r);

//-------------------------------------------------------------------------//

/*
* congruenceExists() - This function checks if (X + a)^n iseqv to (X^n + a)
* mod(X^r - 1, n). 
*
* parameters : number (mpz_t) - the number to be tested
*              r (mpz_t) - the value of r
* return : if congruence exists or not (bool) - true if exist and false otherwise
*/
bool congruenceExists(const mpz_t number, const mpz_t r);

#endif
