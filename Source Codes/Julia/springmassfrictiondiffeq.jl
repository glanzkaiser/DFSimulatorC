using SymPy, Plots, LaTeXStrings, Plots.PlotMeasures
@syms m, t, k, c
@syms x()

# Computing IVP with SymPy
# 2nd Order Differential equation: mx'' + cx' + kx = 0
x(t).diff(t) 
diffeq = Eq(m*(x(t).diff(t)).diff(t), -c*x(t).diff(t) - k*x(t)); string(diffeq)

print("")
print("")
println("The differential equation:")
sympy.pretty_print(diffeq) # The differential equation

# Solving initial value problem
xt = dsolve(diffeq, x(t))
ivp = dsolve(diffeq, x(t), ics = Dict(x(0) => 0))

print("")
println("Initial Value problem solution:")
sympy.pretty_print(ivp) # The solution for the differential equation with x(0) = 0 

println("The solution for the differential equation with certain parameter inputs:")
xt_final = subs(ivp, m=>10, k => 50, c => 0.3) 
sympy.pretty_print(xt_final) # The solution for the differential equation with certain parameter inputs

#= Manual way
# Find the constant
sol_vt = rhs(vt)
c1 = free_symbols(vt)[1]
C1 = solve(sol_vt(t=>0) ~ 0, c1)
sympy.pretty_print(C1) # the constant 

ivp_vt = sol_vt(c1=>C1[1])
sympy.pretty_print(ivp_vt) # the constant 
=#