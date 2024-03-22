1. 最大化似然模型
2. 自动编码器 autoencoder：先将高维的原始数据映射到一个低维特征空间，然后从低维特征学习重建原始的数据。包含两部分：

    - encoder：将原始的高维数据映射到低维特征空间，这个特征维度一般比原始数据维度要小，这样就起到压缩或者降维的目的，这个低维特征也往往成为中间隐含特征
    - decoder：基于压缩后的低维特征来重建原始数据

    ![ae_struct](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/ae_strcut.png)

    $g_\phi$为encoder网络的映射函数， $f_\theta$为decoder网络的映射函数， 从而有 $x'=f_\theta(z)=f_\theta(g_\phi(x))$ ， $x'$ 即为重建的数据。我们的目标是希望重建的数据和原来的数据近似一致，那么AE的训练损失函数可以采用简单的MSE(均方误差)：

    $$L_{AE}(\theta,\phi)=\frac{1}{n}\sum_{i=1}^{n}(x^{(i)}-f_\theta(g_\phi(x^{(i)})))^2$$

    AE不需要对数据进行标注 => AE无监督，由于压缩后的特征能对原始数据进行重建，所以我们可以用AE的encoder对高维数据进行压缩，这和PCA非常类似，当然得到的隐含特征也可以用来做一些其它工作，比如相似性搜索等。

    变种：DAE，去噪自编码器。在训练过程中先对输入$x$进行一定的扰动。相比AE，DAE重建难度增加
3. [变分推断](https://zhuanlan.zhihu.com/p/118377754)：用一些已知统计量推断另一些统计量

    $$p(z|x)=\frac{p(x|z)p(z)}{p(x)}=\frac{p(x|z)p(z)}{\int{p(x|z)p(z)dz}}$$

    目标是计算 $p(z|x)$ ，由于 $p(x)$ 未知，替换成积分。

    办法：神经网络，$x$作为输入， $z$ 的统计量作为输出，因为我们把一个推断问题转化为了一个优化问题，而一个优化问题，可以看作是一个变分问题

    说明： $p(z|x)$ 是后验，需要计算， $p(z)$ 表示先验，是对事物原本的认知； $p(x|z)$ 表示似然，是接触到了新的知识（数据）； $p(x)$ 表示证据，是这个新的知识的可信程度。现在的情况就是，先验和似然已知，要计算后验，而我们难在了计算证据这一步上。

4. 变分自动编码器 -> variational autoencoder

    结构与AE类似，建模方面存在较大区别。本质上VAE是一种基于[变分推断](https://zhuanlan.zhihu.com/p/118377754)的概率模型，属于生成模型，无监督模型。在变分推断中，除了已知的数据（观测数据，训练数据）外还存在一个隐含变量，这里已知的数据集记为 $X=\{x^{(i)}\}_{i=1}^{N}$ 由 $N$ 个连续或者离散变量 $x$ 组成，而未观测的随机变量记为 $z$ ，那么数据的产生包含两个过程:

    1. 从一个先验分布 $p_\theta(z)$ 中采样一个 $z^{(i)}$
    2. 根据条件分布 $p_\theta(x|z)$ ，用 $z^{(i)}$ 生成 $x^{(i)}$

    $\theta$ 指的是分布的参数。我们希望找到一个参数
     $\theta^{*}$ 来最大化生成真实数据的概率

    $$\theta^{*}=\mathop{argmax}\limits_{\theta}(\prod_{i=1}^{n}p_{\theta}(x^{(i)})) \newline p_{\theta}(x^{(i)})=\int{p_{\theta}(x^{(i)}|z)p_{\theta}(z)dz}$$

    上述积分计算不现实：先验分布$p_{\theta}(z)$未知；如果分布复杂，对z穷举计算太耗时间。变分推断引入后验分布$p_\theta(z|x)$来联合建模，根据贝叶斯公式，后验分布为：

    $$p_\theta(z|x)=\frac{p_\theta(x|z)p_\theta(z)}{p_\theta(x)}$$

    ![vae_model_1](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/vae_model_1.png)

    实线代表我们想要得到的生成模型 $p_{\theta}(x|z)p_{\theta}(z)$ ，其中先验分布 $p_{\theta}(z)$ 往往事先定义，而 $p_{\theta}(x|z)$ 用一个网络学习。把 $z$ 看成隐含特征，那么这个网络可以看成一个**probabilistic decoder**。虚线代表的是对后验分布 $p_{\theta}(z|x)$ 的变分估计，记为 $q_{\phi}(z|x)$ ，它也可以用一个网络来学习，这个网络可以看成一个**probabilistic encoder**。最终目标是得到生成模型decoder，而encoder用于建模

    VAE优化目标： $q_\phi(z|x)$ 接近 $p_\theta(z|x)$ ,评估两个分布差异最常用的方式是计算[KL散度(相对熵)](https://zh.wikipedia.org/wiki/%E7%9B%B8%E5%AF%B9%E7%86%B5)

    $$ D_{KL}(q_\phi(z|x)||p_\theta(z|x))=\log{p_\theta(x)+D_{KL}(q_\phi(z|x)||p_\theta(z))}-\mathbb{E}_{z \sim q_\theta(z|x)}\log{p_\theta(x|z)} $$

    由于KL散度非负，下式成立，右侧为ELBO

    $$ \log{p_\theta(x)} > \mathbb{E}_{z \sim q_\theta(z|x)}\log{p_\theta(x|z)}- D_{KL}(q_\phi(z|x)||p_\theta(z)) $$

    ELBO取负就是VAE要最小化的训练目标：

    $$ L_{VAE}(\theta,\phi) = -\mathbb{E}_{z \sim q_\phi(z|x)}\log{p_\theta(x|z)} + D_{KL}(q_\phi(z|x)||p_\theta(z)) \newline \theta^{*},\phi^{*} = \mathop{argmin}\limits_{\theta,\phi}L_{VAE} $$

    步骤：

    3. 假设 $q_\phi(z|x)$ 为各分量独立的多元高斯分布，那么预测的就是高斯分布的均值和方差
    4. 计算多元高斯分布的KL散度
    5. 由于各分量独立，简化为先计算单独各分量的KL散度，然后求和

    一元正态分布的KL散度：

    $$ KL(\mathcal{N(\mu,\sigma^2)|| \mathcal(0,1)})=\frac{1}{2}(-\log{\sigma^2}+\sigma^2+\mu^2-1) $$

    综上，对于训练数据的一个样本,其KL散度项优化目标为：

    $$  D_{KL}(q_\phi(z|x^{(i)})||p_\theta(z))=\frac{1}{2}\sum_{j=0}^{n}(-\log{(\sigma^{(i)}_j)^2}+(\sigma^{(i)}_j)^2+(\mu^{(i)}_j)^2-1) $$

    重建误差： $-\mathbb{E}_{z \sim q_{\phi}(z|x)} \log{p_{\theta}(x|z)}$ , $p_{\theta}(x|z)$ 是给定 $z$ 下生成真实数据 $x$ 的似然

    步骤：

    6. 蒙特卡洛方法估计数学期望
    7. 采样操作无法计算梯度，引入重参数化：直观上是从标准正态分布随机采样一个样本，然后乘以encoder预测的标准差，再加上encoder预测的均值
    8. 假定 $p_\theta(x|z)$ 高斯分布，各分量独立。标准差假定为常量，均值由decoder预测得出 $\mu=f_\theta(z)$ 。重建误差其实就是均方误差
    9. 假定 $p_\theta(x|z)$ 伯努利分布，decoder预测概率值。重建误差是交叉熵

    综合两者：

    $$  L_{VAE}(\theta,\phi)=\frac{C}{L}\sum_{l=1}^{L}\sum_{d}^{D}(x_d^{(i)}-(f_\theta(z^{(i,l)})_d)^2) +\frac{1}{2}\sum_{j=0}^{n}(-\log{(\sigma^{(i)}_j)^2}+(\sigma^{(i)}_j)^2+(\mu^{(i)}_j)^2-1) $$

5. VAE结构图

    ![alt text](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/vae_struct.png)


> 图片来源：[生成模型之VAE](https://zhuanlan.zhihu.com/p/452743042)、[Auto-Encoding Variational Bayes](https://arxiv.org/abs/1312.6114)
