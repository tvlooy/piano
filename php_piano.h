/* php_piano.h */

#define PHP_PIANO_EXTNAME "piano"
#define PHP_PIANO_VERSION "2.0.0"

PHP_MINIT_FUNCTION(piano);
PHP_RINIT_FUNCTION(piano);

PHP_FUNCTION(play_piano);

void alsa_play(char *note, long ms);
