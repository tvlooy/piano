/* alsa_play.c */

/* System libraries */
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <unistd.h>

/* Include PHP API */
#include "php.h"

void alsa_play(char *note, long ms) {
    unsigned int pcm, tmp;
    int rate, channels;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    char *buff;
    int buff_size, loops;
    int fd;
    char filename[7] = "";

    rate = 22050;
    channels = 2;

    if (note[0] == '0' || strlen(note) > 2) {
        usleep(ms * 1000);

        return;
    }

    /* Open the PCM device in playback mode */
    if (pcm = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        printf("ERROR: Can't open \"%s\" PCM device. %s\n", "default", snd_strerror(pcm));
    }

    /* Allocate parameters object and fill it with default values */
    snd_pcm_hw_params_alloca(&params);

    snd_pcm_hw_params_any(pcm_handle, params);

    /* Set parameters */
    if (pcm = snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(pcm));
    }

    if (pcm = snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE) < 0) {
        printf("ERROR: Can't set format. %s\n", snd_strerror(pcm));
    }

    if (pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, channels) < 0) {
        printf("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));
    }

    if (pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0) < 0) {
        printf("ERROR: Can't set rate. %s\n", snd_strerror(pcm));
    }

    /* Write parameters */
    if (pcm = snd_pcm_hw_params(pcm_handle, params) < 0) {
        printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));
    }

    /* Allocate buffer to hold single period */
    snd_pcm_hw_params_get_period_size(params, &frames, 0);

    buff_size = frames * channels * 2 /* 2 -> sample size */;
    buff = (char *) malloc(buff_size);

    snd_pcm_hw_params_get_period_time(params, &tmp, NULL);

    strcat(filename, note);
    strcat(filename, ".wav");
    fd = open(filename, O_RDONLY);

    if (fd <= 0) {
        free(buff);

        return;
    }

    for (loops = ms * 1000 / tmp; loops > 0; loops--) {
        if (pcm = read(fd, buff, buff_size) == 0) {
            close(fd);
            free(buff);

            return;
        }

        if (pcm = snd_pcm_writei(pcm_handle, buff, frames) == -EPIPE) {
            snd_pcm_prepare(pcm_handle);
        }
    }
    close(fd);

    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
    free(buff);
}
