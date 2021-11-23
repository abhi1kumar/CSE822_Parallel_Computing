import numpy as np 
import matplotlib.pyplot as plt 


case1 = np.genfromtxt("case1.csv", delimiter=",")[:,:-1]
case2 = np.genfromtxt("case2.csv", delimiter=",")[:,:-1]

print(case1.shape)

xs = (2)**np.arange(-9,15,1, dtype=np.double)

colors = [plt.cm.plasma(x) for x in [0.5,0.8]]

avg1 = case1.mean(axis=0)
avg2 = case2.mean(axis=0)

print(xs)

fig = plt.figure(figsize=(8,8))

plt.loglog(xs, avg1, label="Nranks=40", color=colors[0])
plt.loglog(xs, avg2, label="Nranks=41", color=colors[1])

plt.legend()
plt.grid()

plt.xlabel("Message size [GB]", fontsize=18)
plt.ylabel("Comm. Time [sec]", fontsize=18)

plt.title("Comm. Time vs. Message Size",fontsize=18)

plt.savefig("hw8_plot.png")