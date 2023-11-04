#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // Added for string operations

#define Max_Cities 100

int N; // Number of Cities
int X[Max_Cities]; // X coordinates of cities
int Y[Max_Cities]; // Y coordinates of cities
int dist[Max_Cities][Max_Cities]; // Distance between cities
char city[Max_Cities][20]; // City names

struct node {
    int value; // Identity number
    int g; // Cost from the start node
    int h; // Heuristic value
    int f; // f = g + h
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
    new_node->parent = NULL;
    return new_node;
}

int Heuristic(Node* current, Node* goal_node) {
    int h;
    h = abs(X[current->value] - X[goal_node->value]) + abs(Y[current->value] - Y[goal_node->value]);
    return h;
}

int distance(Node* current, Node* neighbor) {
    return dist[current->value][neighbor->value];
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
        } else if (open_list[i]->f < lowest_f) {
            lowest_f = open_list[i]->f;
            lowest_node = open_list[i];
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
                    neighbor->f = neighbor->g + neighbor->h;
                    neighbor->parent = current;
                    return neighbor;
                }

                if (closed_list[i]) {
                    continue;
                }

                cost= current->g + distance(current, neighbor);

                if (!open_list[i] || cost< neighbor->g) {
                    neighbor->parent = current;
                    neighbor->g = cost;
                    neighbor->h = Heuristic(neighbor, goal_node);
                    neighbor->f = neighbor->g + neighbor->h;

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
    printf("Enter the number of cities: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        printf("Enter city name: ");
        scanf("%s", city[i]);
        printf("Enter the X coordinate of the city: ");
        scanf("%d", &X[i]);
        printf("Enter the Y coordinate of the city: ");
        scanf("%d", &Y[i]);
    }

    printf("Enter the distance between the two cities\n");
    printf("If there is no path between those two cities, enter '-1'\n");

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            printf("Enter the distance between %s, %s: ", city[i], city[j]);
            scanf("%d", &dist[i][j]);
            dist[j][i] = dist[i][j];
        }
    }

    char start_city[20];
    char goal_city[20];
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

    if (start_node == -1 || goal_node == -1) {
        printf("Start or goal city not found.\n");
        return 1;
    }

    Node* start = Create_Node(start_node);
    Node* goal = Create_Node(goal_node);

    Node* final = A_Star_Search(start, goal);

    if (final) {
        printf("Shortest Path: ");
        while (final != NULL) {
            printf("%s", city[final->value]);
            final = final->parent;
            if (final != NULL) {
                printf(" -> ");
            }
        }
    } else {
        printf("No path found.");
    }

    return 0;
}
