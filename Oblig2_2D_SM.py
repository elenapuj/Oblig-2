import numpy as np
import matplotlib.pyplot as plt
from typing import List



#AVERAGE MAGNETIZATION


#First we open the correspondent file and extract the real part of the correlation function

with  open("M.txt", "r") as  infile:

	lines = infile.readlines()[1:]


	T: List[float] = []
	m_exp: List[float] = []

	for  line in  lines:

		vals = line.split()
		T.append(float(vals [0]))
		m_exp.append(float(vals [1]))




#Then, we plot the data

plt.figure()
plt.plot(T, m_exp, color = 'hotpink' )
plt.title(r'Average magnetization vs T/J', fontsize=10)
plt.ylabel("<m>" )
plt.xlabel("T/J")
plt.grid(True)
plt.savefig("m_vs_T.pdf")






#AVERAGE SQUARED MAGNETIZATION


#We will basically repeat the same process changing the analized quantity

with  open("M2.txt", "r") as  infile:

	lines = infile.readlines()[1:]

	m2_exp: List[float] = []

	for  line in  lines:

		vals = line.split()
		m2_exp.append(float(vals [1]))



plt.figure()
plt.plot(T, m2_exp, color = 'hotpink' )
plt.title(r'Average of |m²| vs T/J', fontsize=10)
plt.ylabel("<|m²|>" )
plt.xlabel("T/J")
plt.grid(True)
plt.savefig("m2_vs_T.pdf")






#GAMMA FUNCTION


#Now, we will basically graph the gamma function against T/J

with  open("G_L8.txt", "r") as  infile:

	lines = infile.readlines()[1:]

	G_L8: List[float] = []

	for  line in  lines:

		vals = line.split()
		G_L8.append(float(vals [1])/8)




with  open("G_L16.txt", "r") as  infile:

	lines = infile.readlines()[1:]

	G_L16: List[float] = []

	for  line in  lines:

		vals = line.split()
		G_L16.append(float(vals [1])/16)



with  open("G_L32.txt", "r") as  infile:

        lines = infile.readlines()[1:]

        G_L32: List[float] = []

        for  line in  lines:

                vals = line.split()
                G_L32.append(float(vals [1])/32)




plt.figure()
plt.plot(T, G_L8, label = 'L = 8', color = 'hotpink' )
plt.plot(T, G_L16, label = 'L = 16', color = 'orange')
plt.plot(T, G_L32, label = 'L = 32', color = 'mediumseagreen')
plt.title(r'Γ/L vs T/J for different values of L', fontsize=10)
plt.ylabel("Γ/L" )
plt.xlabel("T/J")
plt.legend()
plt.grid(True)
plt.savefig("Gammas.pdf")
