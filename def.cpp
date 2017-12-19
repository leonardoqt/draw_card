#include <iostream>
#include <algorithm>
#include "def.h"

using namespace std;

//========================card===============================
card :: card()
{
	label = 0;
	need = 0;
}

card& card :: operator=(const card& B)
{
	this->label = B.label;
	this->need = B.need;
}

void card :: init(int l1)
{
	label = l1;
	need = 0;
}


//========================pack===============================
pack& pack :: operator=(const pack& B)
{
	this->c1[0] = B.c1[0];
	this->c1[1] = B.c1[1];
	this->c1[2] = B.c1[2];
}

void pack :: add_card(int l1)
{
	if (c1[1].label > 0)
	{
		c1[2].init(l1);
	}
	else if (c1[0].label > 0)
		c1[1].init(l1);
	else
		c1[0].init(l1);
}

void pack :: blank()
{
	c1[0].init(0);
	c1[1].init(0);
	c1[2].init(0);
}

//========================deck===============================
deck :: deck()
{
	draw = 0;
}

void deck :: init()
{
	int t1, err;
	int arr[374];
	for (t1 = 0; t1 < 374; t1++)
		arr[t1] = t1%46 + 71;
	random_shuffle(&arr[0],&arr[373]);
	for (t1=0; t1<200; t1++)
		p1[t1].blank();
	for (t1=0; t1<4; t1++)
		provide[t1] = 0;

	for (t1 = 0; t1 < 10 ; t1++)	//add UR
		p1[t1].add_card(t1+1);
	for (t1 = 10; t1 < 22; t1++)	//add SR1
		p1[t1].add_card(t1+1);
	for (t1 = 22; t1 < 34; t1++)	//add SR2
		p1[t1].add_card(t1-11);
	for (t1 = 34; t1 < 66; t1++)	//add R1
		p1[t1].add_card(t1-3);
	for (t1 = 66; t1 < 98; t1++)	//add R2
		p1[t1].add_card(t1-35);
	for (t1 = 98; t1 < 130; t1++)	//add R3
		p1[t1].add_card(t1-67);
	for (t1 = 130; t1 < 162; t1++)	//add R4
		p1[t1].add_card(t1-99);
	for (t1 = 162; t1 < 194; t1++)	//add R5
		p1[t1].add_card(t1-131);
	for (t1 = 194; t1 < 200; t1++)	//add R6
		p1[t1].add_card(t1-163);
	for (t1 = 0; t1 < 26; t1++)		//add R6
		p1[t1].add_card(t1+37);
	for (t1 = 26; t1 < 200; t1++)
		p1[t1].add_card(arr[t1-26]);
	for (t1 = 0; t1 < 200; t1++)
		p1[t1].add_card(arr[t1+174]);

	random_shuffle(&p1[0],&p1[199]);
//	for (t1 = 0; t1 < 200; t1++)
//		cout<<p1[t1].c1[0].label<<'\t'<<p1[t1].c1[1].label<<'\t'<<p1[t1].c1[2].label<<endl;
}

void deck :: update_provide(player a1)
{
	int t1,t2,t3;
	provide[0] = provide[1] = provide[2] = provide[3] = 0;
	for(t1 = draw; t1 < 200; t1++)
	{
		for(t2 = 0; t2 < 4; t2++)
		{
			p1[t1].c1[0].need = p1[t1].c1[1].need = p1[t1].c1[2].need = 0;
			for(t3 = 0; t3 < a1.Need[t2]; t3++)
			{

				if (p1[t1].c1[0].label == a1.need[t2][t3].label && a1.need[t2][t3].need >0)
				{
					p1[t1].c1[0].need = 1;
					provide[t2]++;
				}
				if (p1[t1].c1[1].label == a1.need[t2][t3].label && a1.need[t2][t3].need >0)
				{
					p1[t1].c1[1].need = 1;
					provide[t2]++;
				}
				if (p1[t1].c1[2].label == a1.need[t2][t3].label && a1.need[t2][t3].need >0)
				{
					p1[t1].c1[2].need = 1;
					provide[t2]++;
				}
			}
		}
	}
}

//=========================player================================
player :: player()
{
	pack_drew = 0;
}

void player :: init_need_card(int n1[4])
{
	int t1,t2;
	int ur[10],sr[12],r[32],n[46];
	for (t1=0; t1<4; t1++)
	{
		Need[t1] = n1[t1];
		need[t1] = new card[Need[t1]];
		for (t2=0; t2 < Need[t1]; t2++)
			need[t1][t2].need = 3;
	}
	for (t1=0; t1<10; t1++)
		ur[t1] = t1+1;
	for (t1=0; t1<12; t1++)
		sr[t1] = t1+11;
	for (t1=0; t1<32; t1++)
		r[t1] = t1+31;
	for (t1=0; t1<46; t1++)
		n[t1] = t1+71;
	random_shuffle(&ur[0],&ur[9]);
	random_shuffle(&sr[0],&sr[11]);
	random_shuffle(&r[0],&r[31]);
	random_shuffle(&n[0],&n[45]);
	for (t1=0; t1<Need[0]; t1++)
		need[0][t1].label = ur[t1];
	for (t1=0; t1<Need[1]; t1++)
		need[1][t1].label = sr[t1];
	for (t1=0; t1<Need[2]; t1++)
		need[2][t1].label = r[t1];
	for (t1=0; t1<Need[3]; t1++)
		need[3][t1].label = n[t1];
}

void player :: init_need_num()
{
	int t1, t2;
	for (t1=0; t1<4; t1++ )
		for (t2=0; t2<Need[t1]; t2++)
			need[t1][t2].need = 3;
}

int player :: draw_dect()
{
	
}
