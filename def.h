#ifndef MY_CLASS
#define MY_CLASS

class card;
class pack;
class deck;
class player;

class card
{
public :
	int label; //1-10 UR, 11-22 SR, 31-62 R, 71-116 N
	int need;

	card();
	card& operator=(const card& B);
	void init(int label);
};

class pack
{
public :
	card c1[3];

	pack & operator=(const pack & B);
	void add_card(int label);	//0: succeed, 1: failed
	void blank();
};


class deck
{
public :
	pack p1[200];
	int provide[4];
	int draw;

	deck();
	void init();
	void update_provide(player a1);
};

class player
{
public :
	int Need[4];
	card *need[4];
	int pack_drew;
	player();

	void init_need_card(int n1[4]);
	void init_need_num();
	int draw_deck(deck & d1);
	void draw_decks(deck & d1);
};
#endif
