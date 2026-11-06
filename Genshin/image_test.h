//图片轮播测试
#pragma once
#include<graphics.h>
#include<string>
using namespace std;
const int img_num = 12;
const int fps_img_test = 20;
IMAGE img_left[img_num];
IMAGE img_right[img_num];
//图片类
class image
{
public:
	image() { x = 500; y = 300; }
	~image() = default;
	//加载角色图像
	void load_role()
	{
		for (size_t i = 0; i < img_num; i++)
		{
			wstring path = L"enemy/enemy_left_" + to_wstring(i) + L".png";
			loadimage(&img_left[i], path.c_str());
		}
		for (size_t i = 0; i < img_num; i++)
		{
			wstring path = L"enemy/enemy_right_" + to_wstring(i) + L".png";
			loadimage(&img_right[i], path.c_str());
		}
	}
	//放置角色图像
	void put_player(DWORD start_time)
	{
		int num = (start_time / fps_img_test) % img_num;
		if (dir_left)putimage(x, y, &img_left[num]);
		else putimage(x, y, &img_right[num]);
	}
	//获取角色坐标
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
	//修改角色坐标
	void re_position(int m, int n)
	{
		x = m;
		y = n;
	}
private:
	//坐标
	int x;
	int y;
	//水平方向
	bool dir_left = false;
};
image img_test;