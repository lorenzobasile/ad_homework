## Exercise 2

Considering the algorithm:

`def Ex2 ( A ) `

​	`D ← build ( A )` 

​	`while ¬ is_empty ( D ) `

​		`extract_min ( D )`

​	`endwhile`

` enddef`

If `build`, `is_empty` $\in$ $\Theta(1)$ and `extract_min` $\in$ $\Theta(|D|)$ and supposing that `extract_min` extracts the minimum from the array `D`, the execution time of `Ex2` is:
$$
T=\Theta(1)+\sum_{i=0}^{|D|}\Theta(1)+\Theta(i)=\Theta(1)+\sum_{i=0}^{|D|}c+d\cdot i=\Theta(1)+\Theta(|D|)+\Theta(|D|^2)=\Theta(|D|^2)
$$
If `build` $\in$ $\Theta(|A|)$, `is_empty` $\in$ $\Theta(1)$ and `extract_min` $\in$ $O(log(|D|))$:
$$
T=\Theta(|A|)+\sum_{i=0}^{|D|}\Theta(1)+O(log(i))=\Theta(|A|)+\sum_{i=0}^{|D|}c+d\cdot i=\Theta(|A|)+\Theta(|D|)+O(|D|log(|D|))=\Theta(|A|)+O(|D|log(|D|))
$$
