
#include "Task.h"
//开始/结束/确认面板
//i--panel编号  0-开始 1--保存 2--设置 3--结束 4--战斗选择一 5--战斗选择2 6--战斗物品 7--战斗技能 8--战斗结束 9--状态面板 
//j--按钮编号
void Task::story_panel(int i, int j, HWND hwnd)
{
	switch (i)
	{
	case 0://控制面板按钮时间
		switch (j)
		{
		case 0: //起
			status = 1;
			break;
		case 1: //承 --读取面板
			status=0;//面板
			current_panel = 1;
			break;
		case 2: //转 --保存面板
			status = 0;
			current_panel = 2;
			break;
		case 3: //结--结束
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;
	case 1://保存
		break;
	case 2://设置
		break;
	case 3: //退出确认面板
		switch (j)
		{
		case 0: //起
			status = 1;
			break;
		case 1://承
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;
	case 4: //战斗选择一
		switch (j)
		{
		case 0: //攻击
			current_panel = 5;
			break;
		case 1://物品
			current_panel = 7;
			break;
		case 2://技能
			current_panel = 6;
			break;
		case 3://防御
			break;
		default:
			break;
		}
	case 5: //战斗选择二
		break;

	default:
		break;
	}
}
//地图切换story
void Task::story_changemap(int i, Player player[])
{
	switch (i)
	{
	case 1: //地图切换野外1
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 100;
			player[current_player].y_map = 400;
			player[current_player].face = 3;
			current_map = 1;
		}
		break;
	case 2: //地图切换野外2
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 1200;
			player[current_player].y_map = 400;
			player[current_player].face = 2;
			current_map = 1;
		}
		break;
	case 3: //上山
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 300;
			player[current_player].y_map = 450;
			player[current_player].face = 4;
			current_map = 2;
		}
		break;
	case 4://药店
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 230;
			player[current_player].y_map = 340;
			player[current_player].face = 4;
			current_map = 8;
		}
		break;
	case 5://旅店
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 250;
			player[current_player].y_map = 380;
			player[current_player].face = 4;
			current_map = 10;
		}
		break;
	case 6://武器店
		if (player[current_player].face == 3)
		{
			player[current_player].x_map = 260;
			player[current_player].y_map = 350;
			player[current_player].face = 4;
			current_map = 9;
		}
		break;
	case 7: //野->city1
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 40;
			player[current_player].y_map = 380;
			player[current_player].face = 3;
			current_map = 0;
		}
		break;
	case 8: //野->city2
		if (player[current_player].face == 3)
		{
			player[current_player].x_map = 400;
			player[current_player].y_map = 200;
			player[current_player].face = 3;
			current_map = 0;
		}
		break;
	case 9: //1->city
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 450;
			player[current_player].y_map = 150;
			player[current_player].face = 1;
			current_map = 0;
		}
		break;
	case 10://1->2
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 780;
			player[current_player].y_map = 1250;
			player[current_player].face = 4;
			current_map = 3;
		}
		break;
	case 11://2->1
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 170;
			player[current_player].y_map = 300;
			player[current_player].face = 1;
			current_map = 2;
		}
		break;
	case 12://2->3-1
		if (player[current_player].face == 3)
		{
			player[current_player].x_map = 80;
			player[current_player].y_map = 880;
			player[current_player].face = 3;
			current_map = 4;
		}
		break;
	case 13://2->3-2
		if (player[current_player].face == 3)
		{
			player[current_player].x_map = 0;
			player[current_player].y_map = 340;
			player[current_player].face = 3;
			current_map = 4;
		}
		break;
	case 14://3->2-1
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 880;
			player[current_player].y_map = 900;
			player[current_player].face = 2;
			current_map = 3;
		}
		break;
	case 15://3->2-2
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 850;
			player[current_player].y_map = 340;
			player[current_player].face = 2;
			current_map = 3;
		}
		break;
	case 16://3->4
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 30;
			player[current_player].y_map = 640;
			player[current_player].face = 4;
			current_map = 5;
		}
		break;
	case 17://4->3
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 10;
			player[current_player].y_map = 730;
			player[current_player].face = 1;
			current_map = 4;
		}
		break;
	case 18://4->5
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 230;
			player[current_player].y_map = 440;
			player[current_player].face = 4;
			current_map = 6;
		}
		break;
	case 19://5->4
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 720;
			player[current_player].y_map = 10;
			player[current_player].face = 1;
			current_map = 5;
		}
		break;
	case 20://5->6
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 800;
			player[current_player].y_map = 430;
			player[current_player].face = 2;
			current_map = 7;
		}
		break;
	case 21://y->c
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 280;
			player[current_player].y_map = 600;
			player[current_player].face = 1;
			current_map = 0;
		}
		break;
	case 22://l->c
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 650;
			player[current_player].y_map = 620;
			player[current_player].face = 1;
			current_map = 0;
		}
		break;
	case 23://w->c
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 800;
			player[current_player].y_map = 700;
			player[current_player].face = 2;
			current_map = 0;
		}
		break;
	default:
		break;
	}
}
//地图系统故事 i NPC号 
void maketalk(wchar_t *str,int type ,int *num)
{
	status = 3;
	talk = str;
	talk_type = type;
	*num = *num+1;
}

void Task::story_npctalk(int i, Player player[], Npc npc[])
{
	switch (i)//NPC编号
	{
	case 20: //进入状态面板
		status = 4;
		break;
	case 1:  //开场白
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"配：\n老哥咱这出门一年来找的山头没有一百也有八十了", 1, &npc[i].story_num);
			break;
		case 2://NPC  故事2
			maketalk(L"配：\n火锅都尝到甜味的了", 1, &npc[i].story_num);
			break;
		case 3: //NPC 故事3
			maketalk(L"祝觉：\n打住，打住，我预感这地方一定能找到剑仙！", 1, &npc[i].story_num);
			break;
		case 4: //NPC 故事3
			maketalk(L"钕竹：\n那个老哥你说这句没有一百遍也有八十了。。。", 1, &npc[i].story_num);
			break;
		case 5: //NPC 故事3
			maketalk(L"配，祝觉，钕竹：\n。。。。。。。。。", 1, &npc[i].story_num);
			break;
		case 6: //NPC 故事3
			maketalk(L"祝觉：\n上山上山！", 1, &npc[i].story_num);
			break;
		case 7: //NPC 故事3
			status = 1;
			npc[i].visible = 0;
			npc[i].story_num = 1;
			break;
		default:
			break;
		}
		break;
	case 2:   //敢问老伯
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"祝觉： 敢问这位老哥此地可是九里坡。", 1, &npc[i].story_num);
			break;
		case 2://NPC  故事2
			maketalk(L"路人甲： 奥，此地确实是九里坡，敢问小哥来九里坡做什么呢，我来九里坡做买卖有十几年了，这里出产野兽皮毛却是极好的。", 2, &npc[i].story_num);
			break;
		case 3: //NPC 故事3
			maketalk(L"祝觉： 那，敢问先生可否听闻这个山上仙人的消息？", 1, &npc[i].story_num);
			break;
		case 4: //NPC 故事3
			maketalk(L"路人甲： 仙人？倒是没听过，但这个山上确实是有点古怪。山上一直是雾蒙蒙的，而且会莫名其妙会出现幻觉，确实邪门的很呢。", 2, &npc[i].story_num);
			break;
		case 5: //NPC 故事3
			maketalk(L"路人甲： 这个山啊，连村里人都没有爬到过山顶过，没准真的有仙人呢。", 2, &npc[i].story_num);
			break;
		case 6: //NPC 故事3
			maketalk(L"路人甲： 奥对了，我这有块奇怪铁片，就是在山上偶然得到的，上面刻的字还挺怪，没准对你们有用送给你们好了。", 2, &npc[i].story_num);
			break;
		case 7: //NPC 故事3
			maketalk(L"路人甲： 我还要赶路就不和你们聊了，若以后到了路家庄，可以来找我路人甲。", 2, &npc[i].story_num);
			break;
		case 8: //NPC 故事3
			maketalk(L"祝觉： 谢谢路先生了。", 1, &npc[i].story_num);
			break;
		case 9: //NPC 故事3
			maketalk(L"祝觉习得“剑舞术”，钕竹习得“xx”配习得“x”", 1, &npc[i].story_num);
			break;
		case 10: //NPC 故事3
			status = 1;
			npc[i].story_num = 11;
			break;
		case 11:
			maketalk(L"办完这趟货就能回家养老了。", 1, &npc[i].story_num);
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 3: //赌钱输光
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"舒光：昨晚打麻将把钱都输光了可咋地回家啊。", 2, &npc[i].story_num);
			break;
		case 2: //NPC 故事3
			maketalk(L"舒光：唉", 2, &npc[i].story_num);
			npc[i].story_num = 2;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 4: //狗
		switch (npc[i].story_num)
		{
		case 1: //NPC 故事3
			maketalk(L"单身狗：汪汪汪", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 5: //狗
		switch (npc[i].story_num)
		{
		case 1: //NPC 故事3
			maketalk(L"贵族猫：喵喵喵", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 6://看药
		switch (npc[i].story_num)
		{
		case 1: 
			maketalk(L"侃尧：岁数大了也就晒晒药，想买药的话进屋就行，绝对童叟无欺八块准卖十块明码标价。", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 7://瞎趟
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"夏趟：正着走完，倒着走，好像上山啊，可惜老爹不让。。", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 8://等人
		switch (npc[i].story_num)
		{
		case 1: //NPC 故事3
			maketalk(L"邓仁：那个龟儿子，出门一天了还没回来，莫不是下山喝花酒去了!!", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 9://吐槽老头
		switch (npc[i].story_num)
		{
		case 1: //NPC 故事3
			maketalk(L"图操：知道咱为啥脚下没影子不，我告诉你啊，作者是个渣渣!!", 2, &npc[i].story_num);
			break;
		case 2:
			maketalk(L"配：大叔你说啥？作者是什么意思，渣渣又是啥意思？", 1, &npc[i].story_num);
			break;
		case 3:
			npc[i].story_num = 4;
			status = 1;
			break;
		case 4:
			maketalk(L"沟里郭嘉胜似一，，好诗啊。。。", 2, &npc[i].story_num);
			npc[i].story_num = 3;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Task::story_fight(int i, int j, Fight *fight,Player player[])
{
	switch (i)
	{
	case 4: //战斗选择一
		switch (j)
		{
		case 0: //攻击
			fight->target1_status = 4;
			current_panel = 5;
			break;
		case 1://防御
			fight->target1_status = 8;
			player[fight->select_target1].fstatus = 8;
			fight->select_target1 = -1;
			fight->select_target2 = -1;
			fight->fight_type = 0;
			break;
		case 2://物品
			fight->target1_status = 6;
			current_panel = 7;
			break;
		case 3://技能
			fight->target1_status = 5;
			current_panel = 6;
			break;
		default:
			break;
		}
		break;
	case 5: //战斗选择二
		fight->select_target2 = j;
		fight->fight_type = 4;
		break;
	case 6://技能
		    fight->select_skill = j;
			player[fight->select_target1].fstatus_anm[5] = j;//动画确认
			current_panel = 5;
		break;
	case 7://物品
		    fight->select_item = fight->item_button[j].item_num;
			current_panel = 5;
		break;
	case 8://胜利
		fight->unload();
		status = 1;
		break;
	case 9://战败
		fight->unload();
		status = 0;
		current_panel = 0;
		break;
	default:
		break;
	}
}