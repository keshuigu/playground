include("admm.jl")
include("derivate.jl")
include("second_derivative.jl")
include("lab1_testfunction.jl")
using ForwardDiff
using Plots
f = rosenbrock_2d
grad_f = x -> ForwardDiff.gradient(f, x)
hessian_f = x -> ForwardDiff.hessian(f, x)

# x0 = [-5.0, -30.0]
# xs = nonlinear_conjugate_gradient(f, grad_f, x0)

# a = -6:0.01:6
# b = -30:0.1:30
# z = [rosenbrock_2d([i, j]) for j in b, i in a]

# # 画出罗森布洛克函数的图像
# p = surface(a, b, z, xlabel="x", ylabel="y", zlabel="z", title="Rosenbrock Function", color=:blues)
# # 在 surface 图上画出每次迭代的 x 值
# scatter!(p, [x[1] for x in xs], [x[2] for x in xs], f.(xs), label="Iteration path", color=:red)
# # 画出迭代路径
# plot!(p, [x[1] for x in xs], [x[2] for x in xs], f.(xs), label="Iteration path", color=:green, linewidth=2)
# savefig(p, "nonlinear_conjugate_gradient.png")

# x0 = [-5.0, -30.0]
# xs = bfgs(f, grad_f, hessian_f, x0)
# a = -6:0.01:6
# b = -30:0.1:30
# z = [rosenbrock_2d([i, j]) for j in b, i in a]

# # 画出罗森布洛克函数的图像
# p = surface(a, b, z, xlabel="x", ylabel="y", zlabel="z", title="Rosenbrock Function", color=:blues)
# # 在 surface 图上画出每次迭代的 x 值
# scatter!(p, [x[1] for x in xs], [x[2] for x in xs], f.(xs), label="Iteration path", color=:red)
# # 画出迭代路径
# plot!(p, [x[1] for x in xs], [x[2] for x in xs], f.(xs), label="Iteration path", color=:green, linewidth=2)
# savefig(p, "bfgs.png")



f1 = x -> (1.0 - x[1])^2
g1 = x -> 100.0 * (x[2] - x[1]^2)^2

x0 = [-5.0, -30.0]
xs = admm(f1, g1, x0, 1.0)
# print(xs)
a = -6:0.01:6
b = -30:0.1:30
z = [rosenbrock_2d([i, j]) for j in b, i in a]

# 画出罗森布洛克函数的图像
p = surface(a, b, z, xlabel="x", ylabel="y", zlabel="z", title="Rosenbrock Function", color=:blues)
# 在 surface 图上画出每次迭代的 x 值
scatter!(p, [x[1] for x in xs], [x[2] for x in xs], f.(xs), label="Iteration path", color=:red)
# 画出迭代路径
plot!(p, [x[1] for x in xs], [x[2] for x in xs], f.(xs), label="Iteration path", color=:green, linewidth=2)
savefig(p, "admm.png")