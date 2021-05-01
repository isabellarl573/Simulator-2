# Simulator-2

Team Members

- Isabella Robert Llorens
- Cade Lueker
- Shuyun Wei
- Brian Song

---

## Design Document 

- Isabella Robert Llorens 
- Cade Lueker 

### Description
- This goal of this project is to show via a simulation on how operating systems algorithmically deal with deadlocks and resource allocation. The simulation used is the **the Dining Philosophers** problem where a random drop strategy is implemented against a delayed recovery from a deadlock.
- we represented the philosphers with an array of 5 elements (5 members or different philosophers), each index is an individual philosopher, the value is the state of the philosopher: -1 is idle/thinking; 0 is requesting to eat, has zero chopsticks; 1 is requesting to eat, has one chopstick; 2 is waiting to eat, has zero chopsticks (when not enough chopsticks are available); 3 is waiting to eat, has one chopstick (when not enough chopsticks are available); any number > 3 is eating/the time needed to eat
- In the chopsticks array, each index is the corresponding chopstick in reference to the table and philosophers, for nth philosopher, their corresponding chopsticks are n and n+1, except the last one, whose corresponding chopsticks are the last index and the first. The values correspond to the state of the chopstick: -1 if the chopstick is available/on the table; any positive number is the index of the philosopher who has it
- when a philosopher is in a state where it needs to eat it will make a request, they will then try to get the required chopsticks for them to be able to eat (only one per turn).
- What is a deadlock in this case and when do they occur?
  - Deadlocks are when a philosopher requests a chopstick but one isn't avaliable and none of the philosophers can eat they occur when all the philosophers are waiting to eat and are unable to grab the chopstick(s) required to eat
- Why do deadlocks happen?
    - If in a deadlock state, "Currently in deadlock state, in some time all chopsticks will be dropped and philosophers will go back to thinking/Idle state"
- 1000 units of time is waited before completely resetting the table (all philosophers drop their chopsticks and return to an idle state)
- For the variation we chose #1: an extra chopstick is available on the table, between Philosopher n and Philosopher 1, so n and 1 do not come into conflict over 0.5, because there is an extra at n+.5.
### the probability of eating for time t might vary among philosophers id i.  You may fix that and know it in advance, so your probabilities of dropping a chopstick could be dependent on that t as a function of i.
- Probability of wanting to eat from an idle state is: (20 > rand() % 100)
  - About 20%
- Probability on time to eat depends on id: time_to_eat = clock() + (rand() % ((i + 1) * 1000));
  - Actually affects probability: rand() % (i+1) * 1000
  - Meaning that the time will range to 1000 or 5000 depending on the philosopher id, meaning philosophers with higher id’s have a higher probability of having longer eating times
  - This affects the availability of chopsticks because the philosophers with higher ids can hold up the chopsticks making them unavailable for the surrounding - philosophers
  - This can be improved upon with the variation with the extra chopstick between philosopher 1 and 5, since 5 has the highest probability of having a longer eating time, and taking up 1’s chopstick, the extra chopstick between them will not lead to 5’s “longer” eating time to not affect 1’s chances at obtaining the required chopsticks

#### Expectations from design: 

- I expect that the simulation with an extra chopstick will have fewer deadlocks as there are more resources to go around. This would make sense in terms of computer program resource allocation aswell. If you have a computer with more ram you will get fewer freezes crashes. 

### the summary of results after running the simulation/Analysis
- A deadlock in the graph can be observed when all the “philosophers” (program) needs a “chopstick” (resource) but there isn’t one available, and they are all left waiting for a chopstick to be available. This means that their request has to be ignored and the program can not continue running unless there is a way to resolve that deadlock.
- Since the table is reset once a deadlock is reached, there are spikes downward from the waiting and requsting states, and all return to an idle state.
- There are two methods to reduce these chopstick deadlocks if you will. You can:
  - Add more resources and create a surplus of “chopsticks”
  - Or you can improve the algorithm that decides who gets a chopstick and when they receive it. 
- As we can see with the original graph versus the extra chopstick graph there is still a deadlock towards the beginning of the simulation but there is only one versus - several in the original graph.
- What is also interesting is the fact that in the extra chopstick simulation there are fewer people eating at one time but there are also fewer ups and downs in terms of people waiting. It seems that although there are more people (in an actual operating system this would be programs) there are enough chopsticks for them to “eat” whenever they request which we can see as the waiting dips as soon as a request is made. 


| Graphs                                                                                                                                                              |
|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Baseline experiment**                                                                                                                                             |
| ![graph1](~/Desktop/Simulator-2/graph1.png)                                                                                                                                               |
| Much less stable. Varying number of philosophers waiting. Multiple initial deadlocks                                                                                |
| **Extra chopstick**                                                                                                                                                 |
| ![graph2](~/Desktop/Simulator-2/graph2.png)                                                                                                                                               |
| Many initial deadlocks. Higher “resting” number of waiting philosophers. Much more stable and consistent. Every time a request is made it is addressed immediately  |
