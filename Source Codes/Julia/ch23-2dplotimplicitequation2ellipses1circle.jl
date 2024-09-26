# https://discourse.julialang.org/t/is-there-package-or-method-to-calculate-certain-area-in-julia-symbolically-with-sympy/99751/4
# julia --project="."
using SymPy, Plots, CalculusWithJulia, LaTeXStrings, Plots.PlotMeasures
gr()
f(x,y) = (5*x^2)+(5*y^2) + 4*x*y - 7
g(x,y) = (5*x^2) + (5*y^2) + 4*x*y - 3
g2(x,y) = x^2 + y^2 - 1

implicit_plot(f, label=L"5x^{2} + 5y^{2} + 4xy = 7", xlims = (-2, 2), ylims=(-2, 2),
		linecolor=:blue1, framestyle=:zerolines, size=(1080, 960), 
		legend=:right, bottom_margin=3mm)
implicit_plot!(g, label=L"5x^{2} + 5y^{2} + 4xy = 3", linecolor=:green4)
implicit_plot!(g2, label=L"x^{2} + y^{2} = 1", linecolor=:black)