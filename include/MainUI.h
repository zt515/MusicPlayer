#pragma once

#include "EventEmiter.h"
#include "MusicScanner.h"
#include "MusicEntry.h"
#include "Player.h"
#include "LyricDownloader.h"
#include "Config.h"

#include "koll/Keyboard.h"
#include "koll/Screen.h"

#define PAGE_ITEM 9

namespace kiva {

class MainUI : public EventEmiter<std::string>
{
private:
	koll::Keyboard *keyboard;
	Config *cfg;
	Player *player;
	
	LyricDownloader lyDownloader;
	
	std::vector<MusicEntry> data;
	volatile int current;
	volatile int page;
	volatile PlayMode playMode;
	
	Millisecond currDuration;
	Millisecond currPosition;
	const char *currName;
	const char *currArtist;
	PlayState currState;
	
	volatile bool finish;
	volatile bool needShowHelp;
	volatile bool needShowPlayList;
	volatile bool ui;

private:
	void setupEvent();
	
	void play(int pos);
	void playNext();
	void playPrev();
	
	int getIndex(int page, int i);
	
	void showPlayList();
	void showHelp();
	void showLyric(const Lyric &ly);
	void showProgress();
	void printUI();
	
public:
	MainUI();
	virtual ~MainUI();
	
	void setData(const std::vector<MusicEntry> &data);
	int exec();
};

}

