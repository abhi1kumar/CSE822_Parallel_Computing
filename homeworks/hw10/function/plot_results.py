import numpy as np 
import matplotlib as mpl 
mpl.use("Agg")
import matplotlib.pyplot as plt 


ts = np.array([1.19194e-5, 1.2124e-5, 1.35543e-5, 1.76506e-5, 2.14539e-5, 
                2.83979e-5, 4.30975e-5, 7.74639e-5, 0.000130383, 0.000210377, 
                0.000392108])

arry_sz = 2**np.arange(3,14)

fig = plt.figure()

plt.loglog(arry_sz, ts)

plt.xlabel("B Array size")
plt.ylabel("Run time")

plt.grid()
plt.title("Run time vs. Array size")
plt.savefig("final_plot.png")