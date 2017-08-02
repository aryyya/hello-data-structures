# hello-data-structures

Some casual experiments with sorting algorithms implemented in C++.

Use it to run different sorts on the same sets of data and determine which is faster.

## Compile

```
make
```

## Usage

```

Usage:

  $ ./a.out [data-path] [options]

Options:

  --help               Show help screen and quit.
  --print-results      Show ordered data after each sort.
  --aggregate-results  Show runtime chart after all sorts are complete.

  --bubble-sort        Execute the bubble sort algorithm.
  --insertion-sort     Execute the insertion sort algorithm.

Example:

  $ ./a.out data/mini --bubble-sort --insertion-sort --print-results --aggregate-results

```

## Example

```
$ ./a.out data/medium --bubble-sort --insertion-sort --aggregate-results

Running 'Bubble Sort' on 50000 element data set: COMPLETE
Duration: 64523313 µs (64.5233 seconds).

Running 'Insertion Sort' on 50000 element data set: COMPLETE
Duration: 20857770 µs (20.8578 seconds).

Results Aggregate:

     Bubble Sort:   64523313 µs    64.5233 sec
  Insertion Sort:   20857770 µs    20.8578 sec

```

