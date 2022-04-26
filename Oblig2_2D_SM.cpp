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

const double pconnect = 1 - exp(T);  //Connection probability

const int NCLUSTERS = 3;  //Number of cluster builds in one MC step

const int NESTEPS = 10000;  //Number of equilibrium MC steps

const int NMSTEPS = 10000;  //Number of measurement MC steps

const int NBINS = 10;  //Number of measurement bins

Mat <int> S(N, N);  //The spin array

vec M(q);  //Number of spins in each state

cx_vec W(q);  //Order parameter weights

vector <int> pos(N);





//Now we will define some methods in order to manipulate the lattice

int xpos (int i){

	return i%L;

}


int Nbr(int i, int j, int dir){

	if (dir == 0){

		pos[0] = i;

		pos[1] = (xpos(j) + 1) % L;

	}


	else if(dir == 1){

		pos[0] = i;

		pos[1] = (xpos(j) - 1 + L) % L;

	}


	else if(dir == 2){

		pos[0] = (xpos(i) + 1) % L;

		pos[1] = j;

	}


	else{

		pos[0] = (xpos(i) - 1 + L) % L;

		pos[1] = j;

	}

	return 0;

}


void FlipandBuildFrom(int s, int u){

	int oldstate( S[s, u] ), newstate( (S[s,u]+1) % q );

	S[s, u] = newstate;  //Flip spin

	M[oldstate]--; M[newstate]++;  //Update spin counts

	for(int dir = 0; dir < 4; dir++){

		Nbr(s, u, dir);

		int i = pos[0];

		int j = pos[1];

		if(S[i, j] == oldstate){

			if(rand() / (RAND_MAX + 1.) < pconnect){

				FlipandBuildFrom(i, j);

			}

		}

	}

}




//We finally start to perform the MC method

int main (){


	//Initialize the weights

	for(int s = 0; s < q; s++){

		W(s) = complex<double>(cos( 2 * PI * s / q ), sin( 2 * PI * s / q ));

	}



	//Initialize to the all spins=zero state (SUSTITUUIR POR CREAR DIRECTAMENTE UNA MATRIZ DE CEROS)

	for(int i = 0; i < N; i++){

		for(int j = 0; j < N; j++){

			S[i,j] = 0;

		}

	}



	//Initialize the counters

	for(int s = 1; s < q; s++){

		M[s] = 0;

	}

	M[0] = N*N;



	srand( (unsigned) time(0) );  //Initialize random number generation



	//We now equilibrate the matrix fliping random clusters NESTEPS time

	for(int t = 0; t < NESTEPS; t++){

		for(int c = 0; c < NCLUSTERS; c++){

			FlipandBuildFrom(rand() % N, rand() % N);

		}

	}



	//Finally we perform the measure

	for(int n =0; n < NBINS; n++){

		//We define some variables that we will fill out with our measurements

		complex<double> m( 0. , 0. );

		double m1 = 0, m2 = 0, m4 = 0;



		//Then we make NMSTEPS flips and measure

		for(int t = 0; t < NMSTEPS; t++){

			for(int c = 0; c < NCLUSTERS; c++){

				 FlipandBuildFrom(rand() % N, rand() % N);

			}

			complex<double> tm (0., 0.) ;

			for(int s = 0; s < q; s++){

				tm+= W[s] * double (M[s]);

			}

			tm /= N;

			m += tm;
			m1 += abs(tm);
			m2 += abs(tm) * abs(tm);
			m4 += m2 * m2;

		}

		m /= NMSTEPS;
		m1 /= NMSTEPS;
		m2 /= NMSTEPS;
		m4 /= NMSTEPS;

		cout << m << " " << m1 << " " << m2 << " " << m4 << endl;

	}


	return 0;

}
