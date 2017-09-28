# 单纯形算法

[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg?style=plastic)](https://github.com/Vast-Stars/Algorithm)[![Travis branch](https://img.shields.io/badge/Language-English-green.svg?style=plastic)](https://github.com/Vast-Stars/Algorithm/Simplex-algorithm/README.md)[![Travis branch](https://img.shields.io/badge/Language-%E4%B8%AD%E6%96%87-green.svg?style=plastic)](https://github.com/Vast-Stars/Algorithm/Simplex-algorithm/README_CN.md)



----



##SimpleMthd.m 说明

```Matlab
function [X,Y]=SimpleMthd(C,A,b,N)
min f(X)=CX
St AX=b and X>=0
  A m*n;
  C 1*n;
  b m*1
  N 1*(n-m)
```

这个函数会在每一步都画出单纯形表。详情见函数注释

## Find_Base.m 说明

```matlab
function [  ] = Find_Base(A,b)
  A m*n;
  b m*1
```

这个函数会枚举所有基向量组合，并判断是否可以作为基可行解。

