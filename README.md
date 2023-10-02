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
Commands are:

- `stop`
- `play`
- `deferred_play`
- `fast_forward`
- `rewind`
- `record_strobe`
- `record_exit`
- `record_pause`
- `pause`
- `eject`
- `chase`
- `command_error_reset`
- `mmc_reset`

  
The app wll output Midi Show Control commands from the following OSC inputs, add an int argument for the device ID, a string argument 
for the command target and another string argument for the command type, lastly add extra integer arguments for the command payload (up to 3)

### Here are the command targets:
- `lighting`
- `moving_lights`
- `colour_changers`
- `strobes`
- `lasers`
- `chasers`
- `sound`
- `music`
- `cd_players`
- `eprom_playback`
- `audio_tape_machines`
- `intercoms`
- `amplifiers`
- `audio_effects_devices`
- `equalisers`
- `machinery`
- `rigging`
- `flys`
- `lifts`
- `turntables`
- `trusses`
- `robots`
- `animation`
- `floats`
- `breakaways`
- `barges`
- `video`
- `video_tape_machines`
- `video_cassette_machines`
- `video_disc_players`
- `video_switchers`
- `video_effects`
- `video_character_generators`
- `video_still_stores`
- `video_monitors`
- `projection`
- `film_projectors`
- `slide_projectors`
- `video_projectors`
- `dissolvers`
- `shutter_controls`
- `process_control`
- `hydraulic_oil`
- `h20`
- `co2`
- `compressed_air`
- `natural_gas`
- `fog`
- `smoke`
- `cracked_haze`
- `pyro`
- `fireworks`
- `explosions`
- `flame`
- `smoke_pots`
- `all_types`

### And here are the command types:

- `go`
- `stop`
- `resume`
- `timed_go`
- `load`
- `set`
- `fire`
- `all_off`
- `restore`
- `reset`
- `go_off`
- `go_jam_clock`
- `standby+`
- `standby-`
- `sequence+`
- `sequence-`
- `start_clock`
- `stop_clock`
- `zero_clock`
- `set_clock`
- `mtc_chase_on`
- `mtc_chase_off`
- `open_cue_list`
- `close_cue_list`
- `open_cue_path`
