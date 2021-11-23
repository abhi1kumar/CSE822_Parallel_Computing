"""
    Sample Run:
    python plot_graph.py
"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt


matplotlib.rcParams.update({'font.size': 28})
lw             = 4


def draw_log_graph(x_data, y_data, xlabel, ylabel, xticks, yticks= None, save_path= None):
    
    plt.figure(figsize=(8,6), dpi=200)
    plt.plot  (x_data, y_data  , '-o', lw= lw, c= 'r', ms= 12)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid  ('on')

    ax = plt.gca()
    if yticks is not None:
        ax.set_yticks(yticks)
    ax.set_xscale('log')

    #ax.set_xticks([1000, 10000, 100000, 1000000, 10000000])
    #ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
    #ax.set_xticklabels([r'$10^3$', r'$10^4$', r'$10^5$', r'$10^6$', r'$10^7$'])
    ax.set_xticks(xticks)
    ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
    ax.set_xticklabels(xticks)


    locmin = matplotlib.ticker.LogLocator(base=10.0, subs=(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9),numticks=10) 
    ax.xaxis.set_minor_locator(locmin)
    ax.xaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())

    print("Saving to {}".format(save_path))
    plt.savefig(save_path, bbox_inches='tight')

#===============================================================================
# Main starts here
#===============================================================================
num_points  = np.array([1   , 2, 4, 8, 16, 32, 64 , 128  , 256  , 512  , 1024 , 2048, 4096, 8192, 16384])
area        = np.array([-7.64112, -3.8966, -1.9516, -3.90573, -4.88442, -5.37414, -5.6191, -5.74159, -5.80285, -5.83348, -5.84879, -5.85645, -5.86028, -5.86219,-5.86315 ])
xticks      = np.array([1, 10, 100, 1000, 10000])
yticks      = np.array([0, -2, -4, -6, -8])
xlabel      = "num_points"
ylabel      = "Area"
save_path   = "output/area_vs_num_points.png"
draw_log_graph(x_data= num_points, y_data= area, xlabel= xlabel, ylabel= ylabel, xticks= xticks, yticks= yticks, save_path= save_path)


num_points  = np.array([1   , 2, 4, 8, 16, 32, 64 , 128  , 256  , 512])
area        = np.array([0.00236262, 0.000166143, 9.22159e-05, 6.84274e-05, 0.000165186, 0.000221424, 0.00072719, 0.000681376, 0.00123003, 0.00211773 ])
xticks      = np.array([1, 3, 10, 30, 100, 300, 1000])
yticks      = None
xlabel      = "num_threads"
ylabel      = "Time taken (s)"
save_path   = "output/strong_scaling_time_vs_num_threads.png"
draw_log_graph(x_data= num_points, y_data= area, xlabel= xlabel, ylabel= ylabel, xticks= xticks, yticks= yticks, save_path= save_path)

num_points  = np.array([2, 4, 8, 16, 32, 64 , 128  , 256  , 512, 1024])
area        = np.array([7.2926e-06, 1.21355e-05, 1.93149e-05, 0.000129071, 0.000156321, 0.000634727, 0.000546874, 0.00138674, 0.00216489, 0.00501208 ])
xticks      = np.array([1, 3, 10, 30, 100, 300, 1000])
yticks      = None
xlabel      = "num_threads"
ylabel      = "Time taken (s)"
save_path   = "output/weak_scaling_time_vs_num_threads.png"
draw_log_graph(x_data= num_points, y_data= area, xlabel= xlabel, ylabel= ylabel, xticks= xticks, yticks= yticks, save_path= save_path)
