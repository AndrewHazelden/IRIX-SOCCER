IRIX Soccer V1.2 Alpha
Created by Andrew Hazelden

email: andrew@andrewhazelden.com
web: www.andrewhazelden.com/blog

Version 1.2
Released Jan 24, 2012
Improved the Linux makefile to add support for more platforms.

Version 1.1
Released Feb 16, 2012
Added a textured grass background.

Version 1.0
Released Jan 29, 2012
The first version of the game. It was created for the Winter 2012 RetroChallenge

This is the alpha version of my IRIX soccer game created for the 2012 Winter Warmup RetroChallenge. It is still a work-in-progress. The alpha version of the game is designed for two players.


Player Controls:
The purple soccer guy is controlled by the W, S, A, D keys.
The yellow soccer guy is controlled by the cursor keys.


IRIX Notes:
The IRIX executable is called "irix_soccer". You need to have SDL installed for it to work on IRIX. 

The IRIX version of the soccer game was compiled with GCC on IRIX 6.5.

Windows XP Notes:
The Windows XP executable is called "soccer.exe". For general testing I compiled a copy of the game that runs on Windows XP. The Windows version of the soccer game was compiled using Dev C++ 4.9.9.2 with the SDL 1.2.8 Devpack installed.

The soccer.exe program relies on the supporting file "SDL.dll" and the folder called "images".


Mac Notes:
For the Mac alpha version you need to start it from the command line so the program knows where the image resources are. If you double click on the file mac_soccer you will get an error. I am working on improving my SDL image loading code to fix this issue.

cd irix_soccer_v1.2
cd "soccer_game"
./mac_soccer

To compile it on Mac OS X run:
make -f Makefile.osx



Linux Notes:
The Linux executable is called "linux_soccer". You need to have SDL installed for it to run on Linux. 

To compile the game on Linux run:
make -f Makefile.linux


