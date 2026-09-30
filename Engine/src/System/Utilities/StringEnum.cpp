//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringEnum.h"


StringEnum::StringEnum(Wave::Status status)
{
	switch (status)
	{
	case Wave::Status::EMPTY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::EMPTY));
		break;

	case Wave::Status::PENDING:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::PENDING));
		break;

	case Wave::Status::READY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::READY));
		break;


	default:
		assert(false);
	}
}

StringEnum::StringEnum(Handle::Status status)
{
	switch (status)
	{
	case Handle::Status::SUCCESS:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::SUCCESS));
		break;

	case Handle::Status::INSUFFICIENT_SPACE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::INSUFFIENT_SPACE));
		break;

	case Handle::Status::INVALID_HANDLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::INVALID_HANDLE));
		break;

	case Handle::Status::VALID_HANDLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::VALID_HANDLE));
		break;

	case Handle::Status::HANDLE_ERROR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::HANDLE_ERROR));
		break;

	default:
		assert(false);
	}
}

StringEnum::StringEnum(Wave::ID status)
{
	switch (status)
	{
	case Wave::ID::Bassoon:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Bassoon));
		break;

	case Wave::ID::Calliope:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Calliope));
		break;

	case Wave::ID::Fiddle:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Fiddle));
		break;

	case Wave::ID::Oboe:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Oboe));
		break;

	case Wave::ID::SongA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::SongA));
		break;

	case Wave::ID::SongB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::SongB));
		break;

	case Wave::ID::Strings:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Strings));
		break;

	case Wave::ID::Empty:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Empty));
		break;


	case Wave::ID::Alert:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Alert));
		break;

	case Wave::ID::Electro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Electro));
		break;

	case Wave::ID::Beethoven:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Beethoven));
		break;

	case Wave::ID::Intro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Intro));
		break;

	case Wave::ID::A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::A));
		break;

	case Wave::ID::AtoB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::AtoB));
		break;

	case Wave::ID::B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::B));
		break;

	case Wave::ID::BtoC:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::BtoC));
		break;

	case Wave::ID::C:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::C));
		break;

	case Wave::ID::CtoA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::CtoA));
		break;

	case Wave::ID::End:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::End));
		break;

	case Wave::ID::Coma:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Coma));
		break;

	case Wave::ID::Dial:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Dial));
		break;

	case Wave::ID::MoonPatrol:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::MoonPatrol));
		break;

	case Wave::ID::Sequence:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Sequence));
		break;

	case Wave::ID::Donkey:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Donkey));
		break;

	default:
		assert(false);
	}

}

StringEnum::StringEnum(Sound::ID status)
{
	switch (status)
	{
	case Sound::ID::Bassoon:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Bassoon));
		break;

	case Sound::ID::Calliope:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Calliope));
		break;

	case Sound::ID::Fiddle:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Fiddle));
		break;

	case Sound::ID::Oboe:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Oboe));
		break;

	case Sound::ID::SongA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::SongA));
		break;

	case Sound::ID::SongB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::SongB));
		break;

	case Sound::ID::Strings:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Strings));
		break;

	case Sound::ID::Alert:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Alert));
		break;

	case Sound::ID::Electro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Electro));
		break;

	case Sound::ID::Beethoven:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Beethoven));
		break;

	case Sound::ID::Intro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Intro));
		break;

	case Sound::ID::A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::A));
		break;

	case Sound::ID::AtoB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::AtoB));
		break;

	case Sound::ID::B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::B));
		break;

	case Sound::ID::BtoC:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::BtoC));
		break;

	case Sound::ID::C:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::C));
		break;

	case Sound::ID::CtoA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::CtoA));
		break;

	case Sound::ID::End:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::End));
		break;

	case Sound::ID::Coma:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Coma));
		break;

	case Sound::ID::Dial:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Dial));
		break;

	case Sound::ID::MoonPatrol:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::MoonPatrol));
		break;

	case Sound::ID::Sequence:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Sequence));
		break;

	case Sound::ID::Donkey:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Donkey));
		break;

	case Sound::ID::Uninitialized:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Sound::Uninitialized));
		break;

	default:
		assert(false);
	}

}

StringEnum::operator char* ()
{
	return this->buffer;
}

// --- End of File ---