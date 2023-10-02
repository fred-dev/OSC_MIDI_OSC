# OSC_MIDI_OSC

A simple cross platform OSC to Midi and Midi to OSC convertor made with Made with openframeworks (https://github.com/openframeworks/openFrameworks)  
using ofxMidi (https://github.com/danomatika/ofxMidi)

MAC OS 10.15+ (ish) 64 bit release available on the release tab.

Windows 10+ 64 bit releases available on the release tab.

Linux has many requirements, see below, if you are looking for a fast and light solution for Linux this may not be for you, the openframeworks dependencies are kind of heavy as it 
supports a lot of interesting tools.

To compile and work with this code download openframeworks (for a fast setup go for a release from https://openframeworks.cc/download/)
Follow the instructions for setting up openframeworks on your platform.

Navigate to openframeworksRoot/myApps/ and clone this repository.

Navigate to openframeworksRoot/addons/ and clone the ofxMidi repository (https://github.com/danomatika/ofxMidi)
Navigate to openframeworksRoot/addons/ and clone the ofxTextInputField repository (https://github.com/Flightphase/ofxTextInputField)
Navigate to openframeworksRoot/addons/ and clone the ofxMSAInteractiveObject repository (https://github.com/memo/ofxMSAInteractiveObject)

Use the project generator for your platform to generate a project to work with.

Compile for your platform and make the improvements I never got around too, like finishing midi show control and timecode.

To configure the app go to the data folder and edit the MIDI_OSC_SETTINGS.json file, or change the settings from the GUI!

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


## UPDATE
Now includes Midi Machine control

The app wll output MMC commands from the following OSC inputs, add an int argument for the device ID and a string argument for the command

Address: "/MMCCommand"
- **STOP**
- **PLAY**
- **DEFERRED_PLAY**
- **FAST_FORWARD**
- **REWIND**
- **RECORD_STROBE**
- **RECORD_EXIT**
- **RECORD_PAUSE**
- **PAUSE**
- **EJECT**
- **CHASE**
- **COMMAND_ERROR_RESET**
- **MMC_RESET**


The app will also output these commands over OSC when receiving the relevant MMC commands in the midi input port

## UPDATE
Midi Show Control is now included, but in a betish kind of way.
The app wll output Midi Show Control commands from the following OSC inputs, add an int argument for the device ID, a string argument 
for the command target and another string argument for the command type, lastly add extra integer arguments for the command payload (up to 3)

### Here are the command targets:
- **Lighting**
- **Moving_Lights**
- **Colour_Changers**
- **Strobes**
- **Lasers**
- **Chasers**
- **Sound**
- **Music**
- **CD_Players**
- **EPROM_Playback**
- **Audio_Tape_Machines**
- **Intercoms**
- **Amplifiers**
- **Audio_Effects_Devices**
- **Equalisers**
- **Machinery**
- **Rigging**
- **Flys**
- **Lifts**
- **Turntables**
- **Trusses**
- **Robots**
- **Animation**
- **Floats**
- **Breakaways**
- **Barges**
- **Video**
- **Video_Tape_Machines**
- **Video_Cassette_Machines**
- **Video_Disc_Players**
- **Video_Switchers**
- **Video_Effects**
- **Video_Character_Generators**
- **Video_Still_Stores**
- **Video_Monitors**
- **Projection**
- **Film_Projectors**
- **Slide_Projectors**
- **Video_Projectors**
- **Dissolvers**
- **Shutter_Controls**
- **Process_Control**
- **Hydraulic_Oil**
- **H20**
- **CO2**
- **Compressed_Air**
- **Natural_Gas**
- **Fog**
- **Smoke**
- **Cracked_Haze**
- **Pyro**
- **Fireworks**
- **Explosions**
- **Flame**
- **Smoke_pots**
- **All_types**

### And here are the command types:

- **GO**
- **STOP**
- **RESUME**
- **TIMED_GO**
- **LOAD**
- **SET**
- **FIRE**
- **ALL_OFF**
- **RESTORE**
- **RESET**
- **GO_OFF**
- **GO_JAM_CLOCK**
- **STANDBY+**
- **STANDBY-**
- **SEQUENCE+**
- **SEQUENCE-**
- **START_CLOCK**
- **STOP_CLOCK**
- **ZERO_CLOCK**
- **SET_CLOCK**
- **MTC_CHASE_ON**
- **MTC_CHASE_OFF**
- **OPEN_CUE_LIST**
- **CLOSE_CUE_LIST**
- **OPEN_CUE_PATH**



To use this with windows make sure you install some kind of virtual midi port- we used Loopmidi from Tobias Erichsen you can download it here:

http://www.tobias-erichsen.de/software/loopmidi.html

TO DO 
More detailed MSC and MTC
