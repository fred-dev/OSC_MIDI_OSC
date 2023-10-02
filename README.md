# OSC_MIDI_OSC

A simple cross-platform OSC to Midi and Midi to OSC converter. 

- **Made with**: [openframeworks](https://github.com/openframeworks/openFrameworks)
- **Using**: [ofxMidi](https://github.com/danomatika/ofxMidi)

## Downloads

- **MAC OS 10.15+ (ish) 64 bit**: Available on the release tab.
- **Windows 10+ 64 bit**: Available on the release tab.

> **Note**: Linux has many requirements. If you're looking for a fast and light solution for Linux, this may not be for you due to the heavy dependencies of openframeworks.

## Setup

1. Download [openframeworks](https://openframeworks.cc/download/) and set it up for your platform.
2. Navigate to `openframeworksRoot/myApps/` and clone this repository.
3. Navigate to `openframeworksRoot/addons/` and clone the following repositories:
   - [ofxMidi](https://github.com/danomatika/ofxMidi)
   - [ofxTextInputField](https://github.com/Flightphase/ofxTextInputField)
   - [ofxMSAInteractiveObject](https://github.com/memo/ofxMSAInteractiveObject)
4. Use the project generator for your platform to generate a project.
5. Compile for your platform.

## Configuration

To configure the app, go to the `data` folder and edit the `MIDI_OSC_SETTINGS.json` file, or change the settings from the GUI! You can set the incoming and outgoing midi and OSC ports and the destination IP.

## Updates

- Now includes Midi Machine control.
- Basic interactive GUI for on-the-go settings adjustments.
- Midi Show Control is now included (beta version).

## Windows Users

To use this with Windows, ensure you install a virtual midi port. We recommend [Loopmidi from Tobias Erichsen](http://www.tobias-erichsen.de/software/loopmidi.html).

## To-Do

- More detailed MSC and MTC.

## OSC Format

The OSC format is consistent for both sending and receiving. Here are the detailed descriptions of the address formats:

- **/cc**: For controller values with two int arguments: the controller number and the value. 
- **/noteOn**: For note on messages with two int arguments: note value and velocity.
- **/noteOff**: For note off messages with one int argument: note value.
- **/Aftertouch**: For mono aftertouch off messages with one int argument: value.
- **/PolyAftertouch**: For polyphonic aftertouch messages with two int arguments: pitch and value.
- **/Pitchbend**: For pitch bend messages with one int argument: value.
- **/ProgramChange**: For program change messages with one int argument: program value.

The software receives OSC messages in these formats and will automatically send the corresponding MIDI signals. Incoming MIDI signals will trigger OSC messages in the same formats.

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
