#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#define max_cities 60
#define inf 99999.0

typedef struct {
    char name[50];
    double x, y;
} city;

typedef struct {
    double g_score;
    double f_score;
    city city;
} node;

double calculate_distance(city city1, city city2) {
    double dx = city1.x - city2.x;
    double dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

void astar(city cities[], int n, int start, int goal) {
    double g_scores[max_cities];
    double f_scores[max_cities];
    bool open_set[max_cities] = {false};
    bool closed_set[max_cities] = {false};
    int came_from[max_cities] = {-1};

    for (int i = 0; i < n; i++) {
        g_scores[i] = inf;
        f_scores[i] = inf;
    }

    g_scores[start] = 0;
    f_scores[start] = calculate_distance(cities[start], cities[goal]);

    while (true) {
        int current = -1;
        double min_f = inf;
        for (int i = 0; i < n; i++) {
            if (open_set[i] && f_scores[i] < min_f) {
                current = i;
                min_f = f_scores[i];
            }
        }

        if (current == -1) {
            printf("No path found.\n");
            return;
        }

        if (current == goal) {
            int path[max_cities];
            int path_length = 0;
            int node = goal;
            while (node != -1) {
                path[path_length++] = node;
                node = came_from[node];
            }

            printf("Shortest Path: %s", cities[path[path_length - 1]].name);
            for (int i = path_length - 2; i >= 0; i--) {
                printf(" -> %s", cities[path[i]].name);
            }
            printf("\n");
            printf("Distance: %.2f\n", g_scores[goal]);
            return;
        }

        open_set[current] = false;
        closed_set[current] = true;

        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (cities[current].name != cities[neighbor].name && !closed_set[neighbor]) {
                double tentative_g_score = g_scores[current] + calculate_distance(cities[current], cities[neighbor]);

                if (!open_set[neighbor] || tentative_g_score < g_scores[neighbor]) {
                    came_from[neighbor] = current;
                    g_scores[neighbor] = tentative_g_score;
                    f_scores[neighbor] = g_scores[neighbor] + calculate_distance(cities[neighbor], cities[goal]);
                    if (!open_set[neighbor]) {
                        open_set[neighbor] = true;
                    }
                }
            }
        }
    }
}

int main() {
    int n, start, goal;

    printf("Enter the number of cities (max 60): ");
    scanf("%d", &n);

    if (n < 2 || n > max_cities) {
        printf("Invalid number of cities.\n");
        return 1;
    }

    city cities[max_cities];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of City %d: ", i + 1);
        scanf("%s", cities[i].name);
        printf("Enter the x-coordinate of City %d: ", i + 1);
        scanf("%lf", &cities[i].x);
        printf("Enter the y-coordinate of City %d: ", i + 1);
        scanf("%lf", &cities[i].y);
    }

    double connectivity[max_cities][max_cities];

    printf("Enter distances between cities (0 if not directly connected):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                connectivity[i][j] = 0;
            } else {
                printf("Distance from %s to %s: ", cities[i].name, cities[j].name);
                scanf("%lf", &connectivity[i][j]);
            }
        }
    }

    char start_city[50];
    char goal_city[50];

    while (true) {
        printf("Enter the start city (or 'exit' to quit): ");
        scanf("%s", start_city);

        if (strcmp(start_city, "exit") == 0) {
            break;
        }

        printf("Enter the goal city: ");
        scanf("%s", goal_city);

        start = -1;
        goal = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(cities[i].name, start_city) == 0) {
                start = i;
            }
            if (strcmp(cities[i].name, goal_city) == 0) {
                goal = i;
            }
        }

        if (start == -1 || goal == -1) {
            printf("City not found.\n");
            continue;
        }

        astar(cities, n, start, goal);
    }

    return 0;
}
