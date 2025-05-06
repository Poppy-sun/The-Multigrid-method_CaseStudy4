# Q2: Multi-Grid V-Cycle Solver 

## Requirements

* C compiler supporting C99 (e.g., `gcc`)
* `make`

## Build

```bash
make
```

This will produce the executable `vcycle_solver`.

## Usage

```bash
./vcycle_solver <n0> <numLevels> <nu1> <nu2> <tol> <maxCycles>
```

* `<n0>`: number of interior points on the finest grid (e.g., 127)
* `<numLevels>`: total multigrid levels (e.g., 5)
* `<nu1>`: number of pre-smoothing iterations
* `<nu2>`: number of post-smoothing iterations
* `<tol>`: residual tolerance for stopping (e.g., 1e-8)
* `<maxCycles>`: maximum number of V-cycles (e.g., 100)

### Example

```bash
./vcycle_solver 127 5 3 3 1e-8 100
```

# Q3:Multigrid Convergence Experiments 

This question has code to test multigrid performance  after building the solver.

## Build

```
make clean
make
```

## Experiment 1: Fixed Grid N=128, Varying Levels

#### Run:

```
make exp1
```

**Results:**

| Levels | Time (s) | Coarse Solves | Cycles to tol |
| ------ | -------- | ------------- | ------------- |
| 2      | 0.1009   | 100           | 100           |
| 3      | 0.0732   | 100           | 100           |
| 4      | 0.0458   | 63            | 63            |
| 5      | 0.0185   | 25            | 25            |
| 6      | 0.0176   | 24            | 24            |

**Plot:** see `Plots of experiments.mlx`.



## Experiment 2: Grid-Size Scaling

#### Run:

```
make exp2
```

Tests two schemes for `N = 16, 32, 64, 128, 256`:

- **2-level MG** → `out2_<N>.txt`, `res2_<N>.dat`
- **Full hierarchy** → `outmax_<N>.txt`, `resmax_<N>.dat`

**Results:**

| N    | Scheme  | Time (s) | Coarse Solves | Cycles to tol |
| ---- | ------- | -------- | ------------- | ------------- |
| 16   | 2-level | 0.0003   | 21            | 21            |
| 16   | full    | 0.0003   | 21            | 21            |
| 32   | 2-level | 0.0034   | 66            | 66            |
| 32   | full    | 0.0011   | 23            | 23            |
| 64   | 2-level | 0.0203   | 100           | 100           |
| 64   | full    | 0.0046   | 24            | 24            |
| 128  | 2-level | 0.0715   | 100           | 100           |
| 128  | full    | 0.0186   | 25            | 25            |
| 256  | 2-level | 0.1751   | 100           | 100           |
| 256  | full    | 0.0743   | 26            | 26            |

**Summary Plots:** included in `Plots of experiments.mlx`.

## Clean Up

```bash
make clean
```

