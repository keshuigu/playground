using LinearAlgebra
using ForwardDiff
include("one_dimensional_search.jl")
function bfgs(f, ∇f, hessian, x0; tol=1e-6, max_iter=1000)
  G = hessian(x0)
  H = I
  x = x0
  ∇f_x = ∇f(x)
  xs = [copy(x)]
  for i in 1:max_iter
    if norm(∇f_x) < tol
      return xs
    end
    d = -H * ∇f_x
    a, b = initial_bracket(f, x, d)
    α = golden_section_search(f, x, a, b, d)
    x_new = x + α * d
    ∇f_x_new = ∇f(x_new)
    s = α * d
    y = ∇f_x_new - ∇f_x
    ρ = 1.0 / (y' * s)
    H = (I - ρ * s * y') * H * (I - ρ * y * s') + ρ * s * s'
    x = x_new
    push!(xs, copy(x))
    ∇f_x = ∇f_x_new
    G = hessian(x_new)
  end
  return xs
end

