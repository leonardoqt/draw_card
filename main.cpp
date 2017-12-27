#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "def.h"
#include "mc.h"

using namespace std;
int main()
{
	srand(time(0));
	int need[4]={2,2,2,2};
	double *root_ratio1,*root_ratio0;
	int t1,t2,runs;
	double tot1, tot0;
	deck d1;
	player p1;
	mc mc_run;
	int replic=1000;
	// mc related parameters
	double scale = 0.1;
	int check_scale = 100;
	double T_max = 10;

	cin>>runs;
	root_ratio1 = new double[4];
	root_ratio0 = new double[4];
/*
	root_ratio1[0] = 0.0174829;
	root_ratio1[1] = -0.229551;
	root_ratio1[2] = -0.285825;
	root_ratio1[3] = -0.283079;
*/
	root_ratio1[0] =0.1;
	root_ratio1[1] =0.1;
	root_ratio1[2] =0.1;
	root_ratio1[3] =0.1;
	mc_run.mc_init(scale,check_scale,T_max);
	// start mc
	p1.init_need_card(need);
	tot1 = p1.draw_all_cards(d1, root_ratio1,replic);
	for (t2=0; t2<4; t2++) root_ratio0[t2] = root_ratio1[t2];
	tot0 = tot1;
	for (t1=1; t1<=runs; t1++)
	{
		// update scale
		if (t1%mc_run.check_scale == 0)
			mc_run.update_scale();
		// update temperature
		mc_run.update_T_lin(t1,runs);
		// new ratio
		mc_run.update_root_ratio(root_ratio1);

		p1.init_need_card(need);
		tot1 = p1.draw_all_cards(d1, root_ratio1,replic);
		if (tot1 < tot0 || rand()%1000000/1000000.0 <= exp((tot0-tot1)/mc_run.T))
		{
			cout<<t1<<'\t'<<tot1<<'\t'<<mc_run.scale<<'\t'<<mc_run.T<<'\t';
			for (t2=0; t2<4; t2++) cout<<root_ratio1[t2]<<' ';
			cout<<endl;
			mc_run.accept_scale += 1;
			tot0 = tot1;
			for (t2=0; t2<4; t2++) root_ratio0[t2] = root_ratio1[t2];
		}
		else
		{
			for (t2=0; t2<4; t2++) root_ratio1[t2] = root_ratio0[t2];
		}
	}
	return 0;
}
