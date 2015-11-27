#include <iostream>
#include "helper.h"
#include <cmath>
#include <cstring>

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
  mpz_t number;
	char ip[100];
  printf("Input number to check for AKS LnP\n");
	cin >> ip;
	mpz_init_set_str(number, ip, 10);
	gmp_printf("%Zd \n", number);
	if(aksLnP(number))
		std::cout << " is prime" << std::endl;
	else
		std::cout << " is composite" << std::endl;
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
