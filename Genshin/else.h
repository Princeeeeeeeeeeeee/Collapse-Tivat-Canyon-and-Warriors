#pragma once
#include"player.h"
const int fps_door_img = 60;//传送门动图播放速度
const int door_num = 10;
const int door_length = 512;
const int door_width = 512;
IMAGE img_door[door_num];

//传送门类
class door
{
public:
	door() { x = 100; y = 100; }
	~door() = default;
	//加载角色图像
	void load_role()
	{
		for (size_t i = 0; i < door_num; i++)
		{
			wstring path = L"door/door_" + to_wstring(i) + L".png";
			loadimage(&img_door[i], path.c_str());
		}
	}
	//放置传送门图像
	void put_door(DWORD start_time, int length, int width)
	{
		int num = (start_time / fps_door_img) % door_num;
		putimage_pro(length / 2 - door_length / 2, width / 2 - door_width / 2, &img_door[num]);
	}
	//获取传送门坐标
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}

private:
	//坐标
	int x;
	int y;
};
door Door;