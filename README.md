# OSC_MIDI_OSC

A simple crossplatform OSC to Midi and Midi to OSC convertor

Made with openframeworks (https://github.com/openframeworks/openFrameworks)  
using ofxMidi (https://github.com/danomatika/ofxMidi)

To configure the app go to the data folder and edit the MIDI_OSC_SETTINGS.xml file. 

You can set the incoming and outgoing midi and OSC ports and the destination IP.

The OSC format is the same for sending and receiving. 

address "/cc" is for controller values with two int arguments the first is the controller number and the second is the value. 
The receives OSC in this format and sends the according midi signal. Incoming midi cc will trigger an OSC message in the same format

address "noteOn" is for note on messages with one int argumnet - note value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi note on is received.

address "/noteOff" is for note off messages with one int argumnet - note value. The software receives OSC messages in this format 
and will automatically send OSC messages in this format when a midi note off is received.

This application was made as a helper for people using software that does not suport OSC natively but want to interact with OSC enabled
software. It was developed as part of Crosstalk Body and Technology Laboratory in Tehran in 2015 by Frederick Rodrigues.


To use this with windows make sure you install some kind of virtual midi port- we used Loopmidi from Tobias Erichsen you can download it here:

http://www.tobias-erichsen.de/software/loopmidi.html


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/fred-dev/osc_midi_osc/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

