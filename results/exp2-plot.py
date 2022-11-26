import numpy as np

from utils import plot_achieved_vs_theoretical, compute_theoretical_Tseq, compute_theoretical_Tpar, get_config_params


config_vars_names = {"exp2_" + k: k for k in ["N", "B", "min_nw", "max_nw"]}

for name, value in get_config_params().items():
    if name in config_vars_names:
        exec(config_vars_names[name] + f" = {value}")

b = int(np.log2(B))
n = int(np.log2(N))
nw = np.geomspace(min_nw, max_nw, int(np.log2(max_nw/min_nw)) + 1)
s = (n - np.log2(nw)).astype(int)

T = np.empty(len(nw))
with open("outputs/exp2-results.txt", "r") as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
        splt = line.split()
        T[i] = float(splt[4])

theoretical_Tseq = compute_theoretical_Tseq(n, b)
theoretical_Tpar = np.array([compute_theoretical_Tpar(n, b, x) for x in s])
theoretical_speedups = theoretical_Tseq / theoretical_Tpar

plot_achieved_vs_theoretical(nw, T[0] / T, theoretical_speedups, "speedup", "$n_w$", "$\mathcal{S}$", "exp2-Speedup")
plot_achieved_vs_theoretical(nw, T, theoretical_Tpar, "execution time", "$n_w$", "$T$ ($\mu s$)", "exp2-Tex")
