import numpy as np

from utils import plot_achieved_vs_theoretical, compute_theoretical_Tseq, compute_theoretical_Tpar, get_config_params


config_vars_names = {"exp1_" + k: k for k in ["min_N", "max_N", "B", "nw"]}

for name, value in get_config_params().items():
    if name in config_vars_names:
        exec(config_vars_names[name] + f" = {value}")

b = int(np.log2(B))
n = np.arange(np.log2(min_N), np.log2(max_N) + 1)
N = 2 ** n
s = n - int(np.log2(nw))

T_seq, T_par = np.empty((2, len(N)))
with open("outputs/exp1-results.txt", "r") as f:
    idx = 0
    for line in f.readlines():
        splt = line.split()
        if splt[0] == "nw":
            if splt[2] == "1":
                T_seq[idx] = float(splt[4])
            else:
                T_par[idx] = float(splt[4])
                idx += 1

theoretical_Tseq = np.array([compute_theoretical_Tseq(int(x), b) for x in n])
theoretical_Tpar = np.array([compute_theoretical_Tpar(int(x), b, int(y)) for x, y in zip(n, s)])
theoretical_speedups = theoretical_Tseq / theoretical_Tpar

plot_achieved_vs_theoretical(N, T_seq / T_par, theoretical_speedups, "speedup", "$N$", "$\mathcal{S}$", "exp1-Speedup")
