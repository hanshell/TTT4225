/* 
 * File:   decimation.h
 * Author: hanshell
 *
 * Created on March 14, 2015, 3:48 PM
 */

#ifndef DECIMATION_H
#define	DECIMATION_H

#ifdef	__cplusplus
extern "C" {
#endif

float *downsample_frame(float frame[], int frame_size, int downsample_factor);

#ifdef	__cplusplus
}
#endif

#endif	/* DECIMATION_H */

