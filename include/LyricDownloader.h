#pragma once

#include <thread>
#include <functional>

#include "MusicEntry.h"
#include "Http.h"
#include "EventEmiter.h"

namespace kiva {

typedef struct
{
	const MusicEntry *ent;
	const std::string *lyric;
} DownloadedLyric;


class MusicApi
{
public:
	virtual bool downloadLyric(const std::string &musicName, std::string &lyric) = 0;
};


class CloudMusicApi : public MusicApi {
private:
	std::string host = "music.163.com";
	std::string idParam = "/api/search/get?type=1&offset=0&limit=1&s=";
	std::string lyricParam = "/api/song/lyric?lv=-1&kv=-1&tv=-1&id=";

	int getMusicId(const std::string &name);

public:
	CloudMusicApi();
	~CloudMusicApi();

	bool downloadLyric(const std::string &musicName, std::string &lyric);
};


class LyricDownloader : public EventEmiter<std::string> {
private:
	MusicApi *api = NULL;
	std::thread downloadThread;

public:
	LyricDownloader(MusicApi *api = NULL);
	~LyricDownloader();
	
	void setApi(MusicApi *api);
	void downloadLyric(MusicEntry *entry);
};

}

