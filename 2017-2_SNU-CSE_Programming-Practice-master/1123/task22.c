#include <stdio.h>
#include <math.h>

int sgn(double x) {
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

double cubic(long long a, long long b, long long c, long long d, double x) {
	return ((a*x + b)*x + c)*x + d;
}

double max(double a, double b) {
	return a > b ? a : b;
}

double min(double a, double b) {
	return a < b ? a : b;
}

int get_extremes(long long a, long long b, long long c, double *out) {
	double det = b*b - 3*a*c;
	if (det < 0) {
		return 0;
	}
	else if( det == 0) {
		out[0] = -b / (3*a);
		return 1;
	}
	else {
		out[0] = (-b - sqrt(det)) / (3*a);
		out[1] = (-b + sqrt(det)) / (3*a);
		return 2;
	}
}

int solve(long long a, long long b, long long c, long long d, int lo, int hi) {
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		double fhi = cubic(a, b, c, d, hi);
		double fmid = cubic(a, b, c, d, mid);
		if(fmid == 0)
			lo = hi = mid;
		else if(fhi == 0)
			lo = hi;
		else if(sgn(fhi) == sgn(fmid))
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return lo;
}

void try_solve(long long a, long long b, long long c, long long d, int lo, int hi) {
	if(lo <= hi) {
		double flo = cubic(a, b, c, d, lo);
		double fhi = cubic(a, b, c, d, hi);
		if(sgn(flo) * sgn(fhi) <= 0)
			printf("%d ", solve(a, b, c, d, lo, hi));
	}
}

int main(void) {
	int n;
	scanf("%d", &n);
	while(n--) {
		long long a, b, c, d;
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);

		double exts[2];
		int num_exts = get_extremes(a, b, c, exts);
		if(num_exts <= 1) {
			try_solve(a, b, c, d, -2, 10001);
		}

		else {
			int p1 = (int)(min(exts[0], exts[1]));
			int p2 = (int)(max(exts[0], exts[1]));
			try_solve(a, b, c, d, -2, p1);
			if(solve(a, b, c, d, -2, p1) != solve(a, b, c, d, (p1 + 1), p2))
				try_solve(a, b, c, d, (p1 + 1), p2);
			if(solve(a, b, c, d, p1, p2) != solve(a, b, c, d, (p2 + 1), 10001))
				try_solve(a, b, c, d, (p2 + 1), 10001);
		}
		printf("\n");
	}
	return 0;
}
