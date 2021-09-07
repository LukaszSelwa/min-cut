# min-cut
Implementation in `c++` of an algorithm for the global min-cut problem based on the [paper](https://arxiv.org/abs/2008.02060) written by Paweł Gawrychowski, Shay Mozes, Oren Weimann. This program was prepared as a part of my bachelor thesis at Jagiellonian University.

## Repository structure
- `src` - main directory
  * `src/examples` - examples of undirected weighted graphs with spanning trees
  * `src/graph_generation` - functions for generating random weighted graphs
  * `src/graphs` - definitions of essential graph structures, and

    - `binarized_tree` - structure for converting tree to binary tree, centroid decomposition and finding interesting edges.

    - `gmw_structure` - structure proposed by Gawrychowski, Mozes, and Weimann for calculating the value of cuts 2-respecting given spanning tree and also for checking if given edge pair is cross or down interested

    - `hl_decomposition` - structure for heavy-light decomposition and finding interesting paths pairs

  * `main_algo` - main algorithm for finding min-cut
    - `gmw_algo` - procedure proposed by Gawrychowski, Mozes, and Weimann for finding a minimum cut which 1 or 2-respects given spanning tree

    - `heuristic_algo` - algorithm for finding minimum cut, generates a set of random spanning trees and find a minimum cut which 1 or 2-respects one of them (uses `gmw_algo`)

  * `monge_matrix_min` - algorithms for finding the minimum of Monge matrix as and partial Monge matrix

  * `naive_algo` - slow algorithm for the minimum problem cut with O(n^2 m^2) complexity

  * `range_search` - implementation of 2d spanning trees (some files are unused)

  * `spanning_trees_extractors`, `utils` - self describing directories

- `benchmark` - benchmarks comparing the heuristic algorithm for the min-cut problem with the naive one. 

- `tests` - unit tests for implemented structures
    * `tests/compare` - tests for verifying the correctness of the implemented heuristic algorithm


## Running locally
Running locally requires GNU C++ compiler, [google benchmark](https://github.com/google/benchmark) library as well as [google test](https://github.com/google/googletest) library.

### Commands

- running tests:
```shell
make run_tests
```

- running benchmarks:
```shell
make run_benchmark
```