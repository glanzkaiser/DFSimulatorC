using SymPy, Plots, CalculusWithJulia, LinearAlgebra, LaTeXStrings
gr()

u = [1,8]
v = [8,2]
w = u+v
p = [0,0]
quiver(unzip([p])..., quiver=unzip([u]))
quiver!(unzip([u])..., quiver=unzip([v]))
quiver!(unzip([p])..., quiver=unzip([w]))
annotate!([(2.6,4, (L"\vec{v} + \vec{w}", 10, :black))])
annotate!([(4,8, (L"\vec{w}", 10, :black))])
annotate!([(0.2,5, (L"\vec{v}", 10, :black))])
