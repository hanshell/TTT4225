/*
 **
 ** Example program for filtering a sound file with an FIR filter and saving the filtered
 ** waveform to another sound file. 
 **
 ** The sound files are expected to be in WAV (RIFF) format, and the program uses
 ** the libsndfile library for reading and writing them.
 ** The filter coefficients are read from a text file. The first line of the filter file
 ** specifies the filter length and the second line will have the filter coefficients. 
 **
 ** Copyright Torbjorn Svendsen <torbjorn@iet.ntnu.no>
 **
 ** Adapted from sndfile-mix-to-mono by Erik de Castro Lopo <erikd@mega-nerd.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 2 or version 3 of the
 ** License.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common.h"

static void usage_exit (void) ;
static void fir_filter (SNDFILE * infile, SNDFILE * outfile, char * firfile) ;

#define COEFFS "lpcoeff.txt"
#define BUFSIZE 1024

int main (int argc, char ** argv)
{
	SNDFILE *infile, *outfile ;
	SF_INFO sfinfo ;
	char * firfile = COEFFS;
	
	if ((argc != 4) && (argc != 3))
		usage_exit () ;
	
	if (strcmp (argv [1], argv [2]) == 0)
	{	printf ("Error : input and output file names are the same.\n") ;
		exit (1) ;
	} ;
	if (argc == 4) {
		firfile = argv[argc -1];
	}
	
	/* Delete the output file if it already exists. */
	remove (argv [2]) ;
	
	/* Allocate and initialize memory, and open the input and output file */
	memset (&sfinfo, 0, sizeof (sfinfo)) ;
	if ((infile = sf_open (argv [1], SFM_READ, &sfinfo)) == NULL)
	{	printf ("Error : Not able to open input file '%s'\n", argv [1]) ;
		sf_close (infile) ;
		exit (1) ;
	} ;
	
    /* If the source is stereo, inform that it will be mixed down to mono */ 
	if (sfinfo.channels != 1)
	{	printf ("Input file '%s' not mono. Will mix to single channel.\n", argv [1]) ;
	} ;
	
	
	if ((outfile = sf_open (argv [2], SFM_WRITE, &sfinfo)) == NULL)
	{	printf ("Error : Not able to open output file '%s'\n", argv [2]) ;
		sf_close (infile) ;
		exit (1) ;
	} ;
	
    /* Do the filtering */
	fir_filter (infile, outfile, firfile) ;
	
	sf_close (infile) ;
	sf_close (outfile) ;
	
	return 0 ;
} /* main */

static void fir_filter (SNDFILE * infile, SNDFILE * outfile, char * firfile)
{	double buffer [BUFSIZE], obuf[BUFSIZE] ;
	sf_count_t count, cnt ;
	float *h, *mem;
	int i, n, nt=0,  m, N, Nuse;
	FILE *fid;
	
	/* Read filter coefficients from file */ 
	if ((fid = fopen(firfile,"r")) == NULL) exit(0);
	
	/* first line gives filter order, use to allocate memory */
	fscanf(fid,"%d",&N);
	if ((h=(float *)calloc(N,sizeof(float))) == NULL) exit(0);
	if ((mem=(float *)calloc(N,sizeof(float))) == NULL) exit(0);	
	
	/* second line contains filter coefficients */
	for (i=0; i<N; i++){
		fscanf(fid,"%f",&h[i]); 
		mem[i]=0;        /* initialize filter memory at the same time */
	}
	fclose(fid);
	
	
	/* read blocks of 1024 samples converted to double from wav file, filter using circular buffer */	
	while ((count = sfx_mix_mono_read_double (infile, buffer, ARRAY_LEN (buffer))) > 0){
		cnt = count;
		for (n=0; n<cnt; n++) {
			obuf[n]=0.0;
			mem[(nt%N)]=buffer[n]; /* nt is total sample number, n is sample no in block */
			Nuse = N; 
			if (nt < N){Nuse=nt;}
			for (m=0; m < Nuse; m++){
				obuf[n]+=h[m]*mem[((nt-m)%N)];
			}
			nt++;
		}
		/* block processed, write block to output wav file */ 
		sf_write_double (outfile, obuf, count) ;
	}
	free(h);
	free(mem);
	return ;
} /* fir_filter */

static void usage_exit (void)
{
	puts ("\n"
		  "Usage :\n\n"
		  "    filtprog <input file> <output file> <filter-coeff file>\n"
		  ) ;
	exit (0) ;
} /* usage_exit */