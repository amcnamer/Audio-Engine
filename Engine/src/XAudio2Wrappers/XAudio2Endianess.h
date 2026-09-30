//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef XAUDIO2_ENDIANESS
#define XAUDIO2_ENDIANESS

#ifdef _XBOX //Big-Endian
constexpr unsigned int fourccRIFF = 'RIFF';
constexpr unsigned int fourccDATA = 'data';
constexpr unsigned int fourccFMT = 'fmt ';
constexpr unsigned int fourccWAVE = 'WAVE';
constexpr unsigned int fourccXWMA = 'XWMA';
constexpr unsigned int fourccDPDS = 'dpds';
#endif

#ifndef _XBOX //Little-Endian
constexpr unsigned int fourccRIFF = 'FFIR';
constexpr unsigned int fourccDATA = 'atad';
constexpr unsigned int fourccFMT =  ' tmf';
constexpr unsigned int fourccWAVE = 'EVAW';
constexpr unsigned int fourccXWMA = 'AMWX';
constexpr unsigned int fourccDPDS = 'sdpd';
#endif

#endif

//---  End of File ---
