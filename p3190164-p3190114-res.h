#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>




#define Ntel 3
#define Ncash 2
#define Nseat 10
#define NzoneA 10
#define NzoneB 20
#define PzoneA 0.3
#define CzoneA 30
#define CzoneB 20
#define Nseatlow 1
#define Nseathigh 5
#define treslow 1
#define treshigh 5
#define tseatlow 5
#define tseathigh 13
#define tcashlow 4
#define tcashhigh 8
#define Pcardsuccess 0.9



void *agora(void*);