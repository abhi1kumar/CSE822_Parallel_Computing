"""
    Sample Run:
    python plot_graph.py
"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt

cpu_peak = 4

N_array        = np.array([32   , 64   , 128  , 256  , 512  , 1024 , 2048 , 3162])
mflops_array   = np.array([0.636, 0.633, 0.627, 0.543, 0.479, 0.303, 0.197, 0.191])
cpu_peak_array = cpu_peak* np.ones(N_array.shape)
tot_elem_array = N_array * N_array

matplotlib.rcParams.update({'font.size': 28})
lw             = 4
plt.figure(figsize=(8,6), dpi=200)
plt.plot  (N_array, mflops_array  , '-o', lw= lw, c= 'r', ms= 12, label= 'Achieved')
plt.plot  (N_array, cpu_peak_array, '-o', lw= lw, c= 'g', ms= 12, label= 'Peak')
plt.xlabel(r'Matrix Rows $N$')
plt.ylabel('GFlops/s')
plt.grid  ('on')
plt.legend()

ax = plt.gca()
ax.set_yticks(np.arange(cpu_peak + 0.01))
ax.set_xscale('log')

#ax.set_xticks([1000, 10000, 100000, 1000000, 10000000])
#ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
#ax.set_xticklabels([r'$10^3$', r'$10^4$', r'$10^5$', r'$10^6$', r'$10^7$'])
ax.set_xticks(N_array[::2])
ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax.set_xticklabels(N_array[::2])


locmin = matplotlib.ticker.LogLocator(base=10.0, subs=(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9),numticks=12) 
ax.xaxis.set_minor_locator(locmin)
ax.xaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())

plt.savefig('gflops_vs_tot_elem.png', bbox_inches='tight')
