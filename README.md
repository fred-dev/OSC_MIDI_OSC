# OSC_MIDI_OSC

A simple crossplatform OSC to Midi and Midi to OSC convertor

MAC OS 10.10+
Winddows 8+ 64 and 32 Bit releases available on the release tab.

Made with openframeworks (https://github.com/openframeworks/openFrameworks)  
using ofxMidi (https://github.com/danomatika/ofxMidi)

To configure the app go to the data folder and edit the MIDI_OSC_SETTINGS.xml file. 

You can set the incoming and outgoing midi and OSC ports and the destination IP.

The OSC format is the same for sending and receiving. 

address "/cc" is for controller values with two int arguments the first is the controller number and the second is the value. 
The receives OSC in this format and sends the according midi signal. Incoming midi cc will trigger an OSC message in the same format

address "/noteOn" is for note on messages with two int argumnets - note value and velocity. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi note on is received.

address "/noteOff" is for note off messages with one int argumnet - note value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi note off is received.

address "/Aftertouch" is for mono aftertouch off messages with one int argumnet - value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi aftertouch message is received.

address "/PolyAftertouch" is for polyphonic aftertouch messages with two int argumnets - pitch and value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi poly aftertouch message is received.

address "/Pitchbend" is for pitch bend messages with one int argumnet -  value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi pitch bend is received.

address "/ProgramChange" is for program change messages with one int argumnet - program value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi program change is received.

This application was made as a helper for people using software that does not suport OSC natively but want to interact with OSC enabled
software. It was developed as part of Crosstalk Body and Technology Laboratory in Tehran in 2015 by Frederick Rodrigues.


UPDATE
Now includes Midi Machine ccontrol

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



