## 扩散模型原理

### 前向过程/扩散过程

扩散过程是指的对数据逐渐增加高斯噪音直至数据变成随机噪音的过程。

$$q(x_t|x_{t-1})=\mathcal{N}(x_t;\sqrt{1-\beta_t}x_{t-1},\beta_tI)$$

其中$\{\beta_t\}^{T}_{t=1}$为每一步所采用的方差，介于0 ~ 1 之间。通常情况下，越后面的step会采用更大的方差。在一个设计好的`variance schedule`下，如果扩散步数T足够大，那么最终得到的$x_T$就完全丢失了原始数据而变成了一个随机噪音。扩散过程的每一步都生成一个带噪音的数据，整个扩散过程也就是一个马尔卡夫链：

$$q(x_{1::T}|x_0) = \Pi^T_{t=1}{q(x_t|x_{t-1})}$$

扩散过程往往是固定的，即采用一个预先定义好的`variance schedule`，比如DDPM就采用一个线性的`variance schedule`。

扩散过程的一个重要特性是我们可以直接基于原始数据来对任意t步的$x_t$进行采样：$x_t \sim q(x_t|x_0)$。

定义$\alpha_t = 1 - \beta_t$和$\overline{\alpha}_t=\Pi^t_{i=1}{\alpha_i}$，通过重参数技巧（和VAE类似, 随机从标准高斯分布中采样，再将采样值作为噪声在数据中扩散），那么有：

$$\begin{aligned}
x_t &= \sqrt{\alpha_t}x_{t-1} + \sqrt{1-\alpha_t}\varepsilon_{t-1} \\
    &= \sqrt{\alpha_t}(\sqrt{\alpha_{t-1}}x_{t-2} + \sqrt{1-\alpha_{t-1}}\varepsilon_{t-2}) + \sqrt{1-\alpha_t}\varepsilon_{t-1} \\
    &= \sqrt{\alpha_t\alpha_{t-1}}x_{t-2} + \sqrt{\sqrt{\alpha_t-\alpha_t\alpha_{t-1}^2}+ \sqrt{1-\alpha_t}^2}\overline{\varepsilon}_{t-2}; 高斯分布合并 \mathcal{N}(0,\sigma_1^2I)和\mathcal{N}(0,\sigma_2^2I)相加等于新高斯分布\mathcal{N}(0,(\sigma_1^2 + \sigma_2^2)I)\\
    &= \sqrt{\alpha_t\alpha_{t-1}}x_{t-2} + \sqrt{1-\alpha_t\alpha_{t-1}}\overline{\varepsilon}_{t-2} \\
    &= \cdots \\
    &= \sqrt{\overline{\alpha}_t}x_{0} + \sqrt{1-\overline{\alpha}_t}\varepsilon
\end{aligned}$$

反重参数化后，我们得到:

$$q(x_t|x_{0})=\mathcal{N}(x_t;\sqrt{\overline{\alpha}_t}x_{0},(1-\overline{\alpha}_t)I)$$

1. 可以看到$x_t$可以看成原始数据$x_0$和随机噪音$\varepsilon$的线性组合，其中$\sqrt{\overline{\alpha}_t}$和$\sqrt{1-\overline{\alpha}_t}$为组合系数，它们的平方和等于1，可以称两者为`singal_rate`和`noise_rate`。
2. 可以基于$\overline{\alpha}_t$而不是$\beta_t$来定义`variance schedule`。这样处理更加直接，比如我们直接将$\overline{\alpha}_t$设定为一个接近0的值，那么就可以保证最终得到的$x_T$近似为一个随机噪音。

### 反向过程

扩散过程是将数据噪音化，那么反向过程就是一个去噪的过程，如果我们知道反向过程的每一步的真实分布$q(x_{t-1}|x_t)$，那么从一个随机噪音$x_T \sim \mathcal{N}(0,I)$开始，逐渐去噪就能生成一个真实的样本，所以反向过程也就是生成数据的过程。

估计分布$q(x_{t-1}|x_t)$需要用到整个训练样本，我们可以用神经网络来估计这些分布。这里，我们将反向过程也定义为一个马尔卡夫链，只不过它是由一系列用神经网络参数化的高斯分布来组成：

$$p_{\theta}(x_{0:T}) = p(X_T)\Pi^T_{t=1}{p_{\theta}(x_{t-1}|x_t)} \\
p(x_T) = \mathcal{N}(x_T;0,I)\\
p_{\theta}(x_{t-1}|x_t) = \mathcal{N}(x_{t-1};\mu_{\theta}(x_t,t),\Sigma_{\theta}(x_t,t))$$

分布是$q(x_{t-1}|x_t)$不可直接处理的

> 我的理解：在没有原始图像的情况下，没有办法对一个带噪音的图像去噪

但是加上条件$x_0$的后验分布$q(x_{t-1}|x_t,x_0)$却是可处理的，这里有:

$$q(x_{t-1}|x_t,x_0) = \mathcal{N}(x_{t-1};\widetilde{\mu}(x_t,x_0),\widetilde{\beta_t}I)$$

利用贝叶斯公式

$$q(x_{t-1}|x_t,x_0) = q(x_{t}|x_{t-1},x_0)\frac{q(x_{t-1}|x_0)}{q(x_{t}|x_0)}
$$

第一项与$x_0$无关（马尔可夫链性质），分式两项可以从前向过程得到。因此可以计算。

最终可以得到

$$
\widetilde{\beta_t} = \frac{1 - \overline{\alpha}_{t-1}}{1 - \overline{\alpha}_{t}}\beta_t \\
\widetilde{\mu}(x_t,x_0) = \frac{\sqrt{\alpha_t}(1- \overline{\alpha}_{t-1})}{1- \overline{\alpha}_{t}}x_t + \frac{\sqrt{\overline{\alpha}_{t-1}}\beta_t}{1- \overline{\alpha}_{t}}x_0
$$
可以看到方差是一个定量（扩散过程参数固定），而均值是一个依赖$x_0$和$x_t$
的函数。这个分布将会被用于推导扩散模型的优化目标。

### 优化目标

上面介绍了扩散模型的扩散过程和反向过程，现在我们来从另外一个角度来看扩散模型：如果我们把中间产生的变量看成隐变量的话，那么扩散模型其实是包含$T$个隐变量的隐变量模型，它可以看成是一个特殊的Hierarchical VAEs

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202407301352598.png)

相比VAE来说，扩散模型的隐变量是和原始数据同维度的，而且扩散过程是固定的。既然扩散模型是隐变量模型，那么我们可以就可以基于变分推断(评估两个分布差异最常用的方式是计算KL散度(相对熵))来得到variational lower bound（VLB，又称ELBO）作为最大化优化目标，这里有：

$$\begin{aligned}
\log{p_{\theta}(x_0)} &= \log{\int{p_{\theta}(x_{0:T})dx_{1:T}}}; x_0 是数据样本 \\
&=\log{\int{\frac{p_{\theta}(x_{0:T})q(x_{1:T}|x_0)}{q(x_{1:T}|x_0)}dx_{1:T}}} \\
&\ge \mathbb{E}_{q(x_{1:T}|x_0)}[\log{\frac{p_{\theta}(x_{0:T})}{q(x_{1:T}|x_0)}}]
\end{aligned}$$

则训练目标为：

$$
L = - L_{VLB} = \mathbb{E}_{q(x_{1:T}|x_0)}[-\log{\frac{p_{\theta}(x_{0:T})}{q(x_{1:T}|x_0)}}] = \mathbb{E}_{q(x_{1:T}|x_0)}[\log{\frac{q(x_{1:T}|x_0)}{p_{\theta}(x_{0:T})}}]
$$

最终得到：

$$
L = \underbrace{_{KL}(q(x_T|x_0) || p_\theta(x_T))}_{L_T} + \sum^T_{t=2}{\underbrace{\mathbb{E}_{q(x_t|x_0)}[D_{KL}(q(x_{t-1}|x_t,x_0) || p_\theta(x_{t-1}|x_t))]}_{L_{t-1}}} - \underbrace{\mathbb{E}_{q(x_1|x_0)}\log{p_\theta(x_0|x_1)}}_{L_0}
$$

1. $L0$可以看成原始数据重建，优化的是负对数似然，可以用估计的$\mathcal{N}(x_{0};\mu_{\theta}(x_1,1),\Sigma_{\theta}(x_1,1))$来构建一个离散化的decoder来计算。这一步将像素值范围归一化到[-1,-1]

2. $L_T$计算的是最后得到的噪音的分布和先验分布的KL散度，这个KL散度没有训练参数，近似为0。因为先验为$p(x_T)=\mathcal{N}(0,I)$,而扩散过程最后得到的随机噪音也近似为$\mathcal{N}(0,I)$；

3. $L_{t-1}$计算的是估计分布$p_\theta(x_{t-1}|x_t)$和真实后验分布$q(x_{t-1}|x_t,x_0)$的KL散度，这里希望我们估计的去噪过程和依赖真实数据的去噪过程近似一致；
     - DDPM对$p_\theta(x_{t-1}|x_t)$做了进一步的简化：采用固定的方差$\Sigma_\theta=\sigma^2_tI$,这里的$\sigma^2_t$可以设定为$\beta_t$或者$\widetilde{\beta}_t$（这其实是两个极端，分别是上限和下限，也可以采用可训练的方差
     - 则优化目标 $L_{t-1}$可以变换为：
     - $$L_{t-1}=\mathbb{E_{q(x_t|x_0)}[\frac{1}{2\sigma^2_t}\Vert \widetilde{\mu}_t(x_t,x_0)-\mu(x_t,t) \Vert^2]}$$
     -从上述公式来看，我们是希望网络学习到的均值和后验分布的均值一致。不过DDPM发现预测均值并不是最好的选择。由原来的预测均值而换成预测噪音效果更好

4. 最终优化目标：$L^{simple}_{t-1}=\mathbb{E}_{x_0,\epsilon \sim \mathcal{N}(0,I)}[\lVert \epsilon - \epsilon_\theta (\sqrt{\overline{\alpha}_t}x_0 + \sqrt{1 - \overline{\alpha}_t}\epsilon,t)\rVert^2_2]$，其中t在[1,T]范围内取值，取1是即$L_0$，因此简化后的优化目标中并没有1中的负对数似然

5. 虽然扩散模型背后的推导比较复杂，但是我们最终得到的优化目标非常简单，就是让网络预测的噪音和真实的噪音一致。DDPM的训练过程也非常简单，：随机选择一个训练样本->从1-T随机抽样一个t->随机产生噪音-计算当前所产生的带噪音数据->输入网络预测噪音->计算产生的噪音和预测的噪音的L2损失->计算梯度并更新网络。

6. 一旦训练完成，其采样过程也非常简单，我们从一个随机噪音开始，并用训练好的网络预测噪音，然后计算条件分布的均值，然后用均值加标准差乘以一个随机噪音，直至t=0完成新样本的生成（最后一步不加噪音）。