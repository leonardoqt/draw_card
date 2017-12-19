#include <iostream>
#include <cstdlib>
#include <ctime>
#include "def.h"

using namespace std;
int main()
{
	srand(time(0));
	int need[4]={4,3,2,1};
	deck d1;
	player p1;
	d1.init();
	p1.init_need_card(need);
	p1.init_need_num();
	d1.update_provide(p1);
	return 0;
}
