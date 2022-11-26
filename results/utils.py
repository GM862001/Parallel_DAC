import matplotlib.pyplot as plt
import matplotlib as mlp


def get_config_params(config_filepath = "../config.cfg"):

    params = {}
    with open(config_filepath, "r") as f:
        lines = f.readlines()
        for line in lines:
            line = line.replace(" ", "")
            if line[0] == "#": continue
            eq_loc = line.find("=")
            if eq_loc == -1: continue
            params[line[:eq_loc]] = int(line[eq_loc + 1:])
    return params


for name, value in get_config_params().items():
    if name in ["Td", "Ts", "Tc"]:
        exec(name + f" = {value} * 1000")


def compute_theoretical_Tseq(n, b):

    return (Td + Tc + Ts) * (2 ** (n - b)) - (Td + Tc)


def compute_theoretical_Tpar(n, b, s):

    return (Td + Tc) * (n - s) + compute_theoretical_Tseq(s, b)


def plot_achieved_vs_theoretical(x, y_achieved, y_theoretical, quantity, xlabel, ylabel, title):

    fig = plt.figure(figsize = (12,12))
    plt.plot(x, y_achieved, linestyle = "dotted", marker = "o", color = "k")
    plt.plot(x, y_theoretical, color = "k")
    plt.ylabel(ylabel, fontsize = 16)
    plt.xlabel(xlabel, fontsize = 16)
    handles = [
        mlp.lines.Line2D([0], [0], label = f"Achieved {quantity}", linewidth = 3, linestyle = "dotted", color = "k"),
        mlp.lines.Line2D([0], [0], label = f"Theoretical {quantity}", linewidth = 3, color = "k")
    ]
    plt.legend(handles = handles)
    plt.savefig(f"images/{title}.png")
