# Simplex Algorithm

[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg?style=plastic)](https://github.com/Vast-Stars/Algorithm)[![Travis branch](https://img.shields.io/badge/Language-English-green.svg?style=plastic)](https://github.com/Vast-Stars/Algorithm/Simplex-algorithm/README.md)[![Travis branch](https://img.shields.io/badge/Language-%E4%B8%AD%E6%96%87-green.svg?style=plastic)](https://github.com/Vast-Stars/Algorithm/Simplex-algorithm/README_CN.md)



----

##  SimpleMthd.m  Instructions

```Matlab
function [X,Y]=SimpleMthd(C,A,b,N)
min f(X)=CX
St AX=b and X>=0
  A m*n;
  C 1*n;
  b m*1
  N 1*(n-m)
```

This function will draw Simplex Table every iteration.

## Find_Base.m  Instructions

```matlab
function [  ] = Find_Base(A,b)
  A m*n;
  b m*1
```

This function will display all combination of  Base vector and then judge whether it is a base feasible solution.

