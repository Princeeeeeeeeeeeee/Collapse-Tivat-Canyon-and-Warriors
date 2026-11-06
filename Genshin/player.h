#pragma once
#include<graphics.h>
#include<string>
#include<vector>
#include<Windows.h>
#include<iostream>
#include"scene.h"
#pragma comment(lib,"MSIMG32.LIB")
using namespace std;
const double pai = 3.1416;
const int scene_length = 1365 * 0.8;//画布长
const int scene_width = 1024 * 0.8;//画布宽
const int fps_img = 20;//角色动图播放速度
const int v = 10;
const int player_num = 5;
const int player_length = 80;
const int player_width = 80;
int cd_shoot = 200;//子弹发射cd
const int cd_muda = 0;//技能cd
const int bullet_fix = 55;//子弹的神秘修正值
int player_hp = 5;//玩家生命值上限
const int player_hp_length = 30;//玩家生命值贴图边长
bool poxiao = false;//破晓是否触发
bool wanshi = false;//万世流涌大典是否触发
bool guanchuan = false;//贯穿是否触发
bool dabao = false;//阳光是否触发
bool loveU = false;//超级无敌爱你是否触发
bool A1 = false;//1A秒了是否触发
bool dipai = false;//底牌是否触发
bool aha = false;//猫的摇篮是否触发
IMAGE img_player_left[player_num];
IMAGE img_player_right[player_num];
IMAGE img_player_hp;
IMAGE basketball;

inline void putimage_pro(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//子弹类
class bullet
{
private:
	int v;
public:
	int x;
	int y;
	int flag;
	bullet(int a, int b, int c)
	{
		x = a;
		y = b;
		flag = c;
		v = 20;
	}
	//控制子弹移动
	void move()
	{
		x += v * cos(flag * pai / 180);
		y -= v * sin(flag * pai / 180);
	}
	//放置子弹
	void putimage()
	{
		putimage_pro(x + player_length / 2, y + player_width / 2, &basketball);
	}
	//撞墙销毁
	void crush_wall(int up, int down, int left, int right)
	{
		if ((x + bullet_fix <= left) || (x + bullet_fix >= right) || (y + bullet_fix <= up) || (y + bullet_fix >= down))
			destroy = 1;
	}
	bool destroy = 0;//子弹销毁判定
};
//玩家类
class player
{
public:
	//移动状态
	int dx = 0;
	int dy = 0;
	//外置血条
	int mingdao = 0;
	player(){x = 0; y = 0;}
	~player() = default;
	//加载角色图像
	void load_role()
	{
		for (size_t i = 0; i < player_num; i++)
		{
			wstring path = L"player/player_left_" + to_wstring(i) + L".png";
			loadimage(&img_player_left[i], path.c_str());
		}
		for (size_t i = 0; i < player_num; i++)
		{
			wstring path = L"player/player_right_" + to_wstring(i) + L".png";
			loadimage(&img_player_right[i], path.c_str());
		}
		loadimage(&basketball, _T("player/basketball.png"), 30, 30);
		loadimage(&img_player_hp, _T("player/love.png"), player_hp_length, player_hp_length);
	}
	//放置角色图像
	void put_player(DWORD start_time)
	{
		int num = (start_time / fps_img) % player_num;
		if (dir_left)putimage_pro(x, y, &img_player_left[num]);
		else putimage_pro(x, y, &img_player_right[num]);
	}
	//显示角色生命值
	void put_hp(int d_x, int d_y)
	{
		putimage_pro(d_x, d_y, &img_player_hp);
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
	//键盘控制移动
	void get_move(bool move_up, bool move_down, bool move_left, bool move_right)
	{
		dx = 0;
		dy = 0;
		if ((GetAsyncKeyState(87)) && move_up)//上键
		{
			dy = -1;
		}
		if ((GetAsyncKeyState(83)) && move_down)//下键
		{
			dy = 1;
		}
		if ((GetAsyncKeyState(65)) && move_left)//左键
		{
			dx = -1;
			dir_left = true;
		}
		if ((GetAsyncKeyState(68)) && move_right)//右键
		{
			dx = 1;
			dir_left = false;
		}
	}
	//移动
	void move()
	{
		if ((dx != 0) || (dy != 0))
		{
			x += dx * v / sqrt(dx * dx + dy * dy);
			y += dy * v / sqrt(dx * dx + dy * dy);
		}
	}
	//发射子弹
	void shoot()
	{
		if (GetAsyncKeyState(VK_UP))//上键
			if (GetTickCount() - shoot_time >= cd_shoot)
			{
				fire(90);
				shoot_time = GetTickCount();
			}
		if (GetAsyncKeyState(VK_DOWN))//下键
			if (GetTickCount() - shoot_time >= cd_shoot)
			{
				fire(270);
				shoot_time = GetTickCount();
			}
		if (GetAsyncKeyState(VK_LEFT))//左键
		{
			dir_left = true;
			if (GetTickCount() - shoot_time >= cd_shoot)
			{
				fire(180);
				shoot_time = GetTickCount();
			}
		}
		if (GetAsyncKeyState(VK_RIGHT))//右键
		{
			dir_left = false;
			if (GetTickCount() - shoot_time >= cd_shoot)
			{
				fire(0);
				shoot_time = GetTickCount();
			}
		}
	if (GetTickCount() - mudamuda_time >= cd_muda)
		if (GetAsyncKeyState('J'))//J键
		{
			for (int i = 0; i < 360; i += 12)
			{
				fire(i);
			}
			mudamuda_time = GetTickCount();
		}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP))
		if ((GetTickCount() - aha_time >= 10000) && aha)
		{
			for (int i = 0; i < 360; i += 18)
			{
				fire(i);
			}
			aha_time = GetTickCount();
		}
	}
	void fire(int angel)
	{
		bullet a(x, y, angel);
		atk.push_back(a);
		num_bullet++;
	}
	//子弹
	vector<bullet>atk;
	//子弹数量
	int num_bullet = 0;
	//生命值
	int hp = player_hp;
	//受击判定
	bool shooted = 0;
	//受到伤害
	void hurt()
	{
		if ((shooted) && (GetTickCount() - shooted_time >= 500))
		{
			if (!(loveU && (rand() % 100 < 20)))
				hp--;
			shooted_time = GetTickCount();
		}
	}
	//游戏失败
	bool dead()
	{
		if (hp <= 0)
		{
			if (mingdao <= 0)
				return 1;
			else
			{
				mingdao--;
				hp = player_hp;
				return 0;
			}
		}
		else return 0;
	}
private:
	//坐标
	int x;
	int y;
	//水平方向
	bool dir_left = true;
	//子弹发射cd计时器
	DWORD shoot_time = GetTickCount();
	//受击cd计时器
	DWORD shooted_time = GetTickCount();
	//技能cd计时器
	DWORD mudamuda_time = GetTickCount();
	//猫的摇篮计时器
	DWORD aha_time = GetTickCount() - 10000;
};
player Player;