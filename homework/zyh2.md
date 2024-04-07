# 作业2

俞磊 23S003111

## T1

写代码，共轭梯度法求解：$minf(x) = x_1 − x_2 + 2x_1^2 + 2x_1x_2 + x_2^2$

假设初始点 $x^{(0)}= (0,0)^T, \epsilon = 10^{−6}$

```julia
function func_1(x::Vector{Float64})
  return x[1] - x[2] + 2 * x[1]^2 + 2 * x[1] * x[2] + x[2]^2
end

function ∇func_1(x::Vector{Float64})
  return [1 + 4 * x[1] + 2 * x[2], -1 + 2 * x[1] + 2 * x[2]]
end

function nonlinear_conjugate_gradient(f, ∇f, x0, tol=1e-6, max_iter=1000)
  x = x0
  g = ∇f(x)
  d = -g
  g_norm = norm(g)

  for i in 1:max_iter
    if g_norm < tol
      break
    end
    α = line_search(f, ∇f, x, d)  # 线搜索来确定步长
    x = x + α * d
    g_new = ∇f(x)
    β = dot(g_new, g_new) / dot(g, g)  # Fletcher-Reeves 公式
    d = -g_new + β * d
    g = g_new
    g_norm = norm(g)
  end

  return x
end

function line_search(f, ∇f, x, d, α=1, β=0.5, σ=0.1)
  while f(x + α * d) > f(x) + σ * α * dot(∇f(x), d)
    α = β * α
  end
  return α
end


x0 = [0.0, 0.0]  # 初始解
x_opt = nonlinear_conjugate_gradient(func_1, ∇func_1, x0)

println("最优解: ", x_opt)
println("最优值: ", func_1(x_opt))
```

结果：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071537086.png)

## T2


写代码，用黄金分割法，斐波那契亚数列法，二分法，Dichotomous，Shubert-Piyavskii 分别求解问题
1. $ min f(x) = 2x^2 − x − 1 $ ,初始区间 $[a_0, b_0] = [−1,1]$ , 区间精度 $\delta = 0.06$

2. $min f(x) = 3x^2 − 21.6x − 1$, 初始区间$ [a_0, b_0] = [0,25] $ , 区间精度 $ \delta = 0.08$

```julia
function func_2_a(x)
  return 2 * x^2 - x - 1
end

function func_2_a_1(x)
  return -1 * (2 * x^2 - x - 1)
end


function func_2_b(x)
  return 3 * x^2 - 21.6 * x - 1
end

function func_2_b_1(x)
  return -1 * (3 * x^2 - 21.6 * x - 1)
end

function golden_section_search(f, a, b, tol=1e-6)
  ϕ = (sqrt(5) - 1) / 2  # 黄金比例
  c = b - ϕ * (b - a)
  d = a + ϕ * (b - a)
  while abs(b - a) > tol
    if f(c) < f(d)
      b = d
    else
      a = c
    end
    c = b - ϕ * (b - a)
    d = a + ϕ * (b - a)
  end
  return (a + b) / 2
end

function fibonacci_search(f, a, b, ε)
  fib = [1, 1]
  while fib[end] < (b - a) / ε
    push!(fib, fib[end-1] + fib[end])
  end
  t = length(fib)
  x1 = a + fib[t-2] / fib[t] * (b - a)
  x2 = a + fib[t-1] / fib[t] * (b - a)
  while (b - a > ε && t > 0)
    if f(x1) > f(x2)
      a = x1
      x1 = x2
      x2 = a + fib[t-1] / fib[t] * (b - a)
    elseif f(x1) < f(x2)
      b = x2
      x2 = x1
      x1 = a + fib[t-2] / fib[t] * (b - a)
    else
      a = x1
      b = x2
      x1 = a + fib[t-2] / fib[t] * (b - a)
      x2 = a + fib[t-1] / fib[t] * (b - a)
      t = t - 1
    end
  end
  return (a + b) / 2
end

function bisection_search(f, a, b, tol=1e-6)
  while abs(b - a) > tol
    c = (a + b) / 2
    if f(c - tol) < f(c + tol)
      b = c
    else
      a = c
    end
  end
  return (a + b) / 2
end



function shubert(f, a, b, L, crit=1e-04, nmax=1000)

  nf = 0
  x0 = (a + b) / 2.0
  y0 = f(x0)
  nf += 1
  xmax = x0
  ymax = y0
  fmax = y0 + L * (b - a) / 2.0

  X = zeros(nmax)
  Z = zeros(nmax)
  X[1] = b
  Z[1] = y0 + fmax
  X[2] = a
  Z[2] = y0 + fmax

  n = 2
  while (fmax - ymax > crit && n < nmax)
    xn = X[n]
    zn = Z[n]
    yn = f(xn)
    nf += 1
    if yn > ymax
      xmax = xn
      ymax = yn
    end
    zL = (zn + yn) / 2.0
    zR = zL
    xL = xn - (zn - yn) / 2.0 / L
    xR = xn + (zn - yn) / 2.0 / L

    i1 = 0
    i2 = 0
    if xL >= a && xL <= b
      i1 = 1
    end
    if xR >= a && xR <= b
      i2 = 1
    end

    if i1 == 1 && i2 == 0
      X[n] = xL
      Z[n] = zL
    elseif i1 == 0 && i2 == 1
      X[n] = xR
      Z[n] = zR
    elseif i1 == 1 && i2 == 1
      X[n] = xL
      Z[n] = zL
      X[n+1] = xR
      Z[n+1] = zR
      n += 1
    end
    Zo = sortperm(Z[1:n])
    Z[1:n] = Z[Zo]
    X[1:n] = X[Zo]
    fmax = Z[n]
  end
  return xmax, ymax, nf
end

a, b = -1.0, 1.0
δ = 0.06
println("对 func_2_a 使用 golden_section_search 方法的结果是：", golden_section_search(func_2_a, a, b, δ), "值:", func_2_a(golden_section_search(func_2_a, a, b, δ)))
println("对 func_2_a 使用 fibonacci_search 方法的结果是：", fibonacci_search(func_2_a, a, b, δ), "值:", func_2_a(fibonacci_search(func_2_a, a, b, δ)))
println("对 func_2_a 使用 bisection_search 方法的结果是：", bisection_search(func_2_a, a, b, δ), "值:", func_2_a(bisection_search(func_2_a, a, b, δ)))
println("对 func_2_a 使用 shubert 方法的结果是：", shubert(func_2_a_1, a, b, 1.5, δ))

# func_b
a, b = 0.0, 25.0
δ = 0.08
println("对 func_2_b 使用 golden_section_search 方法的结果是：", golden_section_search(func_2_b, a, b, δ), "值:", func_2_b(golden_section_search(func_2_b, a, b, δ)))
println("对 func_2_b 使用 fibonacci_search 方法的结果是：", fibonacci_search(func_2_b, a, b, δ), "值:", func_2_b(fibonacci_search(func_2_b, a, b, δ)))
println("对 func_2_b 使用 bisection_search 方法的结果是：", bisection_search(func_2_b, a, b, δ), "值:", func_2_b(bisection_search(func_2_b, a, b, δ)))
println("对 func_2_b 使用 shubert 方法的结果是：", shubert(func_2_b_1, a, b, 100, δ))
```

结果：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071540698.png)

## T3

写代码，用不精确一维搜索中的 Goldstein 方法，Goldstein-Price 法，Wolfe-Powell 方法来计算：

$min f(x + \lambda d)$ , 其中 $f(x) = 100(x_2 − x_1^2 )^2 + (1 − x_1 )^2$ ，取 $x^{(0)}= (−1,1)^T, d = (1,1)^T$

```julia
function func(x::Vector{Float64})
  return 100 * (x[2] - x[1]^2)^2 + (1 - x[1])^2
end

function ∇f(x::Vector{Float64})
  return [
    100 * 2 * (x[2] - x[1]^2) * (-2) * x[1] - 2(1 - x[1]),
    100 * 2 * (x[2] - x[1]^2)
  ]
end

function hessian(x)
  return [
    1200*x[1]^2-400*x[2]+2 400*x[1];
    400*x[1] 200
  ]
end

function goldstein_1(f, ∇f, x, λ, d, c1=0.1)
  φ0 = f(x)
  φd0 = ∇f(x)' * d
  φλ = f(x + λ * d)
  return φλ - φ0 <= c1 * λ * φd0
end

function goldstein_2(f, ∇f, x, λ, d, c1=0.1)
  φ0 = f(x)
  φd0 = ∇f(x)' * d # λd == s
  φλ = f(x + λ * d)
  return φλ - φ0 >= (1 - c1) * λ * φd0
end

#  c1 < σ < 1
function goldstein_2_2(f, ∇f, x, λ, d, σ=0.2)
  φ0 = f(x)
  φd0 = ∇f(x)' * d # λd == s
  φλ = f(x + λ * d)
  return φλ - φ0 >= σ * λ * φd0
end

function armijo(f, ∇f, x, λ, d, μ=5, σ=0.2)
  φ0 = f(x)
  φd0 = ∇f(x)' * d
  φλ = f(x + λ * d)
  return φλ - φ0 >= μ * σ * λ * φd0
end

function wolfe_powell(∇f, x, λ, d, σ=0.2)
  φd0 = ∇f(x)' * d
  φdλ = ∇f(x + λ * d)' * d
  return φdλ >= σ * φd0
end

function wolfe_powell_2(∇f, x, λ, d, σ=0.1)
  φd0 = ∇f(x)' * d
  φdλ = ∇f(x + λ * d)' * d
  return abs(φdλ) <= -σ * φd0
end

function inexact_method_with_goledstein(f, ∇f, x, d, λ, α=1.5, β=0.5, c=0.1)
  while true
    if !goldstein_1(f, ∇f, x, λ, d, c)
      λ *= β
      continue
    end
    if !goldstein_2(f, ∇f, x, λ, d, c)
      λ *= α
      continue
    end
    break
  end
  return λ
end

function inexact_method_with_goledstein_1(f, ∇f, x, d, λ, α=1.5, β=0.5)
  while true
    if !goldstein_1(f, ∇f, x, λ, d)
      λ *= β
      continue
    end
    if !goldstein_2_2(f, ∇f, x, λ, d)
      λ *= α
      continue
    end
    break
  end
  return λ
end


function inexact_method_with_armijo(f, ∇f, x, d, λ, α=1.5, β=0.5)
  while true
    if !goldstein_1(f, ∇f, x, λ, d)
      λ *= β
      continue
    end
    if !armijo(f, ∇f, x, λ, d)
      λ *= α
      continue
    end
    break
  end
  return λ
end

function inexact_method_with_wolfe_powell(f, ∇f, x, d, λ, α=1.5, β=0.5)
  while true
    if !goldstein_1(f, ∇f, x, λ, d)
      λ *= β
      continue
    end
    if !wolfe_powell(∇f, x, λ, d)
      λ *= α
      continue
    end
    break
  end
  return λ
end

function inexact_method_with_wolfe_powell_1(f, ∇f, x, d, λ, α=1.5, β=0.5, c=0.1)
  while true
    if !goldstein_1(f, ∇f, x, λ, d, c)
      λ *= β
      continue
    end
    if !wolfe_powell_2(∇f, x, λ, d)
      λ *= α
      continue
    end
    break
  end
  return λ
end


x = [-1.0, 1.0]
d = [1.0, 1.0]
λ = inexact_method_with_goledstein(func, ∇f, x, d, 1)
x = x + λ * d
println("goledstein λ ", λ, x, func(x))


x = [-1.0, 1.0]
d = [1.0, 1.0]
λ = inexact_method_with_goledstein_1(func, ∇f, x, d, 1)
x = x + λ * d
println("goledstein_1 λ ", λ, x, func(x))


x = [-1.0, 1.0]
d = [1.0, 1.0]
λ = inexact_method_with_armijo(func, ∇f, x, d, 1)
x = x + λ * d
println("armijo ", λ, x, func(x))


x = [-1.0, 1.0]
d = [1.0, 1.0]
λ = inexact_method_with_wolfe_powell(func, ∇f, x, d, 1)
x = x + λ * d
println("wolfe_powell ", λ, x, func(x))


x = [-1.0, 1.0]
d = [1.0, 1.0]
λ = inexact_method_with_wolfe_powell_1(func, ∇f, x, d, 1)
x = x + λ * d
println("wolfe_powell_1 λ ", λ, x, func(x))

```

结果：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071543421.png)

## T4

请计算下面凸函数在指定点的次微分

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071544112.png)


## T5

用 DFP 方法求解： $min10x_1^2 + x_2^2$ 取初始H矩阵为单位阵，即 $H^{(0)}= I, x^{(0)} = (1/10,1)^T$ ,做精确一维搜索

```julia
using LinearAlgebra
using ForwardDiff

function dfp(f, ∇f, hessian, x0; max_iter=1000, ϵ=1e-6)
  x = x0
  H = I
  G = hessian(x)
  for i in 1:max_iter
    ∇f_x = ∇f(x)
    if norm(∇f_x) < ϵ
      break
    end
    d = -H * ∇f_x
    # α = line_search(f, ∇f, x, d)
    α = -((∇f_x' * d) / (d' * G * d))
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    δ = x_new - x
    γ = ∇f_x_new - ∇f_x
    H = H + (δ * δ') / (δ' * γ) - (H * γ * γ' * H) / (γ' * H * γ)
    x = x_new
    G = hessian(x_new)
  end
  return x
end


f(x) = 10 * x[1]^2 + x[2]^2

∇f = x -> ForwardDiff.gradient(f, x)

hessian = x -> ForwardDiff.hessian(f, x)

x0 = [0.1, 1.0]
x = dfp(f, ∇f, hessian, x0)
println(x, " ", f(x))
```

结果：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071548906.png)

## T6

用 BFGS 法求解问题：$minx_1^2 + 4x_2^2 − 4x_1 − 8x_2$ 取初始H 矩阵为单位阵，即$H^{(0)}= I, x^{(0)} = (0,0)^T$ ,做精确一维搜索

```julia
using LinearAlgebra
using ForwardDiff

function bfgs(f, ∇f, hessian, x0; tol=1e-6, max_iter=1000)
  G = hessian(x0)
  H = I
  x = x0
  ∇f_x = ∇f(x)
  for i in 1:max_iter
    if norm(∇f_x) < tol
      return x
    end
    d = -H * ∇f_x
    # α = line_search(f, ∇f, x, d)
    α = -((∇f_x' * d) / (d' * G * d))
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    s = α * d
    y = ∇f_x_new - ∇f_x
    ρ = 1.0 / (y' * s)
    H = (I - ρ * s * y') * H * (I - ρ * y * s') + ρ * s * s'
    x = x_new
    ∇f_x = ∇f_x_new
    G = hessian(x_new)
  end
  return x
end

function line_search(f, ∇f, x, d; α=1, β=0.5, σ=0.1)
  while f(x + α * d) > f(x) + σ * α * ∇f(x)' * d
    α *= β
  end
  return α
end

f(x) = x[1]^2 + 4 * x[2]^2 - 4 * x[1] - 8 * x[2]


∇f = x -> ForwardDiff.gradient(f, x)

hessian = x -> ForwardDiff.hessian(f, x)


x0 = [0, 0]
x = bfgs(f, ∇f, hessian, x0)
println(x, " ", f(x))
```

结果：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071549266.png)

## T7

请用精确一维搜索来求解： $min x_1^2 + x_2^2 − x_1x_2 − 10x_1 − 4x_2 + 60$ 取 $x^{(0)} = (0,0)^T$

1. DFP 方法，$H^{(0)} = I$;
2. BFGS 方法，$H^{(0)} = I$;
3. FR 共轭梯度法， $\epsilon = 10^{−6}$ ,初始点可设为 $x^{(0)} = (0,0)^T$ ,或自己设置

```julia
using LinearAlgebra
using ForwardDiff

function bfgs(f, ∇f, hessian, x0; tol=1e-6, max_iter=1000)
  G = hessian(x0)
  H = I
  x = x0
  ∇f_x = ∇f(x)
  for i in 1:max_iter
    if norm(∇f_x) < tol
      return x
    end
    d = -H * ∇f_x
    # α = line_search(f, ∇f, x, d)
    α = -((∇f_x' * d) / (d' * G * d))
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    s = α * d
    y = ∇f_x_new - ∇f_x
    ρ = 1.0 / (y' * s)
    H = (I - ρ * s * y') * H * (I - ρ * y * s') + ρ * s * s'
    x = x_new
    ∇f_x = ∇f_x_new
    G = hessian(x_new)
  end
  return x
end

function dfp(f, ∇f, hessian, x0; max_iter=1000, ϵ=1e-6)
  x = x0
  H = I
  G = hessian(x)
  for i in 1:max_iter
    ∇f_x = ∇f(x)
    if norm(∇f_x) < ϵ
      break
    end
    d = -H * ∇f_x
    # α = line_search(f, ∇f, x, d)
    α = -((∇f_x' * d) / (d' * G * d))
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    δ = x_new - x
    γ = ∇f_x_new - ∇f_x
    H = H + (δ * δ') / (δ' * γ) - (H * γ * γ' * H) / (γ' * H * γ)
    x = x_new
    G = hessian(x_new)
  end
  return x
end


function conjugate_gradient(f, ∇f, x0; max_iter=1000, ϵ=1e-6)
  x = x0
  g = ∇f(x)
  d = -g
  g_norm = norm(g)

  for i in 1:max_iter
    if g_norm < ϵ
      break
    end
    α = line_search(f, ∇f, x, d)  # 线搜索来确定步长
    x = x + α * d
    g_new = ∇f(x)
    β = dot(g_new, g_new) / dot(g, g)  # Fletcher-Reeves 公式
    d = -g_new + β * d
    g = g_new
    g_norm = norm(g)
  end

  return x
end


function line_search(f, ∇f, x, d, α=1, β=0.5, σ=0.1)
  while f(x + α * d) > f(x) + σ * α * dot(∇f(x), d)
    α = β * α
  end
  return α
end

function sgd(f, ∇f, x0; learning_rate=0.01, max_iter=1000, ϵ=1e-6)
  x = x0
  for i in 1:max_iter
    grad = ∇f(x)
    if norm(grad) < ϵ
      break
    end
    x = x - learning_rate * grad
  end
  return x
end

f(x) = x[1]^2 + x[2]^2 - x[1] * x[2] - 10 * x[1] - 4 * x[2] + 60



∇f = x -> ForwardDiff.gradient(f, x)

hessian = x -> ForwardDiff.hessian(f, x)


x0 = [0, 0]
x = dfp(f, ∇f, hessian, x0)
println(x, " ", f(x))
x = bfgs(f, ∇f, hessian, x0)
println(x, " ", f(x))
x0 = [10, 8]
x = conjugate_gradient(f, ∇f, x0)
println(x, " ", f(x))

```

结果：

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071551604.png)


这三种方法都是用于数值优化问题的迭代算法。它们的迭代点和特点如下：

1. DFP（Davidon-Fletcher-Powell）方法：DFP是一种拟牛顿法，其基本思想是通过一系列的近似矩阵来更新Hessian矩阵的逆矩阵，从而加速梯度下降算法的收敛速度。DFP方法的迭代点是通过不断更新逆Hessian矩阵来求解的。DFP方法的特点是在每次迭代中都需要计算和存储逆Hessian矩阵，因此对存储要求较高，但收敛速度较快。
2. BFGS（Broyden-Fletcher-Goldfarb-Shanno）方法：BFGS也是一种拟牛顿法，与DFP方法不同的是，BFGS方法通过近似Hessian矩阵的逆矩阵来更新Hessian矩阵的逆矩阵。BFGS方法的迭代点是通过不断更新逆Hessian矩阵来求解的。BFGS方法的特点是收敛速度快，存储要求较低。
3. FR（Fletcher-Reeves）共轭梯度法：FR方法是一种共轭梯度法，其基本思想是通过共轭梯度方向来寻找全局最优解。FR方法的迭代点是通过不断迭代共轭梯度方向来求解的。FR方法的特点是收敛速度较快，但可能会出现收敛到局部最优解的情况。

总之，DFP和BFGS方法都是拟牛顿法，它们的迭代点是通过不断更新逆Hessian矩阵来求解的，而FR方法是共轭梯度法，它的迭代点是通过迭代共轭梯度方向来求解的。不同方法之间的差异在于更新逆Hessian矩阵的方式和收敛速度等方面。

## T8

请证明梯度下降法和牛顿法的收敛性，并采用梯度法来迭代求解二次规划问题的收敛性分析

梯度下降法的收敛性分析：
1. 在使用梯度下降法时，如果目标函数是凸的且其梯度是连续的，那么梯度下降法可以保证收敛到全局最小值。
2. 收敛速率通常是线性的，但如果采用适当的步长，例如线搜索（Line Search）或者使用适应性步长策略，可能会有更好的收敛速率。
3. 对于步长的选择，常用的有固定步长、递减步长，以及满足Wolfe条件的线搜索方法。

牛顿法的收敛性分析：
1. 牛顿法用于优化问题时，通常假定目标函数是二次可微的。如果目标函数是凸的，并且Hessian矩阵在解的邻域内正定，牛顿法可以保证局部且二次收敛。
2. 牛顿法的收敛速率是二次的，意味着它通常比梯度下降法更快找到极小值，但每一步的计算量更大，因为要计算Hessian矩阵及其逆。
3. 牛顿法的收敛也依赖于初始点的选择。如果初始点选择不当，可能不会收敛到最小值。

在使用梯度下降法来迭代求解二次规划问题时，其收敛性通常可以通过以下方式分析：
1. 二次规划问题通常可以表示为凸优化问题，因此可以保证梯度下降法收敛到全局最小值。
2. 由于二次规划的目标函数形式为 $\frac{1}{2}x^TQx + b^Tx + c$ ，其中 $Q$ 是对称正定矩阵，可以通过适当选择步长来确保收敛性。
3. 通常步长的选择可以通过解析计算来进行，例如对于二次问题的特定步长为 $\frac{\nabla f(x)^T \nabla f(x)}{\nabla f(x)^T Q \nabla f(x)}$，这保证了每一步都是沿着最速下降方向。。

## T9

总结无约束优化求解的基本思想，思考如何将非凸优化问题转化为凸优化问题，如何将有约束问题转化为无约束问题。

1. 无约束优化求解的基本思想

    无约束优化是指在没有约束条件下，寻找使目标函数最小化（最大化）的变量值。其基本思想包括以下步骤：

    - 确定目标函数：首先需要有一个明确的目标函数，它是优化的主体。

    - 确定初始点：选择一个初始点开始优化求解。

    - 梯度计算：计算目标函数在当前点处的梯度，即求偏导数，确定当前点在目标函数曲面上的方向。

    - 更新变量：根据当前点处的梯度方向，对变量进行更新，以期望沿着梯度下降的方向逼近最小值。

    - 判断停止条件：通过设置一个停止条件，比如梯度大小趋近于0或者达到最大迭代次数来终止优化过程。

    - 循环重复：重复上述过程，直到找到目标函数的最小值。

    无约束优化的基本思想是基于梯度下降的方法寻找目标函数的最小值。梯度下降的方法是迭代方法，即通过数值计算不断更新变量，来逼近最优解。其思想简单，易于实现，成为优化求解中的一种常用方法。

2. 如何将非凸优化问题转化为凸优化问题

    将非凸优化问题转化为凸优化问题通常可以通过以下两种方法进行：

    - 对偶问题。本质是将原问题转化为另一个问题，该问题更容易被凸性质所处理。对于一个非凸优化问题，可以考虑它的对偶问题，对偶问题有可能是凸优化问题。一旦找到对偶问题后，再将其求解，就可以得到原问题的最优解。

    - 松弛问题。用一个比原问题更宽松的条件来替代原条件，这样可以将一个非凸问题转化为一个凸问题。

3. 如何将有约束问题转化为无约束问题

    将有约束问题转化为无约束问题通常可以通过以下两种方法进行：

    - Lagrange乘子法。基本思想是将约束条件和目标函数放在一起构建一个新的函数（称为Lagrange函数），然后通过对该函数求解使其等于0的方程，得到原问题的最优解。
    - 无限制最小化算法。基本思想是将原问题的约束条件转化为一个惩罚项加到目标函数上，然后在惩罚项的影响下，求解一个无约束问题。

## T10

请将最速下降法、牛顿法、修正牛顿法的计算公式进行统一描述，并体会变尺度法的基本思想。

$$x_{k+𝟏}＝x_k−\lambda_k H_k \nabla f(x_k),H_k=I, H_k=[\nabla^2 f(x_k)]^{−1} $$

$\lambda_k$ 用一维搜索则为修正牛顿法；如果利用一阶导数信息来逼近二阶Hessian矩阵信息，则称为拟牛顿法，例如变尺度法中采用近似矩阵来逼近 $H_k=H_{k−𝟏}＋C_k$ ,则称为变尺度法，例如 $C_k=t_k \alpha\alpha^T ,\alpha=(\alpha_𝟏,\alpha_𝟐,\dots,\alpha_𝒏 )^T$ ,此时 $C_k$ 秩为1，称为秩1校正，若 $C_k=t_k \alpha\alpha^T+s_k \beta\beta^T$ ,则称为秩2校正，例如后续的DFP方法

变尺度法：变尺度法的基本思想是通过变换自变量来改变问题的尺度，从而使得优化问题更容易求解。在一维情况下，变尺度法可以使用简单的变量替换来实现，例如使用 $t=log⁡(x)$进行替换。在高维情况下，变尺度法需要使用更复杂的技术，例如使用特征值分解来对 Hessian 矩阵进行变换。变尺度法的优点是可以加速优化算法的收敛速度，并且可以使得算法更加稳定。

## T11

尝试采用深度学习中的随机梯度下降算法中各种一阶改进的优化算法来求解上述习题中的典型问题。

```julia
using LinearAlgebra
using ForwardDiff

function bfgs(f, ∇f, hessian, x0; tol=1e-6, max_iter=1000)
  G = hessian(x0)
  H = I
  x = x0
  ∇f_x = ∇f(x)
  for i in 1:max_iter
    if norm(∇f_x) < tol
      return x
    end
    d = -H * ∇f_x
    # α = line_search(f, ∇f, x, d)
    α = -((∇f_x' * d) / (d' * G * d))
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    s = α * d
    y = ∇f_x_new - ∇f_x
    ρ = 1.0 / (y' * s)
    H = (I - ρ * s * y') * H * (I - ρ * y * s') + ρ * s * s'
    x = x_new
    ∇f_x = ∇f_x_new
    G = hessian(x_new)
  end
  return x
end

function dfp(f, ∇f, hessian, x0; max_iter=1000, ϵ=1e-6)
  x = x0
  H = I
  G = hessian(x)
  for i in 1:max_iter
    ∇f_x = ∇f(x)
    if norm(∇f_x) < ϵ
      break
    end
    d = -H * ∇f_x
    # α = line_search(f, ∇f, x, d)
    α = -((∇f_x' * d) / (d' * G * d))
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    δ = x_new - x
    γ = ∇f_x_new - ∇f_x
    H = H + (δ * δ') / (δ' * γ) - (H * γ * γ' * H) / (γ' * H * γ)
    x = x_new
    G = hessian(x_new)
  end
  return x
end


function conjugate_gradient(f, ∇f, x0; max_iter=1000, ϵ=1e-6)
  x = x0
  g = ∇f(x)
  d = -g
  g_norm = norm(g)

  for i in 1:max_iter
    if g_norm < ϵ
      break
    end
    α = line_search(f, ∇f, x, d)  # 线搜索来确定步长
    x = x + α * d
    g_new = ∇f(x)
    β = dot(g_new, g_new) / dot(g, g)  # Fletcher-Reeves 公式
    d = -g_new + β * d
    g = g_new
    g_norm = norm(g)
  end

  return x
end


function line_search(f, ∇f, x, d, α=1, β=0.5, σ=0.1)
  while f(x + α * d) > f(x) + σ * α * dot(∇f(x), d)
    α = β * α
  end
  return α
end

function sgd(f, ∇f, x0; learning_rate=0.01, max_iter=1000, ϵ=1e-6)
  x = x0
  for i in 1:max_iter
    grad = ∇f(x)
    if norm(grad) < ϵ
      break
    end
    x = x - learning_rate * grad
  end
  return x
end


function sgd_momentum(f, ∇f, x0; learning_rate=0.01, momentum=0.9, max_iter=1000, ϵ=1e-6)
  x = x0
  v = zeros(length(x0))
  for i in 1:max_iter
    grad = ∇f(x)
    if norm(grad) < ϵ
      break
    end
    v = momentum * v + learning_rate * grad
    x = x - v
  end
  return x
end

function adagrad(f, ∇f, x0; learning_rate=0.01, ϵ=1e-8, max_iter=1000)
  x = x0
  G = zeros(length(x0))
  for i in 1:max_iter
    grad = ∇f(x)
    G += grad .^ 2
    adjusted_grad = grad ./ (sqrt.(G) .+ ϵ)
    x = x - learning_rate * adjusted_grad
  end
  return x
end

f(x) = x[1]^2 + x[2]^2 - x[1] * x[2] - 10 * x[1] - 4 * x[2] + 60



∇f = x -> ForwardDiff.gradient(f, x)

hessian = x -> ForwardDiff.hessian(f, x)


x0 = [0, 0]
x = dfp(f, ∇f, hessian, x0)
println(x, " ", f(x))
x = bfgs(f, ∇f, hessian, x0)
println(x, " ", f(x))
x0 = [10, 8]
x = conjugate_gradient(f, ∇f, x0)
println(x, " ", f(x))

x0 = [0, 0]
x = sgd(f, ∇f, x0)
println(x, " ", f(x))
x = sgd_momentum(f, ∇f, x0)
println(x, " ", f(x))

```

结果

![](https://cdn.jsdelivr.net/gh/keshuigu/images@main/imgs/202404071553729.png)

## T12

自己查看已有的深度学习模型，训练中其参数的变化是否服从低维特性？尝试画出这些变化的分布。

在深度学习模型中，参数的变化通常不服从低维特性，因为它们通常是高维向量。然而，在训练过程中，这些参数会发生变化以优化模型的性能，这些变化通常具有低维特征。为了可视化这些参数变化的趋势，可以使用一些低维表示技术，例如卷积神经网络 (CNN) 的降维处理，将高维参数映射到低维空间中。在这种情况下，可以使用线性降维技术，例如主成分分析 (PCA) 或线性判别分析 (LDA)，将这些高维参数压缩到低维空间中。

## T13

查阅一阶优化算法的最新加速算法思想，并总结其基本思路。（可查阅北大林宙辰老师的英文版书籍）

目前一阶优化算法中最新的加速算法思想主要包含以下方法：

- Momentum 方法通过引入动量来加速梯度下降算法。动量方法可以在梯度下降过程中启用惯性，以处理梯度方向变化的问题。当梯度方向变化较小时，动量方法可以在最优化过程中平滑搜索方向。Momentum 方法的基本思路是在梯度下降中引入一个历史梯度的加权和，以平滑梯度下降方向，并加速收敛速度。通过设置一个动量超参数，即动量系数，可以控制惯性的大小。

- Nesterov Accelerated Gradient 方法是对 Momentum 方法的改进。在原始 Momentum 方法中，动量方向被独立运用于算法中。Nesterov Accelerated Gradient 方法在 Momentum 方法的基础上，改变了动量的应用方式，引入了一个修正过的梯度估计，它可以告诉算法当前是否远离全局最优解，从而使学习率自适应地调整。该方法不仅可以带来更快的收敛，还可以使优化过程更加稳定和可靠。
- Adagrad：自适应梯度算法（Adaptive Gradient Algorithm），是一种基于梯度平方的动态调节算法。Adagrad 算法的主要思想是通过根据梯度历史记录对学习率进行调整，从而对不同的参数提供不同的学习率。这可以更好地解决数据不平衡和不同维度梯度差异的问题。
- Adadelta：自适应 Delta 算法，其主要思想是固定梯度的历史数据，通过对学习率的动态调整来控制参数更新幅度，使得在不同的情况下有不同的调节策略，进而实现更快的收敛速度。
- Adam：自适应矩估计算法（Adaptive Moment Estimation），是一种基于估计梯度和梯度平方的动态调节方法。Adam 算法主要通过计算各个梯度的一阶和二阶矩来实现动态调节，从而得到不同参数的不同的更新规则。Adam 算法的优势在于可以自动适应不同参数的学习率，并可以很好地处理噪声和稀疏性。

这五种优化算法都是通过对梯度下降过程进行优化来加快收敛速度和优化性能。它们的基本思路是通过引入动量、自适应调节学习率等方法，使优化算法收敛速度更快和性能表现更佳。

## T14

请给出共轭函数的定义，理解如何求解共轭函数，并思考共轭函数和对偶性的联系。

共轭函数和对偶性有着密切的联系，它们之间存在着互相转化的关系，具有相似性。

在数学中，给定一个实数函数 $f(x)$，如果该函数满足一定的条件，那么可以定义出其共轭函数 $f^*(y)$。共轭函数的作用在于将原函数在傅里叶变换领域中的性质与其在原始函数领域中的性质相对应。

另一方面，在凸优化中，对偶性是指将原始问题转化为另一个等价的问题的过程。对于每一个原问题，都存在一个对偶问题，它们之间是等价的。对偶问题中的最优解等于原问题的最优解，而且对于任意一个可行解，原问题的目标函数值不小于对偶问题的目标函数值。

在某些情况下，共轭函数与对偶性之间存在着密切的联系。特别地，如果一个函数 $f(x)$ 在它在定义域上的凸壳（convex hull）内是凸函数，则该函数的共轭函数 $f^*(y)$ 也是凸函数，并且它们之间存在着一种对偶关系，即$f^{**}(x)=f(x)$。