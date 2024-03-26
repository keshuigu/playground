> [Taming Transformers for High-Resolution Image Synthesis](https://arxiv.org/abs/2012.09841):

## 概要

VQ-GAN 是一种利用向量量化(Vector Quantization, VQ) 和 Transformer 来生成高分辨率图像的模型，损失函数(loss function) 主要包括以下几部分：

1. 重建损失(Reconstruction Loss): 这部分损失用于衡量生成的图像与真实图像之间的差异，通常使用 L1 或 L2 范数，或者感知损失(Perceptual Loss)。
2. 量化损失(Quantization Loss): 这部分损失用于训练编码器(Encoder) 和码本(Codebook)，使得编码器的输出能够与码本中的离散编码尽可能接近，通常使用 L2 范数。
3. 对抗损失(Adversarial Loss): 这部分损失用于训练生成器(Generator)和判别器(Discriminator)，使得生成的图像能够欺骗判别器，通常使用 Hinge Loss。
4. Transformer Loss: 指 VQ-GAN 中用于生成压缩图像的 Transformer 模型的损失函数，使 Transformer 的输出尽可能地接近 VQ-GAN 的编码向量，从而实现高分辨率图像的合成。

VQGAN 的整体架构大致是将 VQVAE 的编码生成器从 pixelCNN 换成了 Transformer，并且在训练过程中使用 PatchGAN 的判别器加入对抗损失。

## 离散编码特征

这部分思想同 VQ-VAE，在 VQ-GAN 中，损失如下

$$ \mathcal{L}\_{VQ}(E,G,Z) = \lVert x-\hat{x} \Vert^2 + \lVert sg(z_e(x))-z_q(x) \Vert_2^2 + \beta \lVert sg(z_q(x))- z_e(x)\Vert_2^2 $$

除了重建过程使用的损失，VQ-GAN还加入了GAN中的对抗loss。对于判别器而言，其损失函数可以笼统的表示为

$$\mathcal{L}\_{VQ}(\{E,G,Z\},D)= [\log{D(x)}+\log(1-D(\hat{x}))]$$

总体目标：

$$ Q = \argmin\limits_{E,G,Z}\max\limits_{D}\mathbb{E}_{x\sim p(x)}[\mathcal{L}\_{VQ}(E,G,Z)+\lambda \mathcal{L}\_{VQ}(\{E,G,Z\},D)]$$

VQ-GAN使用的是基于图块的判别器：即判别器不为整幅图输出一个真或假的判断结果，而是把图像拆成若干图块，分别输出每个图块的判断结果，再对所有图块的判断结果取一个均值。

## 自回归式生成

VQ-GAN使用Transformer做离散编码的生成器。code的预测过程可以被视作自回归预测：当已有编码 $s_{\le i}$ 后，Transformer试图去学习预测下一个编码，即预测分布 $\prod_{i}{p(s_i|s_{\le i})}$ ，这也就可以表示为最大化对数似然分布：

$$ \mathcal{L}_{transformer} = \mathbb{E}_{x \sim p(x)}[-\log{p(s)}]$$
