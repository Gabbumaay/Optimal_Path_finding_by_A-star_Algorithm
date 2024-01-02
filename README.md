
## for code - refer "a.star.c"

It's regarding a mini-application named "Optimal_Path_Finder" developed with the help of A-star algorithm .
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

 Kindly follow the Instuctions....

1) Download the input file named  "input.txt" in the main.
2) while executing the code, it takes the file as an input.

// It possess following - no.of.cities, co-ordinates of the respective cities, distances matrix for the cities.

3) you will be prompted whether to go with the HOP path or not 
   Enter 0 / 1 
       if '0' is pressed.
           You will get the output of Rough Mapping, where to go and all.
       if '1' is pressed.
            You will get the HOP path (least visits) while travelling from starting_city to the Goal_city."
