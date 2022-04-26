#include <armadillo>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <complex>

using namespace arma;
using namespace std;

#define PI 3.141592653589793238462643



//First, we introduce the desired settings of the system that we want to study

const int q = 3;  //Number of values each spin can take

const int L = 16;  //System size

const double T = 0.5;  //Temperature in units of J

const int N = L;  //Total number of spins

const double pconnect = 1 - exp(-1/T);  //Connection probability

const int NCLUSTERS = 1;  //Number of cluster builds in one MC step

const int NESTEPS = 10000;  //Number of equilibrium MC steps

const int NMSTEPS = 10000;  //Number of measurement MC steps

const int NBINS = 10;  //Number of measurement bins

vector <int> S (N);  //The spin array

vector <int> M(q);  //Number of spins in each state





//Now we will define some methods in order to manipulate the lattice

int xpos (int i) {

	return i%L;

}


int Nbr(int i , int dir){

	int x = xpos(i);

	if (dir == 0){

		return ( (x+1) % L );

	}


	else{

		return ( (x-1+L) % L );

	}

}


void FlipandBuildFrom(int s){

	int oldstate( S[s] ), newstate( (S[s]+1) % q );

	S[s] = newstate;  //Flip spin

	M[oldstate]--; M[newstate]++;  //Update spin counts

	for(int dir = 0; dir <2; dir++){

		int j = Nbr(s, dir);

		if(S[j] == oldstate){

			if(rand() / (RAND_MAX + 1.) < pconnect){

				FlipandBuildFrom(j);

			}

		}

	}

}




//We finally start to perform the MC method

int main (){

	//Initialize to the all spins=zero state

	for(int i = 0; i < N; i ++){

		S[i] = 0;

	}



	//Initialize the counters

	for(int s = 1; s < q; s++){

		M[s] = 0;

	}

	M[0] = N;


	srand( (unsigned) time(0) );  //Initialize random number generation



	//We now equilibrate the matrix fliping random clusters NESTEPS time

	for(int t = 0; t < NESTEPS; t++){

		for(int c = 0; c < NCLUSTERS; c++){

			FlipandBuildFrom(rand() % N);

		}

	}




	//Finally we perform the measure


	//We create a file that we will fill out with our measurements



	ofstream ofile;
	ofile.open("C(r)_T2.txt");  //That is an example name, but with this program we have generated four different files
	ofile << scientific;


	cx_vec C(N);

	for(int s = 0; s < N; s++){

		complex<double> m0(0., 0.);
		complex<double> mr(0., 0.);
		complex<double> m0r(0., 0.);

		for(int t = 0; t < NMSTEPS; t++){

			for(int c =0; c < NCLUSTERS; c++){

				FlipandBuildFrom(rand() % N);

			}


			m0 += complex<double>(cos( 2 * PI * S[0] / q ), -sin( 2 * PI * S[0] / q ));
                	mr += complex<double>(cos( 2 * PI * S[s] / q ), sin( 2 * PI * S[s] / q ));
			m0r += complex<double>(cos( 2 * PI * S[0] / q ), -sin( 2 * PI * S[0] / q )) * complex<double>(cos( 2 * PI * S[s] / q ), sin( 2 * PI * S[s] / q ));

		}

		m0 /= NMSTEPS;
        	mr /= NMSTEPS;
        	m0r /= NMSTEPS;


		C(s) = m0r - (m0*mr);

        	ofile << real(C(s)) << "      " << imag(C(s)) << endl;

	}

	ofile.close();


	return 0;

}
