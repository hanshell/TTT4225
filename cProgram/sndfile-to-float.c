#include <sndfile-to-float.h>

#define BLOCK_SIZE 512

//This function works and gives 92800 values, verified with matlab
//but i have no idea how this number is being reached
void sndfileToFloat(SNDFILE *infile, int channels, float *s)
{
  //because i think we only use mono files the channels var will always be 1
  float buf [channels * BLOCK_SIZE];
  int k, m, readcount;
  //i think readcount reads files in float and places them in the buf
  //reads 512 frames per time. The last one it reads only 128 because there
  //are not 512 left
  int i = 0;
  while ((readcount = sf_readf_float (infile, buf, BLOCK_SIZE)) > 0)
  {
    //512 in all iterations but the last one. Then 128
    for (k = 0; k < readcount; k++)
    {
      // as stated above: channels = 1
      // so this will only run once in each k-for loop
      for (m = 0; m < channels; m++)
      {
        //prints the element on the k'th place in the buffer
        //this is because channels is 1 and m is 0 on every iteration
        //in our case
        s[i] = buf[k];
        //printf("%12.10f\n", buf[k * channels + m]);
        i++;

      }

    }

  }

}


