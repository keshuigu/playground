using ForwardDiff
include("derivate.jl")

function admm(f, g, x0, ρ, max_iter=100)
  x = x0
  z = x0
  u = zeros(length(x0))
  xs = [copy(x)]
  # x-z = 0
  # f(x) + g(z) + u' * (x-z) + (ρ/2)||x-z||^2
  f1 = x -> f(x) + g(z) + u' * (x - z) + (ρ / 2) * sum((x - z) .^ 2)
  g1 = z -> f(x) + g(z) + u' * (x - z) + (ρ / 2) * sum((x - z) .^ 2)
  ∇f1 = x -> ForwardDiff.gradient(f1, x)
  ∇g1 = z -> ForwardDiff.gradient(g1, z)
  for i in 1:max_iter
    # 更新x

    x = nonlinear_conjugate_gradient(f1, ∇f1, x)[end]
    push!(xs, copy(x))
    # 更新z
    z = nonlinear_conjugate_gradient(g1, ∇g1, z)[end]
    # 更新u
    u = u + x - z
  end

  return xs
end
