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
	draw = 0;
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
/*
	for (t1 = 0; t1 < 200; t1++)
		cout<<p1[t1].c1[0].label<<'\t'<<p1[t1].c1[1].label<<'\t'<<p1[t1].c1[2].label<<endl;
*/
}

void deck :: update_provide(player& a1)
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
	int t1;
	pack_drew = 0;
	for (t1=0; t1<4; t1++)
		need[t1] = nullptr;
}
player :: ~player()
{
	int t1;
	for (t1=0; t1<4; t1++)
		if (need[t1] != nullptr)
			delete[] need[t1];
}

void player :: init_need_card(int n1[4])
{
	int t1,t2;
	int ur[10],sr[12],r[32],n[46];
	for (t1=0; t1<4; t1++)
	{
		Need[t1] = n1[t1];
		if (need[t1] != nullptr)
			delete[] need[t1];
		need[t1] = new card[Need[t1]];
		for (t2=0; t2 < Need[t1]; t2++)
			need[t1][t2].need = 3;		// .need here is the number of cards needed
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
	{
		tot_Need[t1] = 0;
		for (t2=0; t2<Need[t1]; t2++)
		{
			need[t1][t2].need = 3;
			tot_Need[t1] += 3;
		}
	}
}

int player :: draw_deck(deck & d1)
{
	if (d1.draw >= 200)
	{
		cout<<"Error, no card left"<<endl;
		abort();
	}
	int t1, t2, t3, get_card=0;
	for (t1=0; t1<3; t1++)
	{
		for (t2=0; t2<4; t2++)
		{
			for (t3=0; t3<Need[t2]; t3++)
			{
				if (d1.p1[d1.draw].c1[t1].label == need[t2][t3].label && need[t2][t3].need > 0)
				{
					get_card++;
					need[t2][t3].need--;
					tot_Need[t2]--;
					break;
				}
			}
			if (t3 < Need[t2])
				break;
		}
	}
	d1.draw++;
	pack_drew++;
	return get_card;
}

void player :: draw_decks(deck & d1)
{
	int get_card=0;
	int t1,t2,t3;
	while (get_card == 0)
		get_card = draw_deck(d1);
	d1.update_provide(*this);
/*
	cout<<"Start no need card(last is needed)"<<endl;
	for(t1 = 0; t1 < d1.draw; t1++)
		cout<<d1.p1[t1].c1[0].label<<'\t'<<d1.p1[t1].c1[1].label<<'\t'<<d1.p1[t1].c1[2].label<<endl;
	cout<<"End no need card"<<endl;
	cout<<"Start need card"<<endl;
	for(t1 = 0; t1 < 4; t1++)
	{
		for (t2=0; t2<Need[t1]; t2++)
			cout<<need[t1][t2].label<<'\t';
		cout<<endl;
	}
	cout<<"End need card"<<endl;
	cout<<"Pack drew: "<<pack_drew<<endl;
	cout<<"Pack left: "<<200-d1.draw<<endl;
*/
}

int player :: draw_all_cards(deck & d1, double* root_ratio)
{
	int t1,t2,t3, cp[4];	//cp: current pack
	double actual_ratio[4];
	pack_drew = 0;
	while (tot_Need[0]+tot_Need[1]+tot_Need[2]+tot_Need[3] > 0)
	{
		d1.init();
		d1.update_provide(*this);
		draw_decks(d1);
		for (t1=0; t1<4; t1++)
		{
			actual_ratio[t1] = d1.provide[t1] / (200-d1.draw + 0.0000001);
			cp[t1] = tot_Need[t1] * (actual_ratio[t1] > root_ratio[t1]*root_ratio[t1]);
//			cout<<tot_Need[t1]<<','<<actual_ratio[t1]<<','<<root_ratio[t1]*root_ratio[t1]<<'\t';
		}
//		cout<<endl;
		while(cp[0]||cp[1]||cp[2]||cp[3])
		{
/*/ printing
			for(t3 = 0; t3 < 4; t3++)
			{
				for (t2=0; t2<Need[t3]; t2++)
					cout<<need[t3][t2].need<<'\t';
				cout<<endl;
			}
			cout<<endl;
*/// printing end
			draw_decks(d1);
			for (t1=0; t1<4; t1++)
			{
				actual_ratio[t1] = d1.provide[t1] / (200-d1.draw + 0.0000001);
				cp[t1] = tot_Need[t1] * (actual_ratio[t1] > root_ratio[t1]*root_ratio[t1]);
			}
		}
/*/ printing
			for(t3 = 0; t3 < 4; t3++)
			{
				for (t2=0; t2<Need[t3]; t2++)
					cout<<need[t3][t2].need<<'\t';
				cout<<endl;
			}
			cout<<endl;
*/// printing end

	}
	return pack_drew;
}
double player :: draw_all_cards(deck & d1, double* root_ratio, int num)
{
	int t1, tot;
	for (t1=0,tot=0; t1< num; t1++)
	{
		init_need_num();
		tot+=draw_all_cards(d1, root_ratio);
	}
	return tot / (double) num;
}
