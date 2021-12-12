"""
    Sample Run:
    python plot_graph.py
"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt


matplotlib.rcParams.update({'font.size': 20})
lw             = 4


def draw_log_graph(x_data, y_data, xlabel, ylabel, xticks, yticks= None, save_path= None):
    plt.plot  (x_data, y_data  , '-o', lw= lw, c= 'r', ms= 12)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid  ('on')

    ax = plt.gca()
    if yticks is not None:
        ax.set_yticks(yticks)
    ax.set_xscale('log')

    ax.set_xticks(xticks)
    ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
    ax.set_xticklabels(xticks)


    locmin = matplotlib.ticker.LogLocator(base=10.0, subs=(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9),numticks=10) 
    ax.xaxis.set_minor_locator(locmin)
    ax.xaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())

#===============================================================================
# Main starts here
#===============================================================================
num_points  = np.array([1    ,     2,     4,     8,    16,    32,    64, 128  , 256  , 512])
time_copy   = np.array([84.02, 84.47, 85.08, 83.22, 82.81, 84.25, 84.22, 84.09, 84.34, 84.12])
time_matmul = np.array([23.58, 15.80, 15.35, 16.05, 14.56, 16.06, 24.61, 45.40, 86.68, 164.18])
time_total  = time_copy +  time_matmul
time_cpu    = np.ones(time_copy.shape) * 606.78
xticks      = np.array([1, 3, 10, 30, 100, 300, 1000])
yticks      = np.array([10, 30, 100, 300, 600])
xlabel      = "#Blocks"
ylabel      = "Time (us)"
save_path   = "output/time_vs_num_blocks.png"

plt.figure(figsize=(8,6), dpi=200)

plt.plot  (num_points, time_cpu   , '-' , lw= lw, c= 'k', ms= 12, label= 'CPU Total')
plt.plot  (num_points, time_copy  , '-o', lw= lw, c= 'r', ms= 12, label= 'GPU MemCopy')
plt.plot  (num_points, time_matmul, '-o', lw= lw, c= 'g', ms= 12, label= 'GPU MatMul')
plt.plot  (num_points, time_total , '-o', lw= lw, c= 'violet', ms= 12, label= 'GPU Total')
plt.xlabel(xlabel)
plt.ylabel(ylabel)
plt.grid  ('on')

ax = plt.gca()
if yticks is not None:
    ax.set_yticks(yticks)
ax.set_xscale('log')
ax.set_yscale('log')

ax.set_yticks(yticks)
ax.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax.set_yticklabels(yticks)
locmin = matplotlib.ticker.LogLocator(base=10.0, subs=(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9),numticks=10) 
ax.yaxis.set_minor_locator(locmin)
ax.yaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())


ax.set_xticks(xticks)
ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax.set_xticklabels(xticks)
locmin = matplotlib.ticker.LogLocator(base=10.0, subs=(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9),numticks=10) 
ax.xaxis.set_minor_locator(locmin)
ax.xaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())




plt.ylim(top= 700)
plt.legend(loc= 'upper left', bbox_to_anchor=(0,0.9), borderaxespad= 0.05, borderpad= 0.1, labelspacing= 0.1, handletextpad= 0.2)

print("Saving to {}".format(save_path))
plt.savefig(save_path, bbox_inches='tight')
