//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef XAUDIO2_CHUNK_H
#define XAUDIO2_CHUNK_H

#include "File.h"
using namespace Azul;

enum ChunkError
{
	CHUNK_SUCCESS = 0xC0000000,
	CHUNK_FAIL,

};

ChunkError FindChunk(File::Handle hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
ChunkError ReadChunkData(File::Handle hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

#endif

//---  End of File ---
