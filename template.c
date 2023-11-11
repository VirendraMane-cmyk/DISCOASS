/**
 * Group ID - 
 * Member 1 Name - 
 * Member 1 BITS ID - 
 * Member 2 Name - 
 * Member 2 BITS ID - 
 * Member 3 Name - 
 * Member 3 BITS ID - 
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
bool checkGreaterThan4(int adj[], int n){
    int count = 0;
    for(int i = 0; i < n;i++){
        if(adj[i] == 1){
            count++;
        }
    }
    if(count >= 4){
        return true;
    }
    return false;
}
int find_junctions(Graph* g) {
    int junction = 0;
    //Graph representation is done using adjacency matrix 
    //What about the diagonal of the matrix? -> Lengths along the diagonal are represented 
    //infinity in adjacency matrix.
    //Junction if atleast 4 1's in the row
    for(int i  =  0; i < g->n;i++){
        if(checkGreaterThan4(g->adj[i],g->n) == true){
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

    }
    else{

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
    int* upgrades = calloc(g->n, sizeof(int)); // Do not modify
    
    // Code goes here

    return upgrades; // Do not modify
}

/**
 * Q.6
 * Return distance between X and Y
 * city_x is the index of X, city_y is the index of Y
*/
int distance(Graph* g, int city_x, int city_y) {
    
}

/**
 * Q.7
 * Return the index of any one possible railway capital in the network
*/
int railway_capital(Graph* g) {
    
}

/**
 * Helper function for Q.8
*/
bool maharaja_express_tour(Graph* g, int source, int current_city, int previous_city, int* visited) {
    
}

/**
 * Q.8 
 * Return true if it is possible to have a Maharaja Express tour 
 * starting from source city, else return false. 
*/
bool maharaja_express(Graph* g, int source) {
    int* visited = (int*)malloc(g->n * sizeof(int)); 
    for(int i = 0; i < g->n; i++) {
        visited[i] = 0;
    }
    // Hint: Call the helper function and pass the visited array created here.
}

int main() {
    char input_file_path[100] = "testcase_2.txt"; // Can be modified
    Graph* g = create_graph(input_file_path); // Do not modify
    
    // Code goes here
    int vital = find_vital_train_tracks(g);
    printf("%d ",vital);

    

    return 0;
}