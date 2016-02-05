/* piano.c */

/* include PHP API */
#include "php.h"

/* this module's header file */
#include "php_piano.h"

/* define the function we want to add */
zend_function_entry piano_functions[] = {
  PHP_FE(play_piano, NULL)
  { NULL, NULL, NULL }
};

/* "piano_functions" refers to the struct defined above */
zend_module_entry piano_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_PIANO_EXTNAME,
  piano_functions,
  NULL, NULL, NULL, NULL, NULL,
  PHP_PIANO_VERSION,
  STANDARD_MODULE_PROPERTIES
};

/* install module */
ZEND_GET_MODULE(piano)

PHP_FUNCTION(play_piano) {
  php_printf("TODO\n");
}
