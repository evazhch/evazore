#include "head.h"
#include "Animation.h"
#include "Npc.h"
#include "Enemy.h"
#include "Panel.h"
#include "Fight.h"


//����ս������
void Fight::init(Player player[],Animation playerAnm[],Animation enemyAnm[],int fenemy[],Enemy enemy[])
{
	
	//���ر���
	SAFE_RELEASE(back_grand);
		LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/map/fight_tree.bmp", 0, 0, &back_grand);
	//��������״̬����
		SAFE_RELEASE(back_grand1);
		LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/fight/player.bmp", 0, 0, &back_grand1);

	//����һϵ�н�ɫ��Դ
	for (int i = 0; i < 3; i++)
	{
		if (player[i].is_active == 1) //��ɫ�Ƿ񼤻�
		{
			//��ɫ����
			for (int j = 0; j < 3; j++)
			{
				if (player[i].skill[j].on_un == 1 && playerAnm[player[i].skill[j].anm_id].aDecoder==NULL) //��ѧϰ
				{
					playerAnm[player[i].skill[j].anm_id].loadGIF(pRenderTarget,pWICFactory);
				}
			}
			//״̬����
			for (int j = 0; j <= 5; j++)
			{	
				if (playerAnm[player[i].fstatus_anm[j]].aDecoder == NULL) 
				{
					playerAnm[player[i].fstatus_anm[j]].loadGIF(pRenderTarget, pWICFactory);
				}
			}
		}
	}

	//����enemy
	for (int i = 0; i < 3; i++)
	{
		if (fenemy[i] != -1)
		{
			
			fenemy_num[i] = fenemy[i];
			this->fenemy[i] = enemy[fenemy_num[i]];
			enemyAnm[this->fenemy[i].anm_nor].loadGIF(pRenderTarget, pWICFactory);
			enemyAnm[this->fenemy[i].anm_att].loadGIF(pRenderTarget, pWICFactory);
			enemyAnm[this->fenemy[i].anm_skill].loadGIF(pRenderTarget, pWICFactory);
			enemyAnm[this->fenemy[i].anm_hurt].loadGIF(pRenderTarget, pWICFactory);
		}
	}
	//����panel
	//chose���
	chose_panel.set(rc.right/3, rc.bottom/4,NULL, 0, 3);

	chose_button[0].set(rc.right / 3, 0, 50, 50, L"source/fight/g0.png", L"source/fight/g1.png", L"");//����
	chose_button[1].set(rc.right / 3+50, 0, 50, 50, L"source/fight/f0.png", L"source/fight/f1.png", L"");//����
	chose_button[2].set(rc.right / 3+100,0, 50, 50, L"source/fight/w0.png", L"source/fight/w1.png", L"");//��Ʒ
	chose_button[3].set(rc.right / 3+150,0, 50, 50, L"source/fight/j0.png", L"source/fight/j1.png", L"");//����
	//chose_button[4].set(rc.right / 3+75, rc.bottom / 4+50, 50, 50, L"source/fight/w0.bmp", L"source/fight/w1.bmp", L"");//����

	//chose2���
	chose2_panel.set(0,0, L"source/fight/change.png", 0, 8);
	
	chose2_button[0].set(rc.right/3*2, 0, rc.right/3, rc.bottom/4, L"source/fight/change.png", L"source/fight/change1.png", L"");
	chose2_button[1].set(rc.right / 3 * 2, rc.bottom/4, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");
	chose2_button[2].set(rc.right / 3 * 2, rc.bottom /2, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");

	chose2_button[3].set(0, 0, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");//4
	chose2_button[4].set(0, rc.bottom / 4, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");//5
	chose2_button[5].set(0, rc.bottom / 2, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");//5
	
	chose2_button[6].set(0,rc.bottom/4*3 , rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");//5
	chose2_button[7].set(rc.right / 3 , rc.bottom / 4*3, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");//5
	chose2_button[8].set(rc.right / 3 * 2, rc.bottom / 4*3, rc.right / 3, rc.bottom / 4, L"source/fight/change.png", L"source/fight/change1.png", L"");//5

	//�������
	skill_panel.set(rc.right / 3, rc.bottom / 4, L"source/fight/1.bmp", 0, 4);
	skill_button[0].set(rc.right / 3, rc.bottom / 4, rc.right / 3, rc.bottom/10 ,  L"source/fight/change.png", L"source/fight/change1.png", L"");//����1
	skill_button[1].set(rc.right / 3, rc.bottom / 4+ rc.bottom / 10, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");//����2
	skill_button[2].set(rc.right / 3, rc.bottom / 4+rc.bottom / 5, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");//����3
	skill_button[3].set(rc.right / 3, rc.bottom / 4 + rc.bottom / 10*3, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");//����4
	skill_button[4].set(rc.right / 3, rc.bottom / 4 + rc.bottom / 10*4, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");//����5
	//��Ʒ���
	item_panel.set(rc.right / 3, rc.bottom / 4, L"source/fight/1.bmp", 0, 4);
	item_button[0].set(rc.right / 3, rc.bottom / 4, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");
	item_button[1].set(rc.right / 3, rc.bottom / 4 + rc.bottom / 10, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");
	item_button[2].set(rc.right / 3, rc.bottom / 4 + rc.bottom / 5, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");
	item_button[3].set(rc.right / 3, rc.bottom / 4 + rc.bottom / 10 * 3, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");
	item_button[4].set(rc.right / 3, rc.bottom / 4 + rc.bottom / 10 * 4, rc.right / 3, rc.bottom / 10, L"source/fight/change.png", L"source/fight/change1.png", L"");
	item_button[5].set(0, 0, 0, 0, L"", L"", L"");//��һҳ
	//ս���������
	win_panel.set(0, 0, L"source/fight/1.bmp", 0, 0);
	win_button[0].set(rc.left, rc.top, rc.right, rc.bottom,L"source/fight/change.png", L"source/fight/change.png",L"");

	end_panel.set(0, 0, L"source/fight/end.bmp", 0, 0);
	end_button[0].set(rc.left, rc.top, rc.right, rc.bottom, L"source/fight/change.png", L"source/fight/change.png", L"");
}
//ս��ѭ��
void  Fight::run(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[],Item item[],Item item2[],LPDIRECTSOUNDBUFFER pSBuf[])
{
	
	//״̬�ж�
	if (fight_type == 0 && select_target1==-1 && select_target2==-1)
	{
		time2 = end;
		if (time2 - time1 > 500)
		{
			time2 = end;
			if(win_lose(player)==0)
			makeQue(player, enemy);
			time1 = time2;
		}
	}
	else
	{
		if (fight_type != 0)
		{
			time2 = end;
			time1 = time2;
		}
	}
	//״̬��ʾ
	switch (fight_type)
	{
	case -1: //����
		init(player, playerAnm, enemyAnm, fenemy_num, enemy);
		fight_type = 0;
		break;
	case 0: //��ͨ
		normal(player, playerAnm, enemyAnm, enemy,item);
		break;
	case 1: //���
		normal(player, playerAnm, enemyAnm, enemy,item);
		switch (current_panel)
		{
		case 4:
			chose_panel.init(pRenderTarget, chose_button, rc.right / 3, rc.bottom / 4,rc.right/3, rc.bottom/4);
			break;
		case 5:
			chose2_panel.init(pRenderTarget, chose2_button);
			break;
		case 6:
			skill_panel.init(pRenderTarget, skill_button, rc.right / 3, rc.bottom / 4, rc.right / 3, rc.bottom / 2);
			for (int i = 0; i < 5; i++)
			{
				if (player[select_target1].skill[i].on_un = 1)
				{
					player[select_target1].skill[i].show_name(rc.right / 3, rc.bottom / 4 + rc.bottom / 10 * i, rc.right / 3, rc.bottom / 10);
				}
			}
			break;
		case 7:
			item_panel.init(pRenderTarget, skill_button, rc.right / 3, rc.bottom / 4, rc.right / 3, rc.bottom / 2);
			for (int i = 0; i < 5; i++)
			{
				if (i+item_page*5<player_item_num)
				{
					item_button[i].item_num = i + item_page * 5;
					item[i+item_page*5].show_name(rc.right / 3, rc.bottom / 4 + rc.bottom / 10 * i, rc.right / 3, rc.bottom / 10);
					item[i + item_page * 5].show_num(rc.right / 3*2-20, rc.bottom / 4 + rc.bottom / 10 * i, 20, 20);
					if (i == item_panel.current_button)
					{
						item[i + item_page * 5].show_description(rc.right / 3, 0, rc.right, rc.bottom);
					}
				}
			}
			break;
		case 8: //ʤ��
			pSBuf[0]->Stop();
			pSBuf[1]->Stop();
			pSBuf[2]->Play(0, 0, 0);
			pSBuf[3]->Stop();
			win_panel.init(pRenderTarget, win_button,rc.right / 3, rc.bottom / 4, rc.right / 3, rc.bottom / 2);
			for (int i = 0; i < 3; i++)
			{
				if (fenemy_num[i] != -1)
				{
					pRenderTarget->DrawText(
						fenemy[i].itemname,           // Text to render
						wcslen(fenemy[i].itemname),       // Text length
						g_pTextFormat,     // Text format
						D2D1::RectF(rc.right / 3, rc.bottom / 4 + rc.bottom / 6 * i, rc.right / 3 * 2, rc.bottom / 4 + rc.bottom / 6 * (i + 1)),    // The region of the window where the text will be rendered
						pBlueBrush      // The brush used to draw the text
					);
				}
				if (fenemy_num[i] != -1 && getMany==0)
				{
					player[current_player].add_item(fenemy[i].item_id, 1, item, item2);
					money += fenemy[i].many;
				}	
			}
			getMany = 1;
			break;
		case 9: //ʧ��
			end_panel.init(pRenderTarget, end_button);
			break;
		default:
			break;
		}
		break;
	case 4: //��ɫ�
		if(player[select_target1].fstatus<4)
		playerFight(player, playerAnm, enemyAnm, enemy);
		normal(player, playerAnm, enemyAnm, enemy,item);
		break;
	case 5: //���˹���
		if(select_target2==-1)
		enemyFight(player, playerAnm, enemyAnm, enemy);
		normal(player, playerAnm, enemyAnm, enemy,item);
		break;
	default:
		fight_type = 0;
		break;
	}
}
//��ɫ����
void Fight::playerFight(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[])
{
	switch (target1_status)
	{
	case 4: //����
		player[select_target1].fstatus = 4;
		break;
	case 5: //����
		player[select_target1].fstatus = 5;
		break;
	case 6://��Ʒ
		player[select_target1].fstatus = 6;
		break;
	default:
		break;
	}
	if (select_target1 == -1)
	{
		makeQue(player,enemy);
		if (select_target2 < 3)
		{
			player[select_target2].fstatus = 7;
		}
	}
}
void Fight::enemyFight(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[])
{
	long a;
	a = GetTickCount();
	a = a % 2;
	if (a) //����
	{
		fenemy[select_target1 - 4].fstatus = 2;
	}
	else //��ͨ����
	{
		fenemy[select_target1 - 4].fstatus = 1;
	}
	for (int i = 0; i < 3;i++)
	{
		if (player[i].is_active == 1 && player[i].hp > 0)
		{
			select_target2 = i;
			break;
		}
	}
}
//״̬����
void Fight::normal(Player player[],Animation playerAnm[],Animation enemyAnm[],Enemy enemy[],Item item[])
{

	//������
	pRenderTarget->DrawBitmap(
		back_grand,
		D2D1::RectF(
			rc.left,rc.top,rc.right,rc.bottom
		),
		1.0f
	);

	//������
	if (select_target1 == -1 && select_target2 < 3)
	{
		player[select_target2].fstatus = 1;
	}

	for (int i=0;i<3;i++)
	{
		if (player[i].is_active == 1)
		{

			switch (player[i].fstatus)
			{
			case 0: //һ��
				//Ѫ��
				pRenderTarget->DrawRectangle(
					D2D1::RectF(rc.right / 3 * 2 + i * 20, rc.bottom / 4*i, rc.right / 3 * 2 + i * 20 + 200, rc.bottom / 4 * i + 5),
					pBlueBrush
				);
				pRenderTarget->FillRectangle(
					D2D1::RectF(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3 * 2 + i * 20 + 200*player[i].hp/player[i].max_hp, rc.bottom / 4 * i + 5),
					pRedBrush
				);
				//����
				pRenderTarget->DrawRectangle(
					D2D1::RectF(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i+7, rc.right / 3 * 2 + i * 20 + 200, rc.bottom / 4 * i + 12),
					pBlueBrush
				);
				pRenderTarget->FillRectangle(
					D2D1::RectF(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i+7, rc.right / 3 * 2 + i * 20 + 200 * player[i].mp / player[i].max_mp, rc.bottom / 4 * i + 12),
					pBlueBrush
				);
				playerAnm[player[i].fstatus_anm[0]].setAnmPoint(rc.right / 3 * 2+i*20, rc.bottom / 4*i, rc.right / 3, rc.bottom / 2);
				playerAnm[player[i].fstatus_anm[0]].drawAnmLoop();
				break;
			case 1: //����
				playerAnm[player[i].fstatus_anm[1]].setAnmPoint(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3, rc.bottom / 2);
				if (playerAnm[player[i].fstatus_anm[1]].drawAnm() == 1)
				{
					select_target2 = -1;
					fight_type = 0;
					math(player);
					judgPlayerStatus(player);
				}
				break;
			case 2: //����
			    //Ѫ��
				pRenderTarget->DrawRectangle(
					D2D1::RectF(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3 * 2 + i * 20 + 200, rc.bottom / 4 * i + 5),
					pBlueBrush
				);
				pRenderTarget->FillRectangle(
					D2D1::RectF(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3 * 2 + i * 20 + 200 * player[i].hp / player[i].max_hp, rc.bottom / 4 * i + 5),
					pRedBrush
				);
				playerAnm[player[i].fstatus_anm[2]].setAnmPoint(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3, rc.bottom / 2);
				playerAnm[player[i].fstatus_anm[2]].drawAnmLoop();
				break;
			case 3: //����
				playerAnm[player[i].fstatus_anm[3]].setAnmPoint(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3, rc.bottom / 2);
				playerAnm[player[i].fstatus_anm[3]].drawAnmOne();
				break;
			case 4://����
				playerAnm[player[i].fstatus_anm[4]].setAnmPoint(rc.right / 3, rc.bottom / 4 * (select_target2 - 3), rc.right / 3, rc.bottom / 2);
				if (playerAnm[player[i].fstatus_anm[4]].drawAnm() == 1)
				{
					math(player);
					judgPlayerStatus(player);
					if (fight_type == 4)
					{
						fight_type = 0;
					}
					select_target1 = -1;
					target1_status = -1;
					fenemy[select_target2 - 3].fstatus = 3;
					
				}
				break;
				break;
			case 5://����
				playerAnm[player[i].skill[player[i].fstatus_anm[5]].anm_id].setAnmPoint(0, 0 - (5 - select_target2)*rc.bottom / 5,rc.right/3,rc.bottom/2);
				if (playerAnm[player[i].skill[player[i].fstatus_anm[5]].anm_id].drawAnm() == 1)
				{   
					math(player);
					fight_type = 0;
					select_target1 = -1;
					target1_status = -1;
					fenemy[select_target2 - 3].fstatus = 3;
					judgPlayerStatus(player);
				}
				break;
			case 6://��Ʒ�ͷ�
				playerAnm[player[i].fstatus_anm[5]].setAnmPoint(rc.right / 3 * 2, rc.bottom / 4, rc.right / 3, rc.bottom / 2);
				if (playerAnm[player[i].fstatus_anm[5]].drawAnm() == 1)
				{
					player[select_target2].use_item(item[select_item].id, item);
					fight_type = 0;
					select_target1 = -1;
					target1_status = -1;
					player[select_target2].fstatus = 7;
					judgPlayerStatus(player);
				}
				break;
			case 7://��Ʒ/���ܳ���
				if (select_target1 == -1)
				{
					if (playerAnm[player[i].fstatus_anm[7]].drawAnm() == 1)
					{
						math(player);
						select_target2 = -1;
						fight_type = 0;
						judgPlayerStatus(player);
					}
				}
				break;
			case 8://����
				playerAnm[player[i].fstatus_anm[8]].setAnmPoint(rc.right / 3 * 2 + i * 20, rc.bottom / 4 * i, rc.right / 3, rc.bottom / 2);
				playerAnm[player[i].fstatus_anm[8]].drawAnmLoop();
				break;
			default:
				player[i].fstatus = 0;
				break;
			}
		}
	}

	
	
	for (int i=0;i<3;i++)
	{
		if (fenemy_num[i] != -1)
		{
			switch (fenemy[i].fstatus)
			{
			case 0: //һ��
				enemyAnm[enemy[fenemy_num[i]].anm_nor].setAnmPoint(0+i*30, rc.bottom / 4*i , 200, 200);
				enemyAnm[enemy[fenemy_num[i]].anm_nor].drawAnmLoop();
				//Ѫ��
				pRenderTarget->DrawRectangle(
					D2D1::RectF(i * 30, rc.bottom / 4*i, i*30+200, rc.bottom / 4*i+5),
					pBlueBrush
				);
				pRenderTarget->FillRectangle(
					D2D1::RectF(i * 30, rc.bottom / 4*i, i*30+200 * fenemy[i].hp / fenemy[i].maxhp, rc.bottom / 4*i+5),
					pRedBrush
				);
				break;
			case 1://����
				enemyAnm[enemy[fenemy_num[i]].anm_att].setAnmPoint(0 + i * 30, rc.bottom / 4 * i, 200, 200);
				if(enemyAnm[fenemy[i].anm_att].drawAnm()==1)
				{
				math(player);
				judgStatus(enemy);
				select_target1 = -1;
				target1_status = -1;
				}
				break;
			case 2://����
				enemyAnm[enemy[fenemy_num[i]].anm_skill].setAnmPoint(0 + i * 30, rc.bottom / 4 * i, 200, 200);
				if (enemyAnm[enemy[fenemy_num[i]].anm_skill].drawAnm() == 1)
				{
					
					math(player);
					judgStatus(enemy);
					fight_type = 0;
					select_target1 = -1;
					target1_status = -1;
				}
				break;
			case 3: //������
					enemyAnm[fenemy[i].anm_hurt].setAnmPoint(0 + i * 30, rc.bottom / 4 * i, 200, 200);
					if (enemyAnm[fenemy[i].anm_hurt].drawAnm() == 1)
					{
						judgStatus(enemy);
						if (fenemy[i].hp > 0)
						{
							fenemy[i].fstatus = 0;
						}
						else
						{
							fenemy[i].fstatus = 4;
						}
						fight_type = 0;
						select_target2 = -1;
						target2_status = -1;
					}
				break;
			case 4: //����
				break;
			default:
				break;
			}
		}
	}
}
//ս������
void Fight::makeQue(Player player[],Enemy enemy[])
{
		for (int i = 1; i < 4; i++)
		{
			if (player[i - 1].is_active == 1 && i != fight_que[0])
			{
				fight_que[i] -= player[i - 1].fspeed;
			}
			if (fenemy_num[i - 1] != -1 && fenemy[i-1].hp>0 && i + 3 != fight_que[0])
			{
				fight_que[i + 3] -= enemy[fenemy_num[i - 1]].fspeed;
			}
		}
		for (int i = 1; i < 7; i++)
		{
			if (fight_que[i] < fight_que[fight_que[0]])
			{
				fight_que[0] = i;
			}
		}
		if (fight_que[0] < 3)
		{
			select_target1 = fight_que[0] - 1;
			fight_type = 1;//����ѡ�����
			current_panel = 4;
		}
		else
		{
			
			select_target1 = fight_que[0];
			fight_type = 5; //���˹���
		}
}
//�˺�����
void Fight::math(Player player[])
{
	if (select_target1 >= 3)
	{
		player[select_target2].hp -= fenemy[select_target1 - 4].attack;
		if (player[select_target2].hp < 0)
			player[select_target2].hp = 0;
	}
	if (select_target1 < 3)
	{
		switch (target1_status)
		{
		case 4://�չ�
			fenemy[select_target2 - 3].hp -= player[select_target1].attack;
			fenemy[select_target2 - 3].fstatus = 3;
			if (fenemy[select_target2 - 3].hp < 0)
			{
				fenemy[select_target2 - 3].hp=0;
			}
			break;
		case 5://����
			fenemy[select_target2 - 3].hp -= player[select_target1].skill[select_skill].value1;
			if (fenemy[select_target2 - 3].hp < 0)
			{
				fenemy[select_target2 - 3].hp = 0;
			}
			break;
		default:
			break;
		}
	}

}

int Fight::win_lose(Player player[])
{
	int fp = 0;
	int ff = 0;
	for (int i = 0; i < 3; i++)
	{
		if (fenemy_num[i] == -1)
		{
			++ff;
		}
		else if (fenemy[i].hp == 0)
		{
			++ff;
		}
		if (ff == 3)
		{
			fight_type = 1;
			current_panel = 8;// win
			return 1;
		}

		if (player[i].is_active == -1)
		{
			fp++;
		}
		else if (player[i].hp == 0)
		{
			fp++;
		}
		if (fp == 3)
		{
			fight_type = 1;       //mianban
			current_panel = 9; //ս��
			return 1;
		}
	}
	return 0;
}
//״̬�ж�
void Fight::judgPlayerStatus(Player player[])
{
	//��ɫ״̬
	for (int i = 0; i < 3; i++)
	{
		if (player[i].is_active == 1 && i != select_target1 && i != select_target2)
		{
			if (player[i].hp == 0)
			{
				player[i].fstatus = 3;
			}
			else if (player[i].hp < player[i].max_hp / 4)
			{
				player[i].fstatus = 2;
			}
			else
			{
				player[i].fstatus = 0;
			}

		}
	}
}

void Fight::judgStatus(Enemy enemy[])
{
	//��ɫ״̬
	for (int i = 0; i < 3; i++)
	{
		//enemy״̬
		if (fenemy_num[i]!=-1 && i != select_target1-3 && i != select_target2-3)
		{
			if (fenemy[i].hp <= 0)
			{
				fenemy[i].fstatus = 4;
			}
			else
			{
				fenemy[i].fstatus = 0;
			}
		}
	}
	
}

void Fight::key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Enemy enemy[],Task task,Fight fight)
{ 
	switch (fight_type)
	{
	case 1://chose1
		switch (current_panel)
		{
		case 4:
			chose_panel.fight_key(hwnd, wParam, chose_button,this, player, task);
			break;
		case 5:
			chose2_panel.fight_key(hwnd, wParam, chose2_button,this, player, task);
			break;
		case 6:
			skill_panel.fight_key(hwnd, wParam, skill_button,this, player, task);
			break;
		case 7:
			item_panel.fight_key(hwnd, wParam, item_button,this, player, task);
			break;
		case 8:
			win_panel.fight_key(hwnd, wParam, win_button, this, player, task);
			break;
		case 9:
			end_panel.fight_key(hwnd, wParam, end_button, this, player, task);
			break;
		default:
			break;
		}
	}
}

void Fight::unload()
{
	 status = 0; //״̬ 0--һ�� 1--ѡ�����
	 select_target1 = -1;  //ѡ�е�Ŀ��1
	 target1_status = -1;
	 select_target2 = -1;  //ѡ�е�Ŀ��2
	 target2_status = -1;
	 getMany = 0;
	 select_skill=-1;
	 select_item=-1;
	 item_page = 0;
	 time1=0;
	 time2=0;
	 fight_que[0] = 0; //ʱ�����
	 fight_que[1] = 0;
	 fight_que[2] = 0;
	 fight_que[3] = 0;
	 fight_que[4] = 0;
	 fight_que[5] = 0;
	 fight_que[6] = 0;
	 fight_type = -1;
}

