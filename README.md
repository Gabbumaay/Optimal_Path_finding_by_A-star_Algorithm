# Optimal_Path_Finder

## Overview

**Optimal_Path_Finder** is a mini-application developed using the **A-star (A\*) algorithm**, a well-known form of best-first search that minimizes the total estimated solution cost. The A\* algorithm evaluates nodes by combining the cost to reach the node, `g(n)`, and the estimated cost to get from the node to the destination, `h(n)`:

**f(n) = g(n) + h(n)**

- **g(n)**: The cost to reach the node
- **h(n)**: The cost to get from the node to the destination

## Algorithm Explanation

A\* search is a strategy where we first try the node with the lowest value of `g(n) + h(n)`. This approach ensures that A\* search is both complete and optimal, provided that the heuristic function `h(n)` satisfies certain conditions.

### Conditions for Optimality: Admissibility and Consistency

For optimality, the heuristic `h(n)` must be admissible. An admissible heuristic never overestimates the cost to reach the goal. Since `g(n)` is the actual cost to reach `n` along the current path, and `f(n) = g(n) + h(n)`, it follows that `f(n)` never overestimates the cost of a solution along the current path through `n`.

_Admissible heuristics_ are optimistic because they assume the cost of solving the problem is less than it actually is. An example of an admissible heuristic is the straight-line distance `hSLD` used for getting to Bucharest. The straight-line distance is admissible because the shortest path between any two points is a straight line, which cannot be an overestimate.

The above figure shows the progress of an A\* tree search for Bucharest.

## Heuristics

**Manhattan Distance Heuristic**: Commonly used in grid-based pathfinding, such as in games or robotics. It calculates the sum of the horizontal and vertical distances from the current node to the goal node, assuming only orthogonal movements are allowed.

**Euclidean Distance Heuristic**: Used in situations where diagonal movements are allowed. It calculates the straight-line (Euclidean) distance between the current node and the goal node.

**Diagonal Distance Heuristic**: Used in grid-based environments where diagonal moves are allowed. It estimates the distance by considering both horizontal and vertical moves, as well as diagonal moves, using a combination of these distances.

**Octile Distance Heuristic**: A variation of the diagonal distance heuristic that assumes diagonal moves are more costly. It uses a weighted combination of horizontal, vertical, and diagonal distances, reflecting the higher cost of diagonal moves.

**Custom Heuristics**: In many cases, custom heuristics specific to the problem domain can be designed. These heuristics might take into account domain-specific knowledge and features to estimate the cost more accurately.

## Custom Heuristic and Input Data

The application uses a custom heuristic. Real-time data has been taken from the input file, and the distances are computed using the Haversine Formula.

_For more details, refer to this part of the book_: [Artificial Intelligence: A Modern Approach by Russell and Norvig](https://people.engr.tamu.edu/guni/csce421/files/AI_Russell_Norvig.pdf#page=111)

## Usage Instructions

1. Clone the GitHub repository and navigate to the project directory:
   ```
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name
   ```

2. Prepare `input.txt` file with the following format:
   - Number of cities
   - Coordinates (longitude and latitude) for each city
   - City names
   - Distance matrix for the cities

   Example:
   ```
   50
   New_York_City 40.7128 -74.0060
   Los_Angeles 34.0522 -118.2437
   Chicago 41.8781 -87.6298
   ...
   [Distance matrix follows]
   ```

   Note: An input file is already provided. If you want to change the cities or places, modify the latitude and longitude in the macro file in Excel and run it to generate real-time distances. Alternatively, you can manually change the distances in Excel and copy the data to the input file.

3. Compile and run the C program:
   ```
   gcc -o astar astar.c
   ./astar
   ```
   When prompted, enter the path to your `input.txt` file.

4. Choose routing option:
   - Enter `0` for Optimal Path (general route overview)
   - Enter `1` for HOP Path (optimal route with least visits)

Note: Ensure `input.txt` is correctly formatted and in the same directory as the program for smooth execution. If you've just cloned the repository, it should be in the project root directory.
