using SymPy, Plots, LaTeXStrings, Plots.PlotMeasures
@syms m, t, g, gamma
@syms v()

# Computing IVP with SymPy
v(t).diff(t) 
diffeq = Eq(m*v(t).diff(t), m*g - gamma*v(t)); string(diffeq)

print("")
print("")
println("The differential equation:")
sympy.pretty_print(diffeq) # The differential equation

# Solving initial value problem
vt = dsolve(diffeq, v(t))
ivp = dsolve(diffeq, v(t), ics = Dict(v(0) => 0))

print("")
println("Initial Value problem solution:")
sympy.pretty_print(ivp) # The solution for the differential equation with v(0) = 0 

println("The solution for the differential equation with certain parameter inputs:")
vt_final = subs(ivp, m=>10, g => 9.8, gamma => 0.3) 
sympy.pretty_print(vt_final) # The solution for the differential equation with certain parameter inputs

#= Manual way
# Find the constant
sol_vt = rhs(vt)
c1 = free_symbols(vt)[1]
C1 = solve(sol_vt(t=>0) ~ 0, c1)
sympy.pretty_print(C1) # the constant 

ivp_vt = sol_vt(c1=>C1[1])
sympy.pretty_print(ivp_vt) # the constant 
=#