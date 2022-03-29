//
// Created by edgallyot on 14/03/2022.
//

#ifndef ID_NAME_VTS_H
#define ID_NAME_VTS_H

#define VTS_ID_TREE "RainGenerator"
#define VTS_PARAMS_N 12

#define VTS_ID_NOISE_TONE "noise_tone"
#define VTS_NAME_NOISE_TONE "Tone"
#define VTS_MIN_NOISE_TONE 0.00001f
#define VTS_MAX_NOISE_TONE 20000.0f
#define VTS_DEFAULT_NOISE_TONE 20000.0f

#define VTS_ID_NOISE_VOL "noise_vol"
#define VTS_NAME_NOISE_VOL "Volume"
#define VTS_MIN_NOISE_VOL 0.0f
#define VTS_MAX_NOISE_VOL 1.0f
#define VTS_DEFAULT_NOISE_VOL 1.0f

#define VTS_ID_BUBBLE_DENSITY "bubble_density"
#define VTS_NAME_BUBBLE_DENSITY "Density"
#define VTS_MIN_BUBBLE_DENSITY 0.0f
#define VTS_MAX_BUBBLE_DENSITY 1.0f
#define VTS_DEFAULT_BUBBLE_DENSITY 1.0f

#define VTS_ID_BUBBLE_PITCH "bubble_pitch"
#define VTS_NAME_BUBBLE_PITCH "Pitch"
#define VTS_MIN_BUBBLE_PITCH 0.0f
#define VTS_MAX_BUBBLE_PITCH 1.0f
#define VTS_DEFAULT_BUBBLE_PITCH 1.0f

#define VTS_ID_BUBBLE_TONE "bubble_tone"
#define VTS_NAME_BUBBLE_TONE "Tone"
#define VTS_MIN_BUBBLE_TONE 0.00001f
#define VTS_MAX_BUBBLE_TONE 20000.0f
#define VTS_DEFAULT_BUBBLE_TONE 0.00001f

#define VTS_ID_BUBBLE_VOLUME "bubble_vol"
#define VTS_NAME_BUBBLE_VOLUME "Volume"
#define VTS_MIN_BUBBLE_VOLUME 0.0f
#define VTS_MAX_BUBBLE_VOLUME 1.0f
#define VTS_DEFAULT_BUBBLE_VOLUME 1.0f

#define VTS_ID_DROP_DENSITY "drop_density"
#define VTS_NAME_DROP_DENSITY "Density"
#define VTS_MIN_DROP_DENSITY 0.0f
#define VTS_MAX_DROP_DENSITY 1.0f
#define VTS_DEFAULT_DROP_DENSITY 1.0f

#define VTS_ID_DROP_PITCH "drop_pitch"
#define VTS_NAME_DROP_PITCH "Pitch"
#define VTS_MIN_DROP_PITCH 0.0f
#define VTS_MAX_DROP_PITCH 1.0f
#define VTS_DEFAULT_DROP_PITCH 1.0f

#define VTS_ID_DROP_TONE "drop_tone"
#define VTS_NAME_DROP_TONE "Tone"
#define VTS_MIN_DROP_TONE 0.00001f
#define VTS_MAX_DROP_TONE 20000.0f
#define VTS_DEFAULT_DROP_TONE 0.00001f

#define VTS_ID_DROP_VOLUME "drop_volume"
#define VTS_NAME_DROP_VOLUME "Volume"
#define VTS_MIN_DROP_VOLUME 0.0f
#define VTS_MAX_DROP_VOLUME 1.0f
#define VTS_DEFAULT_DROP_VOLUME 1.0f

#define VTS_ID_SPREAD "global_spread"
#define VTS_NAME_SPREAD "Spread"
#define VTS_MIN_SPREAD  0.0f
#define VTS_MAX_SPREAD 1.0f
#define VTS_DEFAULT_SPREAD 1.0f

#define VTS_ID_VOLUME "global_volume"
#define VTS_NAME_VOLUME "Volume"
#define VTS_MIN_VOLUME  0.0f
#define VTS_MAX_VOLUME 1.0f
#define VTS_DEFAULT_VOLUME 1.0f

enum RainParameters
{
    Noise_Tone = 0,
    Noise_Volume,
    Bubble_Density,
    Bubble_Pitch,
    Bubble_Tone,
    Bubble_Volume,
    Drop_Density,
    Drop_Pitch,
    Drop_Tone,
    Drop_Volume,
    Volume,
    Spread
};

enum Envelopes
{
    Parabolic,
    Exponential,
    Guassian
};

#endif //ID_NAME_VTS_H
