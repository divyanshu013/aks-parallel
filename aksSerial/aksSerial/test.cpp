#include <iostream>
#include "helper.h"
#include <cmath>
#include <cstring>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <signal.h>
#include <chrono>
#include<ratio>

using namespace std;
using namespace chrono;

// Use this function in main to generate the required dataset
void genData(void);

// Signal handler in case of termination
void handler(int);


void testIsPower() 
{
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

void testAksLnPSerial() {
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
  	if(aksLnPserial(number))
  		std::cout << " is prime" << std::endl;
  	else
  		std::cout << " is composite" << std::endl;
  }
  //clock();
  //uint64 time_after = GetTimeMs64();
  clock_t time_after = clock();
  printf("Execution Time is %f s\n", (float)(time_after - time_before)/CLOCKS_PER_SEC);
}

void generateDatasetSerial()
{
  mpz_t number, fifty_three;
  mpz_init_set_str(fifty_three, "53", 10);
  ofstream datafile;
  datafile.open ("plot_serial.dat");
  datafile << "#This is the datafile for gnuplot running aksLnPserial\n";
  datafile << "#Iteration \t Number \t Execution time (ms)\n";
  unsigned long int prime_array[] = {19, 31, 109, 199, 409, 571, 631, 829, 1489,
    1999, 2341, 2971, 3529, 4621, 4789, 7039, 7669, 8779, 9721, 10459, 10711,
    13681, 14851, 16069, 16381, 17659, 20011, 20359, 23251, 25939, 27541, 29191,
    29611, 31321, 34429, 36739, 40099, 40591, 42589, 53471161}; // Populate dataset, limit of 2 * 10^9 for INT_MAX
  int len = 40;
  //gmp_printf("%Zd \n", number);
  //gmp_printf("%Zd \n", number);
  //int len = prime_array.length;
  for (int i = 0; i < len; ++i) {
    mpz_init_set_ui (number, prime_array[i]);
    gmp_printf("%Zd \n", number);
    std::cout << "Working " << (i+1) << " of " << len << std::endl;
    clock_t time_before = clock();
    if(mpz_cmp(fifty_three, number) >= 0) {
      int diff = mpz_get_ui(number);

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
            std::cout << prime_array[i] << " is prime" << std::endl;
            break;
          default:
            std::cout << prime_array[i] << " is composite in switch" << std::endl;
        }
      }
    }
    else  {
    	if(aksLnPserial(number))
        std::cout << prime_array[i] << " is prime" << std::endl;
    	else
        std::cout << prime_array[i] << " is composite in else" << std::endl;
    }
    //clock();
    //uint64 time_after = GetTimeMs64();
    clock_t time_after = clock();
    float execution_time = (float)(time_after - time_before)/CLOCKS_PER_SEC;
    std::cout << execution_time << std::endl;
    execution_time *= 1000; // time in ms
    datafile << i;
    datafile << "\t";
    datafile << prime_array[i];
    datafile << "\t";
    datafile << execution_time;
    datafile << "\n";
  }
  datafile.close();
  std::cout << "Run gnuplot plot_serial.dat for results" << std::endl;
}

void testAksLnPparallel() {
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
  	if(aksLnP2core(number))
  		std::cout << " is prime" << std::endl;
  	else
  		std::cout << " is composite" << std::endl;
  }
  //clock();
  //uint64 time_after = GetTimeMs64();
  clock_t time_after = clock();
  printf("Execution Time is %f s\n", (float)(time_after - time_before)/CLOCKS_PER_SEC);
}

void generateDatasetParallel()
{
  mpz_t number, fifty_three;
  mpz_init_set_str(fifty_three, "53", 10);
  ofstream datafile;
  datafile.open ("plot_parallel.dat");
  datafile << "#This is the datafile for gnuplot running aksLnPparallel\n";
  datafile << "#Iteration \t Number \t Execution time (ms)\n";
  unsigned long int prime_array[] = {19, 31, 109, 199, 409, 571, 631, 829, 1489,
    1999, 2341, 2971, 3529, 4621, 4789, 7039, 7669, 8779, 9721, 10459, 10711,
    13681, 14851, 16069, 16381, 17659, 20011, 20359, 23251, 25939, 27541, 29191,
    29611, 31321, 34429, 36739, 40099, 40591, 42589, 53471161}; // Populate dataset, limit of 2 * 10^9 for INT_MAX
  int len = 40;
  //gmp_printf("%Zd \n", number);
  //gmp_printf("%Zd \n", number);
  //int len = prime_array.length;
  for (int i = 0; i < len; ++i) {
    mpz_init_set_ui (number, prime_array[i]);
    gmp_printf("%Zd \n", number);
    std::cout << "Working " << (i+1) << " of " << len << std::endl;
    clock_t time_before = clock();
    if(mpz_cmp(fifty_three, number) >= 0) {
      int diff = mpz_get_ui(number);

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
            std::cout << prime_array[i] << " is prime" << std::endl;
            break;
          default:
            std::cout << prime_array[i] << " is composite in switch" << std::endl;
        }
      }
    }
    else  {
    	if(aksLnP2core(number))
        std::cout << prime_array[i] << " is prime" << std::endl;
    	else
        std::cout << prime_array[i] << " is composite in else" << std::endl;
    }
    //clock();
    //uint64 time_after = GetTimeMs64();
    clock_t time_after = clock();
    float execution_time = (float)(time_after - time_before)/CLOCKS_PER_SEC;
    std::cout << execution_time << std::endl;
    execution_time *= 1000; // time in ms
    datafile << i;
    datafile << "\t";
    datafile << prime_array[i];
    datafile << "\t";
    datafile << execution_time;
    datafile << "\n";
  }
  datafile.close();
  std::cout << "Run gnuplot plot_parallel.dat for results" << std::endl;
}

int main()
{

  printf("AKS Test class\n\
          1. Test isPower()\
          2. Test getOrder()\
          3. Test getMinR()\
          4. Test aksLnPSerial()\
          5. Generate serial dataset\
          6. Test aksLnPparallel()\
          7. Generate parallel dataset\
          8. Call genData() to generate data\
          9. Exit\n\
          Input your choice\n");
  int choice;
  scanf("%d", &choice);
  switch (choice) {
    case 1:
      testIsPower();
      break;
    case 2:
      break; //TODO
    case 3:
      break; //TODO
    case 4:
      testAksLnPSerial();
      break;
    case 5:
      generateDatasetSerial();
      break;
    case 6:
      testAksLnPparallel();
      break;
    case 7:
      generateDatasetParallel();
      break;
    case 8:
        genData();
        break;
    default:
      break;
  }
  
  //genData();
  return 0;
}

// gen data
// Sorry but these have to be global for signal handler
ifstream infile("in.txt", ios::in);
ofstream outfile("plot.dat", ios::app);
int num,
    iteration = 0;

void genData(void)
{
    // signal thread
    signal(SIGABRT, handler);
    signal(SIGTERM, handler);
    signal(SIGINT, handler);

    #ifdef LINUX
    signal(SIGQUIT, handler);
    signal(SIGKILL, handler);
    #endif

    char number[10];
  
    float logSt,
          logPt;
    mpz_t gNum;
    
    high_resolution_clock::time_point t1,
                                      t2,
                                      core1,
                                      core2,
                                      chore4,
                                      core6,
                                      core8;
    
    cout << setw(5) << "#Iter" << setw(12) << "Number" << setw(10) << "1C(ms)"
         << setw(10) << "2C" << setw(10) << "4C(ms)" << setw(10) << "6C"  << setw(10) << "8C" << endl;

    outfile << setw(5) << "#Iter" << setw(12) << "Number" << setw(10) << "1C(ms)"
            << setw(10) << "2C" << setw(10) << "4C(ms)" << setw(10) << "6C" << setw(10) << "8C" << '\n';


    while (!infile.eof())
    {
        infile.getline(number, 100);
        num = atoi(number);
        mpz_init_set_ui(gNum, num);

        // Serial Execution
        t1 = high_resolution_clock::now();
        aksLnPserial(gNum);
        t2 = high_resolution_clock::now();
        duration<double> core1 = duration_cast<chrono::milliseconds>(t2 - t1);

        // Serial Execution
        t1 = high_resolution_clock::now();
        aksLnP2core(gNum);
        t2 = high_resolution_clock::now();
        duration<double> core2 = duration_cast<chrono::milliseconds>(t2 - t1);

        // Serial Execution
        t1 = high_resolution_clock::now();
        aksLnP4core(gNum);
        t2 = high_resolution_clock::now();
        duration<double> core4 = duration_cast<chrono::milliseconds>(t2 - t1);

        // Serial Execution
        t1 = high_resolution_clock::now();
        aksLnP6core(gNum);
        t2 = high_resolution_clock::now();
        duration<double> core6 = duration_cast<chrono::milliseconds>(t2 - t1);
        
        // Serial Execution
        t1 = high_resolution_clock::now();
        aksLnP8core(gNum);
        t2 = high_resolution_clock::now();
        duration<double> core8 = duration_cast<chrono::milliseconds>(t2 - t1);
                                                                                
        // On terminal
        cout << setw(5) << iteration << setw(12) << num << setw(10) << core1.count()
             << setw(10) << core2.count() << setw(10) << core4.count() << setw(10) << core6.count()
             << setw(10) << core8.count() << endl;

        // To file
        outfile << setw(5) << iteration << setw(12) << num << setw(10) << core1.count()
                << setw(10) << core2.count() << setw(10) << core4.count() << setw(10) << core6.count()
                << setw(10) << core8.count() << '\n';

        iteration++;
    }
    infile.close();
    outfile.close();
}

// Signal handler
void handler(int param)
{
    outfile.flush();
    outfile.close();
    infile.close();
    char buff[100];

    cerr << endl << "Encountered Error in iteration " << iteration << ", Number " << num << endl;
    sprintf(buff, "echo Iteration : %d , Number : %d > error.log", iteration, num);

    system(buff);
    exit(0);
}