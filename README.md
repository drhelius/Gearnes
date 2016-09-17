Gearnes (currently in development)
=========
<b>Copyright &copy; 2016 by Ignacio Sanchez</b>

----------
[![Build Status](https://travis-ci.org/drhelius/Gearnes.svg?branch=master)](https://travis-ci.org/drhelius/Gearnes)

Gearnes is a Nintendo Entertainment System (NES) / Famicom emulator written in C++ that runs on iOS, Raspberry Pi, Mac, Windows and Linux.

Follow me on Twitter for updates: http://twitter.com/drhelius

----------

Build Instructions
----------------------

### Mac OS X
- You need Qt Creator, included in the Qt 5 SDK.
- Install Xcode and run <code>xcode-select --install</code> in the terminal for the compiler to be available on the command line.
- Install the [Qt 5 SDK for Mac OS](http://qt-project.org/downloads).
- Download [SDL 2](http://www.libsdl.org/download-2.0.php) source code. Then run this commands:
``` shell
./configure
make
sudo make install
```
- Open the Gearnes Qt project with Qt Creator and build.

### Linux
- Install dependencies (Ubuntu: <code>sudo apt-get install build-essential qt5-default qttools5-dev-tools freeglut3-dev libsdl2-dev libglew-dev</code>).
- Move to the <code>platforms/linux/Gearnes/</code> folder and run <code>qmake -o Makefile Gearnes.pro && make</code> to build the project.
- In Ubuntu I had to <code>export SDL_AUDIODRIVER=ALSA</code> before running the emulator for the sound to work properly.

License
-------

<i>Gearnes - Nintendo Entertainment System / Famicom Emulator</i>

<i>Copyright (C) 2016  Ignacio Sanchez</i>

<i>This program is free software: you can redistribute it and/or modify</i>
<i>it under the terms of the GNU General Public License as published by</i>
<i>the Free Software Foundation, either version 3 of the License, or</i>
<i>any later version.</i>

<i>This program is distributed in the hope that it will be useful,</i>
<i>but WITHOUT ANY WARRANTY; without even the implied warranty of</i>
<i>MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the</i>
<i>GNU General Public License for more details.</i>

<i>You should have received a copy of the GNU General Public License</i>
<i>along with this program.  If not, see http://www.gnu.org/licenses/</i>
