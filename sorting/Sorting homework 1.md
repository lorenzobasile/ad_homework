## Sorting: homework 1

#### Exercise 2

![](/home/lorenzo/Desktop/ad_homework/sorting/Figure_1.png)

![](/home/lorenzo/Desktop/ad_homework/sorting/Figure_2.png)

#### Exercise 3



#### Exercise 4

The equation:
$$
T(n)=\begin{cases}\Theta(1) & \text{if n=32}\\ 3*T(\frac{n}{4})+\Theta(n^\frac{3}{2}) & \text{otherwise}\end{cases}
$$
can be solved using the following recursion tree:




$$
T(n)=\Theta(n^{\log_43})+cn^\frac{3}{2} \sum_{i=0}^{\log_4\frac{n}{32}}(\frac{3}{8})^i=\Theta(n^{\log_43})+Cn^\frac{3}{2}\implies T(n)\in \Theta(n^\frac{3}{2})
$$
