#pragma once
#include<graphics.h>
#include<string>
#include<vector>
#include<Windows.h>
#include<iostream>
#include"scene.h"
#pragma comment(lib,"MSIMG32.LIB")
const int key_start_num = 3;
const int key_quit_num = 3;
const int key_length = 192;
const int key_width = 75;
const int length = 1365 * 0.8;
const int width = 1024 * 0.8;
const int num_prop = 9;
IMAGE key_start[key_start_num];
IMAGE key_quit[key_quit_num + 1];
IMAGE bkg;

class start_img
{
public:
	//加载启动界面图像
	void load_start()
	{
		loadimage(&bkg, _T("player/start.jpg"), 1000 * width / 563, width);
		for (size_t i = 0; i < key_start_num; i++)
		{
			wstring path = L"player/ui_start_" + to_wstring(i) + L".png";
			loadimage(&key_start[i], path.c_str());
		}
		for (size_t i = 0; i < key_quit_num; i++)
		{
			wstring path = L"player/ui_quit_" + to_wstring(i) + L".png";
			loadimage(&key_quit[i], path.c_str());
		}
		loadimage(&key_quit[3], _T("player/ui_quit_3.png"), 332 * 0.8, 125 * 0.8);
	}
	//绘制启动界面背景
	void draw_bkg()
	{
		putimage(-45, 0, &bkg);
	}
	//绘制按键
	void draw_key(int choose, bool& go_on, bool& go_down, int d_break)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			if (choose == 1)
			{
				if (d_break < 3)putimage(length / 4, width * 2 / 3, &key_quit[2]);
				putimage(length / 4, width / 3, &key_start[1]);
				go_on = true;
			}
			if (choose == 2)
			{
				putimage(length / 4, width / 3, &key_start[2]);
				putimage(length / 4, width * 2 / 3, &key_quit[1]);
				go_down = true;
			}
		}
		else
		{
			if (choose == 1)
			{
				if (d_break < 3)putimage(length / 4, width * 2 / 3, &key_quit[2]);
				putimage(length / 4, width / 3, &key_start[0]);
			}
			if (choose == 2)
			{
				putimage(length / 4, width / 3, &key_start[2]);
				putimage(length / 4, width * 2 / 3, &key_quit[0]);
			}
		}
	}
	//按键彩蛋
	void quit_fade(DWORD t)
	{
		if (GetTickCount() - t <= 300)
			putimage_pro(length / 4 - 37, width * 2 / 3 - 12.5, &key_quit[3]);
	}
};
//背景图类
class background
{
public:
	void load_background(int i)
	{
		wstring path = L"background/Game_" + to_wstring(i) + L".png";
		loadimage(&bkg, path.c_str(), scene_length, scene_width);
	}
	void put_background()
	{
		putimage(0, 0, &bkg);
	}
	void put_background(DWORD t)
	{
		double f = double(t) / 1000;
		putimage(length / 2 * (1 - f), width / 2 * (1 - f), length * f, width * f, &bkg, length / 2 * (1 - f), width / 2 * (1 - f));
	}
private:
	IMAGE bkg;
};
//转场图类
class choose_img
{
public:
	IMAGE prop[num_prop];
	IMAGE word[num_prop];
	//加载启动界面图像
	int left;
	choose_img()
	{
		left = 0;
	}
	void load_image()
	{
		for (size_t i = 0; i < num_prop; i++)
		{
			wstring path = L"prop/prop_" + to_wstring(i) + L".jpg";
			loadimage(&prop[i], path.c_str(), 94, 94);
		}
		for (size_t i = 0; i < num_prop; i++)
		{
			wstring path = L"prop/word_" + to_wstring(i) + L".png";
			loadimage(&word[i], path.c_str(), 945, 708.5);
		}
	}
	//绘制按键
	void draw_key(bool& go_on)
	{
		for (int i = left; i <= left + 3; i++)
			putimage(length / 2 - 340 + 300 * (i - left), width * 3 / 4, &prop[i]);
		if (GetAsyncKeyState(VK_RETURN))
			go_on = true;
	}
	void draw_word(int w)
	{
		putimage_pro(70, -200, &word[w + left]);
	}
};
