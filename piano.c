/* piano.c */

/* Include PHP API */
#include "php.h"

/* This module's header file */
#include "php_piano.h"

//static zend_op_array* (*old_compile_file)(zend_file_handle* file_handle, int type);
//static zend_op_array* vld_compile_file(zend_file_handle*, int);

/* Define function entries */
ZEND_BEGIN_ARG_INFO(arginfo_play_piano, 0)
  ZEND_ARG_INFO(0, freq)
  ZEND_ARG_INFO(0, ms)
ZEND_END_ARG_INFO();

zend_function_entry piano_functions[] = {
    PHP_FE(play_piano, arginfo_play_piano)
    PHP_FE_END
};

zend_module_entry piano_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_PIANO_EXTNAME,
    piano_functions,        /* Function entries */
    PHP_MINIT(piano),       /* Module init */
    NULL,                   /* Module shutdown */
    PHP_RINIT(piano),       /* Request init */
    NULL,                   /* Request shutdown */
    NULL,                   /* Module information */
    PHP_PIANO_VERSION,
    STANDARD_MODULE_PROPERTIES
};

/*
void play_oparray(zend_op_array *op_array)
{
	unsigned int i;

	for (i = 0; i < op_array->last; i++) {
    zend_op op = op_array->opcodes[i];
    printf("[%s (%d)]\n", zend_get_opcode_name(op.opcode), op.opcode);

    if (op.opcode < 15) {
        //play_piano(261, 500); //PG("PIANO_C"), 500);
    } else if (op.opcode < 30) {
        // play_piano(261, 500);
    } else if (op.opcode < 45) {
    } else if (op.opcode < 60) {
    } else if (op.opcode < 75) {
    } else if (op.opcode < 90) {
    } else if (op.opcode < 105) {
    } else if (op.opcode < 120) {
    } else if (op.opcode < 135) {
    } else if (op.opcode < 150) {
    } else if (op.opcode < 165) {
    } else {
      //
    }
	}
}*/

//void play_piano_c(int freq, int ms) {
//  int console_fd;

//  if ((console_fd = open("/dev/console", O_WRONLY)) == -1) {
    //  fprintf(stderr, "Can't play the piano. Could not open /dev/console for writing.\n");
  //    exit(1);
//  }

  //if (freq == 0) {
    //  ioctl(console_fd, KIOCSOUND, 0);
  //} else {
      /* the PC uses a base rate of 1,193,180 Hz, generated by an oscillator chip */
//      ioctl(console_fd, KIOCSOUND, 1193180 / freq);
//  }
  /* beep for given duration */
//  usleep(ms * 1000);

  /* KIOCSOUND generates an endless beep, we have to stop beeping */
//  ioctl(console_fd, KIOCSOUND, 0);

//  close(console_fd);
//}

/* Hook compilation */
//static zend_op_array *piano_compile_file(zend_file_handle *file_handle, int type) {
//    zend_op_array *op_array;

//    op_array = old_compile_file (file_handle, type);
//    play_oparray(op_array);

//    return op_array;
//}

/* Install module */
ZEND_GET_MODULE(piano)

/* Module init */
PHP_MINIT_FUNCTION(piano) {
    REGISTER_LONG_CONSTANT("PIANO_0",   0, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_C",   1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_D",   2, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_E",   3, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_F",   4, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_G",   5, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_A",   6, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_B",   7, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_C6",  8, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_D6",  9, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_E6", 10, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_F6", 11, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("PIANO_G6", 12, CONST_CS | CONST_PERSISTENT);

    return SUCCESS;
}

/* Request init */
PHP_RINIT_FUNCTION(piano) {
//    old_compile_file = zend_compile_file;
//    zend_compile_file = piano_compile_file;

    return SUCCESS;
}

/* function play_piano(int $freq, int ms): void */
PHP_FUNCTION(play_piano) {
  long freq;
  long ms;

  if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &freq, &ms) == FAILURE) {
      return;
  }

  alsa_play(freq, ms);
  RETURN_TRUE;
}
/*
    int freq;
    int ms;
int console_fd;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &freq, &ms) == FAILURE) {
        return;
    }

    //play_piano_c(freq, ms);

    //int console_fd;

    if ((console_fd = open("/dev/console", O_WRONLY)) == -1) {
        fprintf(stderr, "Can't play the piano. Could not open /dev/console for writing.\n");
        exit(1);
    }

    if (freq == 0) {
        ioctl(console_fd, KIOCSOUND, 0);
    } else {
        /* the PC uses a base rate of 1,193,180 Hz, generated by an oscillator chip * /
        ioctl(console_fd, KIOCSOUND, 1193180 / freq);
    }
    /* beep for given duration * /
    usleep(ms * 1000);

    /* KIOCSOUND generates an endless beep, we have to stop beeping * /
    ioctl(console_fd, KIOCSOUND, 0);

    close(console_fd);
}
*/
