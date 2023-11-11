# DISCOASS
Disco assignment 2-1
Discrete Structures for Computer Science (CS F222)
Assignment - 1
First Semester 2023-2024

Date: 08/11/2023
Maximum Marks: 30

General Instructions:
This is a group assignment. You can only work with the members of your group, which has been submitted already
You must implement the following assignment using C language only.
In this assignment, you have to write a program that can solve certain problems related to concepts of relations and graph theory. A template file has been provided to you and you have to implement the functions as asked in the questions. 
Please refrain from plagiarizing the code. We may additionally run a plagiarism checker and if your code is found to be plagiarized then it will incur a strict penalty as per the EC.
We expect you to have a complete knowledge of whatever you have implemented in the assignment and your final scores will depend upon your ability to answer and explain questions in the viva as well.
In addition to the solution file, you will also need to submit a word document containing an explanation of your approach for each of the questions.

Problem Statement:
You are given a railway network, with tracks connecting distinct railway stations in various cities. All tracks are bi-directional, that is, a train can travel in both directions on any given track. Any pair of cities may be connected  by at most one track.
Implement functions to solve the following problems on this network:

Q.1 A railway station is called a junction if it is directly connected to at least 4 different stations by train tracks. Find the number of junctions in the network. //Done

Q.2 Sheldon is a train enthusiast and wants to travel every through single train track in the country! However, he also gets bored quickly, and does not want to travel through any track multiple times. Please help Sheldon find if the following tours of the country are possible or not:
A tour which starts at a particular station, goes through every track exactly once, and ends at the same station. 
A tour which starts at a particular station, goes through every track exactly once, and ends at some different station. 
Note: This question will only be tested on networks that are connected.

Q.3 Find the number of pairs of cities (x, y) such that it is impossible to travel between these two cities using one or more trains. Note that (x, y) and (y, x) are the same pair, do not count it twice! Hint: Use Warshall’s Algorithm to compute the transitive closure of the graph. //Done

Q.4 The Ministry of Railways is considering upgrading the train tracks, to reduce travel times for passengers. However, this requires the tracks to undergo maintenance, during which trains cannot run on the tracks and must be rerouted. But sometimes, there might not be any alternative route! This can cause some cities which were originally connected, to become disconnected. Let us call a train track vital, if its maintenance can cause some cities to become disconnected (that is, there is no alternative route for those cities that doesn’t pass through this track). 
As advisor to the Ministry, you have to find the number of vital train tracks in the network.

For example, in the network shown on the left, the following tracks are vital:
(B-D) as its removal disconnects cities C and E
(D-E) as its removal disconnects cities A and E
(D-F) as its removal disconnects cities A and F
The other tracks are not vital. For example, removal of the track (A-B) will still keep all cities connected, as the new route can be (A-C-B-D) for travel from A to D. You may verify that it is true for all such pairs of cities.

Second example: Here, the tracks (D-F) and (D-E) are vital. Note that track (A-C) is NOT vital, as its removal does not disconnect any cities that were connected previously. For example, since F and B were already disconnected, the removal of (A-C) has no impact.






Q.5 Now that the train tracks have been upgraded, it is time to upgrade the railway stations. There are two main demands - stations need restaurants for waiting passengers, and maintenance depots for servicing trains. However, due to space constraints, it is only possible to add one of these two upgrades to a station. Some stations will have restaurants while some will have maintenance depots. 
In such a scenario, it would be optimal to upgrade the railway stations in such a way that if two stations are connected by a train track, then one of the stations always has a restaurant and another always has a maintenance depot. This would mean that at the two ends of every train track, both upgrades are present. Find out if it is possible to upgrade the stations in a way that satisfies these constraints.
Note: This question will only be tested on networks that are connected.


For example, in the network shown on the left, a possible valid configuration of upgrades is:
Cities A, C, F get restaurants
Cities B, D, E get maintenance depots. 
In this case, every track would have one end having a restaurant and another having a maintenance depot.




Q.6 Let us define the distance between two cities as the minimum number of train tracks that must be traversed to travel between the cities. Given two cities X and Y, find the distance between them. If it is not possible to travel between the two cities, then the distance can be assumed to be -1. 

Q.7 The Ministry of Railways wants to crown a city as the Railway Capital of India! To become the railway capital, it must be as centrally located in the network as possible. The exact criteria chosen by the Ministry is that : the railway capital must have the minimum possible sum of distances from every other city in the network. (Distance is as defined in the previous question). Your task is to nominate a city as the railway capital. Note that there may be multiple valid nominations, in which case, you may choose any one of them. Note: This question will only be tested on networks that are connected. 


For example, in the network shown on the left, let us calculate the sum of distances for various cities:
City A = (1 + 2 + 1 + 1 + 2 + 3 + 4) = 14
City B = (1 + 1 + 2 + 2 + 2 + 3 + 3) = 14
City G = (1 + 1 + 2 + 2 + 3 + 4 + 5) = 18
And similarly for other cities. You will see that Cities A, B, C and D are possible nominees for the railway capital. Hence, any one of them is the correct answer.



Q.8 The Maharaja Express is a luxury tourist train run by the Indian Railways. It starts at a particular city (let’s call it the source city), travels to many different cities (and stays at each new city for one day so that tourists can explore) and finally ends its journey back at the source city. 
More formally, a tour of the Maharaja Express satisfies the following constraints:
It starts and ends in the same city. 
Each day (except for the final day), the train goes to a new city.
The train is not allowed to travel the same railway track twice.
Your task is to find out which cities in the Railway Network can be source cities for this tour. Note that there is no constraint on the length of the tour.


Coding Instructions:
The ZIP folder contains a “template.c” file as well as some test cases. These test cases are to help with testing and debugging your code. You are encouraged to make more test cases yourself, to ensure that your code is correct. The final code will be evaluated on a different set of test cases. The example test case outputs do not have a strict output format and are just to help you understand the problems. 
You have to write all of your code in the “template.c” file only. The file contains instructions to help you with the flow of the program. 
Do not modify the structure definition, function signatures or any pre-written code. You must code inside the functions only. Modifying the functions in any way will incur a strict penalty. Additionally, do not create your own functions. Do not create any global variables. However, you may call already created functions from anywhere. You may also #include more standard libraries if desired (although it is possible to solve the entire assignment with the libraries included in template.c). 
Please ensure that your code compiles successfully before submitting. Files that do not compile successfully will be awarded 0 marks. Similarly, the functions that give runtime errors/segmentation faults will be given 0 marks for the particular test case. Your code will be run using the GNU GCC compiler.
Please note that it is not required to come up with the most efficient algorithm for each question. That is, the time complexity of the algorithm is irrelevant to the marks awarded, as long as it can run in reasonable time for small inputs (such as networks containing 25 to 30 cities). It is more important that you understand your approach. You may be asked to explain your code in the viva. 


