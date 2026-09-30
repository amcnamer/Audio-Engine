
#ifndef INTERNAL_PLAYLIST_CALLBACK_H
#define INTERNAL_PLAYLIST_CALLBACK_H

class Internal_Playlist_CallBack
{
public:
	Internal_Playlist_CallBack(bool& DoneFlag);
	Internal_Playlist_CallBack(const Internal_Playlist_CallBack&) = delete;
	Internal_Playlist_CallBack& operator = (const Internal_Playlist_CallBack&) = delete;
	~Internal_Playlist_CallBack() = default;

	void Execute();

private:
	bool& finished;
};

#endif
