#include <iostream>
#include "helper.h"
#include <cmath>
#include <cstring>
#include <time.h>
/*
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

typedef long long int64;
typedef unsigned long long uint64;

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Should work on both
 * windows and linux. TODO Check on Windows*/
/*
uint64 GetTimeMs64()
{
  #ifdef _WIN32
  /* Windows *//*
  FILETIME ft;
  LARGE_INTEGER li;

  /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
   * to a LARGE_INTEGER structure. *//*
  GetSystemTimeAsFileTime(&ft);
  li.LowPart = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;

  uint64 ret = li.QuadPart;
  ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. *//*
  ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals *//*

  return ret;
  #else
  /* Linux *//*
  struct timeval tv;

  gettimeofday(&tv, NULL);

  uint64 ret = tv.tv_usec;
  /* Convert from micro seconds (10^-6) to milliseconds (10^-3) *//*
  ret /= 1000;

  /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) *//*
  ret += (tv.tv_sec * 1000);

  return ret;
  #endif
}
*/

using namespace std;

void testIsPower() {
  mpz_t number;
	char ip[100];
  printf("Input number to check for perfect power\n");
	cin >> ip;
	mpz_init_set_str(number, ip, 10);
	gmp_printf("%Zd \n", number);
	if(isPower(number))
		std::cout << " is perfect power" << std::endl;
	else
		std::cout << " is NOT perfect power" << std::endl;
}

void testAksLnP() {
  mpz_t number, fifty_three;
  int diff;
	char ip[100];
  printf("Input number to check for AKS LnP\n");
	cin >> ip;
	mpz_init_set_str(number, ip, 10);
  mpz_init_set_str(fifty_three, "53", 10);
	gmp_printf("%Zd \n", number);
  //clock();
  //uint64 time_before = GetTimeMs64();
  clock_t time_before = clock();
  if(mpz_cmp(fifty_three, number) >= 0) {
    diff = mpz_get_ui(number);

    // Lookup table for numbers upto 53 where the algorithm fails
    if(diff >= 0)  {
      switch (diff) {
        case 2:
        case 3:
        case 5:
        case 7:
        case 11:
        case 13:
        case 17:
        case 19:
        case 23:
        case 29:
        case 31:
        case 37:
        case 41:
        case 43:
        case 47:
        case 53:
          std::cout << " is prime" << std::endl;
          break;
        default:
          std::cout << " is composite" << std::endl;
      }
    }
  }
  else  {
  	if(aksLnP(number))
  		std::cout << " is prime" << std::endl;
  	else
  		std::cout << " is composite" << std::endl;
  }
  //clock();
  //uint64 time_after = GetTimeMs64();
  clock_t time_after = clock();
  printf("Execution Time is %f s\n", (float)(time_after - time_before)/CLOCKS_PER_SEC);
}

int main()
{
  printf("AKS Test class\n\
          1. Test isPower()\
          2. Test getOrder()\
          3. Test getMinR()\
          4. Test aksLnP()\
          5. Exit\n\
          Input your choice\n");
  int choice;
  scanf("%d", &choice);
  switch (choice) {
    case 1:
      testIsPower();
      break;
    case 4:
      testAksLnP();
      break;
    default:
      break;
  }
  return 0;
}
