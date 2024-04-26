using LinearAlgebra
include("one_dimensional_search.jl")

function nonlinear_conjugate_gradient(f, ∇f, x0, tol=1e-6, max_iter=1000)
  x = x0
  g = ∇f(x)
  d = -g
  g_norm = norm(g)
  xs = [copy(x)]
  for i in 1:max_iter
    if g_norm < tol
      break
    end
    a, b = initial_bracket(f, x, d)
    α = golden_section_search(f, x, a, b, d)
    x = x + α * d
    push!(xs, copy(x))
    g_new = ∇f(x)
    β = dot(g_new, g_new) / dot(g, g)  # Fletcher-Reeves 公式
    d = -g_new + β * d
    g = g_new
    g_norm = norm(g)
  end

  return xs
end
