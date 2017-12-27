#include <cstdlib>
#include "mc.h"
mc :: mc()
{
	scale=accept_scale=0;
	check_scale=0;
	T = T_max = 1;
}

void mc :: mc_init(double Scale, int Check_scale, double t_max)
{
	scale = Scale;
	check_scale = Check_scale;
	accept_scale = 0;
	T = T_max = t_max;
}

void mc :: update_scale()
{
	if (accept_scale/check_scale < 0.2)
		scale = scale / 2;
	else if (accept_scale/check_scale > 0.4)
		scale = scale * 1.618;
	if (scale < 0.01) scale = 0.01;
	if (scale > 0.5) scale = 0.5;
	
	accept_scale = 0;
}

void mc :: update_root_ratio(double *& root_ratio)
{
	int t1;
	for (t1=0; t1<4; t1++)
		root_ratio[t1] += scale*(rand()%2000001 - 1000000)/1000000.0;
}

void mc :: update_T_lin(int iter, int period)
{
	T = T_max + (0.1 - T_max) * ((iter%period)+1)/(double)period;
}
