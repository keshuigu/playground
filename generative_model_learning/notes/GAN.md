> [论文原文](https://arxiv.org/abs/1406.2661)

## 模型结构

GAN通过一个对抗性过程来估计一个生成模型。GAN同时训练两个模型：
- $G(z;\theta_{g})$ ：捕捉数据的分布,目标是学习数据 $x$ 上的一个分布 $p_g$ ，做法：定义一个关于噪音的分布 $p_z(z)$ , 然后建立到数据空间上的映射G
- $D(x;\theta_{d})$ ：辨别模型，用于评估一个样本是从数据中得到的，还是由G生成的

难训练，不易收敛

## 算法

在训练中，最大化D分辨样本来自数据还是G的能力; 同时训练G以最小化 $\log{(1-D(G(z)))}$ , 即，使得D尽量犯错。总体而言，目标函数为：

$$\min\limits_{G}\max\limits_{D}V(D,G)=\mathbb{E}_{x \sim p_{data}(x)}[\log{D(x)}]+\mathbb{E}_{z \sim p_{z}(z)}[\log{(1-D(G(z)))}]$$

博弈论，minmax游戏，纳什均衡

![算法](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202403221647310.png)

## 理论结果

1. 目标函数存在全局最优解，当且仅当 $p_g=p_{data}$
2. 上述算法确实能求解目标函数

### 目标函数存在全局最优解

当G固定，最优的D是 $D_G^{*}(x)=\frac{p_{data}(x)}{p_{data}(x)+p_g(x)}$

证明：

![证明](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202403221718147.png)

定理1：C(G)取得全局最小值时当且仅当 $p_g=p_{data}$ ，最小值为 $-\log{4}$

![定理1证明](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202403221729944.png)

### 算法证明

假定算法每一步都能使得D达到给定G下的最优解，那么优化目标就是

$$\mathbb{E}_{x \sim p_{data}(x)}[\log{D_{G}^{*}(x)}]+\mathbb{E}_{x \sim p_{g}(x)}[\log{(1-D_{G}^{*}(x))}]$$

将 $V(G,D)$ 视为 $U(p_g,D)$ , 即一个作用在 $p_g$ 上的函数，代入到上面的目标中。可以得到 $U(p_g,D)$ 是一个关于 $p_g$ 的凸函数（目标其他项与 $p_g$ 无关），由于每一步D求解为最优，根据凸函数的上界函数仍然是凸函数，故整个函数是凸函数。故迭代会逐渐靠近全局最优解。


