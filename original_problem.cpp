#include <iostream>

using namespace std;

//if in deadlock, returns -1, otherwise, returns 0
int state_of_philosophers (int[] philosophers, int[] chopsticks, int members) {
    int idle = 0;
    int requesting = 0;
    int waiting = 0;



    return 0;
}

int main()
{
    srand (time(NULL));
    int start_time = clock();
    //
    int members = 5;//5 + (rand() % 5) ;
    //each index is an individual philosopher, the value is the state of the philosopher:
    // - 0: is idle/thinking,
    // - 1: is requesting to eat,
    // - 2: is waiting to eat when not enough chopsticks are available,
    // - any num > 2: is eating/the time needed to eat
    int philosphers[members];
    //each index is the corresponding chopstick in reference to the table and philosophers
    // for nth philosopher, their corresponding chopstick are n and n+1
    // the values correspond to the state of the chopstick:
    // - -1: if the chopstick is available/on the table
    // - positive number: the index of the philosopher who has it
    int chopsticks[members];

    //initializes all the philosophers and chopsticks to idle/on the table
    for (int i = 0; i < members; i++) {
        philosphers[i] = 0;
        chopsticks[i] = -1;
    }

    //how many rounds/how much time do we want this to run for?
    while (clock() - start_time < 100000) {
        for (int i = 0; i < members; i++) {
            switch (philosphers[i]) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                default:

            }
        }

    }

    cout << "Hello world!" << endl;
    return 0;
}
