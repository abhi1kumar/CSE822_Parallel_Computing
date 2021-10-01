"""
    Sample Run:
    python plot_graph.py
"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt

R_array        = np.array([1   , 2, 4, 8, 16, 32, 64 , 128  , 256  , 512  , 1024 , 2048])
mflops_array   = np.array([3720.192279, 3708.743329, 3704.15103725, 3686.40708725, 3687.5468236875, 3646.81044959375, 3577.03871690625, 3426.66070842969, 2997.0153621875, 1593.04758426562, 286.623139417968, 3.62456220898438 ])

matplotlib.rcParams.update({'font.size': 28})
lw             = 4
plt.figure(figsize=(8,6), dpi=200)
plt.plot  (R_array, mflops_array  , '-o', lw= lw, c= 'r', ms= 12, label= 'Achieved')
plt.xlabel(r'Num Threads')
plt.ylabel('Time per thread (ms)')
plt.grid  ('on')
#plt.legend()

ax = plt.gca()
ax.set_yticks(np.array([3, 300, 1000, 3000]) + 0.01)
ax.set_xscale('log')

#ax.set_xticks([1000, 10000, 100000, 1000000, 10000000])
#ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
#ax.set_xticklabels([r'$10^3$', r'$10^4$', r'$10^5$', r'$10^6$', r'$10^7$'])
ax.set_xticks(R_array[::2])
ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax.set_xticklabels(R_array[::2])


locmin = matplotlib.ticker.LogLocator(base=10.0, subs=(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9),numticks=12) 
ax.xaxis.set_minor_locator(locmin)
ax.xaxis.set_minor_formatter(matplotlib.ticker.NullFormatter())

plt.savefig('output/per_thread_time_vs_thread_time.png', bbox_inches='tight')
