# Digital Controls & Audio Effects for Audio Interface

This is the software side of our senior design project, which was designing and building an
audio interface that could apply effects such as reverb, distortion, etc. to its audio inputs.

![The finished audio interface UI](../media/interface.jpeg?raw=True)

The interface uses a Teensy 4.1 as its microprocessor, and our system uses a mix of C++ and
Arduino language. The Teensy 4.1 is connected to an ILI9341 display which shows input monitoring
and lets the user switch between effects. The two encoders below the display are used for this.


## Usage
Several Arduino projects that test different features are located under the Tests/ directory.
To run them, we have been compiling & uploading using the Arduino IDE, with the Teensy add-on.
Make sure the Teensy board is put in audio mode, so a connected computer recognizes it as an
audio device.

The majority of the audio processing and control are wrtten in C++, intended to be its own
library. Before compiling, run a script (wincpy.ps1 on Windows, copy_to_teensy on Mac,
linux_copy_to_teensy on Linux) which will copy the library files to their designated location
on your computer. If you installed the Teensy in a non-default location, you will have to edit
the scripts.
