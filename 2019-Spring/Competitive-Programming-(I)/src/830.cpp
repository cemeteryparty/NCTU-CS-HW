#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
// Problem: https://oj.nctu.edu.tw/problems/830/
int main(int argc, char const *argv[]){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	double x[3] = {0}, y[3] = {0};
	while (std::cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2]) {
		double ans_x = 0.0, ans_y = 0.0, r = -10.0;
		long long int r2[3];
		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 3; j++) {
				int xs = x[i] - x[j], ys = y[i] - y[j];
				r2[i + j - 1] = xs * xs + ys * ys;
				if (sqrt(r2[i + j - 1]) > 2 * r) {
					r = sqrt(r2[i + j - 1]) / 2;
					ans_x = (double)((x[i] + x[j]) / 2.0);
					ans_y = (double)((y[i] + y[j]) / 2.0);
				}
			}	
		}
		std::sort(r2, r2 + 3);
		if (r2[2] < r2[0] + r2[1]) {
			long long int d = (x[0] - x[2]) * (y[1] - y[2]) - (x[1] - x[2]) * (y[0] - y[2]);
			long long int r02 = x[0] * x[0] + y[0] * y[0] - x[2] * x[2] - y[2] * y[2];
			long long int r12 = x[1] * x[1] + y[1] * y[1] - x[2] * x[2] - y[2] * y[2];
			ans_x = (double)(r02 * (y[1] - y[2]) - r12 * (y[0] - y[2])) / d / 2;
			ans_y = (double)(r12 * (x[0] - x[2]) - r02 * (x[1] - x[2])) / d / 2;
			r = sqrt((x[0] - ans_x) * (x[0] - ans_x) + (y[0] - ans_y) * (y[0] - ans_y));
		}
		std::cout << std::fixed << std::setprecision(6) << ans_x << ' ' << ans_y << ' ' << r << '\n';
	}
	return 0;
}
