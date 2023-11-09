using Plots, CalculusWithJulia, LinearAlgebra, LaTeXStrings
gr()

u = [1,8]
v = [8,2]
w = u-v
p = [0,0]
plot(legend=false)
arrow!(p, u)
arrow!(u, v)
arrow!(p, w)
arrow!(u, -v)

scatter!([1], [8], color = "red1", label="", markersize = 3)
scatter!([0], [0], color = "red1", label="", markersize = 3)
scatter!([-7], [6], color = "red1", label="", markersize = 3)

annotate!([(-5,3, (L"\vec{v} - \vec{w}", 10, :black))])
annotate!([(4,8, (L"\vec{w}", 10, :black))])
annotate!([(0.2,5, (L"\vec{v}", 10, :black))])
annotate!([(-2.4,6.9, (L"-\vec{w}", 10, :black))])
