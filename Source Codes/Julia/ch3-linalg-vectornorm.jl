using Plots, CalculusWithJulia, LinearAlgebra, LaTeXStrings
gr()

v = [8,2]
uv = v/norm(v)
p = [0,0]
plot(legend=false)
arrow!(p, v)
arrow!(p, uv, linewidth=5)

annotate!([(3.7,1, (L"\vec{v}", 10, :black))])
annotate!([(0.2,0.2, (L"||\vec{v}||", 10, :black))])
