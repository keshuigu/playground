> [论文原文](https://arxiv.org/abs/1701.07875)
> 
> [令人拍案叫绝的Wasserstein GAN](https://zhuanlan.zhihu.com/p/25071913)

## 文章概括

GAN：训练困难，生成器和判别器的loss无法指示训练进程，生成样本缺乏多样性

WAN：

1. 解决GAN训练不稳定问题，不需要平衡生成器和判别器的训练程度
2. 基本解决了collapse mode的问题，确保生成样本的多样性。collapse mode：模式坍塌，只生成一类满足真实分布的数据，例如真实数据可分为猫狗鱼等等，但是GAN只生成狗
3. 训练过程存在可以指示训练进程的值
4. 网络结构简单，可以用多层全连接层实现

WGAN对比GAN的流程改进：

1. 判别器最后一层去掉sigmod
2. 生成器和判别器的loss不取log
3. 每次更新判别器的参数之后把他们的绝对值截断到不超过一个固定常数c
4. 不使用基于动量的优化算法（实验得到，非理论）

## GAN的问题

GAN最小化的损失函数为：

$$\begin{equation} -\mathbb{E}_{x \sim p_{data}(x)}[\log{D(x)}]-\mathbb{E}_{z \sim p_{z}(z)}[\log{(1-D(G(z)))}] \end{equation}$$

对于生成器，有两种损失函数

$$\begin{equation}\mathbb{E}_{x \sim p_{g}(x)}[\log{(1-D(x))}]\end{equation}$$

$$\begin{equation}\mathbb{E}_{x \sim p_{g}(x)}[-\log{D(x)}]\end{equation}$$

### 公式(2)的问题

对于使用公式(2)形式的损失函数，原始GAN的问题是：**判别器越好，生成器梯度消失越严重**。根据原始GAN定义的判别器loss，我们可以得到最优判别器的形式，而在最优判别器下，我们可以把原始GAN定义的生成器loss等价变换为最小化 $p_{data}$ 和 $p_g$ 之间的JS散度。也即，越训练判别器，它越接近最优，最小化生成器的loss也就会越近似化最小化JS散度


如果两个分布之间越接近，它们的JS散度越小，我们通过优化JS散度就能将 $p_g$ 拉向 $p_{data}$ ，最终以假乱真。这个希望在两个分布有所重叠的时候是成立的，但是如果两个分布完全没有重叠的部分，或者它们重叠的部分可忽略，JS散度为 $\log{2}$

也就是说，只要 $p_g$ 和 $p_{data}$ 没有重叠部分或者重叠部分可以忽略，JS散度就是固定值 $\log{2}$ ，而这意味着梯度为0，而 $p_g$ 和 $p_{data}$ 不重叠的概率非常大

> $p_g$ 与 $p_{data}$ 的支撑集（support）是高维空间中的低维流形（manifold）时，$p_g$ 与 $p_{data}$ 重叠部分测度（measure）为0的概率为1

### 公式(3)的问题

**最小化第二种生成器loss，会等价于最小化一个不合理的距离衡量，导致两个问题，一是梯度不稳定，二是collapse mode**

将 $D^{*}$ 带入KL散度中，得到以下结果

$$ \begin{equation} KL(p_g||p_r)=\mathbb{E}_{x \sim p_g}[\log{[1-D^{*}(x)]}] - \mathbb{E}_{x \sim p_g}[\log{D^{*}(x)}] \end{equation} $$

由公式(1),(3),(4)可得到最小化目标的等价变形

$$ \mathbb{E}_{x \sim p_g}[-\log{D^{*}(x)}] = KL(p_g||p_r)- 2JS(p_r||p_g) + 2log2 + \mathbb{E}_{x \sim p_r}[\log{D^{*}(x)}]$$

注意到最后两项不依赖于生成器，最终得到最小化目标：

$$ KL(p_g||p_r)- 2JS(p_r||p_g) $$

这个等价最小化目标存在两个严重的问题。第一是它要同时最小化生成分布与真实分布的KL散度，却又要最大化两者的JS散度。JS在数值上会导致梯度不稳定。KL不对称导致对于不同的错误惩罚不一样，对于**生成器没能生成真实的样本**惩罚微小，而对于**生成器生成了不真实的样本**惩罚巨大，导致collapse mode

## 过渡方案

直观解释：对生成样本和真实样本加噪声，使得原本的两个低维流形弥散到整个高维空间，强行让它们产生不可忽略的重叠。而一旦存在重叠，JS散度就能真正发挥作用，此时如果两个分布越靠近，JS散度也会越小而不会一直是一个常数，于是梯度消失的问题就解决了。在训练过程中，我们可以对所加的噪声进行退火，慢慢减小其方差，到后面两个低维流形本体都已经有重叠时，就算把噪声完全拿掉，JS散度也能照样发挥作用，继续产生有意义的梯度把两个低维流形拉近，直到它们接近完全重合。

## Wasserstein距离到WGAN

Wasserstein距离（Earth-Mover距离）定义：

$$ \begin{equation}W(p_r,p_g) = \inf_{\gamma \sim \prod{(p_r, p_g)}}{\mathbb{E}_{(x,y) \sim \gamma}[||x-y||]}\end{equation} $$

解释：

1. $\prod{(p_r, p_g)}$ ：$p_r$ 和 $p_g$ 组合起来所有可能的联合分布的集合
2. 对于每一个可能的联合分布 $\gamma$ ,可以从中采样 $(x,y) \sim \gamma$ 得到一个真实样本x和一个生成样本y
3. 算出这对样本的距离 $||x-y||$ 。所以可以计算该联合分布 $\gamma$ 下样本对距离的期望值 $\mathbb{E}_{(x,y) \sim \gamma}[||x-y||]$ 。
4. 在所有可能的联合分布中能够对这个期望值取到的下界，就是Wasserstein距离

Wasserstein距离优点在于，即使两个分布没有重叠，它仍然能够反映它们的远近。

公式(5)直接替换loss是不行的，因为该公式没法直接求解，需要变形

$$ \begin{equation}W(p_r,p_g) = \frac{1}{K}\sup_{{||f||}_L \leq K}{\mathbb{E}_{x \sim p_r}[f(x)]-\mathbb{E}_{x \sim p_g}[f(x)]}\end{equation} $$


解释：

1. Lipschitz连续:它其实就是在一个连续函数 $f$ 上面额外施加了一个限制，要求存在一个常数 $K$ 使得定义域内的任意两个元素 $x_1$ 和 $x_2$ 都满足 $|f(x_1)-f(x_2)|\leq K|x_1-x_2|$ 。对于实数域，上面的要求等价于 $f$ 的导函数绝对值不超过 $K$ 。Lipschitz连续条件限制了一个连续函数的最大局部变动幅度。
2. 公式(6)要求函数 $f$ 的Lipschitz常数 ${||f||}_L$ 不超过 $K$ 的条件下，对所有可能满足条件的 $f$ 取到下面函数的上界，然后再除以 $K$ :

   $$\mathbb{E}_{x \sim p_r}[f(x)]-\mathbb{E}_{x \sim p_g}[f(x)] $$

3. 特别地，我们可以用一组参数 $w$ 来定义一系列可能的函数 $f_w$ ，此时求解公式(6)可以近似变成求解如下形式

   $$ \begin{equation}K\cdot W(p_r,p_g) = \max_{w:{||f_w||}_L \leq K}{\mathbb{E}_{x \sim p_r}[f_w(x)]-\mathbb{E}_{x \sim p_g}[f_w(x)]}\end{equation} $$

4. 神经网络拟合 $f_w$ ，不关心具体K是多少，只要不是无穷就行。做法：限制神经网络的所有参数不超过某个范围，此时关于输入样本的导数也不会超过某个范围，所以一定存在某个不知道的常数使得局部变动幅度不会超过它，Lipschitz连续条件得以满足

到此为止，可以构造一个含参数 $w$ ，最后一层不是非线性激活层的判别器网络 $f_w$ ，在限制 $w$ 不超过某个范围的条件下，使得下式尽可能取到最大。此时 $L$ 就会近似真实分布与生成分布之间的Wasserstein距离。注意原始GAN的判别器做的是真假二分类任务，所以最后一层是sigmoid，但是现在WGAN中的判别器做的是近似拟合Wasserstein距离，属于回归任务，所以要把最后一层的sigmoid拿掉。

$$\begin{equation}L = \mathbb{E}_{x \sim p_r}[f_w(x)]-\mathbb{E}_{x \sim p_g}[f_w(x)]\end{equation}$$


接下来生成器要近似地最小化Wasserstein距离，可以最小化 $L$ ，由于Wasserstein距离的优良性质，我们不需要担心生成器梯度消失的问题。再考虑到 $L$ 的第一项与生成器无关，就得到了WGAN的两个loss。

$$ \begin{equation}-\mathbb{E}_{x \sim p_g}[f_w(x)]\end{equation}$$

$$ \begin{equation}\mathbb{E}_{x \sim p_g}[f_w(x)]-\mathbb{E}_{x \sim p_r}[f_w(x)]\end{equation}$$

(9) 为生成器loss，(10)为判别器loss