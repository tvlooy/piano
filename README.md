# Piano

This is a PHP extension to "play the piano" from PHP userland.

## How does it work

  - This only works on Linux.
  - This only works on PHP 7.
  - This module uses the PC speaker, so make sure you have the Linux kernal module ```pcspkr``` loaded.
  - This is not by default so check with ```lsmod``` and ```sudo insmod pcspkr``` if needed.
  - Start php with sudo because we will try to write to ```/dev/console```.

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

Call function ```play_piano(100, 500);``` to play 100 Hz for half a second. Or use the pre-defined constants:

  - PIANO_0  (to pause beteen notes)
  - PIANO_C
  - PIANO_D
  - PIANO_E
  - PIANO_F
  - PIANO_G
  - PIANO_A
  - PIANO_B
  - PIANO_C6
  - PIANO_D6
  - PIANO_E6
  - PIANO_F6
  - PIANO_G6

There is a proof of concept song in ```test_happy.php```.

