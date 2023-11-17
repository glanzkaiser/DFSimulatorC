using Plots, LaTeXStrings, ValidatedNumerics
gr()

f(x) = x^2

#plot(f, 0, 2, aspect_ratio=:equal, fill=(0, :green), alpha=0.2, label="")

function make_intervals(N=10)
    xs = range(0, stop=2, length=N+1)
    return [xs[i]..xs[i+1] for i in 1:length(xs)-1]
end

intervals = make_intervals()

# Plot Riemann Sums
intervals = make_intervals(6)
 
p = plot()
for X in intervals
    Y = f(X)

    plot!(IntervalBox(X, Interval(0, Y.hi)), c=:blue, label="", alpha=0.1)
end

plot!(f, 0, 2, xtick=false, xlims=(0,2), ylims=(-0.3,4),
	legend=:topleft, label=L"x^2")

plot!([1.33,1.33],[0,f(1.33)], label="", linecolor=:blue, linestyle=:dash)
annotate!([(1.27,0.85, (L"f(x_{i})", 7, :blue))])

plot!([1,1.33],[0,0], label="", linecolor=:blue, linestyle=:dash)
annotate!([(1,-0.08, (L"x_{i-1}", 7, :blue))])
annotate!([(1.33,-0.08, (L"x_{i}", 7, :blue))])

annotate!([(1.1,0.95, (L"R_{n}", 11, :black))])
annotate!([(0.2,-0.07, (L"x_{0}", 6, :black))])
annotate!([(0.5,-0.07, (L"x_{1}", 6, :black))])
annotate!([(0.85,-0.07, (L"x_{2}", 6, :black))])
annotate!([(0.95,0.27, (L"f(x_{2})", 6, :black))])
annotate!([(1.2,-0.07, (L"\dots", 6, :black))])
annotate!([(1.5,-0.07, (L"x_{n-1}", 6, :black))])
annotate!([(1.6,1, (L"f(x_{n-1})", 6, :black))])
annotate!([(1.85,-0.07, (L"x_{n}", 6, :black))])
annotate!([(1.95,1.37, (L"f(x_{n})", 6, :black))])
