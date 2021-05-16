# Sturm sequences

A way to find real eigenvalues and eigenvectors of symmetric matrix.
(Your matrix should be entered into the file input_Matrix.txt with its dimensions).

## Example of usage:

```
Original matrix:
5x^0  4x^0  6x^0  9x^0  8x^0
4x^0  5x^0  4x^0  1x^0  2x^0
6x^0  4x^0  6x^0  5x^0  1x^0
9x^0  1x^0  5x^0  4x^0  2x^0
8x^0  2x^0  1x^0  2x^0  7x^0

Determinant of the characteristic equation:
-1x^5 + 27x^4 + -41x^3 + -1170x^2 + 3294x^1 + 2615x^0
Sturm sequence for:
-1.000000 27.000000 -41.000000 -1170.000000 3294.000000 2615.000000

-1.000000 27.000000 -41.000000 -1170.000000 3294.000000 2615.000000
-1.000000 21.600000 -24.600000 -468.000000 658.800000
-1.000000 8.328412 -1.077414 -61.577414
-1.000000 4.835399 1.820854
-1.000000 3.946381
-5.329255

5 distinct real eigenvalues: -6.383103; -0.649106; 4.142186; 6.519747; 23.370277;
1 eigenvector:
|-2.184|
|0.375|
|0.229|
|1.554|
|1    |
2 eigenvector:
|-0.555|
|-1.258|
|2.192|
|-1.443|
|1    |
3 eigenvector:
|-0.743|
|4.255|
|0.010|
|-2.716|
|1    |
4 eigenvector:
|0.171|
|-0.339|
|-0.747|
|-0.212|
|1    |
5 eigenvector:
|1.465|
|0.714|
|1.042|
|1.090|
|1    |
```
