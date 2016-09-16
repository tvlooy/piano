/* piano.c */

/* Include PHP API */
#include "php.h"

/* This module's header file */
#include "php_piano.h"

static zend_op_array* (*old_compile_file)(zend_file_handle* file_handle, int type);

/* Define function entries */
ZEND_BEGIN_ARG_INFO(arginfo_play_piano, 0)
    ZEND_ARG_INFO(0, note)
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

PHP_INI_BEGIN()
PHP_INI_ENTRY("piano.play_opcodes", "0", PHP_INI_ALL, NULL)
PHP_INI_END()

/* Translate opcodes into piano tunes */
void play_oparray(zend_op_array *op_array) {
    int i;
    char note[3] = "";

    for (i = 0; i < op_array->last; i++) {
        zend_op op = op_array->opcodes[i];

        if (op.opcode < 15) {
            strcpy(note, "C");
        } else if (op.opcode < 30) {
            strcpy(note, "D");
        } else if (op.opcode < 45) {
            strcpy(note, "E");
        } else if (op.opcode < 60) {
            strcpy(note, "F");
        } else if (op.opcode < 75) {
            strcpy(note, "G");
        } else if (op.opcode < 90) {
            strcpy(note, "A");
        } else if (op.opcode < 105) {
            strcpy(note, "B");
        } else if (op.opcode < 120) {
            strcpy(note, "C6");
        } else if (op.opcode < 135) {
            strcpy(note, "D6");
        } else if (op.opcode < 150) {
            strcpy(note, "E6");
        } else if (op.opcode < 165) {
            strcpy(note, "F6");
        } else {
            strcpy(note, "G6");
        }

        printf("[%s (%d) sounds like %s]\n", zend_get_opcode_name(op.opcode), op.opcode, note);
        alsa_play(note, 200 + op.opcode * 2);
    }
}

/* Hook opcode compilation */
static zend_op_array *piano_compile_file(zend_file_handle *file_handle, int type) {
    zend_op_array *op_array;

    op_array = old_compile_file (file_handle, type);
    if (INI_BOOL("piano.play_opcodes") == 1) {
        play_oparray(op_array);
    }

    return op_array;
}

/* Install module */
ZEND_GET_MODULE(piano)

/* Module init */
PHP_MINIT_FUNCTION(piano) {
    REGISTER_STRING_CONSTANT("NOTE_0",   "0", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_C",   "C", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_D",   "D", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_E",   "E", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_F",   "F", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_G",   "G", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_A",   "A", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_B",   "B", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_C6", "C6", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_D6", "D6", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_E6", "E6", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_F6", "F6", CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("NOTE_G6", "G6", CONST_CS | CONST_PERSISTENT);

    REGISTER_INI_ENTRIES();

    return SUCCESS;
}

/* Request init */
PHP_RINIT_FUNCTION(piano) {
    old_compile_file = zend_compile_file;
    zend_compile_file = piano_compile_file;

    return SUCCESS;
}

/* function play_piano(string $note, int ms): void */
PHP_FUNCTION(play_piano) {
    char *note = NULL;
    size_t note_len = 0;
    long ms;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl", &note, &note_len, &ms) == FAILURE) {
        return;
    }

    alsa_play(note, ms);

    return;
}
