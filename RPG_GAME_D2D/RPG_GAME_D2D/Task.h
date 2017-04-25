#pragma once
#include "head.h"
#include "Player.h"
#include "Npc.h"
#include "Fight.h"
class Npc;

class Task
{
public:
	//开始/结束/确认面板/设置面板
	void story_panel(int i, int j, HWND hwnd);
	//地图切换story
	void story_changemap(int i, Player player[]);
	//地图系统故事 i NPC号 
	void story_npctalk(int i, Player player[], Npc npc[]);
	void story_fight(int i, int j, Fight *fight,Player player[]);
};