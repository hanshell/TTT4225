// Function for generating Gaussian distributed random numbers

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int rand_gauss (float *x, int N) {
/* Create Gaussian N(0,1) distributed numbers from uniformly distributed numbers using */
/* the Box-Muller transform as described in                                            */
/* D. E. Knuth: The Art of Computer Programming, Vol II, p 104                         */
  float v1,v2,s;
  int i, j, M;
  
  M=N/2;
  
  // Initialize uniform number generator 
  srand(time(NULL));
  
  // Loop - each iteration generates two Gaussian numbers
  for (i=0; i<M; i++){
  j=2*i;
  
  // See Knuth or http://en.wikipedia.org/wiki/Box_Muller_transform
  // for algorithm description
  	do {
    	v1 = 2.0 * ((float) rand()/RAND_MAX) - 1;
    	v2 = 2.0 * ((float) rand()/RAND_MAX) - 1;

    	s = v1*v1 + v2*v2;
  	  } while ( s >= 1.0 );

  	if (s == 0.0) 
    	i=i-1;
  	  else {
    	x[j]=(v1*sqrt(-2.0 * log(s) / s));
		if (j+1<N)
			x[j+1]=(v2*sqrt(-2.0 * log(s) / s));
	  }
  	}
	return 0;
}
