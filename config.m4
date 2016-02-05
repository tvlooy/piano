PHP_ARG_ENABLE(piano, whether to add a piano,
[  --enable-piano   Enable piano])

if test "$PHP_PIANO" != "no"; then
  PHP_NEW_EXTENSION(piano, piano.c, $ext_shared)
fi
