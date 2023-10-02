//
//  MSCConstants.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 29/09/2023.
//

#pragma once

#include <unordered_map>
#include <string>

// Define the Midi Show Control Target Type map
const std::unordered_map<uint8_t, std::string> MIDI_SHOW_CONTROL_TARGET_TYPE = {
    {0x01, "lighting"},
    {0x02, "moving_lights"},
    {0x03, "colour_changers"},
    {0x04, "strobes"},
    {0x05, "lasers"},
    {0x06, "chasers"},
    {0x10, "sound"},
    {0x11, "music"},
    {0x12, "cd_players"},
    {0x13, "eprom_playback"},
    {0x14, "audio_tape_machines"},
    {0x15, "intercoms"},
    {0x16, "amplifiers"},
    {0x17, "audio_effects_devices"},
    {0x18, "equalisers"},
    {0x20, "machinery"},
    {0x21, "rigging"},
    {0x22, "flys"},
    {0x23, "lifts"},
    {0x24, "turntables"},
    {0x25, "trusses"},
    {0x26, "robots"},
    {0x27, "animation"},
    {0x28, "floats"},
    {0x29, "breakaways"},
    {0x2a, "barges"},
    {0x30, "video"},
    {0x31, "video_tape_machines"},
    {0x32, "video_cassette_machines"},
    {0x33, "video_disc_players"},
    {0x34, "video_switchers"},
    {0x35, "video_effects"},
    {0x36, "video_character_generators"},
    {0x37, "video_still_stores"},
    {0x38, "video_monitors"},
    {0x40, "projection"},
    {0x41, "film_projectors"},
    {0x42, "slide_projectors"},
    {0x43, "video_projectors"},
    {0x44, "dissolvers"},
    {0x45, "shutter_controls"},
    {0x50, "process_control"},
    {0x51, "hydraulic_oil"},
    {0x52, "h20"},
    {0x53, "co2"},
    {0x54, "compressed_air"},
    {0x55, "natural_gas"},
    {0x56, "fog"},
    {0x57, "smoke"},
    {0x58, "cracked_haze"},
    {0x60, "pyro"},
    {0x61, "fireworks"},
    {0x62, "explosions"},
    {0x63, "flame"},
    {0x64, "smoke_pots"},
    {0x7f, "all_types"}
};

const std::unordered_map<uint8_t, std::string> MIDI_SHOW_CONTROL_COMMAND_TYPE = {
    {0x01, "go"},
    {0x02, "stop"},
    {0x03, "resume"},
    {0x04, "timed_go"},
    {0x05, "load"},
    {0x06, "set"},
    {0x07, "fire"},
    {0x08, "all_off"},
    {0x09, "restore"},
    {0x0a, "reset"},
    {0x0b, "go_off"},
    {0x10, "go_jam_clock"},
    {0x11, "standby+"},
    {0x12, "standby-"},
    {0x13, "sequence+"},
    {0x14, "sequence-"},
    {0x15, "start_clock"},
    {0x16, "stop_clock"},
    {0x17, "zero_clock"},
    {0x18, "set_clock"},
    {0x19, "mtc_chase_on"},
    {0x1a, "mtc_chase_off"},
    {0x1b, "open_cue_list"},
    {0x1c, "close_cue_list"},
    {0x1d, "open_cue_path"}
};

const std::unordered_map<uint8_t, std::string> MIDI_MACHINE_CONTROL_COMMAND_TYPE = {
    {0x01, "stop"},
    {0x02, "play"},
    {0x03, "deferred_play"},
    {0x04, "fast_forward"},
    {0x05, "rewind"},
    {0x06, "record_strobe"},
    {0x07, "record_exit"},
    {0x08, "record_pause"},
    {0x09, "pause"},
    {0x0a, "eject"},
    {0x0b, "chase"},
    {0x0c, "command_error_reset"},
    {0x0d, "mmc_reset"}
};

