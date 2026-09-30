
#include "XAudio2Chunk.h"
#include "XAudio2Endianess.h"


ChunkError FindChunk(File::Handle hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    ChunkError cError = ChunkError::CHUNK_SUCCESS;
    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD dwOffset = 0;

    //Set file pointer to beginning of file
    if (File::Error::SUCCESS != File::Seek(hFile, File::Position::BEGIN, 0))
    {
        cError = ChunkError::CHUNK_FAIL;
    }

    // loop until you find it
    while (cError == CHUNK_SUCCESS)
    {
        //Read Data type
        if (File::Error::SUCCESS != File::Read(hFile, &dwChunkType, sizeof(DWORD)))
        {
            cError = ChunkError::CHUNK_FAIL;
        }
        //Read Data Size
        if (File::Error::SUCCESS != File::Read(hFile, &dwChunkDataSize, sizeof(DWORD)))
        {
            cError = ChunkError::CHUNK_FAIL;
        }
        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (File::Error::SUCCESS != File::Read(hFile, &dwFileType, sizeof(DWORD)))
            {
                cError = ChunkError::CHUNK_FAIL;
            }
            break;
        default:
            //Move file pointer to the next chunk, continue
            if (File::Error::SUCCESS != File::Seek(hFile, File::Position::CURRENT, (int)dwChunkDataSize))
            {
                cError = ChunkError::CHUNK_FAIL;
            }
        }
        //Since the headers are only 2 words long, keep a running total.
        dwOffset += sizeof(DWORD) * 2;

        //Found type
        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            break;
        }

        dwOffset += dwChunkDataSize;

    }
    return cError;
}
ChunkError ReadChunkData(File::Handle hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    ChunkError cerror = ChunkError::CHUNK_SUCCESS;

    // Seek to the offset to chunk
    if (File::Error::SUCCESS != File::Seek(hFile, File::Position::BEGIN, (int)bufferoffset))
    {
        cerror = ChunkError::CHUNK_FAIL;
    }

    // Read data chunk 
    if (File::Error::SUCCESS != File::Read(hFile, buffer, buffersize))
    {
        cerror = ChunkError::CHUNK_FAIL;
    }

    return cerror;
}