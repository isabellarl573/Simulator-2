#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

int start_time = 0;
int deadlock_amount = 0;

//if in deadlock, returns -1, otherwise, returns 0
int state_of_philosophers (int philosophers[], int chopsticks[], int members) {
    int idle = 0;
    int requesting = 0;
    int waiting = 0;
    int eating = 0;
    int avaible_chopsticks = 0;
    int used_chopsticks = 0;

    for (int i = 0; i < members; i++) {
        switch(philosophers[i]) {
            case -1:
                idle++;
                break;
            case 0:
            case 1:
                requesting++;
                break;
            case 2:
            case 3:
                waiting++;
                break;
            default:
                eating++;
        }
        if (chopsticks[i] == -1) {
            avaible_chopsticks++;
        } else {
            used_chopsticks++;
        }
    }

    if (chopsticks[members] == -1) {
        avaible_chopsticks++;
    } else {
        used_chopsticks++;
    }

    cout << "At time: " << (clock() - start_time);
    cout << " Idle/Thinking : " << idle << " Requesting : " << requesting << " Waiting : " << waiting << " Eating : " << eating << endl;
    //deadlock
    if (waiting == members && avaible_chopsticks == 0) {
        deadlock_amount++;
        return -1;
    }

    return 0;
}

int main()
{
    srand (time(NULL));
    start_time = clock();
    //
    int members = 5;//5 + (rand() % 5) ;
    //each index is an individual philosopher, the value is the state of the philosopher:
    // - -1: is idle/thinking,
    // - 0: is requesting to eat, has zero chopsticks
    // - 1: is requesting to eat, has one chopstick
    // - 2: is waiting to eat, has zero chopsticks (when not enough chopsticks are available)
    // - 3: is waiting to eat, has one chopstick (when not enough chopsticks are available)
    // - any num > 3: is eating/the time needed to eat
    int philosphers[members];
    //each index is the corresponding chopstick in reference to the table and philosophers
    // for nth philosopher, their corresponding chopstick are n and n+1
    // the values correspond to the state of the chopstick:
    // - -1: if the chopstick is available/on the table
    // - positive number: the index of the philosopher who has it
    int chopsticks[members + 1];

    //initializes all the philosophers and chopsticks to idle/on the table
    for (int i = 0; i < members; i++) {
        philosphers[i] = 0;
        chopsticks[i] = -1;
    }
    chopsticks[members] = -1;

    int next_stick;
    int time_to_eat;
    //how many rounds/how much time do we want this to run for?
    while (clock() - start_time < 10000) {
        for (int i = 0; i < members; i++) {
            next_stick = (i + 1 == members) ? 0: i + 1;

            switch (philosphers[i]) {
                //chance to request to eat
                case -1:
                    //if probability is met, they request to eat
                    if (20 > rand() % 100)
                        philosphers[i] = 0;
                    break;
                //has zero chopstick, wants to grab a chopstick, if one is available, it is grabbed (needs one)
                case 0:
                    if (chopsticks[i] == -1) {
                        chopsticks[i] = i;
                        philosphers[i] = 1;
                    } else if (chopsticks[next_stick] == -1) {
                        chopsticks[next_stick] = i;
                        philosphers[i] = 1;
                    //extra chopstick
                    } else if ((i == 0 || i == (members - 1)) && chopsticks[members] == -1) {
                        chopsticks[members] = i;
                        philosphers[i] = 1;
                    } else {
                        philosphers[i] = 2;
                    }
                    break;
                //has one chopstick, wants to grab a chopstick, if one is available, it is grabbed (if they have both, they start eating)
                case 1:
                    time_to_eat = clock() + (rand() % ((i + 1) * 1000));
                    if (chopsticks[i] == -1) {
                        chopsticks[i] = i;
                        philosphers[i] = time_to_eat;
                    } else if (chopsticks[next_stick] == -1) {
                        chopsticks[next_stick] = i;
                        philosphers[i] = time_to_eat;
                    //extra chopstick
                    } else if ((i == 0 || i == (members - 1)) && chopsticks[members] == -1) {
                        chopsticks[members] = i;
                        philosphers[i] = 1;
                    } else {
                        philosphers[i] = 3;
                    }
                //waiting - zero chopsticks
                case 2:
                    if (chopsticks[i] == -1) {
                        chopsticks[i] = i;
                        philosphers[i] = 1;
                    } else if (chopsticks[next_stick] == -1) {
                        chopsticks[next_stick] = i;
                        philosphers[i] = 1;
                    //extra chopstick
                    } else if ((i == 0 || i == (members - 1)) && chopsticks[members] == -1) {
                        chopsticks[members] = i;
                        philosphers[i] = 1;
                    } // else, stays at 2

                //waiting (one chopstick)- chance to drop the chopstick (if they get bored)
                case 3:
                    time_to_eat = clock() + (rand() % ((i + 1) * 1000));
                    if (chopsticks[i] == -1) {
                        chopsticks[i] = i;
                        philosphers[i] = time_to_eat;
                    } else if (chopsticks[next_stick] == -1) {
                        chopsticks[next_stick] = i;
                        philosphers[i] = time_to_eat;
                    //extra chopstick
                    } else if ((i == 0 || i == (members - 1)) && chopsticks[members] == -1) {
                        chopsticks[members] = i;
                        philosphers[i] = 1;
                    } /* else {

                        //if gets too bored, drops a chopstick and goes back to thinking
                        if (5 > rand() % 100) {
                            if (chopsticks[i] == i) {
                                chopsticks[i] = -1;
                                philosphers[i] = -1;
                            } else if (chopsticks[next_stick] == i) {
                                chopsticks[next_stick] = -1;
                                philosphers[i] = -1;
                            }
                        } //else stays at 3
                    }*/
                    break;
                //es hora de comer
                default:
                    //done eating
                    if (philosphers[i] < clock()) {
                        philosphers[i] = -1;
                        chopsticks[i] = -1;
                        chopsticks[next_stick] = -1;
                    }
                    //else stays eating
            }
        }

        if (state_of_philosophers(philosphers, chopsticks, members) == -1) {
            cout << "Currently in deadlock state, in some time all chopsticks will be dropped and philosophers will go back to thinking" << endl;
            while (clock() - start_time < 1000) {
                //waiting time to reset
            }
            for (int i = 0; i < members; i++) {
                philosphers[i] = -1;
                chopsticks[i] = -1;
            }
            chopsticks[members] = -1;
        }
    }
    cout << "Amount of times went into deadlock state: " << deadlock_amount << endl;

    return 0;
}
