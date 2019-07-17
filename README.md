Gearnes (currently in development)
=======
<b>Copyright &copy; 2016 by Ignacio Sanchez</b>

----------
[![Build Status](https://travis-ci.org/drhelius/Gearnes.svg?branch=master)](https://travis-ci.org/drhelius/Gearnes)

*This is a work in progress project, not intended to be used right now.*

Gearnes is a Nintendo Entertainment System (NES) / Famicom emulator  written in C++ that runs on iOS, Raspberry Pi, Mac, Windows, Linux and RetroArch.

Follow me on Twitter for updates: http://twitter.com/drhelius

----------

Build Instructions
------------------

### Mac OS X
- You need Qt Creator, included in the Qt 5 SDK.
- Install Xcode and run <code>xcode-select --install</code> in the terminal for the compiler to be available on the command line.
- Install the [Qt 5 SDK for Mac OS](https://www.qt.io/download/).
- Download [SDL 2](http://www.libsdl.org/download-2.0.php) source code. Then run this commands:
``` shell
./configure
make
sudo make install
```
- Open the <code>platforms/macosx/Gearnes/Gearnes.pro</code> project file with Qt Creator and build.

### Linux
- Ubuntu / Debian:
``` shell
sudo apt-get install build-essential qt5-default qttools5-dev-tools freeglut3-dev libsdl2-dev libglew-dev
cd platforms/linux/Gearnes
qmake Gearnes.pro && make
```
- Fedora:
``` shell
sudo dnf install @development-tools gcc-c++ qt5-devel freeglut-devel SDL2-devel glew-devel
cd platforms/linux/Gearnes
qmake-qt5 Gearnes.pro && make
```

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
