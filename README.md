# Oblig-2

Here I will explain briefly what does each file contain and how to execute them all.

First, we have the files "Oblig2_1D_SM.cpp" and "Oblig2_2D_SM.cpp". In them, we simulate a 1D and 2D system of particles using boundary conditions.
With the first one, we generate the files "C(r)_T1.txt" and "C(r)_T2.txt" and with the second one we generate the files "M.txt", "M2.txt", "G_L8.txt", "G_L16.txt" and "G_L32.txt". You will find all of these plots in the folder "Data".


For build and executing these .cpp files in your terminal you just have to write (in the case of, for example, the first one):

Build: Oblig2_1D_SM.cpp -o Oblig2_1D_SM.exe -larmadillo
Run: ./Oblig2_1D_SM.exe



Then, with the files "Oblig2_1D_SM.py" and "Oblig2_2D_SM.py" we produce all the plots stored in the folder "Plots". We produce 
