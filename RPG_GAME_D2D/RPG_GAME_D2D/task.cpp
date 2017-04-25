
#include "Task.h"
//��ʼ/����/ȷ�����
//i--panel���  0-��ʼ 1--���� 2--���� 3--���� 4--ս��ѡ��һ 5--ս��ѡ��2 6--ս����Ʒ 7--ս������ 8--ս������ 9--״̬��� 
//j--��ť���
void Task::story_panel(int i, int j, HWND hwnd)
{
	switch (i)
	{
	case 0://������尴ťʱ��
		switch (j)
		{
		case 0: //��
			status = 1;
			break;
		case 1: //�� --��ȡ���
			status=0;//���
			current_panel = 1;
			break;
		case 2: //ת --�������
			status = 0;
			current_panel = 2;
			break;
		case 3: //��--����
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;
	case 1://����
		break;
	case 2://����
		break;
	case 3: //�˳�ȷ�����
		switch (j)
		{
		case 0: //��
			status = 1;
			break;
		case 1://��
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;
	case 4: //ս��ѡ��һ
		switch (j)
		{
		case 0: //����
			current_panel = 5;
			break;
		case 1://��Ʒ
			current_panel = 7;
			break;
		case 2://����
			current_panel = 6;
			break;
		case 3://����
			break;
		default:
			break;
		}
	case 5: //ս��ѡ���
		break;

	default:
		break;
	}
}
//��ͼ�л�story
void Task::story_changemap(int i, Player player[])
{
	switch (i)
	{
	case 1: //��ͼ�л�Ұ��1
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 100;
			player[current_player].y_map = 400;
			player[current_player].face = 3;
			current_map = 1;
		}
		break;
	case 2: //��ͼ�л�Ұ��2
		if (player[current_player].face == 2)
		{
			player[current_player].x_map = 1200;
			player[current_player].y_map = 400;
			player[current_player].face = 2;
			current_map = 1;
		}
		break;
	case 3: //��ɽ
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 300;
			player[current_player].y_map = 450;
			player[current_player].face = 4;
			current_map = 2;
		}
		break;
	case 4://ҩ��
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 230;
			player[current_player].y_map = 340;
			player[current_player].face = 4;
			current_map = 8;
		}
		break;
	case 5://�õ�
		if (player[current_player].face == 4)
		{
			player[current_player].x_map = 250;
			player[current_player].y_map = 380;
			player[current_player].face = 4;
			current_map = 10;
		}
		break;
	case 6://������
		if (player[current_player].face == 3)
		{
			player[current_player].x_map = 260;
			player[current_player].y_map = 350;
			player[current_player].face = 4;
			current_map = 9;
		}
		break;
	case 7: //Ұ->city1
		if (player[current_player].face == 1)
		{
			player[current_player].x_map = 40;
			player[current_player].y_map = 380;
			player[current_player].face = 3;
			current_map = 0;
		}
		break;
	case 8: //Ұ->city2
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
//��ͼϵͳ���� i NPC�� 
void maketalk(wchar_t *str,int type ,int *num)
{
	status = 3;
	talk = str;
	talk_type = type;
	*num = *num+1;
}

void Task::story_npctalk(int i, Player player[], Npc npc[])
{
	switch (i)//NPC���
	{
	case 20: //����״̬���
		status = 4;
		break;
	case 1:  //������
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"�䣺\n�ϸ��������һ�����ҵ�ɽͷû��һ��Ҳ�а�ʮ��", 1, &npc[i].story_num);
			break;
		case 2://NPC  ����2
			maketalk(L"�䣺\n�����������ζ����", 1, &npc[i].story_num);
			break;
		case 3: //NPC ����3
			maketalk(L"ף����\n��ס����ס����Ԥ����ط�һ�����ҵ����ɣ�", 1, &npc[i].story_num);
			break;
		case 4: //NPC ����3
			maketalk(L"����\n�Ǹ��ϸ���˵���û��һ�ٱ�Ҳ�а�ʮ�ˡ�����", 1, &npc[i].story_num);
			break;
		case 5: //NPC ����3
			maketalk(L"�䣬ף��������\n������������������", 1, &npc[i].story_num);
			break;
		case 6: //NPC ����3
			maketalk(L"ף����\n��ɽ��ɽ��", 1, &npc[i].story_num);
			break;
		case 7: //NPC ����3
			status = 1;
			npc[i].visible = 0;
			npc[i].story_num = 1;
			break;
		default:
			break;
		}
		break;
	case 2:   //�����ϲ�
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"ף���� ������λ�ϸ�˵ؿ��Ǿ����¡�", 1, &npc[i].story_num);
			break;
		case 2://NPC  ����2
			maketalk(L"·�˼ף� �£��˵�ȷʵ�Ǿ����£�����С������������ʲô�أ�������������������ʮ�����ˣ��������Ұ��Ƥëȴ�Ǽ��õġ�", 2, &npc[i].story_num);
			break;
		case 3: //NPC ����3
			maketalk(L"ף���� �ǣ����������ɷ��������ɽ�����˵���Ϣ��", 1, &npc[i].story_num);
			break;
		case 4: //NPC ����3
			maketalk(L"·�˼ף� ���ˣ�����û�����������ɽ��ȷʵ���е�Ź֡�ɽ��һֱ�������ɵģ����һ�Ī���������ֻþ���ȷʵа�ŵĺ��ء�", 2, &npc[i].story_num);
			break;
		case 5: //NPC ����3
			maketalk(L"·�˼ף� ���ɽ�����������˶�û��������ɽ������û׼����������ء�", 2, &npc[i].story_num);
			break;
		case 6: //NPC ����3
			maketalk(L"·�˼ף� �¶��ˣ������п������Ƭ��������ɽ��żȻ�õ��ģ�����̵��ֻ�ͦ�֣�û׼�����������͸����Ǻ��ˡ�", 2, &npc[i].story_num);
			break;
		case 7: //NPC ����3
			maketalk(L"·�˼ף� �һ�Ҫ��·�Ͳ����������ˣ����Ժ���·��ׯ������������·�˼ס�", 2, &npc[i].story_num);
			break;
		case 8: //NPC ����3
			maketalk(L"ף���� лл·�����ˡ�", 1, &npc[i].story_num);
			break;
		case 9: //NPC ����3
			maketalk(L"ף��ϰ�á���������������ϰ�á�xx����ϰ�á�x��", 1, &npc[i].story_num);
			break;
		case 10: //NPC ����3
			status = 1;
			npc[i].story_num = 11;
			break;
		case 11:
			maketalk(L"�������˻����ܻؼ������ˡ�", 1, &npc[i].story_num);
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 3: //��Ǯ���
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"��⣺������齫��Ǯ������˿�զ�ػؼҰ���", 2, &npc[i].story_num);
			break;
		case 2: //NPC ����3
			maketalk(L"��⣺��", 2, &npc[i].story_num);
			npc[i].story_num = 2;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 4: //��
		switch (npc[i].story_num)
		{
		case 1: //NPC ����3
			maketalk(L"������������", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 5: //��
		switch (npc[i].story_num)
		{
		case 1: //NPC ����3
			maketalk(L"����è��������", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 6://��ҩ
		switch (npc[i].story_num)
		{
		case 1: 
			maketalk(L"٩Ң����������Ҳ��ɹɹҩ������ҩ�Ļ����ݾ��У�����ͯ�����۰˿�׼��ʮ�������ۡ�", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 7://Ϲ��
		switch (npc[i].story_num)
		{
		case 1:
			maketalk(L"���ˣ��������꣬�����ߣ�������ɽ������ϧ�ϵ����á���", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 8://����
		switch (npc[i].story_num)
		{
		case 1: //NPC ����3
			maketalk(L"���ʣ��Ǹ�����ӣ�����һ���˻�û������Ī������ɽ�Ȼ���ȥ��!!", 2, &npc[i].story_num);
			break;
		case 2:
			npc[i].story_num = 1;
			status = 1;
			break;
		default:
			break;
		}
		break;
	case 9://�²���ͷ
		switch (npc[i].story_num)
		{
		case 1: //NPC ����3
			maketalk(L"ͼ�٣�֪����Ϊɶ����ûӰ�Ӳ����Ҹ����㰡�������Ǹ�����!!", 2, &npc[i].story_num);
			break;
		case 2:
			maketalk(L"�䣺������˵ɶ��������ʲô��˼����������ɶ��˼��", 1, &npc[i].story_num);
			break;
		case 3:
			npc[i].story_num = 4;
			status = 1;
			break;
		case 4:
			maketalk(L"�������ʤ��һ������ʫ��������", 2, &npc[i].story_num);
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
	case 4: //ս��ѡ��һ
		switch (j)
		{
		case 0: //����
			fight->target1_status = 4;
			current_panel = 5;
			break;
		case 1://����
			fight->target1_status = 8;
			player[fight->select_target1].fstatus = 8;
			fight->select_target1 = -1;
			fight->select_target2 = -1;
			fight->fight_type = 0;
			break;
		case 2://��Ʒ
			fight->target1_status = 6;
			current_panel = 7;
			break;
		case 3://����
			fight->target1_status = 5;
			current_panel = 6;
			break;
		default:
			break;
		}
		break;
	case 5: //ս��ѡ���
		fight->select_target2 = j;
		fight->fight_type = 4;
		break;
	case 6://����
		    fight->select_skill = j;
			player[fight->select_target1].fstatus_anm[5] = j;//����ȷ��
			current_panel = 5;
		break;
	case 7://��Ʒ
		    fight->select_item = fight->item_button[j].item_num;
			current_panel = 5;
		break;
	case 8://ʤ��
		fight->unload();
		status = 1;
		break;
	case 9://ս��
		fight->unload();
		status = 0;
		current_panel = 0;
		break;
	default:
		break;
	}
}