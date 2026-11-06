#pragma once
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

void load_music()
{
	mciSendString(_T("open music/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open music/win.MP3 alias win"), NULL, 0, NULL);
	mciSendString(_T("open music/lose.mp3 alias lose"), NULL, 0, NULL);
	mciSendString(_T("open music/Game3.MP3 alias Game3"), NULL, 0, NULL);
	mciSendString(_T("open music/Game3-4.MP3 alias Game34"), NULL, 0, NULL);
	mciSendString(_T("open music/boss.MP3 alias boss"), NULL, 0, NULL);
}
void play_bgm()
{
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
}
void close_bgm()
{
	mciSendString(_T("close bgm"), NULL, 0, NULL);
}
void play_win()
{
	mciSendString(_T("play win repeat from 0"), NULL, 0, NULL);
}
void play_lose()
{
	mciSendString(_T("play lose repeat from 0"), NULL, 0, NULL);
}
void play_Game3()
{
	mciSendString(_T("play Game3 repeat from 0"), NULL, 0, NULL);
}
void close_Game3()
{
	mciSendString(_T("close Game3"), NULL, 0, NULL);
}
void play_Game34()
{
	mciSendString(_T("play Game34 from 0"), NULL, 0, NULL);
}
void close_Game34()
{
	mciSendString(_T("close Game34"), NULL, 0, NULL);
}
void play_boss()
{
	mciSendString(_T("play boss repeat from 0"), NULL, 0, NULL);
}
void close_boss()
{
	mciSendString(_T("close boss"), NULL, 0, NULL);
}
void close_all()
{
	mciSendString(_T("close bgm"), NULL, 0, NULL);
	mciSendString(_T("close Game3"), NULL, 0, NULL);
	mciSendString(_T("close boss"), NULL, 0, NULL);
}
//HOYO-MiX - Swirls of the Stream ä§Ó³µÄäöÁ÷.mp3