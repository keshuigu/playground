# 初始区间
function initial_bracket(f, x, d, s=1e-2, k=2.0)
  g = t -> f(x + t * d)
  a, ya = 0, g(0)
  b, yb = a + s, g(a + s)

  if yb > ya
    a, b = b, a
    ya, yb = yb, ya
    s = -s
  end

  while true
    c, yc = b + s, g(b + s)
    if yc > yb
      return a < c ? (a, c) : (c, a)
    end
    a, ya, b, yb = b, yb, c, yc
    s *= k
  end
end

# 精确一维搜索
function golden_section_search(f, x, a, b, direct, tol=1e-6)
  g = t -> f(x + t * direct)
  ϕ = (sqrt(5) - 1) / 2  # 黄金比例
  c = b - ϕ * (b - a)
  d = a + ϕ * (b - a)
  while abs(b - a) > tol
    if g(c) < g(d)
      b = d
    else
      a = c
    end
    c = b - ϕ * (b - a)
    d = a + ϕ * (b - a)
  end
  return (a + b) / 2
end


# 不精确一维搜索

# goldstein_1
function condition_1(f, ∇f, x, λ, d, c1=0.1)
  φ0 = f(x)
  φd0 = ∇f(x)' * d
  φλ = f(x + λ * d)
  return φλ - φ0 <= c1 * λ * φd0
end


# wolfe_powell
function condition_2(∇f, x, λ, d, σ=0.1)
  φd0 = ∇f(x)' * d
  φdλ = ∇f(x + λ * d)' * d
  return abs(φdλ) <= -σ * φd0
end

function inexact_method(f, ∇f, x, d, λ, α=1.5, β=0.5, c=0.1)
  while true
    if condition_1(f, ∇f, x, λ, d, c)
      λ *= β
      continue
    end
    if condition_2(∇f, x, λ, d)
      λ *= α
      continue
    end
    break
  end
  return λ
end



