#pragma once
#include<graphics.h>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include"image_test.h"
#include"player.h"
#include"start.h"
#include"monster.h"
#include"else.h"
#include"music.h"
DWORD start_time = GetTickCount();
DWORD end_time = GetTickCount();
DWORD last = end_time - start_time;
ExMessage msg;
int choose_which = 0;
const int fps = 60;//游戏帧率
const int room_left = 80;//房间左壁
const int room_right = scene_length - 50;//房间右壁
const int room_up = 120;//房间上壁
const int room_down = scene_width-150;//房间下壁
const int player_hp_x = 30;//玩家生命条x坐标
const int player_hp_y = 30;//玩家生命条y坐标
//场景基类
class Scene
{
public:
	Scene() = default;
	~Scene() = default;


	virtual void on_enter() {}//启动场景
	virtual void on_input(ExMessage& msg) {}//读取操作
	virtual void on_update(bool& quit) {}//处理数据
	virtual void on_draw() {}//绘制画面
	virtual void on_exit() {}//退出场景
};
//游戏启动界面
class start :public Scene
{
public:
	start()
	{
		img->load_start();
	}
	~start()
	{
		delete img;
	}
	void on_enter()
	{
		BeginBatchDraw();
	}
	void on_input(ExMessage& msg)
	{
		if ((choose == 1) && (GetAsyncKeyState('S')))
			if (d_break < 3)
				choose = 2;
		if ((choose == 2) && (GetAsyncKeyState('W')))
				choose = 1;
	}
	void on_update(bool& quit)
	{
		if (go_on)
		{
			if (!GetAsyncKeyState(VK_RETURN))quit = true;
		}
		if (go_down)
		{
			if (!GetAsyncKeyState(VK_RETURN))
			{
				d_break++;
				go_down = false;
			}
		}
		if ((d_break == 3) && (once))
		{
			quit_break = GetTickCount();
			choose = 1;
			once = false;
		}
	}
	void on_draw()
	{
		img->draw_bkg();
		img->draw_key(choose, go_on, go_down, d_break);
		if (d_break >= 3)
			img->quit_fade(quit_break);
	}
	void on_exit()
	{
		EndBatchDraw();
	}
private:
	int choose = 1;
	bool go_on;
	bool go_down;
	bool once = true;
	int d_break = 0;
	DWORD quit_break = GetTickCount() - 500;
	start_img* img = new start_img;
};
//失败界面
class Ending :public Scene
{
public:
	Ending()
	{
		loadimage(&img_end, _T("background/end.jpg"), scene_length, 853 * 0.8);
		close_all();
		play_lose();
	}
	~Ending()
	{
		
	}
	void on_enter()
	{
		BeginBatchDraw();
	}
	void on_input(ExMessage & msg)
	{
	}
	void on_update(bool& quit)
	{
	}
	void on_draw()
	{
		putimage(0, 66, &img_end);
	}
	void on_exit()
	{
		EndBatchDraw();
		closegraph();
	}
private:
	IMAGE img_end;
};
//游戏胜利界面
class Win :public Scene
{
public:
	Win()
	{
		loadimage(&img_end, _T("background/win.png"), 1119.6, 497.7);
		close_all();
		play_win();
	}
	~Win()
	{

	}
	void on_enter()
	{
		BeginBatchDraw();
	}
	void on_input(ExMessage& msg)
	{
	}
	void on_update(bool& quit)
	{
	}
	void on_draw()
	{
		putimage(-13.8, 66, &img_end);
	}
	void on_exit()
	{
		EndBatchDraw();
		closegraph();
	}
private:
	IMAGE img_end;
};
//场景运转函数
void play(Scene* scene)
{
	bool quit = false;
	scene->on_enter();
	while (1)
	{
		start_time = GetTickCount();
		cleardevice();
		scene->on_input(msg);
		scene->on_update(quit);
		scene->on_draw();
		end_time = GetTickCount();
		last = end_time - start_time;
		if (last < 1000 / fps)
			Sleep(1000 / fps - last);
		if (quit)break;
		FlushBatchDraw();
	}
	scene->on_exit();
	delete scene;
}

//选道具的场景
class Choose :public Scene
{
public:

	bool over = 0;
	DWORD update = GetTickCount();
	IMAGE white;
	Choose()
	{
		img->load_image();
		Door.load_role();
		loadimage(&white, _T("player/white.png"), 100, 100);
		if (choose_which == 2)play_Game34();
	}
	~Choose()
	{
		delete img;
	}
	void on_enter()
	{
		BeginBatchDraw();
		img->left = choose_which * 3;
		if(GetAsyncKeyState(VK_RETURN)){}//缓冲指令
	}
	void on_input(ExMessage& msg)
	{
		if ((choose < 2) && (GetAsyncKeyState('D')))
			if (GetTickCount() - move >= 200)
			{
				choose++;
				move = GetTickCount();
			}
		if ((choose > 0) && (GetAsyncKeyState('A')))
			if (GetTickCount() - move >= 200)
			{
				choose--;
				move = GetTickCount();
			}
	}
	void on_update(bool& quit)
	{
		if (go_on)
		{
			if (!GetAsyncKeyState(VK_RETURN))
			{
				quit = true;
				if (choose + choose_which * 3 == 0)
					poxiao = true;
				if (choose + choose_which * 3 == 1)
				{
					player_hp += 5;
					wanshi = true;
				}
				if (choose + choose_which * 3 == 2)
					Player.mingdao++;
				if (choose + choose_which * 3 == 3)
					guanchuan = true;
				if (choose + choose_which * 3 == 4)
					dabao = true;
				if (choose + choose_which * 3 == 5)
				{
					cd_shoot = cd_shoot * 2 / 3;
					loveU = true;
				}
				if (choose + choose_which * 3 == 6)
					A1 = true;
				if (choose + choose_which * 3 == 7)
					dipai = true;
				if (choose + choose_which * 3 == 8)
					aha = true;
				choose_which++;
			}
		}
	}
	void on_draw()
	{
		putimage(length / 2 - 343 + 300 * (choose), width * 3 / 4 - 3, &white);
		Door.put_door(start_time, scene_length, scene_width);//传送门
		img->draw_key(go_on);
		img->draw_word(choose);
	}
	void on_exit()
	{
		EndBatchDraw();
	}
private:
	int choose = 0;
	bool go_on = false;
	bool once = true;
	choose_img* img = new choose_img;
	DWORD move = GetTickCount();
};
//第一关
class Game_1 :public Scene
{
public:
	vector<monster1>monster_1;
	background bkg;
	int num_monster1 = 0;
	int total_monster1 = 20;
	bool over = 0;
	DWORD update = GetTickCount();
	DWORD begin = GetTickCount();
	Game_1()
	{
		Player.load_role();
		img_test.load_role();
		Door.load_role();
		bkg.load_background(1);
		load_monster();
		for (int i = 0; i < num_monster1; i++)
		{
			monster1 give(i * 100, 0);
			monster_1.push_back(give);
		}
	}
	void on_enter()
	{
		Player.re_position(scene_length / 2, scene_width / 2);
		BeginBatchDraw();
	}
	void on_input(ExMessage& msg)
	{
		bool move_up = (Player.get_y() >= 120);
		bool move_down = (Player.get_y() <= scene_width - player_width - 150);
		bool move_left = (Player.get_x() >= 80);
		bool move_right = (Player.get_x() <= scene_length - player_length - 50);
		Player.get_move(move_up, move_down, move_left, move_right);
		Player.move();
		Player.shoot();
	}
	void on_update(bool& quit)
	{
		quit = false;//退出判定
		//怪物刷新
		if (GetTickCount() - begin > 1000)
		    if ((num_monster1 < 5) && (GetTickCount() - update >= 0) && (total_monster1 >= 0))
		    {
		    	monster1 give(80 + rand() % (scene_length - 130), 120 + rand() % (scene_width - 270));
			    monster_1.push_back(give);
	    		num_monster1++;
		    	total_monster1--;
			    update = GetTickCount();
		    }
		//怪物索敌
		for (int i = 0; i < num_monster1; i++)
		{
			monster_1[i].move();
		}
		//子弹移动及撞墙
		for (int i = 0; i < Player.num_bullet; i++)
		{
			Player.atk[i].move();
			Player.atk[i].crush_wall(room_up, room_down, room_left, room_right);
		}
		//子弹命中判定
		for (int i = 0; i < num_monster1; i++)
			for (int j = 0; j < Player.num_bullet; j++)
			{
				if (monster_1[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
				{
					monster_1[i].hp--;
					Player.atk[j].destroy = 1;
				}
				if (monster_1[i].hp <= 0)
					monster_1[i].death = 1;
			}
		//怪物被击败判定
		for (int i = 0; i < num_monster1; i++)
		{
			if (monster_1[i].death)
			{
				if (i != num_monster1 - 1)
					swap(monster_1[i], monster_1[num_monster1 - 1]);
				monster_1.pop_back();
				num_monster1--;
				//play_ji();
			}
		}
		//子弹销毁判定
		for (int i = 0; i < Player.num_bullet; i++)
		{
			if (Player.atk[i].destroy)
			{
				if (i != Player.num_bullet - 1)
					swap(Player.atk[i], Player.atk[Player.num_bullet - 1]);
				Player.atk.pop_back();
				Player.num_bullet--;
			}
		}
		//玩家受击判定
		Player.shooted = 0;
		for (int i = 0; i < num_monster1; i++)
		{
			monster_1[i].fire();
		}
		Player.hurt();
		//关卡结束判定
		if ((num_monster1 <= 0) && (total_monster1 <= 0))
		{
			Player.hp = player_hp;
			over = 1;
		}
		//失败判定
		if(Player.dead())
			play(new Ending);
		//进入传送门
		if (over)
		{
			if (GetAsyncKeyState(32))
			    if ((Player.get_x() <= scene_length / 2 + door_length / 8) && (Player.get_x() + player_length >= scene_length / 2 - door_length / 8) && (Player.get_y() <= scene_width / 2 + door_width / 6) && (Player.get_y() + player_width >= scene_width / 2 - door_width / 6))
			    {
					quit = true;
			    }
		}
	}
	void on_draw()
	{
		if (GetTickCount() - begin <= 1000)
			bkg.put_background(GetTickCount() - update);
		if (GetTickCount() - begin > 1000)
		{
			bkg.put_background();//背景
			if (over)
				Door.put_door(start_time, scene_length, scene_width);//传送门
			//怪物1
			for (int i = 0; i < num_monster1; i++)
			{
				monster_1[i].put_monster(start_time);
			}
			Player.put_player(start_time);//玩家
			//子弹
			for (int i = 0; i < Player.num_bullet; i++)
			{
				Player.atk[i].putimage();
			}
		}
		//玩家生命值
		for (int i = 0; i < Player.hp; i++)
		{
			Player.put_hp(player_hp_x + i * player_hp_length, player_hp_y);
		}
	}
	void on_exit()
	{
		EndBatchDraw();
	}
};
//第二关
class Game_2 :public Scene
{
public:
	vector<monster1>monster_1;
	vector<monster2>monster_2;
	background bkg;
	int num_monster1 = 0;
	int num_monster2 = 4;
	int des_monster2[4][2] = { {80,120},{scene_length - wendy_length - 80,120},{80,scene_width - wendy_width - 150},{scene_length - wendy_length - 80,scene_width - wendy_width - 150} };
	bool wendy_face[4] = { true,false,true,false };
	int total_monster1 = 20;
	bool over = 0;
	DWORD update = GetTickCount();
	DWORD begin = GetTickCount();
	Game_2()
	{
		Player.load_role();
		img_test.load_role();
		Door.load_role();
		bkg.load_background(2);
		load_monster();
		for (int i = 0; i < num_monster2; i++)
		{
			monster2 give(des_monster2[i][0], des_monster2[i][1], 5, wendy_face[i]);
			monster_2.push_back(give);
		}
	}
	void on_enter()
	{
		Player.hp = player_hp;
		Player.re_position(scene_length / 2, scene_width / 2);
		BeginBatchDraw();
	}
	void on_input(ExMessage& msg)
	{
		bool move_up = (Player.get_y() >= 120);
		bool move_down = (Player.get_y() <= scene_width - player_width - 150);
		bool move_left = (Player.get_x() >= 80);
		bool move_right = (Player.get_x() <= scene_length - player_length - 80);
		Player.get_move(move_up, move_down, move_left, move_right);
		Player.move();
		Player.shoot();
	}
	void on_update(bool& quit)
	{
		quit = false;//退出判定
		//怪物刷新
		if ((num_monster1 < 3) && (GetTickCount() - update >= 0) && (total_monster1 >= 0) && (GetTickCount() - begin > 1000))
		{
			monster1 give(80 + rand() % (scene_length - 130), 120 + rand() % (scene_width - 270), 5);
			monster_1.push_back(give);
			num_monster1++;
			total_monster1--;
			update = GetTickCount();
		}
		//怪物索敌
		for (int i = 0; i < num_monster1; i++)
		{
			monster_1[i].move();
		}
		//子弹移动及撞墙
		for (int i = 0; i < Player.num_bullet; i++)
		{
			Player.atk[i].move();
			Player.atk[i].crush_wall(room_up, room_down, room_left, room_right);
		}
		//远程怪物子弹移动及撞墙
		for (int j = 0; j < num_monster2; j++)
			for (int i = 0; i < monster_2[j].num_bullet; i++)
			{
				monster_2[j].atk[i].move();
				monster_2[j].atk[i].crush_wall(room_up, room_down, room_left, room_right);
			}
		//子弹命中判定
		for (int i = 0; i < num_monster1; i++)
			for (int j = 0; j < Player.num_bullet; j++)
			{
				if (monster_1[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
				{
					monster_1[i].hp--;
					if ((poxiao)&&(rand() % 100 < 20))monster_1[i].hp -= rand() % 4 + 1;
					Player.atk[j].destroy = 1;
				}
				if (monster_1[i].hp <= 0)
					monster_1[i].death = 1;
			}
		for (int i = 0; i < num_monster2; i++)
			for (int j = 0; j < Player.num_bullet; j++)
			{
				if (monster_2[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
				{
					monster_2[i].hp--;
					if ((poxiao) && (rand() % 100 < 20))monster_2[i].hp -= rand() % 4 + 1;
					Player.atk[j].destroy = 1;
				}
				if (monster_2[i].hp <= 0)
					monster_2[i].death = 1;
			}
		//怪物被击败判定
		for (int i = 0; i < num_monster1; i++)
		{
			if (monster_1[i].death)
			{
				if (i != num_monster1 - 1)
					swap(monster_1[i], monster_1[num_monster1 - 1]);
				monster_1.pop_back();
				num_monster1--;
				if (wanshi && (rand() % 100 < 20) && (Player.hp < player_hp))
					Player.hp++;
				//play_ji();
			}
		}
		for (int i = 0; i < num_monster2; i++)
		{
			if (monster_2[i].death)
			{
				if (i != num_monster2 - 1)
					swap(monster_2[i], monster_2[num_monster2 - 1]);
				monster_2.pop_back();
				num_monster2--;
				if (wanshi && (rand() % 100 < 20) && (Player.hp < player_hp))
					Player.hp++;
				//play_ji();
			}
		}
		//子弹销毁判定
		for (int i = 0; i < Player.num_bullet; i++)
		{
			if (Player.atk[i].destroy)
			{
				if (i != Player.num_bullet - 1)
					swap(Player.atk[i], Player.atk[Player.num_bullet - 1]);
				Player.atk.pop_back();
				Player.num_bullet--;
			}
		}
		for (int j = 0; j < num_monster2; j++)
			for (int i = 0; i < monster_2[j].num_bullet; i++)
			{
				if (monster_2[j].atk[i].destroy)
				{
					if (i != monster_2[j].num_bullet - 1)
						swap(monster_2[j].atk[i], monster_2[j].atk[monster_2[j].num_bullet - 1]);
					monster_2[j].atk.pop_back();
					monster_2[j].num_bullet--;
				}
			}
		//远程怪物攻击
		for (int i = 0; i < num_monster2; i++)
		{
			monster_2[i].go_fire();
		}
		//玩家受击判定
		Player.shooted = 0;
		for (int i = 0; i < num_monster1; i++)
		{
			monster_1[i].fire();
		}
		//远程怪物子弹命中判定
		for (int i = 0; i < num_monster2; i++)
			for (int j = 0; j < monster_2[i].num_bullet; j++)
			{
				if (monster_2[i].atk[j].hurt())
					Player.shooted = true;
			}
		Player.hurt();
		//关卡结束判定
		if ((num_monster1 <= 0) && (total_monster1 <= 0) && (num_monster2 <= 0))
		{
			Player.hp = player_hp;
			over = 1;
		}
		//失败判定
		if (Player.dead())
			play(new Ending);
		//进入传送门
		if (over)
		{
			if (GetAsyncKeyState(32))
				if ((Player.get_x() <= scene_length / 2 + door_length / 8) && (Player.get_x() + player_length >= scene_length / 2 - door_length / 8) && (Player.get_y() <= scene_width / 2 + door_width / 6) && (Player.get_y() + player_width >= scene_width / 2 - door_width / 6))
				{
					quit = true;
				}
		}
	}
	void on_draw()
	{
		if (GetTickCount() - begin <= 1000)
			bkg.put_background(GetTickCount() - update);
		if (GetTickCount() - begin > 1000)
		{
			bkg.put_background();//背景
			if (over)
				Door.put_door(start_time, scene_length, scene_width);//传送门
			//怪物1
			for (int i = 0; i < num_monster1; i++)
			{
				monster_1[i].put_monster(start_time);
			}
			//怪物2
			for (int i = 0; i < num_monster2; i++)
			{
				monster_2[i].put_monster(start_time);
			}
			Player.put_player(start_time);//玩家
			//子弹
			for (int i = 0; i < Player.num_bullet; i++)
			{
				Player.atk[i].putimage();
			}
			//远程怪物子弹
			for (int j = 0; j < num_monster2; j++)
				for (int i = 0; i < monster_2[j].num_bullet; i++)
				{
					monster_2[j].atk[i].putimage(start_time);
				}
		}
		//玩家生命值
		for (int i = 0; i < Player.hp; i++)
		{
			Player.put_hp(player_hp_x + i * player_hp_length, player_hp_y);
		}
	}
	void on_exit()
	{
		EndBatchDraw();
	}
};
//第三关
class Game_3 :public Scene
{
public:
	vector<monster1>monster_1;
	vector<monster2>monster_2;
	background bkg;
	int num_monster1 = 0;
	int num_monster2 = 4;
	int des_monster2[4][2] = { {80,120},{scene_length - wendy_length - 80,120},{80,scene_width - wendy_width - 150},{scene_length - wendy_length - 80,scene_width - wendy_width - 150} };
	bool wendy_face[4] = { true,false,true,false };
	int total_monster1 = 5;
	bool over = 0;
	int boci = 3;
	DWORD update = GetTickCount();
	DWORD begin = GetTickCount();
	Game_3()
	{
		close_bgm();
		play_Game3();
		Player.load_role();
		img_test.load_role();
		Door.load_role();
		bkg.load_background(3);
		load_monster();
		for (int i = 0; i < num_monster2; i++)
		{
			monster2 give(des_monster2[i][0], des_monster2[i][1], 3, wendy_face[i]);
			monster_2.push_back(give);
		}
	}
	void on_enter()
	{
		Player.re_position(scene_length / 2, scene_width / 2);
		BeginBatchDraw();
	}
	void on_input(ExMessage& msg)
	{
		bool move_up = (Player.get_y() >= 120);
		bool move_down = (Player.get_y() <= scene_width - player_width - 150);
		bool move_left = (Player.get_x() >= 80);
		bool move_right = (Player.get_x() <= scene_length - player_length - 80);
		Player.get_move(move_up, move_down, move_left, move_right);
		Player.move();
		Player.shoot();
	}
	void on_update(bool& quit)
	{
		if ((GetTickCount() - begin > 1000))
		{
			quit = false;//退出判定
			//怪物刷新
			if ((num_monster1 < 3) && (GetTickCount() - update >= 0) && (total_monster1 >= 0))
			{
				monster1 give(80 + rand() % (scene_length - 130), 120 + rand() % (scene_width - 270), 5);
				monster_1.push_back(give);
				num_monster1++;
				total_monster1--;
				update = GetTickCount();
			}
			//怪物索敌
			for (int i = 0; i < num_monster1; i++)
			{
				monster_1[i].move();
			}
			//子弹移动及撞墙
			for (int i = 0; i < Player.num_bullet; i++)
			{
				Player.atk[i].move();
				Player.atk[i].crush_wall(room_up, room_down, room_left, room_right);
			}
			//远程怪物子弹移动及撞墙
			for (int j = 0; j < num_monster2; j++)
				for (int i = 0; i < monster_2[j].num_bullet; i++)
				{
					monster_2[j].atk[i].move();
					monster_2[j].atk[i].crush_wall(room_up, room_down, room_left, room_right);
				}
			//子弹命中判定
			for (int i = 0; i < num_monster1; i++)
				for (int j = 0; j < Player.num_bullet; j++)
				{
					if (monster_1[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
					{
						monster_1[i].hp--;
						if ((poxiao) && (rand() % 100 < 20))monster_1[i].hp -= rand() % 4 + 1;
						if ((dabao) && (rand() % 100 < 50))monster_1[i].hp--;
						Player.atk[j].destroy = 1;
					}
					if (monster_1[i].hp <= 0)
					{
						if (guanchuan)
						{
							Player.atk[j].destroy = 0;
						}
						monster_1[i].death = 1;
					}
				}
			for (int i = 0; i < num_monster2; i++)
				for (int j = 0; j < Player.num_bullet; j++)
				{
					if (monster_2[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
					{
						monster_2[i].hp--;
						if ((poxiao) && (rand() % 100 < 20))monster_2[i].hp -= rand() % 4 + 1;
						if ((dabao) && (rand() % 100 < 50))monster_2[i].hp--;
						Player.atk[j].destroy = 1;
					}
					if (monster_2[i].hp <= 0)
					{
						if (guanchuan)
						{
							Player.atk[j].destroy = 0;
						}
						monster_2[i].death = 1;
					}
				}
			//怪物被击败判定
			for (int i = 0; i < num_monster1; i++)
			{
				if (monster_1[i].death)
				{
					if (guanchuan)
					{
						for (int j = 1; j <= 5; j++)
						{
							bullet a(monster_1[i].x, monster_1[i].y, rand() % 360);
							Player.atk.push_back(a);
							Player.num_bullet++;
						}
					}
					if (i != num_monster1 - 1)
						swap(monster_1[i], monster_1[num_monster1 - 1]);
					monster_1.pop_back();
					num_monster1--;
					if (wanshi && (rand() % 100 < 20) && (Player.hp < player_hp))
						Player.hp++;
					//play_ji();
				}
			}
			for (int i = 0; i < num_monster2; i++)
			{
				if (monster_2[i].death)
				{
					if(guanchuan)
						for (int j = 1; j <= 5; j++)
						{
							bullet a(monster_2[i].x, monster_2[i].y, rand() % 360);
							Player.atk.push_back(a);
							Player.num_bullet++;
						}
					if (i != num_monster2 - 1)
						swap(monster_2[i], monster_2[num_monster2 - 1]);
					monster_2.pop_back();
					num_monster2--;
					if (wanshi && (rand() % 100 < 20) && (Player.hp < player_hp))
						Player.hp++;
					//play_ji();
				}
			}
			//子弹销毁判定
			for (int i = 0; i < Player.num_bullet; i++)
			{
				if (Player.atk[i].destroy)
				{
					if (i != Player.num_bullet - 1)
						swap(Player.atk[i], Player.atk[Player.num_bullet - 1]);
					Player.atk.pop_back();
					Player.num_bullet--;
				}
			}
			for (int j = 0; j < num_monster2; j++)
				for (int i = 0; i < monster_2[j].num_bullet; i++)
				{
					if (monster_2[j].atk[i].destroy)
					{
						if (i != monster_2[j].num_bullet - 1)
							swap(monster_2[j].atk[i], monster_2[j].atk[monster_2[j].num_bullet - 1]);
						monster_2[j].atk.pop_back();
						monster_2[j].num_bullet--;
					}
				}
			//远程怪物攻击
			for (int i = 0; i < num_monster2; i++)
			{
				monster_2[i].go_fire();
			}
			//玩家受击判定
			Player.shooted = 0;
			for (int i = 0; i < num_monster1; i++)
			{
				monster_1[i].fire();
			}
			//远程怪物子弹命中判定
			for (int i = 0; i < num_monster2; i++)
				for (int j = 0; j < monster_2[i].num_bullet; j++)
				{
					if (monster_2[i].atk[j].hurt())
						Player.shooted = true;
				}
			Player.hurt();
			//关卡结束判定
			if ((num_monster1 <= 0) && (total_monster1 <= 0) && (num_monster2 <= 0))
			{
				boci--;
				if (boci <= 0)
				{
					Player.hp = player_hp;
					over = 1;
				}
				else
				{
					if (boci == 2)
					{
						Player.hp += 5;
						if (Player.hp > player_hp)Player.hp = player_hp;
						for (int i = 0; i < 10; i++)
						{
							monster1 give(80 + rand() % (scene_length - 130), 120 + rand() % (scene_width - 270), 5);
							monster_1.push_back(give);
							num_monster1++;
						}
					}
					if (boci == 1)
					{
						Player.hp += 5;
						if (Player.hp > player_hp)Player.hp = player_hp;
						num_monster2 = 4;
						for (int i = 0; i < 4; i++)
						{
							monster2 give(des_monster2[i][0], des_monster2[i][1], 20, wendy_face[i], 500);
							monster_2.push_back(give);
						}
					}   
				}

			}
			//失败判定
			if (Player.dead())
				play(new Ending);
			//进入传送门
			if (over)
			{
				if (GetAsyncKeyState(32))
					if ((Player.get_x() <= scene_length / 2 + door_length / 8) && (Player.get_x() + player_length >= scene_length / 2 - door_length / 8) && (Player.get_y() <= scene_width / 2 + door_width / 6) && (Player.get_y() + player_width >= scene_width / 2 - door_width / 6))
					{
						quit = true;
						close_Game3();
					}
			}
		}
	}
	void on_draw()
	{
		if (GetTickCount() - begin <= 1000)
			bkg.put_background(GetTickCount() - update);
		if (GetTickCount() - begin > 1000)
		{
			bkg.put_background();//背景
			if (over)
				Door.put_door(start_time, scene_length, scene_width);//传送门
			//怪物1
			for (int i = 0; i < num_monster1; i++)
			{
				monster_1[i].put_monster(start_time);
			}
			//怪物2
			for (int i = 0; i < num_monster2; i++)
			{
				monster_2[i].put_monster(start_time);
			}
			Player.put_player(start_time);//玩家
			//子弹
			for (int i = 0; i < Player.num_bullet; i++)
			{
				Player.atk[i].putimage();
			}
			//远程怪物子弹
			for (int j = 0; j < num_monster2; j++)
				for (int i = 0; i < monster_2[j].num_bullet; i++)
				{
					monster_2[j].atk[i].putimage(start_time);
				}
		}
		//玩家生命值
		for (int i = 0; i < Player.hp; i++)
		{
			Player.put_hp(player_hp_x + i * player_hp_length, player_hp_y);
		}
	}
	void on_exit()
	{
		EndBatchDraw();
	}
};
//Boss关
class Game_4 :public Scene
{
public:
	vector<monster1>monster_1;
	boss Boss;
	background bkg;
	int num_monster1 = 0;
	bool over = 0;
	DWORD update = GetTickCount();
	DWORD begin = GetTickCount();
	bool boom = true;
	Game_4()
	{
		close_Game34();
		play_boss();
		Player.load_role();
		img_test.load_role();
		Door.load_role();
		bkg.load_background(2);
		load_monster();
	}
	void on_enter()
	{
		Player.re_position(scene_length / 2, scene_width / 2);
		BeginBatchDraw();
		if (dipai)
			Boss.hp -= 30;
	}
	void on_input(ExMessage& msg)
	{
		bool move_up = (Player.get_y() >= 120);
		bool move_down = (Player.get_y() <= scene_width - player_width - 150);
		bool move_left = (Player.get_x() >= 80);
		bool move_right = (Player.get_x() <= scene_length - player_length - 80);
		Player.get_move(move_up, move_down, move_left, move_right);
		Player.move();
		Player.shoot();
	}
	void on_update(bool& quit)
	{
		quit = false;//退出判定
		//怪物刷新
		if ((num_monster1 < 5) && (GetTickCount() - update >= 1000) && (GetTickCount() - begin > 1000) && (!Boss.death))
		{
			monster1 give(80 + rand() % (scene_length - 130), 120 + rand() % (scene_width - 270), 5);
			monster_1.push_back(give);
			num_monster1++;
			update = GetTickCount();
		}
		//怪物索敌
		for (int i = 0; i < num_monster1; i++)
		{
			monster_1[i].move();
		}
		//子弹移动及撞墙
		for (int i = 0; i < Player.num_bullet; i++)
		{
			Player.atk[i].move();
			Player.atk[i].crush_wall(room_up, room_down, room_left, room_right);
		}
		//远程怪物子弹移动及撞墙
		if (!Boss.death)
			for (int i = 0; i < Boss.num_bullet; i++)
			{
				Boss.atk[i].move();
				Boss.atk[i].crush_wall(room_up, room_down, room_left, room_right);
			}
		//子弹命中判定
		if (A1)
		{
			for (int i = 0; i < num_monster1; i++)
				for (int j = 0; j < Player.num_bullet; j++)
				{
					if (monster_1[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
					{
						monster_1[i].death = 1;
						Player.atk[j].destroy = 1;
					}
				}
		}
		else
		{
			for (int i = 0; i < num_monster1; i++)
				for (int j = 0; j < Player.num_bullet; j++)
				{
					if (monster_1[i].shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
					{
						monster_1[i].hp--;
						if ((poxiao) && (rand() % 100 < 20))monster_1[i].hp -= rand() % 4 + 1;
						if ((dabao) && (rand() % 100 < 50))monster_1[i].hp--;
						Player.atk[j].destroy = 1;
					}
					if (monster_1[i].hp <= 0)
						monster_1[i].death = 1;
				}
		}
		if(!Boss.death)
			for (int j = 0; j < Player.num_bullet; j++)
			{
				if (Boss.shooted(Player.atk[j].x + bullet_fix, Player.atk[j].y + bullet_fix))
				{
					Boss.hp--;
					if ((poxiao) && (rand() % 100 < 20))Boss.hp -= rand() % 4 + 1;
					if ((dabao) && (rand() % 100 < 50))Boss.hp--;
					Player.atk[j].destroy = 1;
				}
				if (Boss.hp <= 0)
				{
					Boss.death = 1;
					if (wanshi && (rand() % 100 < 20) && (Player.hp < player_hp))
						Player.hp++;
				}
			}
		//怪物被击败判定
		for (int i = 0; i < num_monster1; i++)
		{
			if (monster_1[i].death)
			{
				if (guanchuan)
				    for (int j = 1; j <= 5; j++)
				    {
				    	bullet a(monster_1[i].x, monster_1[i].y, rand() % 360);
				    	Player.atk.push_back(a);
					    Player.num_bullet++;
			    	}
				if (i != num_monster1 - 1)
					swap(monster_1[i], monster_1[num_monster1 - 1]);
				monster_1.pop_back();
				num_monster1--;
				if (wanshi && (rand() % 100 < 20) && (Player.hp < player_hp))
					Player.hp++;
				//play_ji();
			}
		}
		//子弹销毁判定
		for (int i = 0; i < Player.num_bullet; i++)
		{
			if (Player.atk[i].destroy)
			{
				if (i != Player.num_bullet - 1)
					swap(Player.atk[i], Player.atk[Player.num_bullet - 1]);
				Player.atk.pop_back();
				Player.num_bullet--;
			}
		}
		for (int i = 0; i < Boss.num_bullet; i++)
		{
			if (Boss.atk[i].destroy)
			{
				if (i != Boss.num_bullet - 1)
					swap(Boss.atk[i], Boss.atk[Boss.num_bullet - 1]);
				Boss.atk.pop_back();
				Boss.num_bullet--;
			}
		}
		//远程怪物攻击
        if(!Boss.death)
			Boss.go_fire();
		//玩家受击判定
		Player.shooted = 0;
		for (int i = 0; i < num_monster1; i++)
		{
			monster_1[i].fire();
		}
		//远程怪物子弹命中判定
		for (int j = 0; j < Boss.num_bullet; j++)
		{
			if (Boss.atk[j].hurt())
				Player.shooted = true;
		}
		Player.hurt();
		//关卡结束判定
		if (Boss.death)
		{
			Player.hp = player_hp;
			if(boom)
				for (int j = 1; j <= 5; j++)
				{
					bullet a(Boss.x, Boss.y, rand() % 360);
					Player.atk.push_back(a);
					Player.num_bullet++;
				}
			boom = false;
			while (num_monster1 > 0)
			{
				monster_1.pop_back();
				num_monster1--;
			}
			over = 1;
		}
		//失败判定
		if (Player.dead())
			play(new Ending);
		//进入传送门
		if (over)
		{
			if (GetAsyncKeyState(32))
				if ((Player.get_x() <= scene_length / 2 + door_length / 8) && (Player.get_x() + player_length >= scene_length / 2 - door_length / 8) && (Player.get_y() <= scene_width / 2 + door_width / 6) && (Player.get_y() + player_width >= scene_width / 2 - door_width / 6))
				{
					quit = true;
				}
		}
	}
	void on_draw()
	{
		if (GetTickCount() - begin <= 1000)
			bkg.put_background(GetTickCount() - update);
		if (GetTickCount() - begin > 1000)
		{
			bkg.put_background();//背景
			if (over)
				Door.put_door(start_time, scene_length, scene_width);//传送门
			//怪物1
			for (int i = 0; i < num_monster1; i++)
			{
				monster_1[i].put_monster(start_time);
			}
			//怪物2
			if(!Boss.death)
				Boss.put_monster(start_time);
			Player.put_player(start_time);//玩家
			//子弹
			for (int i = 0; i < Player.num_bullet; i++)
			{
				Player.atk[i].putimage();
			}
			//远程怪物子弹
			if(!Boss.death)
				for (int i = 0; i < Boss.num_bullet; i++)
				{
					Boss.atk[i].putimage(start_time);
				}
		}
		//玩家生命值
		for (int i = 0; i < Player.hp; i++)
		{
			Player.put_hp(player_hp_x + i * player_hp_length, player_hp_y);
		}
	}
	void on_exit()
	{
		EndBatchDraw();
	}
};