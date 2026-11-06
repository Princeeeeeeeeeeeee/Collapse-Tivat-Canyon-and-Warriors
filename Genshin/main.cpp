#include<conio.h>
#include<iostream>
#include<cstdio>
#include<Windows.h>
#include<mmsystem.h>
#include"scene.h"
#pragma comment(lib,"winmm.lib")
using namespace std;


int main()
{

	srand(time(0));
	load_music();
	initgraph(scene_length, scene_width);
	play(new start);
	play_bgm();
	play(new Game_1);
	play(new Choose);
	play(new Game_2);
	play(new Choose);
	play(new Game_3);
	play(new Choose);
	play(new Game_4);
	play(new Win);
	_getch();
	closegraph();
	return 0;
}