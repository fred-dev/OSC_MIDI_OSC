# OSC_MIDI_OSC

A simple cross platform OSC to Midi and Midi to OSC convertor made with Made with openframeworks (https://github.com/openframeworks/openFrameworks)  
using ofxMidi (https://github.com/danomatika/ofxMidi)

MAC OS 10.10+ (ish) 64 bit release available on the release tab.

Windows 8+ 64 and 32 Bit releases available on the release tab.

Linux has many requirements, see below, if you are looking for a fast and light solution for Linux this may not be for you, the openframeworks dependencies are kind of heavy as it 
supports a lot of interesting tools.

For OSX 10.13 or later the release does not seem to work, feel free to compile it yourself, or wait until I get around to upgrading.


To compile and work with this code download openframeworks (for a fast setup go for a release from https://openframeworks.cc/download/)
Follow the instructions for setting up openframeworks on your platform.

Navigate to openframeworksRoot/myApps/ and clone this repository.

Navigate to openframeworksRoot/addons/ and clone the ofxMidi repository (https://github.com/danomatika/ofxMidi)

Compile for your platform and make the improvements I never got around too, like midi show control and timecode.


To configure the app go to the data folder and edit the MIDI_OSC_SETTINGS.xml file. 

You can set the incoming and outgoing midi and OSC ports and the destination IP.

The OSC format is the same for sending and receiving. 

address "/cc" is for controller values with two int arguments the first is the controller number and the second is the value. 
The receives OSC in this format and sends the according midi signal. Incoming midi cc will trigger an OSC message in the same format

address "/noteOn" is for note on messages with two int arguments - note value and velocity. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi note on is received.

address "/noteOff" is for note off messages with one int argument - note value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi note off is received.

address "/Aftertouch" is for mono aftertouch off messages with one int argument - value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi aftertouch message is received.

address "/PolyAftertouch" is for polyphonic aftertouch messages with two int arguments - pitch and value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi poly aftertouch message is received.

address "/Pitchbend" is for pitch bend messages with one int argument -  value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi pitch bend is received.

address "/ProgramChange" is for program change messages with one int argument - program value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi program change is received.

This application was made as a helper for people using software that does not support OSC natively but want to interact with OSC enabled
software. It was developed as part of Crosstalk Body and Technology Laboratory in Tehran in 2015 by Frederick Rodrigues.


UPDATE
Now includes Midi Machine control

Will output MMC commands from the following OSC inputs (no values needed, just the correct address)

"/MMCCommand/stop"

"/MMCCommand/play"

"/MMCCommand/forward"

"/MMCCommand/rewind"

"/MMCCommand/punchIn"

"/MMCCommand/punchOut"

"/MMCCommand/recordPause"

"/MMCCommand/pause"


The app will also output these commands over OSC when receiving the relevant MMC commands in the midi input port


To use this with windows make sure you install some kind of virtual midi port- we used Loopmidi from Tobias Erichsen you can download it here:

http://www.tobias-erichsen.de/software/loopmidi.html

TO DO 
MSC and MTC




