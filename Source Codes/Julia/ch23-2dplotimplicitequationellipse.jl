# https://discourse.julialang.org/t/is-there-package-or-method-to-calculate-certain-area-in-julia-symbolically-with-sympy/99751/4

using SymPy, Plots, CalculusWithJulia, LaTeXStrings
g(x,y) =(5*x^2) - 4*x*y + (8*y^2)-36

implicit_plot(g, label=L"5x^{2} - 4xy + 8y^{2} - 36 = 0",color=:blue)
