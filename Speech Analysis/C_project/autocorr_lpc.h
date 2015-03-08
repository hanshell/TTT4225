/* 
 * File:   autocorr_lpc.h
 * Author: hanshell
 *
 * Created on March 8, 2015, 2:08 PM
 */

#define FRAME_LENGTH 16
#define PREDICTION_ORDER 4


float *autocorrelation(float frame[], int frame_size);
float *levinson_durbin_recursion(float frame[], int order);

#ifndef AUTOCORR_LPC_H
#define	AUTOCORR_LPC_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* AUTOCORR_LPC_H */

