/* 
 * File:   interpolation.h
 * Author: hanshell
 *
 * Created on March 14, 2015, 4:27 PM
 */

#ifndef INTERPOLATION_H
#define	INTERPOLATION_H

#ifdef	__cplusplus
extern "C" {
#endif

float *upsample_frame(float frame[], int frame_size, int upsampling_factor);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERPOLATION_H */

