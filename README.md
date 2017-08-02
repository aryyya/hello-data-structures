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
$ ./a.out data/mini --bubble-sort --print-results

Running 'Bubble Sort' on 25 element data set: COMPLETE
Duration: 22 microseconds (2.2e-05 seconds).
Results:
        Lynn    1
   Kimberley    1
       Erica    6
     Bradley   23
     Cassady   25
      Kareem   37
       Nehru   45
        Ivan   58
     Raymond   59
      Clarke   65
        Jane   80
      Tyrone   86
         Ira   86
      Keaton  119
      Ciaran  123
       Aimee  123
       Lacey  125
     Malachi  137
     Zachery  141
       Sacha  152
      Holmes  154
     Cecilia  160
       Lacey  166
      Burton  169
       Perry  197
```
