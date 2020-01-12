#include "header/header.h"
void dda(t_contr *contr)
{

	double angle = contr->angle;
	double pos_x = contr->p_x;
	double pos_y = contr->p_y;
	double Ya = 1;
	double Xa;

	//int up;

	// up = -1; 
	// if(sin(angle) >= 0)
	// 	up = 1;
	Xa = 1 / tan(angle);
	double val;
//	Ya = Xa / tan(angle);
//	double dist_y =  pos_x - ((int)(contr->p_y * contr->map_w) / contr->res_h);
	//double dist_x =  modf(pos_x, &val);
	double hypoth_first =  

	printf("Xa = %f\n", Xa);
	printf("Ya = %f\n", Ya);

	
}