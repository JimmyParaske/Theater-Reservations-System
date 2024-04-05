#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "p3190164-p3190114-res.h"

pthread_mutex_t MUTEX_avgWait_custTOtel;
pthread_mutex_t MUTEX_avgWait_custTOcashier;
pthread_mutex_t MUTEX_avgEksyphrethsh;

pthread_mutex_t MUTEX_NTEL;
pthread_mutex_t MUTEX_NCASH;
pthread_mutex_t MUTEX_NSEAT;
pthread_mutex_t MUTEX_NESODA;
pthread_mutex_t MUTEX_PRINT;
pthread_mutex_t COUNTER_SUCC;
pthread_mutex_t COUNTER_FAILSEATS;
pthread_mutex_t COUNTER_FAILCARD;
pthread_mutex_t COUNTER_TOTAL;



pthread_cond_t CONDMUTEX_NTEL;
pthread_cond_t CONDMUTEX_NCASH;
pthread_cond_t CONDMUTEX_NSEAT;
pthread_cond_t CONDMUTEX_NESODA;

struct timespec startAgora, startPlhrwmh,stopAgora, stopPlhrwmh, stopSynallagh;

double avgWait_custTOtel;
double avgWait_custTOcashier;
double avgEksyphrethsh;

double successcount;
double failseatscount;
double failcard;
double totalcount;




int seats[30][10];
int balance;

int seed;


int tyxaiosArithmos(int low, int high)
{

    int number = (rand_r(&seed) % (high - low + 1)) + low;
    return number;
}


unsigned int Ntel_free = 3;
unsigned int Ncash_free = 10;

void* plhrwmh(int total, int row, int firstseat, int seatcount){

    double waitcustTocash;
    double waiteksyphrethsh;

    pthread_mutex_lock(&MUTEX_NCASH);

    while(Ncash_free==0){

        pthread_cond_wait(&CONDMUTEX_NCASH, &MUTEX_NCASH);
    }


    Ncash_free--;
    clock_gettime(CLOCK_REALTIME, &stopPlhrwmh);

    waitcustTocash = stopPlhrwmh.tv_sec - startPlhrwmh.tv_sec;

    pthread_mutex_lock(&MUTEX_avgWait_custTOcashier);
    avgWait_custTOcashier += waitcustTocash;
    pthread_mutex_unlock(&MUTEX_avgWait_custTOcashier);

    pthread_mutex_unlock(&MUTEX_NCASH);


    int randNum2 = tyxaiosArithmos(tcashlow, tcashhigh);
    sleep(randNum2);



    int randNum3 = tyxaiosArithmos(1,100);


    if (randNum3 <=90){
        pthread_mutex_lock(&MUTEX_NESODA);
        balance = balance + total;
        pthread_mutex_unlock(&MUTEX_NESODA);
        if(row<10){
            printf("Reservation successful! Your seats are in zone: A , row %d ",row);
        }
        else{
            printf("Reservation successful! Your seats are in zone: B, row %d ",row);
        }
        printf("number: ");
        for(int i=0; i<seatcount; i++){

            printf("%d ",firstseat+i+1);
        }
        printf(", the total cost is: %d\n", total);

        pthread_mutex_lock(&COUNTER_SUCC);
        successcount++;
        pthread_mutex_unlock(&COUNTER_SUCC);

        pthread_mutex_lock(&COUNTER_TOTAL);
        totalcount++;
        pthread_mutex_unlock(&COUNTER_TOTAL);
    }
    else{
        pthread_mutex_lock(&MUTEX_NSEAT);
        for(int i=0; i<seatcount; i++){

            seats[row][i+firstseat]= -1;

        }
        pthread_mutex_unlock(&MUTEX_NSEAT);
        printf("Card is declined!\n");

        pthread_mutex_lock(&COUNTER_FAILCARD);
        failcard++;
        pthread_mutex_unlock(&COUNTER_FAILCARD);

        pthread_mutex_lock(&COUNTER_TOTAL);
        totalcount++;
        pthread_mutex_unlock(&COUNTER_TOTAL);
    }

    pthread_mutex_lock(&MUTEX_NCASH);
    Ncash_free++;
    pthread_mutex_unlock(&MUTEX_NCASH);
    pthread_cond_signal(&CONDMUTEX_NCASH);
    clock_gettime(CLOCK_REALTIME, &stopSynallagh);

    waiteksyphrethsh = stopSynallagh.tv_sec - startAgora.tv_sec;

    pthread_mutex_lock(&MUTEX_avgEksyphrethsh);
    avgEksyphrethsh += waiteksyphrethsh;
    pthread_mutex_unlock(&MUTEX_avgEksyphrethsh);

}


void* agora(void *id){

    double waitcustTotel;
    int row=0;
    int firstseat=0;


    clock_gettime(CLOCK_REALTIME,&startAgora);


    pthread_mutex_lock(&MUTEX_NTEL);
    while(Ntel_free == 0)
    {

        pthread_cond_wait(&CONDMUTEX_NTEL, &MUTEX_NTEL);

    }
    clock_gettime(CLOCK_REALTIME, &stopAgora);

    waitcustTotel = stopAgora.tv_sec - startAgora.tv_sec;

    pthread_mutex_lock(&MUTEX_avgWait_custTOtel);
    avgWait_custTOtel += waitcustTotel;
    pthread_mutex_unlock(&MUTEX_avgWait_custTOtel);


    Ntel_free--;


    pthread_mutex_unlock(&MUTEX_NTEL);

    int randNum = tyxaiosArithmos(tseatlow, tseathigh);
    sleep(randNum);


    int epiloghZone = tyxaiosArithmos(1, 100);
    int sumtickets = tyxaiosArithmos(Nseatlow, Nseathigh);
    int totalcost=0;

    bool found = false;

    if(epiloghZone <=30){

        pthread_mutex_lock(&MUTEX_NSEAT);

        for(int i=0; i <10; i++){

            int e=0;
            while(e+sumtickets<=10 && !found){

                if(seats[i][e]== -1){
                    int countseats = 0;
                    row=i;
                    firstseat=e;

                    for(int k=0; k<sumtickets; k++){
                        if(seats[i][e+k] ==-1){
                            countseats++;
                        }

                    }
                    if (countseats == sumtickets){

                        for(int k=0; k<sumtickets; k++){

                            seats[i][e+k] = id;

                        }
                        pthread_mutex_unlock(&MUTEX_NSEAT);
                        found = true;
                    }

                }

                e++;
            }

        }

        if(found){
            totalcost = sumtickets*30;


        }
        else{

            printf("Not enough seats!\n");
            pthread_mutex_lock(&COUNTER_FAILSEATS);
            failseatscount++;
            pthread_mutex_unlock(&COUNTER_FAILSEATS);

            pthread_mutex_lock(&COUNTER_TOTAL);
            totalcount++;
            pthread_mutex_unlock(&COUNTER_TOTAL);
        }
    }
    else{
        pthread_mutex_lock(&MUTEX_NSEAT);
        for(int i=10; i <30; i++){

            int e=0;
            while(e+sumtickets<=10 && !found){

                if(seats[i][e]== -1){
                    int countseats = 0;
                    row =i;
                    firstseat=e;

                    for(int k=0; k<sumtickets; k++){
                        if(seats[i][e+k] ==-1){
                            countseats++;
                        }

                    }
                    if (countseats == sumtickets){

                        for(int k=0; k<sumtickets; k++){

                            seats[i][e+k] = id;

                        }
                        pthread_mutex_unlock(&MUTEX_NSEAT);
                        found = true;

                    }
                }
                e++;
            }

        }

        if(found){
            totalcost = sumtickets*20;


        }
        else{

            printf("Not enough seats!\n");
            pthread_mutex_lock(&COUNTER_FAILSEATS);
            failseatscount++;
            pthread_mutex_unlock(&COUNTER_FAILSEATS);

            pthread_mutex_lock(&COUNTER_TOTAL);
            totalcount++;
            pthread_mutex_unlock(&COUNTER_TOTAL);
        }

    }


    pthread_mutex_lock(&MUTEX_NTEL);



    Ntel_free++;
    clock_gettime(CLOCK_REALTIME, &startPlhrwmh);
    pthread_mutex_unlock(&MUTEX_NTEL);
    pthread_cond_signal(&CONDMUTEX_NTEL);
    if(found){
        plhrwmh(totalcost, row, firstseat, sumtickets);
    }


}





int main(int argc, char ** argv) {



    int Ncust;

    //χρησιμοποιείται για να μετατρέψει string σε int
    Ncust = atoi(argv[1]);
    seed = atoi(argv[2]);





    balance = 0;

    for(int i=0; i<30; i++){

        for(int e=0; e<10; e++){

            seats[i][e] = -1;
        }
    }


    pthread_mutex_init(&MUTEX_avgWait_custTOtel, NULL);
    pthread_mutex_init(&MUTEX_avgWait_custTOcashier, NULL);
    pthread_mutex_init(&MUTEX_avgEksyphrethsh, NULL);
    pthread_mutex_init(&COUNTER_TOTAL, NULL);
    pthread_mutex_init(&COUNTER_FAILSEATS, NULL);
    pthread_mutex_init(&COUNTER_FAILCARD, NULL);
    pthread_mutex_init(&COUNTER_SUCC, NULL);


    pthread_mutex_init(&MUTEX_NTEL, NULL);
    pthread_mutex_init(&MUTEX_NCASH, NULL);
    pthread_mutex_init(&MUTEX_NSEAT, NULL);
    pthread_mutex_init(&MUTEX_NESODA, NULL);
    pthread_mutex_init(&MUTEX_PRINT, NULL);
    pthread_cond_init(&CONDMUTEX_NTEL, NULL);
    pthread_cond_init(&CONDMUTEX_NCASH, NULL);
    pthread_cond_init(&CONDMUTEX_NSEAT,NULL);
    pthread_cond_init(&CONDMUTEX_NESODA,NULL);

    pthread_t threads[Ncust];

    int rc;

    for (int i=0; i<Ncust; i++){

        rc = pthread_create(&threads[i], NULL, agora, (void*)i);
        int waitNextcust = tyxaiosArithmos(treslow,treshigh);
        sleep(waitNextcust);



    }

    for(int i=0; i<Ncust;i++){

        pthread_join(threads[i], NULL);
    }


    for(int r=0; r<30; r++){

        for(int c=0; c<10; c++){


            if (r<10){

                printf("Zone: A / ");
                printf("Row: %d / ", r);
                printf("Seat: %d / ", c+1);
                if(seats[r][c] == -1){
                    printf("Empty!\n");
                }
                else{
                    printf("Customer %d\n", seats[r][c]);
                }
            }
            else{
                printf("Zone: B / ");
                printf("Row: %d / ", r);
                printf("Seat: %d / ", c+1);
                if(seats[r][c] == -1){
                    printf("Empty!\n");
                }
                else{
                    printf("Customer %d\n", seats[r][c]);
                }

            }
        }
    }

    printf("Balance: %d\n", balance);
    printf("Average wait customer to tel: %.3f\n", (avgWait_custTOtel/100)/60.0);
    printf("Average wait customer to cashier: %.3f\n", (avgWait_custTOcashier/100)/60.0);
    printf("Average time of eksyphrethsh: %.3f\n", (avgEksyphrethsh/100)/60.0);
    printf("Successful reservation percentage out of total %d reservations is: ", totalcount);
    printf("%.2f %\n",(successcount/totalcount)*100);
    printf("Failed reservation percentage due to unavailable seats is: ");
    printf("%.2f %\n",(failseatscount/totalcount)*100);
    printf("Failed reservations percentage due to declined card is: ");
    printf("%.2f %\n",(failcard/totalcount)*100);




    pthread_mutex_destroy(&MUTEX_NSEAT);
    pthread_mutex_destroy(&MUTEX_NTEL);
    pthread_mutex_destroy(&MUTEX_NCASH);
    pthread_mutex_destroy(&MUTEX_NESODA);
    pthread_mutex_destroy(&MUTEX_avgEksyphrethsh);
    pthread_mutex_destroy(&MUTEX_avgWait_custTOcashier);
    pthread_mutex_destroy(&MUTEX_avgWait_custTOtel);
    pthread_mutex_destroy(&COUNTER_TOTAL);
    pthread_mutex_destroy(&COUNTER_FAILSEATS);
    pthread_mutex_destroy(&COUNTER_SUCC);
    pthread_mutex_destroy(&COUNTER_FAILCARD);
    pthread_cond_destroy(&CONDMUTEX_NCASH);
    pthread_cond_destroy(&CONDMUTEX_NTEL);
    pthread_cond_destroy(&CONDMUTEX_NESODA);
    pthread_cond_destroy(&CONDMUTEX_NSEAT);

    pthread_exit(NULL);


    return 0;
}

