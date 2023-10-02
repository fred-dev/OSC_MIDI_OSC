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
    {0x01, "Lighting"},
    {0x02, "Moving_Lights"},
    {0x03, "Colour_Changers"},
    {0x04, "Strobes"},
    {0x05, "Lasers"},
    {0x06, "Chasers"},
    {0x10, "Sound"},
    {0x11, "Music"},
    {0x12, "CD_Players"},
    {0x13, "EPROM_Playback"},
    {0x14, "Audio_Tape_Machines"},
    {0x15, "Intercoms"},
    {0x16, "Amplifiers"},
    {0x17, "Audio_Effects_Devices"},
    {0x18, "Equalisers"},
    {0x20, "Machinery"},
    {0x21, "Rigging"},
    {0x22, "Flys"},
    {0x23, "Lifts"},
    {0x24, "Turntables"},
    {0x25, "Trusses"},
    {0x26, "Robots"},
    {0x27, "Animation"},
    {0x28, "Floats"},
    {0x29, "Breakaways"},
    {0x2A, "Barges"},
    {0x30, "Video"},
    {0x31, "Video_Tape_Machines"},
    {0x32, "Video_Cassette_Machines"},
    {0x33, "Video_Disc_Players"},
    {0x34, "Video_Switchers"},
    {0x35, "Video_Effects"},
    {0x36, "Video_Character_Generators"},
    {0x37, "Video_Still_Stores"},
    {0x38, "Video_Monitors"},
    {0x40, "Projection"},
    {0x41, "Film_Projectors"},
    {0x42, "Slide_Projectors"},
    {0x43, "Video_Projectors"},
    {0x44, "Dissolvers"},
    {0x45, "Shutter_Controls"},
    {0x50, "Process_Control"},
    {0x51, "Hydraulic_Oil"},
    {0x52, "H20"},
    {0x53, "CO2"},
    {0x54, "Compressed_Air"},
    {0x55, "Natural_Gas"},
    {0x56, "Fog"},
    {0x57, "Smoke"},
    {0x58, "Cracked_Haze"},
    {0x60, "Pyro"},
    {0x61, "Fireworks"},
    {0x62, "Explosions"},
    {0x63, "Flame"},
    {0x64, "Smoke_pots"},
    {0x7F, "All_types"}
};

const std::unordered_map<uint8_t, std::string> MIDI_SHOW_CONTROL_COMMAND_TYPE = {
    {0x01, "GO"},
    {0x02, "STOP"},
    {0x03, "RESUME"},
    {0x04, "TIMED_GO"},
    {0x05, "LOAD"},
    {0x06, "SET"},
    {0x07, "FIRE"},
    {0x08, "ALL_OFF"},
    {0x09, "RESTORE"},
    {0x0A, "RESET"},
    {0x0B, "GO_OFF"},
    {0x10, "GO_JAM_CLOCK"},
    {0x11, "STANDBY+"},
    {0x12, "STANDBY-"},
    {0x13, "SEQUENCE+"},
    {0x14, "SEQUENCE-"},
    {0x15, "START_CLOCK"},
    {0x16, "STOP_CLOCK"},
    {0x17, "ZERO_CLOCK"},
    {0x18, "SET_CLOCK"},
    {0x19, "MTC_CHASE_ON"},
    {0x1A, "MTC_CHASE_OFF"},
    {0x1B, "OPEN_CUE_LIST"},
    {0x1C, "CLOSE_CUE_LIST"},
    {0x1D, "OPEN_CUE_PATH"}
};

const std::unordered_map<uint8_t, std::string> MIDI_MACHINE_CONTROL_COMMAND_TYPE = {
    {0x01, "STOP"},
    {0x02, "PLAY"},
    {0x03, "DEFERRED_PLAY"},
    {0x04, "FAST_FORWARD"},
    {0x05, "REWIND"},
    {0x06, "RECORD_STROBE"},
    {0x07, "RECORD_EXIT"},
    {0x08, "RECORD_PAUSE"},
    {0x09, "PAUSE"},
    {0x0A, "EJECT"},
    {0x0B, "CHASE"},
    {0x0C, "COMMAND_ERROR_RESET"},
    {0x0D, "MMC_RESET"}
};
    
