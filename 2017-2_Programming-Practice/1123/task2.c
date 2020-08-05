#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPS = 1e-6;

int sgn(double x) {
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int max (double a, double b) {
	return a > b ? a : b;
}

int min (double a, double b) {
	return a < b ? a : b;
}

double cubic(double a, double b, double c, double d, double x) {
	return ((a * x + b) * x + c) * x + d;
}

double quad(double a, double b, double c, double x) {
	return (3 * a * x + 2 * b) * x + c;
}

double solve_quad(double *x1, double *x2, double a, double b, double c) {
	double d = b * b - 4 * a * c;
	if (d < 0) {
		*x1 = -100000;
		*x2 = -100000;
		return d;
	}
	else {
		double offset = sqrt(d);
		*x1 = (-b - offset) / (2.0 * a);
		*x2 = (-b + offset) / (2.0 * a);
		return d;
	}
}

int solfind(double ub, double lb, double a, double b, double c, double d) {
	if((ub - lb) <= EPS) {
		return (int)(ub + 0.5);
	}
	else {
		double mid;
		mid = ((ub + lb) / 2.0);
		double fmid = cubic(a, b, c, d, mid);
		double fub = cubic(a, b, c, d, ub);
		if(sgn(fub) * sgn(fmid) <= 0)
			return solfind(ub, mid, a, b, c, d);
		else
			return solfind(mid, lb, a, b, c, d);
	}
}

int main(void) {
	int n;
	scanf("%d", &n);

	while(n-- > 0) {
		double lb= -2, ub = 10000;
		double a, b, c, d;
		scanf("%lf %lf %lf %lf" , &a, &b, &c, &d);
	
//		else {
			double z1, z2 ,w1, w2;
			double indicator = solve_quad(&z1, &z2, 3 * a, 2 * b, c);
			if(indicator <= EPS) {
				printf("%d\n", solfind(ub, lb, a, b, c, d));
			}
			else {
				w1 = min(z1, z2);
				w2 = max(z1, z2);
				double fw1 = cubic(a, b, c, d, w1);
				double fw2 = cubic(a, b, c, d, w2);
				double fub = cubic(a, b, c, d, ub);
				double flb = cubic(a, b, c, d, lb);
				if(fabs(fw1) < EPS) {
					printf("%d ", (int)(w1));
					printf("%d\n", solfind(ub, w2, a, b, c, d));
				}
				else if(fabs(fw2) < EPS) {
					printf("%d ", solfind(w1, lb, a, b, c, d));
					printf("%d\n", (int)(w2));
				}
				else if(sgn(fw1) * sgn(fw2) < 0) {
					printf("%d ", solfind(w1, lb, a, b, c, d));
					printf("%d ", solfind(w2, w1, a, b, c, d)); 
					printf("%d\n", solfind(ub, w2, a, b, c, d));
				}
				else if(sgn(fub) * sgn(flb) < 0) {
					printf("%d\n", solfind(ub, lb, a, b, c, d));
				}
				else {
					printf("\n");
				}
//			}
		}
	}
}
