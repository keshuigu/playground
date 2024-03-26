> [轻松理解 VQ-VAE：首个提出 codebook 机制的生成模型](https://zhuanlan.zhihu.com/p/633744455)

## 从 AE 到 VQ-VAE

Vector Quantisation: 向量量化

### AE

AE 包含一个编码器 $e$ 和一个解码器 $d$ 。在训练时，输入图像 $x$ 会被编码成一个较短的向量 $z$ ，再被解码回另一幅长得差不多的图像 $\hat{x}$。网络的学习目标是让重建出来的图像和原图像尽可能相似。

AE 编码器只能识别编码器生成的向量，不能够随机生成图片

### VAE

VAE 加入对后验分布的变分估计，使得 AE 中的 $z$ 可以成为一个分布。从而也就可以进行随机采样，从而生成随机图片。VAE 编码出来的向量是连续向量。如果把向量的某一维稍微改动，解码器还是认得这个向量，并且会生成一张和原向量对应图片差不多的图片。

### VQ-VAE

VQ-VAE 认为把图片编码成离散向量会更加自然。借鉴 NLP 中对于离散单词的处理方法，把每个输入映射到一个独一无二的连续变量上。在 NLP 中一般是词嵌入层。

将类似的嵌入层加入到 VQ-VAE 的解码器前。这个嵌入层在 VQ-VAE 里叫做嵌入空间，在后续文章中则被称作 codebook。

离散向量问题是不好采样。它和 AE 一样，只能很好地完成图像压缩，把图像变成一个短得多的向量，而不支持随机图像生成。VQ-VAE 和 AE 的唯一区别，就是 VQ-VAE 会编码出离散向量，而 AE 会编码出连续向量。

VQ-VAE 作者利用 VQ-VAE 能编码离散向量的特性，使用了一种特别的方法对 VQ-VAE 的离散编码空间采样。VQ-VAE 的作者之前设计了一种图像生成网络，叫做 PixelCNN。PixelCNN 能拟合一个离散的分布。比如对于图像，PixelCNN 能输出某个像素的某个颜色通道取 0~255 中某个值的概率分布。VQ-VAE 能把图像映射成一个「小图像」。我们可以把 PixelCNN 生成图像的方法搬过来，让 PixelCNN 学习生成「小图像」。这样，我们就可以用 PixelCNN 生成离散编码，再利用 VQ-VAE 的解码器把离散编码变成图像。

VQ-VAE 工作过程：

1. 训练 VQ-VAE 的编码器和解码器，使得 VQ-VAE 能把图像变成「小图像」，也能把「小图像」变回图像
2. 训练 PixelCNN，让它学习怎么生成「小图像」
3. 随机采样时，先用 PixelCNN 采样出「小图像」，再用 VQ-VAE 把「小图像」翻译成最终的生成图像

## VQ-VAE 设计细节

### 输出离散编码

![vq-vae](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202403261551293.png)

关联编码器输出与解码器输入：

假设嵌入空间已经训练完毕，对于编码器的每个输出向量 $z_e(x)$ ,找出它在嵌入空间里的最近邻 $z_q(x)$ ,把 $z_e(x)$ 替换成 $z_q(x)$ 作为解码器的输入

### 编码器和解码器的优化过程

由于 VQ-VAE 其实是一个 AE，误差函数里应该只有原图像和目标图像的重建误差。

$$L_{resconstruct} = \lVert x-decoder(z_q(x)) \Vert_2^2$$

该式中 $z_q(x)$ 是解码器的输入。从 $z_e(x)$ 到 $z_q(x)$ 是不可导的。

引入 straight-through estimator，前向传播和反向传播的计算可以不对应。基于这一技术，VQ-VAE 使用了一种叫做 $sg$ (stop gradient，停止梯度)的运算：

$$ sg(x)=\begin{cases}x \;(forward) \newline 0\;(backword) \end{cases} $$

也就是说，前向传播时，$sg$ 里的值不变；反向传播时，$sg$ 按值为 0 求导，即此次计算无梯度。
基于这种运算，我们可以设计一个把梯度从 $z_e(x)$ 复制到到 $z_q(x)$ 的误差：

$$L_{resconstruct} = \lVert x-decoder(z_e(x)+ sg(z_q(x)-z_e(x))) \Vert_2^2$$

前向传播时，拿解码器输入 $z_q(x)$ 算误差：

$$L_{resconstruct} = \lVert x-decoder(z_q(x)) \Vert_2^2$$

反向传播时，按下式求梯度，等价于把解码器的梯度全部传给 $z_e(x)$ 。

$$L_{resconstruct} = \lVert x-decoder(z_e(x)) \Vert_2^2$$

### 优化嵌入空间

嵌入空间的每一个向量应该能概括一类编码器输出的向量。因此，嵌入空间的向量应该和其对应编码器输出尽可能接近。

$$L_{e} = \lVert z_e(x)-z_q(x) \Vert_2^2$$

但 VQ-VAE 作者认为，编码器和嵌入向量的学习速度应该不一样快。于是，他们再次使用了停止梯度的技巧，把误差函数拆成了两部分。其中，$\beta$ 控制了编码器的相对学习速度。

$$L_{e} = \lVert sg(z_e(x))-z_q(x) \Vert_2^2 + \beta \lVert z_e(x)-sg(z_q(x)) \Vert_2^2$$

第一个误差来自字典学习算法里的经典算法 Vector Quantisation(VQ)，用于优化嵌入空间。第二个误差叫做专注误差，它用于约束编码器的输出，不让它跑到离嵌入空间里的向量太远的地方

VQ-VAE 的总体损失函数：

$$
\begin{align*}
    L_{resconstruct} &= \lVert x-decoder(z_e(x)+ sg(z_q(x)-z_e(x))) \Vert_2^2 \\ &+ \alpha\lVert sg(z_e(x))-z_q(x) \Vert_2^2 + \beta \lVert z_e(x)-sg(z_q(x)) \Vert_2^2
\end{align*}
$$

## 总结

VQ-VAE 最大的贡献是提供了一种图像压缩思路，把生成大图像的问题转换成了一个更简单的生成「小图像」的问题。图像压缩成离散向量时主要借助了嵌入空间，或者说"codebook"这一工具。这种解决问题的思路可以应用到所有图像生成类任务上，比如超分辨率、图像修复、图像去模糊等。所以近两年我们能看到很多使用了 codebook 的图像生成类工作。
