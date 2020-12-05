# GraphTheory_F2020_HonorsProject
MATH-4673 Graph Theory, Fall 2020. Honors Contract Project to implement structures and algorithms from Graph Theory.

## Map Representation
We represent a graph as a map from edge labels to pairs of vertex labels. We accept an edge list as input:
```      
{{a, b}, {b, c}, {c, a}, {c, c}, {b, a}}

Graph g = {
    0 -> (0, 1),
    1 -> (1, 2),
    2 -> (2, 0),
    3 -> (2, 2),
    4 -> (1, 0)
}
```

## Available Algorithms
### 1. Cayley's Deletion-Contraction Algorithm for Counting Spanning Trees
```
g = {{a, b}, {a, c}, {a, d}, {b, c}, {b, d}, {d, c}}    // K4
unsigned int spanning_trees = cayley_deletion_contraction(g);
std::cout << spanning_trees;
>> 16
```

## Dependencies
- Catch2: Unit testing {https://github.com/catchorg/Catch2}
