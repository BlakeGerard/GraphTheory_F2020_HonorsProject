# GraphTheory_F2020_HonorsProject
MATH-4673 Graph Theory, Fall 2020. Honors Contract Project to implement structures and algorithms from Graph Theory.

## Map Representation
We represent a graph as a map from edge labels to pairs of vertex labels. A map from vertex label to vertex degree is also maintained to improve vertex degree queries.

We accept an edge list as input. Isolated vertices can be added to the graph by specifying an individual vertex label within curly brackets. The following shows example input and the resulting internal structures:
```      
>> {{a, b}, {b, c}, {c, a}, {c, c}, {b, a}, {d}}

incidence_map = {
    0 -> (0, 1),    // 0 -> {a, b}
    1 -> (1, 2),    // 1 -> {b, c}
    2 -> (2, 0),    // 2 -> {c, a}
    3 -> (2, 2),    // 3 -> {c, c}
    4 -> (1, 0)     // 4 -> {b, a}
}

vertex_degree_map = {
    0 -> 3,         // a
    1 -> 3,         // b
    2 -> 4,         // c 
    3 -> 0          // d
}
```

## Available Algorithms
### 1. Cayley's Deletion-Contraction Algorithm for Counting Spanning Trees
Cayley's Deletion-Contraction algorithm is a recursive method for counting the number of spanning trees in a graph. Of course, there are better methods to compute the number of spanning trees, but the recursive method was chosen as a learning exercise.

```
>>  {{a, b}, {a, c}, {a, d}, {b, c}, {b, d}, {d, c}}    // K4

Graph *g = new Graph();
parser(g).parse();
unsigned int spanning_trees = cayley_deletion_contraction(g);
std::cout << spanning_trees;

>> 16
```

## Design Challenges
The first attempt at graph implementation relied too heavily on object representation. Edges and Vertices were each classes with members such as ```degree```, ```weight```, and ```color```. In this formulation, it seemed natural that each Vertex should store references to adjacent vertices and incident edges, while edges stored references to the vertices at their ends. One can imagine the severe redundancy in this design, and how it turns a simple operation such as edge deletion into a laborious search through multiple data structures to remove any reference to that edge object in the program. Furthermore, the size of the Graph object itself, which maintained a map from edge _objects_ to pairs of _references_ to vertex objects, added unecessary overhead to graph copying. This design was scrapped in favor of the much lighter-weight design presented above.

An interesting takeaway from this simple design is the idea that certain properties that one might assign to a graph, such as vertex color or edge weight, are not necessarily _intrinsic_ properties of the graph, but rather an external application of properties onto the graph. When more algorithms are added to this project, the Graph class can be slowly extended by adding light-weight mappings of properties onto vertices and edges when such properties are needed by an algorithm.

## Future Work
1. Allow users to add weights to edges. This would require a simple update to the parser to permit vertex pairs to have a third element to represent edge weight. One option for storing weights would be to extend the incidence_map to store a triple with the weight as the third entry. Another option would  
2. The next algorithm to implement will be Dijkstra's algorithm for finding shortest paths.
