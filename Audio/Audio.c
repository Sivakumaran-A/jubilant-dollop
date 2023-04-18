#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <stdint.h>

#include <SDL2/SDL.h>

#define SAMPLE_RATE 44100

#define AMPLITUDE 32767

#define FREQUENCY 440

void fill_audio_buffer(void *userdata, Uint8 *stream, int len) {

    int i;

    Sint16 *samples = (Sint16*)stream;

    int num_samples = len / 2;

    double freq = FREQUENCY;

    double amplitude = AMPLITUDE;

    double phase = 0.0;

    double phase_step = (freq * 2.0 * M_PI) / SAMPLE_RATE;

    for (i = 0; i < num_samples; i++) {

        samples[i] = (Sint16)(amplitude * sin(phase));

        phase += phase_step;

        if (phase > 2.0 * M_PI) {

            phase -= 2.0 * M_PI;

        }

    }

}

int main(int argc, char **argv) {

    SDL_AudioSpec want, have;

    SDL_AudioDeviceID dev;

    SDL_memset(&want, 0, sizeof(want));

    want.freq = SAMPLE_RATE;

    want.format = AUDIO_S16SYS;

    want.channels = 1;

    want.samples = 4096;

    want.callback = fill_audio_buffer;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);

    if (dev == 0) {

        fprintf(stderr, "Failed to open audio device: %s\n", SDL_GetError());

        return 1;

    }

    SDL_PauseAudioDevice(dev, 0);

    printf("Playing sine wave at %d Hz\n", FREQUENCY);

    SDL_Delay(5000);

    SDL_CloseAudioDevice(dev);

    return 0;

}

