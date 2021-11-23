import numpy as np
import matplotlib as mpl
mpl.use("Agg")

import matplotlib.pyplot as plt

mpl.rcParams.update({'font.size': 28})

def remove_pad(data):
    return data[2:-2,2:-2]


save_path   = "output/plate_temperature.png"
plate_init  = remove_pad(np.genfromtxt("output/T_init.csv",delimiter=","))
plate_final = remove_pad(np.genfromtxt("output/T_final.csv",delimiter=","))

fig = plt.figure(figsize= (16,6), dpi= 200)

plt.subplot(1,2,1)
vmax = np.max(plate_init)
vmin = np.min(plate_init)
plt.imshow(plate_init, vmin= vmin, vmax= vmax, cmap= 'jet')
plt.title('Initial')
plt.colorbar()

plt.subplot(1,2,2)
vmax = np.max(plate_final)
vmin = np.min(plate_final)
plt.imshow(plate_final, vmin= vmin, vmax= vmax)
plt.title('Final')
plt.colorbar()

plt.savefig(save_path)
