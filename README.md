# Recharge

A graph with vertices representing cities and edges representing roads connecting cities. The weights of the edges represent the distances between two cities (positive distances). An EV starts from city s and aims to reach city t. The EV has a range of k kilometers. Each city has a recharging station, and the goal is to find the minimum number of refueling stops needed to reach the destination, along with the corresponding route.

## Algorithm

1. Yen's algorithm to find possible path. ( https://en.wikipedia.org/wiki/Yen%27s_algorithm )
2. Filter possible paths, removing paths with hops longer than EV range,
3. Simulate travelling shortest remaining path, counting required stops

## Example

Input

```
g 0 1           // undirected, same costs
l 1 2 2
l 2 3 2
l 2 4 10
l 4 3 2
s 1             // start
e 4             // end
c 5             // range
```

Output

```
1 2 3 4  with 1 stops
```

