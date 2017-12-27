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
	void add_card(int label);
	void blank();	// equivalent to init
};


class deck
{
public :
	pack p1[200];
	int provide[4];
	int draw;

	deck();
	void init();
	void update_provide(player& a1);
};

class player
{
public :
	int Need[4];
	int tot_Need[4];
	card *need[4];
	int pack_drew;
	player();
	~player();

	void init_need_card(int n1[4]);		// initialize cards that needed
	void init_need_num();				// initialize number of each cards needed and total need
	int draw_deck(deck & d1);			// draw one card, update player need, but not update provide
	void draw_decks(deck & d1);			// draw decks until get need, update provide
	int draw_all_cards(deck & d1, double* root_ratio);	// draw all cards needed, return pack_drew;
	double draw_all_cards(deck & d1, double* root_ratio, int num);
};
#endif
