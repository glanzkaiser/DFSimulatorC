# https://discourse.julialang.org/t/is-there-package-or-method-to-calculate-certain-area-in-julia-symbolically-with-sympy/99751/4

using SymPy, Plots, CalculusWithJulia, LaTeXStrings, Plots.PlotMeasures
f(x,y) = (4*x^2)+(9*y^2)-36
g(x,y) =(5*x^2) - 4*x*y + (8*y^2)-36

implicit_plot(g, label=L"5x^{2} - 4xy + 8y^{2} - 36 = 0",linecolor=:blue1, framestyle=:zerolines,
		legend=:topright, bottom_margin=3mm)
implicit_plot!(f, label=L"4x^{2} + 9y^{2} = 36", linecolor=:green4)
