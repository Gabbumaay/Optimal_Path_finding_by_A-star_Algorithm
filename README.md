
It's regarding a mini-application named **Optimal_Path_Finder** developed with the help of **A-star algorithm** .
Most widely known form of best-first search is called A*-search minimizes the total estimated solution cost.
It evaluated nodes by combining g(n) & h(n)
  **f(n) = g(n) + h(n)**      g(n) - the cost to reach the node
                          h(n) - the cost to get from the node to the destination.
finally f(n) becomes the estimated cost of the cheapest solution through n.

   If we are trying to find the cheapest solution, a reasonable thing to try first is the node with the lowest value of g(n) + h(n). It turns out that this strategy is more than just reasonable: provided that the heuristic function h(n) satisfies certain conditions, A* search is both complete and optimal. The algorithm is identical to UNIFORM-COST-SEARCH except that A* uses g+h instead of g.

**Conditions for optimality: Admissibility and Consistency**
 The first condition we require for optimality is that h(n) be an admissible heuristic. An admissible heuristic is one that never overestimates the c9ost to reach the goal. Because g(n) is the actual cost to reach n along the current path, and f(n) = g(n) + h(n), we have as an immediate consequence that f(n) never overestimates the cost of a solution along the current path through n.
   Admissible heuristics are be nature optimistic because they think the cost of solving the problem is less than it actually is . An obvious example of an admissible heuristic is the straight-line distance hSLD that we used in getting to Bucharest. Straight-line distance is
admissible because the shortest path between any two points is a straight line, so the straight line cannot be an overestimate.

![Screenshot from 2024-05-07 09-25-12](https://github.com/Gabbumaay/Optimal_Path_finding_by_A-star_Algorithm/assets/120372287/9f65da41-42d2-43a7-bd45-4ffdb5fbe8ab)

In the above figure, we show the progress of an A* tree search for Bucharest.


Following are the Heuiristics.

**Manhattan Distance Heuristic**: The Manhattan distance heuristic is commonly used in grid-based pathfinding, such as in games or robotics. It calculates the sum of the horizontal and vertical distances from the current node to the goal node, assuming only orthogonal movements are allowed.

**Euclidean Distance Heuristic:** The Euclidean distance heuristic is used in situations where diagonal movements are allowed. It calculates the straight-line (Euclidean) distance between the current node and the goal node.

**Diagonal Distance Heuristic:** This heuristic is used in grid-based environments where diagonal moves are allowed. It estimates the distance by considering both horizontal and vertical moves, as well as diagonal moves, using a combination of these distances.

**Octile Distance Heuristic:** The octile distance heuristic is a variation of the diagonal distance heuristic that assumes diagonal moves are more costly. It uses a weighted combination of horizontal, vertical, and diagonal distances, reflecting the higher cost of diagonal moves.

**Custom Heuristics:** In many cases, custom heuristics specific to the problem domain can be designed. These heuristics might take into account domain-specific knowledge and features to estimate the cost more accurately.

-> It is made using a custom heuiristic.
Real time data had been taken in the input file and the distances are computed using Haversine Formula.



* _Input file had been generated using Google Maps API._


## Usage
To run this, kindly follow Readme_Group1.txt.

