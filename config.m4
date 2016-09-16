PHP_ARG_ENABLE(piano, whether to add a piano,
[  --enable-piano   Enable piano])

if test "$PHP_PIANO" != "no"; then
  CFLAGS="-lasound"
  PHP_NEW_EXTENSION(piano, piano.c alsa_play.c, $ext_shared)
fi
