## 背景知识

生成模型：给定来自观测分布的样本$x$，生成模型的目标是学习建模其真实数据分布$p ( x )$吗，然后从近似模型中任意生成新的样本。此外，在一些情况下下，可以使用学习到的模型来评估观测或采样数据的可能性。

### ELBO

对于许多模态，我们可以认为我们所观察到的数据是由一个相关的看不见的潜变量表示或生成的，我们可以用随机变量$z$表示。

在生成建模中，我们通常寻求学习低维的潜在表征而不是高维的潜在表征。这是因为在没有强先验的情况下，试图学习一个比观察维度更高的表征是徒劳的。另一方面，学习低维隐变量也可以被看作是一种压缩的形式，可以潜在地发现描述观测的语义有意义的结构。

在数学上，我们可以将潜变量和我们观察到的数据想象成一个联合分布$p(x , z)$。回想一下生成式建模的一种方法，称为"似然法"，即学习一个模型，使所有观测x的似然$p ( x )$最大化。我们有两种方法可以操纵这个联合分布来恢复纯观测数据$p ( x )$的似然；我们可以显式地将潜变量$z$边缘化：

$$\begin{equation}
  p(x) = \int{p(x,z)dz}
\end{equation}$$

或者，我们也可以使用链式法则：

$$\begin{equation}
  p(x) = \frac{p(x,z)}{p(z|x)}
\end{equation}$$

直接计算和最大化似然$p ( x )$是困难的，因为它要么涉及到在方程1中整合出所有的潜变量$z$，这对于复杂的模型来说是困难的，要么涉及到在方程2中获得一个真实潜编码器$p ( z | x )$。然而，利用这两个方程，我们可以推导出一个称为证据下界(ELBO)的项，顾名思义，它是证据的下界。在这种情况下，证据被量化为观测数据的对数似然$\log{p(x)}$。然后，最大化ELBO成为优化潜变量模型的代理目标；在最好的情况下，当ELBO被强大的参数化和完美优化时，它就完全等价于证据。形式上，ELBO的方程为：

$$\begin{equation}
  \mathbb{E}_{q_\phi(z|x)}[
    \log{\frac{p(x,z)}{q_\phi(z|x)}}
  ]
\end{equation}$$

为了使与证据的关系显性化，我们可以从数学上写出：

$$\begin{equation}
  \log{p(x)} \ge
  \mathbb{E}_{q_\phi(z|x)}[
    \log{\frac{p(x,z)}{q_\phi(z|x)}}
  ]
\end{equation}$$

这里，$q_\phi(z|x)$是我们寻求优化的参数为$\phi$的近似变分分布。从直觉上讲，它可以被认为是一个可参数化的模型，用来估计给定观测值x在潜变量上的真实分布；换句话说，它寻求逼近真后验$p ( z | x )$。正如我们在探索变分自编码器时看到的那样，当我们通过调节参数$\phi$来增加下界以最大化ELBO时，我们可以获得用于建模真实数据分布的组件并从中采样，从而学习生成模型。就目前而言，让我们尝试更深入地探讨为什么ELBO是我们希望最大化的目标。

有两种方式推出公式(4):

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408131428755.png)

从第二种方式中，我们清楚地观察到证据等于ELBO加上近似后验$q \phi ( z | x )$和真实后验$p ( z | x )$之间的KL散度。事实上，正是这个KL散度项被第一种方式中Jensen不等式巧妙地去掉了。

首先，我们现在知道为什么ELBO确实是一个下界：证据与ELBO的差值是一个严格非负的KL项，因此ELBO的值永远不能超过证据。其次，我们探究为什么要寻求ELBO的最大化。在引入了我们想要建模的潜变量z之后，我们的目标是学习这个描述我们观测数据的潜在结构。换句话说，我们想要优化我们的变分后验$q\phi ( z | x )$的参数来精确匹配真实的后验分布$p ( z | x )$，这是通过最小化它们的KL散度(理想情况下为零)来实现的。遗憾的是，由于我们无法获得$p ( z | x )$分布的真值，直接最小化这个KL散度项是困难的。

然而，注意到我们的证据项$log p ( x)$总是关于$\phi$的常数，因为它是通过从联合分布$p( x , z)$中边际化出所有潜变量$z$而计算的，而不依赖于任何$\phi$。由于ELBO和KL散度项加总为常数，因此ELBO项关于$\phi$的任何最大化都必然引起KL散度项的等式最小化。因此，可以最大化ELBO作为学习如何完美建模真实潜在后验分布的代理；我们越优化ELBO，我们的近似后验就越接近真实后验。此外，ELBO一旦被训练，也可以用来估计观测或生成数据的似然，因为它被学习来近似模型证据$log p ( x )$。

### VAE

在变分自编码器( Variational Autoencoder，VAE )的默认形式中，我们直接最大化ELBO。这种方法是变分的，因为我们优化了由$\phi$参数化的一族潜在后验分布中的最佳$q_\phi ( z | x )$。它被称为自动编码器，因为它类似于传统的自动编码器模型，输入数据在经历了一个中间的瓶颈表示步骤后被训练来预测自己。为了明确这种联系，让我们进一步剖析ELBO项：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408131443217.png)

在这种情况下，我们学习一个中间瓶颈分布$q_\phi ( z | x )$，可以作为编码器处理；它将输入转换为可能的隐变量的分布。同时，我们学习一个确定性函数$p_\theta ( x | z )$将给定的隐向量z转换为观测x，这个观测x可以解释为一个解码器。

EBLO转换的最终结果中两项各有直观的描述：第一项从我们的变分分布中度量解码器的重构似然；这保证了学习到的分布是对原始数据可再生的有效隐变量进行建模。第二项度量了学习到的变分分布与对潜变量持有的先验信念的相似程度。最小化这个项鼓励编码器实际学习一个分布，而不是崩溃成狄拉克delta函数。因此，最大化ELBO等价于最大化其一次项和最小化其二次项。

VAE的一个显著特点是ELBO如何在参数φ和θ上联合优化。VAE的编码器通常被选为对角线协方差的多变量高斯建模，而先验通常被选为标准的多变量高斯：

$$\begin{equation}
  q_\phi(z|x) = \mathcal{N}(z;\mu_\phi(x), \sigma_\phi^2(x)I)
\end{equation}$$

$$\begin{equation}
  p(z) = \mathcal{N}(z;0,I)
\end{equation}$$

然后，ELBO的KL散度项可以解析计算，重构项可以用蒙特卡洛估计近似。我们的目标可以改写为：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408131524622.png)

其中，对于数据集中的每个观测x，从$q_\phi( z | x )$中采样隐变量$\{z^{(l)}\}^L_{l = 1}$(从隐变量采样，然后用解码器生成)。然而，在这个默认设置中出现了一个问题：我们计算损失的每个$z^{( l )}$都是由一个随机采样过程产生的，通常是不可微的。幸运的是，当$q_\phi( z | x )$被设计来建模某些分布，包括多元高斯分布时，这可以通过重新参数化技巧来解决。

重新参数化技巧将随机变量改写为噪声变量的确定性函数；这允许通过梯度下降对非随机项进行优化。例如，来自任意均值为$\mu$，方差为$\sigma^2$的正态分布的样本可以改写为：

$$
x = \mu + \sigma\epsilon,\quad \epsilon \sim \mathcal{N}(\epsilon;0,I)
$$

也就是说，任意高斯分布都可以理解为标准高斯(其中是一个样本)，其均值通过加法从零移动到目标均值，其方差被目标方差拉伸。因此，通过重新参数化技巧，从任意高斯分布中采样可以通过从标准高斯中采样，将结果按目标标准差缩放，并按目标均值移动来执行。

在VAE中，每个z被计算为输入x和辅助噪声变量的确定性函数

$$
z = \mu_\phi(x) + \sigma_phi(x)\odot\epsilon,
\quad \epsilon \sim \mathcal{N}(\epsilon;0,I)
$$

在这个z的重新参数化版本下，梯度可以根据需要通过$\phi$，以优化$\mu_\phi$和$\sigma_\phi$。因此，VAE利用再参数化技巧和蒙特卡洛估计联合优化$\phi$和$\theta$上的ELBO。

在训练一个VAE之后，生成新的数据可以通过直接从潜在空间$p ( z )$采样，然后通过解码器运行。当z的维数小于输入x的维数时，变分自编码器特别有趣，因为我们可能会学习紧凑的、有用的表示。此外，当学习到语义有意义的潜在空间时，可以在传递给解码器之前对潜在向量进行编辑，以更精确地控制生成的数据。

### 层次化VAE

层次变分自编码器( Hierarchical Variational Autoencoder，HVAE ) 是VAE在潜变量上扩展到多个层次的推广。在这种提法下，潜变量本身被解释为产生于其他更高层次、更抽象的潜变量。

而在一般的具有T个层次的HVAE中，每个隐变量都被允许对所有以前的隐变量进行条件化，在本文中我们关注一个特殊的情况，我们称之为马尔可夫HVAE ( MHVAE)。在MHVAE中，生成过程是一个马尔科夫链；也就是说，层级结构的每一个变迁都是马尔科夫的，其中每个隐变量$z^t$只对前一个隐变量$z^{t + 1}$进行解码。数学上，我们将马尔科夫HVAE的联合分布和后验表示为：

$$\begin{equation}
  p(x,z_{1:T}) = p(z_T)p_\theta(x|z_1)
  \prod^T_{t=2}{p_\theta(z_{t-1}|z_t)}
\end{equation}$$

$$\begin{equation}
  q_\phi(z_{1:T} | x) = q_\phi(z_1|x)
  \prod^T_{t=2}{q_\phi(z_{t}|z_{t-1})}
\end{equation}$$

EBLO 扩展为：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408131525461.png)

当我们研究变分扩散模型时，这个目标可以进一步分解为可解释的成分。


## 变分扩散模型

最简单的想法是将其简化为一个具有三个关键限制的马尔科夫分层变分自编码器：

- 潜在维度恰好等于数据维度
- 每个时间步的潜在编码器的结构没有被学习；它预先定义为线性高斯模型。换句话说，它是以前一时间步的输出为中心的高斯分布。
- 潜在编码器的高斯参数随时间变化，以至于最终时间步T的潜在编码器的分布是标准的高斯分布

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408140940213.png)


让我们对这些假设的含义进行扩展。

1. 由第一个假设，可以将真实数据样本和潜变量都表示为$x_t$，其中$t = 0$表示真实数据样本，$t \in [ 1 , T]$表示相应的以t为索引的隐变量。VDM后验与MHVAE后验相同，但现在可以改写为：

$$\begin{equation}
  q(x_{1:T}|x_0) = \prod^T_{t=1}{q(x_{t}|x_{t-1})}
\end{equation}$$

2. 由第二个假设，我们知道每个潜变量在编码器中的分布是以其先前的分层潜变量为中心的高斯。与马尔科夫HVAE一样，不学习每个时间步t的编码器结构；它被固定为线性高斯模型，其中的均值和标准差可以预先设置为超参数，或者学习为参数。我们将高斯编码器参数化，其均值$\mu_t(x_t)=\sqrt{\alpha_t}x_{t-1}$,方差$\Sigma_t(x_t)=( 1-\alpha_t)I$，其中系数的形式被选择使得隐变量的方差保持在相似的尺度；换句话说，编码过程是保方差的。注意，允许交替高斯参数化，并导致类似的推导。主要原因是，$\alpha_t$是一个(潜在可学习的)系数，可以随层次深度t变化，以实现灵活性。在数学上，编码器变迁表示为：

$$\begin{equation}
  q(x_t|x_{t-1})=\mathcal{N}(x_t;\sqrt{\alpha}x_{t-1},\sqrt{1-\alpha_t}I)
\end{equation}$$

1. 由第三个假设，我们知道$\alpha_t$是按照一个固定的或可学习的时间表演化的，使得最终的潜变量$p ( x_T )$的分布是标准的高斯分布。然后，更新马尔科夫HVAE的联合分布，将VDM的联合分布写为：

$$\begin{equation}
  p(x_{0:T}) = p(x1_T)
  \prod^T_{t=1}{p_\theta(x_{t-1}|x_t)}
\end{equation}$$


值得注意的是，我们的编码器分布$q ( x_t | x_{t-1} )$不再由$\phi$参数化，因为它们在每个时间步被完全建模为具有定义的均值和方差参数的高斯分布。因此，在VDM中，我们只对学习条件分布$p_\theta( x_{t-1} | x_t )$感兴趣，这样我们就可以模拟新的数据。优化VDM后，采样过程与从$p ( x_T )$中采样高斯噪声一样简单，迭代运行T步的去噪转移$p_\theta ( x_{t-1} | x_t )$，生成新的$x_0$。

与任何HVAE一样，VDM可以通过最大化ELBO来优化，可以推导出：


![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141032234.png)

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141032338.png)


1. 重构项，在给定第一步隐变量的情况下，预测原始数据样本的对数概率。这一术语也出现在普通德VAE中，并且可以进行类似的训练。
2. 先验匹配项；当最终的潜在分布与高斯先验匹配时，它被最小化。这一项不需要优化，因为它没有可训练的参数；进一步地，由于我们假定了足够大的T使得最终分布是高斯的，因此该项实际上变为零。
3. 一致性项；它从前向和后向两个过程努力使xt处的分布保持一致。也就是说，对于每一个中间时间步，从噪声图像中得到的去噪步骤应该与从干净图像中得到的相应去噪步骤相匹配；这在数学上通过KL散度得到了体现。

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141039484.png)

优化一个VDM的成本主要由第三项决定，因为我们必须在所有的时间步长t上进行优化。在这种推导下，ELBO的所有项都被计算为期望值，因此可以用蒙特卡洛估计来近似。然而，实际上使用我们刚推导出的条件来优化ELBO可能是次优的；由于一致性项在每个时间步上都被计算为两个随机变量$\{x_{t-1},x_{t + 1} \}$的期望值，因此其蒙特卡洛估计的方差有可能高于每个时间步仅使用一个随机变量估计的项。由于它是通过求和$T - 1$相容项来计算的，因此ELBO的最终估计值可能具有很大的方差

相反，我们尝试推导出一个ELBO的形式，其中每一项在一个时刻只作为一个随机变量的期望计算。关键是，我们可以将编码器转换改写为$q ( x_t | x_{t-1} ) = q( x_t | x_{t-1} , x0)$，其中由于马尔可夫性，额外的条件项不产生影响的。然后，根据贝叶斯法则，我们可以将每个变迁改写为：

$$\begin{equation}
q(x_t|x_{t-1},x_0) = \frac{q(x_{t-1}|x_t,x_0)q(x_t|x_0)}{q(x_{t-1}|x_0)}
\end{equation}$$

有了这个新的方程，我们可以重新尝试推导ELBO：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141106140.png)

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141106560.png)

因此，我们成功地推导出了ELBO的一个解释，即可以用较低的方差进行估计，因为每个项都是一次至多一个随机变量的期望。这个提法也有一个优雅的解释，这是在检查每个单独的术语时揭示的：

1. 重构项；与它在普通VAE的ELBO中的类似物一样，这个项可以用Monte Carlo估计来近似和优化。
2. 先验匹配项：最终噪声输入的分布与标准高斯先验的接近程度。它没有可训练的参数，在我们的假设下也等于零。
3. 去噪匹配项。我们学习期望的去噪转移步$p_\theta (x_{t - 1} | x_t )$作为易处理的、真实的去噪转移步$q( x_{t-1} | x_t , x_0)$的近似。$q( x_{t-1} | x_t , x_0)$过渡步可以作为一个真实信号，因为它定义了如何对含噪图像$x_t$进行去噪，并获得最终的、完全去噪的图像$x_0$。因此，当两个去噪步骤尽可能匹配时，这个项被最小化，这可以用它们的KL散度来衡量。

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141342151.png)

在ELBO的这一推导过程中，优化成本的大部分再次在于求和项，而求和项在重构项中占主导地位。然而，在任意复杂的Markovian HVAEs中，由于同时学习编码器的复杂性，每个KL散度项$D_{KL}( q ( x_{t-1} | x_t , x_0)‖p_\theta ( x_{t-1} | x_t ))$对任意后验都很难最小化，在VDM中，我们可以利用高斯转移假设使优化易于处理。由贝叶斯法则，我们有：

$$\begin{equation}
  q(x_{t-1}|x_t,x_0) = \frac{q(x_t|x_{t-1},x_0)q(x_{t-1}|x_0)}{q(x_{t}|x_0)}
\end{equation}$$

由于我们关于编码器转移的假设可以得到$q( x_t | x_{t-1} , x0) = q( x_t | x{t-1} ) = \mathcal{N} ( x_t ;\sqrt{\alpha_t}x_{t-1} , ( 1-\alpha_t )I)$，剩下的就是推导出$q ( x_t | x_0 )$和$q ( x_{t-1} | x_0 )$的形式。幸运的是，利用VDM的编码器转换是线性高斯模型的事实，这些也是可以处理的。回想一下，在重新参数化技巧下，样本$x_t \sim q( x_t | x_{t-1} )$可以改写为：

$$\begin{equation}
  x_t = \sqrt{\alpha_t}x_{t-1} + \sqrt{1-\alpha_t}\epsilon, \quad \epsilon \sim \mathcal{N}(\epsilon;0,I)
\end{equation}$$

类似地，样本$x_{t - 1} \in q ( x_{t-1} | x_{t-2} )$可以改写为：

$$\begin{equation}
  x_t = \sqrt{\alpha_{t-1}}x_{t-2} + \sqrt{1-\alpha_{t-1}}\epsilon, \quad \epsilon \sim \mathcal{N}(\epsilon;0,I)
\end{equation}$$

然后，通过反复应用再参数化技巧，可以递归地导出$q ( xt | x0 )$的形式。假设我们有2T个独立同分布德随机噪声变量${ \epsilon^*_t，\epsilon_t }^T_{t=0}\sim \mathcal{N}(\epsilon ; 0 , I)$那么，对于任意的样本$x_t \in q ( x_t | x_0 )$，我们可以将其改写为：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141357977.png)

因此，我们推导出$q ( x_t | x_0 )$的高斯形式。这一推导可以修改为同样可以得到描述$q ( x_{t-1} | x_0 )$的高斯参数化。现在，已知$q ( x_t | x_0 )$和$q ( x_{t-1} | x0 )$的形式，代入贝叶斯法则展开式即可计算出$q( x_{t-1} | x_t , x_0)$的形式：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141425001.png)

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141425724.png)

因此，我们已经证明，在每一步，$x_{t-1}\sim q( x_{t-1} | x_t , x_0)$都是正态分布的，均值$\mu_q( x_t , x_0)$是$x_t$和$x_0$的函数，方差$\Sigma_q ( t )$是$\alpha$系数的函数。这些$\alpha$系数是已知的，并且在每个时间步都是固定的；它们要么在被建模为超参数时被永久设置，要么被视为寻求对其进行建模的网络的当前推理输出。根据上面的结果，我们可以将方差方程改写为$\Sigma_q(t) = \sigma^2_q ( t ) I$。其中：

$$\begin{equation}
  \sigma^2_q ( t ) = \frac{(1-\alpha_t)(1 - \overline{\alpha}_{t-1})}{1-\overline{\alpha}_t}
\end{equation}$$

为了尽可能地将近似去噪变换$p_θ ( x_{t-1} | x_t )$与真值去噪变换$q( x_{t-1} | x_t , x0)$相匹配，我们也可以将其建模为高斯模型。此外，由于已知在每个时间步中所有的α项都被固定，我们可以立即构造近似去噪转换的方差也是$\Sigma q ( t ) = \sigma^2_q ( t ) I$。由于$p θ ( x_{t-1} | x_t )$不依赖于$x_0$，我们必须将其均值$\mu_\theta ( x_t , t)$参数化为$x_t$的函数。

两个高斯分布间的KL计算公式如下,d是维度：

$$\begin{equation}
  D_{KL}(
    \mathcal{N}(x;\mu_x,\Sigma_x) ||
    \mathcal{N}(y;\mu_y,\Sigma_y)
  )
  = \frac{1}{2}[
    \log{\frac{| \Sigma_y |}{| \Sigma_x |}}
    - d
    + tr(\Sigma_y^{-1}\Sigma_x)
    + (\mu_y - \mu_x)^T\Sigma_y^{-1}(\mu_y-\mu_x)
  ]
\end{equation}$$


我们可以设置两个高斯的方差精确匹配，优化KL散度项可以归结为最小化两个分布的均值之差：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141456858.png)

其中$\mu_q$已经有推导的结果，

$$\begin{equation}
  \mu_q(x_t,x_0) = \frac
  {
    \sqrt{\alpha_t}(1-\overline{\alpha}_{t-1})x_t
    +  \sqrt{\alpha_{t-1}}(1-\alpha_t)x_0
  }
  {1-\overline{\alpha}_t}
\end{equation}$$

由于$\mu_\theta( x_t , t)$也是对$x_t$的条件函数，因此我们可以将其设置为如下形式对$\mu_q( x_t , x_0)进行紧密匹配：

$$\begin{equation}
  \mu_\theta(x_t,t) = \frac
  {
    \sqrt{\alpha_t}(1-\overline{\alpha}_{t-1})x_t
    +  \sqrt{\alpha_{t-1}}(1-\alpha_t)\hat{x}_\theta(x_t,t)
  }
  {1-\overline{\alpha}_t}
\end{equation}$$

其中，$\hat{x}_θ ( x_t , t)$ 由一个神经网络参数化，该神经网络试图从含噪图像xt和时间索引t预测x0。然后，优化问题简化为：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408141509987.png)

因此，优化VDM可归结为学习一个神经网络，从任意一个被噪声化的版本中预测原始的真实图像。此外，在所有噪声水平上最小化我们导出的ELBO目标的求和项可以通过在所有时间步上最小化期望来近似，然后可以使用随时间步的随机样本进行优化。

## 优化扩散模型参数

让我们研究如何联合学习VDM的噪声参数。一种潜在的方法是使用参数为$\eta$的神经网络$\hat{\alpha}_\eta ( t )$对$\alpha_t$建模。然而，这是很低效的，因为在每个时间步t必须执行多次推理。而缓存可以减轻这种计算成本，我们也可以推导出一种学习扩散噪声参数的替代方法。将方差方程代入推导每步目标，可得：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408150927876.png)

顾名思义，SNR表示原始信号与存在的噪声量之间的比值；信噪比越高代表信号越多，信噪比越低代表噪声越多。在扩散模型中，我们要求SNR随时间t单调递减；这形式化了扰动输入xt随时间变得越来越嘈杂的概念，直到它在t = T时与标准高斯一致。在对上述目标进行简化后，我们可以使用神经网络直接参数化每个时间步的SNR，并与扩散模型一起学习。由于SNR必须随时间单调递减，我们可以将其表示为：

$$\begin{equation}
  SNR(t) = \exp{(-\omega_\eta(t))}
\end{equation}$$

其中$\omega_\eta(t)$被建模为一个参数为η的单调递增神经网络。$-\omega_\eta(t)$导致单调递减的函数，而指数迫使结果项为正。结合$sigmoid = \frac{1}{1+e^{-x}}$我们还可以显式地得到以下形式：

$$\begin{equation}
  \frac{\overline{\alpha}_t}{1- \overline{\alpha}_t} = \exp{(-\omega_\eta(t))}
\end{equation}$$

$$\begin{equation}
  \overline{\alpha}_t = sigmoid(-\omega_\eta(t))
\end{equation}$$

$$\begin{equation}
  1 - \overline{\alpha}_t = sigmoid(\omega_\eta(t))
\end{equation}$$


## 三种等价解释

正如我们之前所证明的那样，变分扩散模型可以通过简单地学习一个神经网络来训练，从一个任意的噪声版本xt和它的时间指数t来预测原始自然图像x0。然而，x0有另外两种等价的参数化，这导致了对一个VDM的两种进一步的解释。首先，我们可以利用重新参数化技巧。在我们对$q ( x_t | x_0 )$形式的推导中，我们可以整理结果，将$x_0$视为变量，来得到以下结果：

$$\begin{equation}
  x_0 = \frac{x_t - \sqrt{1-\overline{\alpha}_t}\epsilon_0}{\sqrt{\overline{\alpha}_t}}
\end{equation}$$

将其代入我们之前推导的真去噪转移均值$\mu_q( x_t , x_0)$，我们可以重新推导为：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202408151012231.png)


这里学习从x0中确定xt的源噪声。因此，我们已经表明，通过预测原始图像x0来学习VDM等价于学习预测噪声；然而，在实证方面，一些工作发现预测噪声可以获得更好的性能

为了得到变分扩散模型的第三种常见解释，我们借助特威迪公式。在英语中，特威迪的公式指出，给定一个指数族分布的样本，它的真实均值可以通过样本的极大似然估计(也就是经验均值)加上一些包含估计得分的修正项来估计。在只有一个观测样本的情况下，经验均值只是样本本身。它常用于缓解样本偏差；如果观测样本全部位于潜在分布的一端，则负分数变大，并将样本的朴素极大似然估计修正为真实均值。

在数学上，对于一个高斯变量$z\sim \mathcal{N} ( z ; \mu_z , \Sigma_z)$，特威迪的公式为：

$$\mathbb{E}[\mu_z | z] = z + \Sigma_z\nabla_z\log{p(z)}$$

在这种情况下，我们应用它来预测给定样本的$x_t$的真实后验均值。由之前的结果：

$$q(x_t|x_0) = \mathcal{N}(x_t;\sqrt{\overline{\alpha}_t}x_0,(1-\overline{\alpha}_t)I)$$

然后，由特威迪的公式，我们有：

$$\begin{equation}
  \mathbb{E}[\mu_{x_t} | x_t] = x_t + (1-\overline{\alpha_t})\nabla_{x_t}\log{p(x_t)}
\end{equation}$$

根据特威迪公式，真实均值最佳估计定义为：

$$\begin{equation}
  \sqrt{\overline{\alpha}_t}x_0 = x_t + (1-\overline{\alpha_t})\nabla_{x_t}\log{p(x_t)}
\end{equation}$$

$$\begin{equation}
  x_0 =\frac{ x_t + (1-\overline{\alpha_t})\nabla_{x_t}\log{p(x_t)}}{\sqrt{\overline{\alpha}_t}}
\end{equation}$$

然后，我们可以将上述方程再次代入我们的$\mu_q( x_t , x_0)$并推导出新的形式：



这里，学习预测得分函数$\nabla_{x_t}\log{p(x_t)}$，它是对于任意的噪声水平t,$x_t$在数据空间的梯度，