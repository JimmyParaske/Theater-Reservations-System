# Theater-Reservations-System

Assignment for course: "**Operating Systems**"
<br>Department of Computer Science, AUEB


Theater reservation system using threads and mutexes

The code utilizes threads and mutexes for concurrent execution and synchronization, allowing customers to reserve seats and processing their payments while keeping track of relevant statistics.

The code consists of main and 2 methods, the
agora & plhrwmh. main creates the threads with the command
pthread_create. Then the program flow
goes to the agora method and later to the plhrwmh
and with the help of the appropriate mutexes the critical sections "lock".

The agora method corresponds to the client's settlement with
the answering machine, while plhrwmh corresponds to the communication
of the customer with the cashier, which is done as soon as the
execution of the agora method ends.

At the end, the following results are printed:
    <br>• The seat plan
    <br>• The total revenue
    <br>• The percentage of transactions completed with each
        of the three ways
    <br>• The average customer waiting time (from the moment
        appears until the customer speaks to the operator and
        if the transaction proceeds to payment, from the moment that
        the answering machine ends until the moment it takes over
        cashier)
    <br>• The average customer service time (from the moment
        the client appears, until it completes or fails
        reservation)



The .sh file prompts the user to provide as input the path to
where the .c and .h files are located