#pragma once
#include<graphics.h>
#include"player.h"
#include"scene.h"
using namespace std;
const int fps_monster = 20;
const int fps_wendy = 100;
const int fps_pig = 20;
const int monster_num = 12;
const int wendy_num = 13;
const int pig_num = 6;
const int monster1_length = 50;
const int monster1_width = 70;
const int wendy_length = 83.6;
const int wendy_width = 141.2;
const int pig_length = 50;
const int pig_width = 40;
const int boss_length = 125.4;
const int boss_width = 211.8;
const int fire_dir = 40;//近战攻击范围
IMAGE img_monster_left[monster_num];
IMAGE img_monster_right[monster_num];
IMAGE img_wendy_left[wendy_num];
IMAGE img_wendy_right[wendy_num];
IMAGE img_pig_left[pig_num];
IMAGE img_pig_right[pig_num];
IMAGE img_boss[wendy_num];

void load_monster()
{
	for (size_t i = 0; i < monster_num; i++)
	{
		wstring path = L"enemy/enemy_left_" + to_wstring(i) + L".png";
		loadimage(&img_monster_left[i], path.c_str(), monster1_length, monster1_width);
	}
	for (size_t i = 0; i < monster_num; i++)
	{
		wstring path = L"enemy/enemy_right_" + to_wstring(i) + L".png";
		loadimage(&img_monster_right[i], path.c_str(), monster1_length, monster1_width);
	}
	for (size_t i = 0; i < wendy_num; i++)
	{
		wstring path = L"enemy/wendy_left_" + to_wstring(i) + L".png";
		loadimage(&img_wendy_left[i], path.c_str(), wendy_length, wendy_width);
	}
	for (size_t i = 0; i < wendy_num; i++)
	{
		wstring path = L"enemy/wendy_right_" + to_wstring(i) + L".png";
		loadimage(&img_wendy_right[i], path.c_str(), wendy_length, wendy_width);
	}
	for (size_t i = 0; i < pig_num; i++)
	{
		wstring path = L"enemy/pig_left_" + to_wstring(i) + L".png";
		loadimage(&img_pig_left[i], path.c_str(), pig_length, pig_width);
	}
	for (size_t i = 0; i < pig_num; i++)
	{
		wstring path = L"enemy/pig_right_" + to_wstring(i) + L".png";
		loadimage(&img_pig_right[i], path.c_str(), pig_length, pig_width);
	}
	for (size_t i = 0; i < wendy_num; i++)
	{
		wstring path = L"enemy/wendy_right_" + to_wstring(i) + L".png";
		loadimage(&img_boss[i], path.c_str(), boss_length, boss_width);
	}
}
//弓箭手的子弹类
class wendy_bullet
{
private:
	bool dir_left;
	int v;
public:
	int x;
	int y;
	int dx;
	int dy;
	wendy_bullet(int a, int b, bool c)
	{
		x = a;
		y = b;
		v = 5;
		dir_left = c;
		dx = Player.get_x() - x;
		dy = Player.get_y() - y;
	}
	//控制子弹移动
	void move()
	{
		if ((dx != 0) || (dy != 0))
		{
			x += dx * v / sqrt(dx * dx + dy * dy);
			y += dy * v / sqrt(dx * dx + dy * dy);
		}
	}
	//放置子弹
	void putimage(DWORD start_time)
	{
		int num = (start_time / fps_pig) % pig_num;
		if (dir_left)putimage_pro(x, y, &img_pig_right[num]);
		else putimage_pro(x, y, &img_pig_left[num]);
	}
	//撞墙销毁
	void crush_wall(int up, int down, int left, int right)
	{
		if ((x + bullet_fix <= left) || (x + bullet_fix >= right) || (y + bullet_fix <= up) || (y + bullet_fix >= down))
			destroy = 1;
	}
	//命中角色判定
	bool hurt()
	{
		if ((Player.get_x() <= x + pig_length) && (Player.get_x() + player_length >= x) && (Player.get_y() <= y + pig_width) && (Player.get_y() + player_width >= y))
		{
			Player.shooted = true;
			destroy = 1;
			return 1;
		}
		else return 0;
	}
	bool destroy = 0;//子弹销毁判定
};
//近战怪物
class monster1
{
	int atk_1 = 1; int v_1 = 2;
	bool dir_left;//坐标、血量、攻击、速度（具体数值未确定）
	double normalized_x = 1;
	double normalized_y = 1;

public:
	int x; int y;
	bool death = 0;//被击败判定
	int hp = 3;
	int hp_max = hp;
	monster1(int a = 0, int b = 0, int c = 3)
	{
		x = a;
		y = b;
		hp = c;
		hp_max = c;
	}//为x、y以及hp赋值

	int dir_x = Player.get_x() - x;
	int dir_y = Player.get_y() - y;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);//怪物与角色的距离

	//放置怪物图像
	void put_monster(DWORD start_time)
	{
		int num = (start_time / fps_monster) % monster_num;
		if (dir_left)putimage_pro(x, y, &img_monster_left[num]);
		else putimage_pro(x, y, &img_monster_right[num]);
		setfillcolor(RED);
		solidrectangle(x, y - 10, x + monster1_length / hp_max * hp, y - 5);
	}

	//受击判定
	bool shooted(int b_x, int b_y)
	{
		if ((x <= b_x) && (x + monster1_length >= b_x) && (y <= b_y) && (y + monster1_width >= b_y))
			return 1;
		else return 0;
	}

	//追踪玩家移动
	void move()
	{
		dir_x = Player.get_x() - x;
		dir_y = Player.get_y() - y;
		len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
		if ((len_dir != 0) && (len_dir <= 1000))
		{
			normalized_x = dir_x / len_dir;
			normalized_y = dir_y / len_dir;
			x += int(v_1 * normalized_x);
			y += int(v_1 * normalized_y);
		}
	}   
	//攻击判定
	void fire()
	{
		if (len_dir <= fire_dir)
			Player.shooted = 1;
	}
};
//远程怪物
class monster2
{
private:
	bool dir_left;//坐标、血量、攻击、速度（具体数值未确定）
	DWORD gap_fire;
	bool ttk = false;
	bool no_more = false;
public:
	int cd;
	int x; int y;
	bool death = 0;
	int hp;
	int hp_max;
	vector<wendy_bullet>atk;
	int num_bullet = 0;
	monster2(int a = 0, int b = 0, int c = 1, bool flag = true, int d = 2000)
	{
		x = a;
		y = b;
		hp = c;
		hp_max = c;
		cd = d;
		dir_left = flag;
		gap_fire = GetTickCount();
	}//生成敌人，同上

	int dir_x = Player.get_x() - x;
	int dir_y = Player.get_y() - y;

	//放置怪物图像
	void put_monster(DWORD start_time)
	{
		if (ttk)
		{
			int num = (start_time / fps_wendy) % 8;
			if (dir_left)putimage_pro(x, y, &img_wendy_left[num]);
			else putimage_pro(x, y, &img_wendy_right[num]);
			if ((num == 5) && (no_more))
			{
				wendy_bullet a(x + (wendy_length - pig_length) / 2, y + (wendy_width - pig_width) / 2 + 30, dir_left);
				atk.push_back(a);
				num_bullet++;
				gap_fire = GetTickCount();
				no_more = false;
			}
		}
		else
		{
			int num = 8 + (start_time / fps_wendy) % 5;
			if (dir_left)putimage_pro(x, y, &img_wendy_left[num]);
			else putimage_pro(x, y, &img_wendy_right[num]);
		}
		setfillcolor(RED);
		solidrectangle(x, y - 10, x + wendy_length / hp_max * hp, y - 5);
	}

	//受击判定
	bool shooted(int b_x, int b_y)
	{
		if ((x <= b_x) && (x + wendy_length >= b_x) && (y <= b_y) && (y + wendy_width >= b_y))
			return 1;
		else return 0;
	}
	//攻击
	void go_fire()
	{
		if (GetTickCount() - gap_fire >= cd)
		{
			ttk = true;
			no_more = true;
		}
		else ttk = false;
	}
};
//Boss
class boss
{
private:
	bool dir_left;//坐标、血量、攻击、速度（具体数值未确定）
	DWORD gap_fire;
	bool ttk = false;
	bool no_more = false;
public:
	int cd;
	int x; int y;
	bool death = 0;
	int hp;
	int hp_max;
	vector<wendy_bullet>atk;
	int num_bullet = 0;
	boss()
	{
		x = length - boss_length - 90;
		y = width / 2 - boss_width / 2;
		hp = 100;
		hp_max = 100;
		cd = 1000;
		gap_fire = GetTickCount();
	}

	int dir_x = Player.get_x() - x;
	int dir_y = Player.get_y() - y;

	//放置怪物图像
	void put_monster(DWORD start_time)
	{
		if (ttk)
		{
			if (hp > 50)
			{
				int num = (start_time / fps_wendy) % 8;
				putimage_pro(x, y, &img_boss[num]);
				if ((num == 5) && (no_more))
				{
					wendy_bullet a(x + (boss_length - pig_length) / 2, y + (boss_width - pig_width) / 2 + 30, dir_left);
					atk.push_back(a);
					num_bullet++;
					gap_fire = GetTickCount();
					no_more = false;
				}
			}
			if ((hp > 20) && (hp <= 50))
			{
				cd = 500;
				int num = (start_time / fps_wendy) % 8;
				putimage_pro(x, y, &img_boss[num]);
				if ((num == 5) && (no_more))
					for (int i = 0; i < 3; i++)
					{
						wendy_bullet a(x + (boss_length - pig_length) / 2, y + (boss_width - pig_width) / 2 + 30 + (i - 1) * 60, dir_left);
						atk.push_back(a);
						num_bullet++;
						gap_fire = GetTickCount();
						no_more = false;
					}
			}
			if (hp < 20)
			{
				cd = 300;
				int num = (start_time / fps_wendy) % 8;
				putimage_pro(x, y, &img_boss[num]);
				if ((num == 5) && (no_more))
					for (int i = 0; i < 5; i++)
					{
						wendy_bullet a(x + (boss_length - pig_length) / 2, y + (boss_width - pig_width) / 2 + 30 + (i - 2) * 60, dir_left);
						atk.push_back(a);
						num_bullet++;
						gap_fire = GetTickCount();
						no_more = false;
					}
			}
		}
		else
		{
			int num = 8 + (start_time / fps_wendy) % 5;
			putimage_pro(x, y, &img_boss[num]);
		}
		setfillcolor(BLACK);
		solidrectangle(50, 10, length - 50, 30);
		setfillcolor(RED);
		solidrectangle(52, 12, 52 + (length - 52 * 2) * hp / hp_max, 28);
	}

	//受击判定
	bool shooted(int b_x, int b_y)
	{
		if ((x <= b_x) && (x + boss_length >= b_x) && (y <= b_y) && (y + boss_width >= b_y))
			return 1;
		else return 0;
	}
	//攻击
	void go_fire()
	{
		if (GetTickCount() - gap_fire >= cd)
		{
			ttk = true;
			no_more = true;
		}
		else ttk = false;
	}
};