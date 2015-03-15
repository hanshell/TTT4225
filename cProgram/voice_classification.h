/* 
 * File:   voice_classification.h
 * Author: hanshell
 *
 * Created on March 12, 2015, 7:43 PM
 */

int voiced_unvoiced_detection(float frame[], int frame_length);
int find_zero_crossings(float frame[], int frame_length);
int pitch_period_length(float frame[], int frame_length);

#ifndef VOICE_CLASSIFICATION_H
#define	VOICE_CLASSIFICATION_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* VOICE_CLASSIFICATION_H */

