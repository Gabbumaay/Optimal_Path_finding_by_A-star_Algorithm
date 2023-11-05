#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define Max_Cities 100

int N; // Number of Cities
double X[Max_Cities]; // Latitudes
double Y[Max_Cities]; // Longitudes
int  dist[Max_Cities][Max_Cities]; // Distance between cities
char city[Max_Cities][20]; // City names
int w;//weight for the heuristic


struct node {
    int value; // Identity number
    double g; // Cost from the start node
    double h; // Heuristic value
    double f; // f = g + h
    int hops; // Number of hops
    char name[20]; // City name
    struct node* parent;
};

typedef struct node Node;

Node* open_list[Max_Cities];
Node* closed_list[Max_Cities];

int open_list_size = 0;
int closed_list_size = 0;

Node* Create_Node(int vertex) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = vertex;
    new_node->g = 0;
    new_node->h = 0;
    new_node->f = 0;
    new_node->hops = 0;
    new_node->parent = NULL;
    return new_node;
}

double Heuristic(Node* current, Node* goal_node) {
    double d_lat = (X[current->value] - X[goal_node->value]) * M_PI / 180.0;
    double d_lon = (Y[current->value] - Y[goal_node->value]) * M_PI / 180.0;

    double lat1 = (X[current->value]) * M_PI / 180.0;
    double lat2 = (X[goal_node->value]) * M_PI / 180.0;

    double a = pow(sin(d_lat / 2), 2) + pow(sin(d_lon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371.0;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

double distance(Node* current, Node* neighbor) {
    double t=(double)1.6093*dist[current->value][neighbor->value];
    return t;
}

int Is_Openlist_Empty() {
    return open_list_size == 0;
}

Node* Get_Lowest_Node() {
    Node* lowest_node = open_list[0];
    int lowest_f = lowest_node->f;

    for (int i = 1; i < N; i++) {
        if (open_list[i] == NULL) {
            continue;
        } 
        else 
        if(w==1){
        if (open_list[i]->f < lowest_f || (open_list[i]->f == lowest_f && open_list[i]->hops < lowest_node->hops)) {
            lowest_f = open_list[i]->f;
            lowest_node = open_list[i];
          }
       }

        if(w==0){
            if(open_list[i]->f < lowest_f){
                lowest_f=open_list[i]->f;
                lowest_node = open_list[i];
            }
        }
    }


    return lowest_node;
}

void Add_To_Open(Node* node) {
    open_list[open_list_size] = node;
    open_list_size++;
}

void Add_To_Closed(Node* node) {
    closed_list[closed_list_size] = node;
    closed_list_size++;
}

void Remove_From_Openlist(Node* node) {
    int i = 0;
    while (open_list[i] != node) {
        i++;
    }
    for (; i < open_list_size - 1; i++) {
        open_list[i] = open_list[i + 1];
    }
    open_list[open_list_size - 1] = NULL;
    open_list_size--;
}

Node* A_Star_Search(Node* start_node, Node* goal_node) {
    int cost;
    open_list_size = 0;
    closed_list_size = 0;

    Add_To_Open(start_node);

    while (!Is_Openlist_Empty()) {
        Node* current = Get_Lowest_Node();

        if (current->value == goal_node->value) {
            return current;
        }
        Remove_From_Openlist(current);
        Add_To_Closed(current);

        for (int i = 0; i < N; i++) {
            if (dist[current->value][i] > 0) {
                Node* neighbor = Create_Node(i);

                if (neighbor->value == goal_node->value) {
                    neighbor->g = current->g + distance(current, neighbor);
                    neighbor->h = Heuristic(neighbor, goal_node);
                    neighbor->hops = current->hops + 1;
                    neighbor->f = neighbor->g + neighbor->h + w*neighbor->hops;
                    neighbor->parent = current;
                    return neighbor;
                }

                if (closed_list[i]) {
                    continue;
                }

                cost = current->g + distance(current, neighbor);

                if (!open_list[i] || cost < neighbor->g) {
                    neighbor->parent = current;
                    neighbor->g = cost;
                    neighbor->h = Heuristic(neighbor, goal_node);
                    neighbor->f = neighbor->g + neighbor->h + w*neighbor->hops;
                    neighbor->hops = current->hops + 1;

                    if (!open_list[i]) {
                        Add_To_Open(neighbor);
                    }
                }
            }
        }
    }

    return NULL;
}

int main() {
    
    printf("Enter 1 if you want less hop path else enter 0\n");
    scanf("%d",&w);

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    fscanf(file, "%d", &N);
    

    for (int i = 0; i < N; i++) {
        fscanf(file, "%s %lf %lf", city[i], &X[i], &Y[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(file, "%lf", &dist[i][j]);
        }
    }

    fclose(file);

    char start_city[20];
    char goal_city[20];

    for(int i=0;i<N;i++){
        printf("%s\n",city[i]);
    }

    printf("Enter the start city: ");
    scanf("%s", start_city);
    printf("Enter the goal city: ");
    scanf("%s", goal_city);

    int start_node = -1;
    int goal_node = -1;
    for (int i = 0; i < N; i++) {
        if (strcmp(city[i], start_city) == 0) {
            start_node = i;
        }
        if (strcmp(city[i], goal_city) == 0) {
            goal_node = i;
        }
    }

    if (start_node == -1) {
        printf("Start city not found.\n");
        printf("Enter correct spelling from the list above.\n");
        return 1;
    }

    if ( goal_node == -1) {
        printf(" Goal city not found.\n");
        printf("Enter correct spelling from the list above.\n");
        return 1;
    }

    Node* start = Create_Node(start_node);
    Node* goal = Create_Node(goal_node);

    Node* final = A_Star_Search(start, goal);

    if (final) {
        if(w){
        printf("Path based on Less-Hop Distance: ");
        }
        while (final != NULL) {
            printf("%s", city[final->value]);
            final = final->parent;
            if (final != NULL) {
                printf(" <<<---- ");
            }
        }
}
 else {
        printf("No path found.\n");
    }

}
