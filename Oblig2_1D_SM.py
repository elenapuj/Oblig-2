import numpy as np
import matplotlib.pyplot as plt
from typing import List



#FIRST CASE: T/J = 0.25


#First we open the correspondent file and extract the real part of the correlation function

with  open("C(r)_T1.txt", "r") as  infile:

	lines = infile.readlines ()

	Cr1_exp: List[float] = []

	for  line in  lines:

		vals = line.split()
		Cr1_exp.append(float(vals [0]))



#After that, we create a vector containing the values for r

r = np.linspace(0, 15, 16)



#Then we calculate our theoretical correlation function

N = 16

L1 = np.exp(1/0.25) - 1

L2 = np.exp(1/0.25) + 2

Z = 2*(L1)**N + L2**N

Cr1_t = ( 1 / Z ) * ( L2**(N-r)*L1**r + L1**(N-r)*L2**r + L1**N )




#Finally, we plot everything together

plt.figure()
plt.plot(r, Cr1_exp, label = 'Experimental values', color = 'hotpink' )
plt.plot(r, Cr1_t, label = 'Theoretical values', color = 'orange')
plt.title(r'Correlation function at T/J = 0.25', fontsize=10)
plt.ylabel("C(r)" )
plt.xlabel("r")
plt.legend()
plt.grid(True)
plt.savefig("C(r)_T1.pdf")






#SECOND CASE: T/J = 0.5

#We will basically repeat the same process changing the temperature

with  open("C(r)_T2.txt", "r") as  infile:

        lines = infile.readlines ()

        Cr2_exp: List[float] = []

        for  line in  lines:

                vals = line.split()
                Cr2_exp.append(float(vals [0]))



r = np.linspace(0, 15, 16)


L1 = np.exp(1/0.5) - 1

L2 = np.exp(1/0.5) + 2

Z = 2*(L1)**N + L2**N

Cr2_t = ( 1 / Z ) * ( L2**(N-r)*L1**r + L1**(N-r)*L2**r + L1**N )




plt.figure()
plt.plot(r, Cr2_exp, label = 'Experimental values', color = 'hotpink' )
plt.plot(r, Cr2_t, label = 'Theoretical values', color = 'orange')
plt.title(r'Correlation function at T/J = 0.5', fontsize=10)
plt.ylabel("C(r)" )
plt.xlabel("r")
plt.legend()
plt.grid(True)
plt.savefig("C(r)_T2.pdf")
