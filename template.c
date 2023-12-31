/**
 * Group ID - 28
 * Member 1 Name - Virendrasinh Mane 
 * Member 1 BITS ID - 2022A7PS1175P
 * Member 2 Name - Samrath Singh Khanuja
 * Member 2 BITS ID - 2022A7PS1171P
 * Member 3 Name - Harsh Raj
 * Member 3 BITS ID - 2022A7PS1179P
*/

// ---------------------------DO NOT MODIFY (Begin)------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Graph {
    int n; // Size of the graph
    int** adj; // Adjacency matrix
    char** station_names; // Array of station names
} Graph;

/**
 * This function has been pre-filled. It reads the input testcase 
 * and creates the Graph structure from it.
*/
Graph* create_graph(char input_file_path[]) {
    FILE* f = fopen(input_file_path, "r");
    Graph* g = (Graph*)malloc(sizeof(Graph));
    // Size of graph
    fscanf(f, "%d", &(g->n));
    // Names of stations
    g->station_names = (char**)malloc(g->n * sizeof(char*));
    for(int i = 0; i < g->n; i++) {
        g->station_names[i] = (char*)malloc(100 * sizeof(char));
        fscanf(f, "%s", g->station_names[i]);
    }
    // Adjacency matrix
    g->adj = (int**)malloc(g->n * sizeof(int*));
    for(int i = 0; i < g->n; i++) {
        g->adj[i] = calloc(g->n, sizeof(int));
    }
    int edges;
    fscanf(f, "%d", &edges);
    for(int i = 0; i < edges; i++) {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        g->adj[x][y] = 1;
        g->adj[y][x] = 1;
    }
    fclose(f);
    return g;
}
// ---------------------------DO NOT MODIFY (End)------------------------------

/**
 * Q.1 
 * Return the number of junctions.
*/
int find_junctions(Graph* g) {
    int junction = 0;

    for (int i = 0; i < g->n; i++) {
        int count = 0;
        for (int j = 0; j < g->n; j++) {
            if (g->adj[i][j] == 1) {
                count++;
            }
        }

        if (count >= 4) {
            junction++;
        }
    }

    return junction;
}

/**
 * Q.2
 * Return true if the tour specified in the question is possible for this 
 * graph, else return false.
 * Parameter SAME_STATION - If it is true, then question 2(a) must be solved. 
 * If false, then question 2(b) must be solved.
*/
bool sheldons_tour(Graph* g, bool SAME_STATION) {
    int len = g->n; //Number of nodes in the graph
    
    if(SAME_STATION == true){
        //First case involves checking whether the given graph is a Euler circuit
        //Return true if it is possible to find a euler curcuit , return false in any other
        //case
        bool flag = true; //Flag will be set to false and the function will return immediately
        //the moment a vertex having odd degree is found;
        for(int i = 0; i < len;i++){
            int tempDegree = 0;
            for(int j = 0; j < len;j++){
                if(g->adj[i][j] == 1){
                    tempDegree++;
                }
            }
            if(tempDegree%2 != 0){
                flag = false;
                return flag;
            }
        }
        return flag;
    }
    else{
        //A connected multigraph has an Euler path but not an Euler circuit if and only 
        //if it has exactly two vertices of odd degree.
        //Euler curcuit are subsets of euler paths.
        //For a given graph to be a euler curcuit but not a euler graph we need to have 
        //exactly two vertices having odd degrees.
        //Return true if an path which an euler path exclusively is found i.e exactly two 
        //odd degrees exist, false otherwise.
        int countOdd = 0;
        for (int i = 0; i < len; i++)
        {
            int tempDegree = 0;
            for (int j = 0; j < len; j++)
            {
                if(g->adj[i][j] == 1){
                    tempDegree++;
                }
            }
            if(tempDegree%2 != 0){
                countOdd++;
            }
            
        }
        if(countOdd == 2){
            return true;
        }
        return false;
        
    }
}

/**
 * Q.3
 * Return closure, an n * n matrix filled with 0s and 1s as required. 
*/
int** warshall(Graph* g) {
    // Do not modify or delete pre-filled code!
    int** closure = (int**)malloc(g->n * sizeof(int*));
    for(int i = 0; i < g->n; i++) {
        closure[i] = calloc(g->n, sizeof(int));
    }

    // Code goes here
    //Loop to assign closure = g->adj
    int len = g->n;
    for(int i = 0;i < len;i++){
        for(int j = 0; j < len;j++){
            closure[i][j] = g->adj[i][j];
        }
    }
        
    for(int k = 0; k < len;k++){
        for(int i = 0;i < len;i++){
            for(int j = 0;j < len;j++){
                int temp = (closure[i][j]) + (closure[i][k]*closure[k][j]);
                if(temp >= 1){
                    temp = 1;
                }
                closure[i][j] = temp;
            }
        }
    }
    
    return closure; // Do not modify
}

/**
 * Q.3
 * Return the number of impossible pairs.
*/
int find_impossible_pairs(Graph* g) {
    int** closure = warshall(g); // Do not modify
    int len = g->n;
    //As the train can travel in both directions on any given track,the graph is undirected
    //hence if a path from x->y exists,then it is guarenteed that a path from y->x will also
    //exist
    int count = 0;
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            printf("%d ",closure[i][j]);
        }
        printf("\n");
    }
    for(int i = 0;i < len;i++){
        for(int j = 0; j < len;j++){
            if(closure[i][j] == 0){
                count++;
            }
        }
    }
    return count/2;//To ensure that same path is not counted twice
    
}

/**
 * Q.4
 * Return the number of vital train tracks.
*/

int find_vital_train_tracks(Graph* g) {
    int len = g->n;
    int vital_tracks = 0;

    // Iterate over all edges in the graph
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (g->adj[i][j] == 1) {
                // Temporarily remove the edge (i, j)->To completely remove the edge 
                //you will have to set both (i,j) and (j,i) pairs to zero in the adj matrix
                g->adj[i][j] = 0;
                g->adj[j][i] = 0;

                // Check if the closure changes
                int** closure = warshall(g);
                int is_connected = closure[i][j];//You have to check just for the connectivity of
                //the removed edge as the other paths can then be traversed by traversing the 
                //path using the closure

                // Restore the edge
                g->adj[i][j] = 1;
                g->adj[j][i] = 1;

                // Count the vital track
                if (!is_connected) {
                    vital_tracks++;
                }

                // Free memory for closure
                for (int m = 0; m < len; m++) {
                    free(closure[m]);
                }
                free(closure);
            }
        }
    }

    return vital_tracks;
}


/**
 * Q.5
 * Return upgrades, an array of size n.
 * upgrades[i] should be 0 if railway station i gets a restaurant
 * upgrades[i] should be 1 if railway station i gets a maintenance depot
 * If it is not possible to upgrade, then return "-1" in the entire array
*/

int* upgrade_railway_stations(Graph* g) {
    int* upgrades = calloc(g->n, sizeof(int)); // 0: no upgrade, 1: restaurant, 2: maintenance depot
    
    // Checking if the graph is bipartite using BFS
    int* color = calloc(g->n, sizeof(int));

    // Assign temporary color as -1 to all structures
    for (int i = 0; i < g->n; i++) {
        color[i] = -1;
    }

    int queue[g->n];
    int front = 0, rear = -1;
    queue[++rear] = 0;
    color[0] = 0; // Assign the starting vertex a color

    while (front <= rear) {
        int current = queue[front++];

        for (int i = 0; i < g->n; i++) {
            if (g->adj[current][i] && color[i] == -1) {
                color[i] = 1 - color[current];
                queue[++rear] = i;

                if (rear == g->n - 1) {
                    rear = 0;
                }
            } else if (g->adj[current][i] && color[i] == color[current]) {
                // Graph is not bipartite, assign NULL to upgrades and return
                free(upgrades);
                free(color);
                return NULL;
            }
        }
    }

    // Assign upgrades based on the colors using if-else statement
    for (int i = 0; i < g->n; i++) {
        if (color[i] == 0) {
            upgrades[i] = 0;
        } else {
            upgrades[i] = 1;
        } // 0: no upgrade, 1: restaurant, 2: maintenance depot
    }

    free(color);
    return upgrades;
}
/**
 * Q.6
 * Return distance between X and Y
 * city_x is the index of X, city_y is the index of Y
*/
int distance(Graph* g, int city_x, int city_y) {
    
    //paths if transitive closure does not contain a path then return -1;
    int** warshallMatrix = warshall(g);
    //asthe cities passed as paramter are zero indexed 
    if(warshallMatrix[city_x][city_y] == 0){
        return -1;
        //It is impossible to travel between city_x and city_y if the transitive closure does not
        //contain 1 at their indices.
    }
    //check if a direct path exists between the two vertices
    if(g->adj[city_x][city_y] == 1){
        return 1;
    }
    int len = g->n;
    //can brute force to check all the possible path lengths 
    //Length of each path in track is 1
    //make a new warshall matrix this time calculating path length
    int** warshallNew = (int**)calloc(len, sizeof(int*));
    for (int i = 0; i < len; i++) {
        warshallNew[i] = (int*)calloc(len, sizeof(int));
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            warshallNew[i][j] = g->adj[i][j];
            if(warshallNew[i][j] == 0){
                warshallNew[i][j] = INT32_MAX;//->change made to show no path at length max;
            }
        }
        
    }
    
    for (int k = 0; k < len; k++) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            int temp = warshallNew[i][k] + warshallNew[k][j];
            if (temp < warshallNew[i][j] && temp >= 1) {
                warshallNew[i][j] = temp;
            }
        }
    }
}
    
    
    return warshallNew[city_x][city_y];

}

/**
 * Q.7
 * Return the index of any one possible railway capital in the network
*/
int railway_capital(Graph* g) {
    int len = g->n;
    int capital = 0;
    int minDistance = 99999999999;
    for(int i  = 0;i < len;i++){
        int tempDistance = 0;
        for(int j = 0; j < len;j++){
            if(i != j){
                tempDistance += distance(g,i,j);     
            }
            
        }

        if(tempDistance < minDistance){
            minDistance = tempDistance;
            capital = i;
            printf("%d ",minDistance);
        }
    }
    return capital;
}

/**
 * Helper function for Q.8
*/

bool maharaja_express_tour(Graph* g, int source, int current_city, int previous_city, int* visited) {
    visited[current_city] = 1;
   
    int len = g->n;
    for (int i = 0; i < len; i++) {
        if (g->adj[current_city][i] == 1) {
            if (!visited[i]) {
                if (maharaja_express_tour(g, source, i, current_city, visited)) {
                    return true;
                }
            } else if (i != previous_city && i == source) {
                // If we encounter a visited city (other than the previous city) and it is the source,
                // it indicates a cycle
                return true;
            }
        }
    }

    return false;
}


/**
 * Q.8 
 * Return true if it is possible to have a Maharaja Express tour 
 * starting from source city, else return false. 
*/
bool maharaja_express(Graph* g, int source) {
    int* visited = (int*)malloc(g->n * sizeof(int)); 
    for (int i = 0; i < g->n; i++) {
        visited[i] = 0;
    }

    // Call the helper function and pass the visited array
    return maharaja_express_tour(g,source,source,-1,visited);
    
}
int main() {
    char input_file_path[100] = "testcase_3.txt"; // Can be modified
    Graph* g = create_graph(input_file_path); // Do not modify
    
   
    for(int i = 0; i < g->n;i++){
        printf("%s",g->station_names[i]);
        bool check = maharaja_express(g,i);
        if(check == true){
            printf(": Possible\n");
        }
        else{
            printf(": Impossible\n");
        }
    }
 
        
       

}