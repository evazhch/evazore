#pragma once
#include "head.h"
#include "Player.h"
#include "Npc.h"
#include "Fight.h"
class Npc;

class Task
{
public:
	//��ʼ/����/ȷ�����/�������
	void story_panel(int i, int j, HWND hwnd);
	//��ͼ�л�story
	void story_changemap(int i, Player player[]);
	//��ͼϵͳ���� i NPC�� 
	void story_npctalk(int i, Player player[], Npc npc[]);
	void story_fight(int i, int j, Fight *fight,Player player[]);
};