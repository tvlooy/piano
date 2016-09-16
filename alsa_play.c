/* alsa_play.c */

/* System libraries */
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <unistd.h>

/* Include PHP API */
#include "php.h"

void alsa_play(long freq, long ms) {
    unsigned int pcm, tmp, dir;
    int rate, channels, seconds;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    char *buff;
    int buff_size, loops;

    int fd;

    if (freq == 0) {
      printf("0\n");
      usleep(ms);

      return;
    }

    rate = 22050;
    channels = 2;

    /* Open the PCM device in playback mode */
    if (pcm = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
        printf("ERROR: Can't open \"%s\" PCM device. %s\n", "default", snd_strerror(pcm));

    /* Allocate parameters object and fill it with default values*/
    snd_pcm_hw_params_alloca(&params);

    snd_pcm_hw_params_any(pcm_handle, params);

    /* Set parameters */
    if (pcm = snd_pcm_hw_params_set_access(pcm_handle, params,
                    SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
        printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(pcm));

    if (pcm = snd_pcm_hw_params_set_format(pcm_handle, params,
                        SND_PCM_FORMAT_S16_LE) < 0)
        printf("ERROR: Can't set format. %s\n", snd_strerror(pcm));

    if (pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, channels) < 0)
        printf("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));

    if (pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0) < 0)
        printf("ERROR: Can't set rate. %s\n", snd_strerror(pcm));

    /* Write parameters */
    if (pcm = snd_pcm_hw_params(pcm_handle, params) < 0)
        printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));

    /* Resume information */
    printf("PCM name: '%s'\n", snd_pcm_name(pcm_handle));

    printf("PCM state: %s\n", snd_pcm_state_name(snd_pcm_state(pcm_handle)));

    snd_pcm_hw_params_get_channels(params, &tmp);
    printf("channels: %i ", tmp);

    if (tmp == 1)
        printf("(mono)\n");
    else if (tmp == 2)
        printf("(stereo)\n");

    snd_pcm_hw_params_get_rate(params, &tmp, 0);
    printf("rate: %d bps\n", tmp);

    /* Allocate buffer to hold single period */
    snd_pcm_hw_params_get_period_size(params, &frames, 0);

    buff_size = frames * channels * 2 /* 2 -> sample size */;
    buff = (char *) malloc(buff_size);

    snd_pcm_hw_params_get_period_time(params, &tmp, NULL);

    if (freq == 1) {
      printf("C\n");
      fd = open("c.wav", O_RDONLY);
    } else if (freq == 2) {
      printf("D\n");
      fd = open("d.wav", O_RDONLY);
    } else if (freq == 3) {
      printf("E\n");
      fd = open("e.wav", O_RDONLY);
    } else if (freq == 4) {
      printf("F\n");
      fd = open("f.wav", O_RDONLY);
    } else if (freq == 5) {
      printf("G\n");
      fd = open("g.wav", O_RDONLY);
    } else if (freq == 6) {
      printf("A\n");
      fd = open("a.wav", O_RDONLY);
    } else if (freq == 7) {
      printf("B\n");
      fd = open("b.wav", O_RDONLY);
    } else if (freq == 8) {
      printf("C6\n");
      fd = open("c6.wav", O_RDONLY);
    } else if (freq == 9) {
      printf("D6\n");
      fd = open("d6.wav", O_RDONLY);
    } else if (freq == 10) {
      printf("E6\n");
      fd = open("e6.wav", O_RDONLY);
    } else if (freq == 11) {
      printf("F6\n");
      fd = open("f6.wav", O_RDONLY);
    } else {
      printf("G6\n");
      fd = open("g6.wav", O_RDONLY);
    }

    for (loops = ms * 1000 / tmp; loops > 0; loops--) {
        if (pcm = read(fd, buff, buff_size) == 0) {
            printf("Early end of file.\n");
            return;
        }

        if (pcm = snd_pcm_writei(pcm_handle, buff, frames) == -EPIPE) {
            printf("XRUN.\n");
            snd_pcm_prepare(pcm_handle);
        } else if (pcm < 0) {
            printf("ERROR. Can't write to PCM device. %s\n", snd_strerror(pcm));
        }
    }
    close(fd);

    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
    free(buff);
}
