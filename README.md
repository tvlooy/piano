# Piano

This is a PHP extension to "play the piano" from PHP userland.

## How does it work?

  - This only works on Linux, uses ALSA.
  - This only works on PHP 7.

## Build

```
git clone https://github.com/tvlooy/piano
cd piano
phpize
./configure
make
sudo make install
```

Add the following to your configuration to enable the extension:

```
extension=piano.so
```

## Using

Call function ```play_piano(NOTE_C, 500);``` to play C for half a second.
All notes are pre-defined constants:

  - NOTE_0  (to pause beteen notes)
  - NOTE_C
  - NOTE_D
  - NOTE_E
  - NOTE_F
  - NOTE_G
  - NOTE_A
  - NOTE_B
  - NOTE_C6
  - NOTE_D6
  - NOTE_E6
  - NOTE_F6
  - NOTE_G6

There is a proof of concept song in ```test_happy.php```.

## Opcodes

Another feature in this extension is that it can play opcodes.

There is a small test program in ```test.php```.

```
$ cat test.php
<?php

$i = 'foo';
$j = 'bar';
echo strlen($i) + strlen($j);
````

Now use [VLD](https://github.com/derickr/vld) to show the opcodes:

```
$ php -dextension=vld.so -d vld.active=1 -d vld.execute=0 test.php
Finding entry points
Branch analysis from position: 0
Jump found. Position 1 = -2
filename:       test.php
function name:  (null)
number of ops:  7
compiled vars:  !0 = $i, !1 = $j
line     #* E I O op                           fetch          ext  return  operands
-------------------------------------------------------------------------------------
   3     0  E >   ASSIGN                                                   !0, 'foo'
   4     1        ASSIGN                                                   !1, 'bar'
   5     2        STRLEN                                           ~4      !0
         3        STRLEN                                           ~5      !1
         4        ADD                                              ~6      ~4, ~5
         5        ECHO                                                     ~6
         6      > RETURN                                                   1

branch: #  0; line:     3-    5; sop:     0; eop:     6; out1:  -2
path #1: 0,
```

Now let's use this extension to see and hear how that sounds:

```
$ php -dextension=modules/piano.so -dpiano.play_opcodes=1 test.php
[ZEND_ASSIGN (38) sounds like E]
[ZEND_ASSIGN (38) sounds like E]
[ZEND_STRLEN (121) sounds like D6]
[ZEND_STRLEN (121) sounds like D6]
[ZEND_ADD (1) sounds like C]
[ZEND_ECHO (40) sounds like E]
[ZEND_RETURN (62) sounds like G]
6
```

[There is a demo on YouTube.](https://www.youtube.com/watch?v=_bgDQP_OB2k)

