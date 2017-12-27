#ifndef MY_MC
#define MY_MC
class mc
{
public:
	double scale;		// scale random move vector
	int check_scale;	// number of runs to adjust scale
	double accept_scale;	// update scale
	double T, T_max;

	// initialization
	mc();

	// functions
	void mc_init(double Scale, int Check_scale, double t_max);
	void update_scale();
	void update_root_ratio(double*& root_ratio);
	void update_T_lin(int iter, int period);
};
#endif
