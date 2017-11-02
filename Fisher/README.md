---
This article also be posted in My blog: www.vast-stars.com/2017/10/31/Fisher线性判别/
---

#Fisher

所有代码可以在 https://github.com/Vast-Stars/Algorithm/tree/master/Fisher 中看到。欢迎star

# 一. 算法介绍

这是Fisher在1936年提出的线性分类方法。对于二分类问题，训练集$D={ (\mathbf{x}_i,y_i),i=1,2\ldots n}$, 其中

 ${\mathbf{x}_i\in \mathscr{R^d}, y_i\in \lbrace 0,1\rbrace}$, 我们需要寻找一个权重向量$\mathbf{\omega}$ 和$\mathbf{\omega_0}$ 满足

$$
\mathbf{\omega^T}\mathbf{x}+\omega_0 
\begin{cases}
\lt 0  \\
\gt 0
\end{cases}
\Rightarrow y=
\begin{cases}
0  \\ 1
\end{cases}
$$

Fisher准则的思路是将d维空间中的点$\mathbf{x_i}$投影到一条直线（分类超平面的法线）上，通过适当地选择直线的方向$\mathbf{\omega}$，有可能找到能够最大限度地区分各类样本数据点的投影方向。选择直线方向的思路是：最大化投影后类间距离和类内距离比（希望样本点向所求直线投影后，不同类别之间的距离大，相同类别之间的距离小）

$$
\begin{align}
J_F(\mathbf{\omega} )&=\frac{\Vert{\mathbf{\omega}^T\mathbf{m_0}-\mathbf{\omega}^T\mathbf{m_1} }\Vert_2^2}{\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }\\
&=\frac{\mathbf{\omega}^T({\mathbf{m_0}-\mathbf{m_1} } ){ ( {\mathbf{m_0}-\mathbf{m_1} } ) }^T\mathbf{\omega} }{\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }\\
&=\frac{\mathbf{\omega}^T\mathbf{S}_{\mathbf{b} }\mathbf{\omega} } {\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }
\end{align}
$$

其中$\mathbf{m}_i$ 表示第$i$ 类的均值。$\mathbf{S}_w$ 为类内散度矩阵(within-class scatter matrix)，$\mathbf{S}_b$ 为类内散度矩阵(between-class scatter matrix) 

$$
\begin{align}
\mathbf{S}_w&=\mathbf{\Sigma_0}+\mathbf{\Sigma_1 } \\
&=\sum_{y=0}(\mathbf{x}-\mathbf{m_0} ){ (\mathbf{x}-\mathbf{m_0} )}^T+\sum_{y=1}(\mathbf{x}-\mathbf{m_1} ){ (\mathbf{x}-\mathbf{m_1} )}^T
\end{align}
$$

$$
\mathbf{S}_b=({\mathbf{m_0}-\mathbf{m_1} } ){ ({\mathbf{m_0}-\mathbf{m_1} } )}^T
$$

其中$\Sigma_i$ 表示第$i$类的协方差矩阵。显然$\mathbf{S}_w$ 和$\mathbf{S}_b$ 均为对称矩阵 

寻找$\mathbf{\omega}$使 $ J_F(\mathbf{\omega} )$ 最大，我们可以通过对$ J_F(\mathbf{\omega} )$ 求$\mathbf{\omega}$的偏导数并令其为$0$ 计算$\mathbf{\omega}$. 

注意 ${ (\mathbf{m_0}-\mathbf{m_1} )}^T\mathbf{\omega}$ 和 $\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega}$ 均为标量，且 $\frac{\partial(\mathbf{\omega}^T\mathbf{S}\mathbf{\omega} )}{\partial \mathbf{\omega} }=(\mathbf{S}+\mathbf{S}^T)\mathbf{\omega} $ .

$$
\begin{align}
\frac{\partial J_F(\mathbf{\omega} )}{\partial \mathbf{\omega} }&=\frac{\frac{\partial(\mathbf{\omega}^T\mathbf{S}_{\mathbf{b} }\mathbf{\omega} )}{\partial \mathbf{\omega} }\cdot\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega}-\mathbf{\omega}^T\mathbf{S}_{\mathbf{b} }\mathbf{\omega}\cdot\frac{\partial(\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} )}{\partial\mathbf{\omega}}}{ { (\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} )}^2}\\
&=\frac{2\mathbf{S}_{\mathbf{b} }\mathbf{\omega}\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega}-\mathbf{\omega}^T\mathbf{S}_{\mathbf{b} }\mathbf{\omega}\cdot 2\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }{ { (\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} )}^2}\\
&=2\cdot\frac{ (\mathbf{m_0}-\mathbf{m_1} ){ (\mathbf{m_0}-\mathbf{m_1} )}^T\mathbf{\omega}\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega}-\mathbf{\omega}^T(\mathbf{m_0}-\mathbf{m_1} ){ (\mathbf{m_0}-\mathbf{m_1} )}^T\mathbf{\omega}\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }{ { (\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} )}^2}\\
&=2\cdot\frac{ { (\mathbf{m_0}-\mathbf{m_1} )}^T\mathbf{\omega} }{\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }\cdot((\mathbf{m_0}-\mathbf{m_1} )-\frac{\mathbf{\omega}^T(\mathbf{m_0}-\mathbf{m_1} )\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }{\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} } )=0
\end{align}
$$

同时，由于$\frac{ { (\mathbf{m_0}-\mathbf{m_1} )}^T\mathbf{\omega} }{\mathbf{\omega}^T\mathbf{S}_{\mathbf{w} }\mathbf{\omega} }$ 为标量， 因此

$$
(\mathbf{m_0}-\mathbf{m_1} )-\lambda\cdot\mathbf{S}_{\mathbf{w} }\mathbf{\omega}=0
$$

其中$\lambda\in \mathscr{R}$ ,由于我们在做线性分类时，主要关心直线的方向，因此可取$\lambda=1 $，如果$\mathbf{S}_w $ 可逆（如果不可逆，则用伪逆），则 

$$
\mathbf{\omega}=\mathbf{S}_{\mathbf{w} }^{-1}(\mathbf{m_0}-\mathbf{m_1} )
$$

关于 $\omega_0$ 的选择，有以下几种常见方法：

- 我们知道当投影直线的方向确定后，d维空间中的点$\mathbf{x}_i$ 在直线的投影位置确定。为此，我们希望$y=0$ 类的样本点到$0$ 的距离与$y=1$ 类的样本点到$0$ 的距离越接近越好（当一条直线上两个点之间的距离确定，两点构成线段的中垂面为最好的分类超平面）。于是 $ -\sum_{y=0}(\mathbf{\omega^T}\mathbf{x}+\omega_0)=\sum_{y=1}(\mathbf{\omega^T}\mathbf{x}+\omega_0) $ 。再设$ n_0、n_1 $ 分别为两类样本数量，因此：

$$
\omega_0=-\frac{n_0\mathbf{\omega^T}\mathbf{m}_0+n_1\mathbf{\omega^T}\mathbf{m}_1}{n_0+n_1}
$$

- $\omega_0=-\frac{1}{2}(m_1+m_2)^T (S_\omega)^{-1}(m_1-m_2)-ln \frac{P(\omega_2)}{P(\omega_1)} $ 
- 暂无。待补充。



#  二. 测试

为了便于计算，统一规定如下：

- $X_{m\times n}$   $m$ 个$n$ 维样本以行向量构成矩阵X ； $Y_{m\times 1}$ 对应储存着样本的类别信息（也可视作label）
- 函数及关键语句附带说明。
- 注明数据来源。
- 统一采用[十倍交叉验证](https://zh.wikipedia.org/wiki/交叉驗證) 。
- F1=P*R/2(P+R) 

##  1 SONAR

数据集全称： **Connectionist Bench (Sonar, Mines vs. Rocks) Data Set** 

数据集来源： http://archive.ics.uci.edu/ml/machine-learning-databases/undocumented/connectionist-bench/sonar/sonar.all-data

数据说明： 见[UCI官网](http://archive.ics.uci.edu/ml/datasets/connectionist+bench+(sonar,+mines+vs.+rocks))

本地文件名：  `SONAR.csv` 

运行结果：

```matlab
accuracy =
    0.7286
    
precision =
    0.7019

recall =
    0.7374

f1 =
    0.3596
```

由于算法具有随机性，每次运行会有小范围波动。

##  2 USPS (3 && 8)

数据集全称： **Optical Recognition of Handwritten Digits Data Set**  

数据集来源： https://archive.ics.uci.edu/ml/machine-learning-databases/optdigits/optdigits.tes

https://archive.ics.uci.edu/ml/machine-learning-databases/optdigits/optdigits.tra

数据说明： 见[UCI官网](https://archive.ics.uci.edu/ml/datasets/Optical+Recognition+of+Handwritten+Digits)

本地文件名：  `optdigits.tes`   `optdigits.tra`

运行结果：

```matlab
accuracy =
    0.9938
    
precision =
    0.9982

recall =
    0.9895

f1 =
    0.4969
```

由于算法具有随机性，每次运行会有小范围波动。

##  3 IRIS (Iris-setosa && Iris-versicolor)

数据集全称：**Iris Data Set** 

数据集来源： https://archive.ics.uci.edu/ml/machine-learning-databases/iris/bezdekIris.data

数据说明： 见[UCI官网](https://archive.ics.uci.edu/ml/datasets/iris)

本地文件名：  `bezdekIris.data`

运行结果：

```matlab
accuracy =
    1
    
precision =
    1

recall =
    1

f1 =
    0.5
```

IRIS第一类和第二三类线性可分。Fisher收敛到正解。

----



# Reference

http://blog.leanote.com/post/directfly/Linear-Classification-Fisher-s-criterion-线性分类-Fisher准则

http://blog.csdn.net/htyang725/article/details/6571550

