// An example program demonstrating how to generate normal distributed
// random mumbers, and to write the generated data to a wav-file as
// float numbers. 
// See the libsndfile documentation for details about format specifications
// (http://www.mega-nerd.com/libsndfile/api.html)
//
// Written by: T. Svendsen, Jan 2014


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sndfile.h>

int rand_gauss (float *x, int N);

/////////////////////////////////////////////////////////////////////////////
#define OUT "noise.wav"

float *randNoise(int N){
	float *Array = NULL;       // Array for holding the generated data
	//int N=100;     // Number of samples
	char *outfile=OUT; // Filename to write data to

	SNDFILE *sndfile;
	SF_INFO sfinfo ;
	//sf_count_t Nret;
	
	// Need to set format information for libsndfile
	memset (&sfinfo, 0, sizeof (sfinfo)) ;
	sfinfo.channels=1;
	sfinfo.samplerate=16000;
	sfinfo.format=SF_FORMAT_WAV | SF_FORMAT_FLOAT;
	
	// Open the wav file for storing the generated data
	if ((sndfile = sf_open(outfile, SFM_WRITE, &sfinfo)) == NULL)
	{	printf ("Error : Not able to open output file '%s'\n", outfile) ;
		exit (1) ;
	} ;
	
	// Allocate memory for holding the normal distributed data
	if ((Array=(float *)calloc(N, sizeof(*Array))) == NULL) exit(1);
	
	// Generate the data
	rand_gauss(Array,N);
 
	//// Write data to file
	//if ((Nret=sf_write_float(sndfile, Array, (sf_count_t) N)) != (sf_count_t) N){
	//	printf("Error: Only %lld of %d samples written to file %s\n",Nret, N, outfile);
	//} else {
	//	printf("%lld items written to file %s\n",Nret,outfile);
	//}
	
	// Clean up
	sf_close(sndfile);
        return Array;
}
