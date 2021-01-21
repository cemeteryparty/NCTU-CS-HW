#include <iostream>
#define INF 10000.0

int main(int argc, char const *argv[]){
	int n = 5;
	double p[n + 1] = {-1.0,0.15,0.1,0.05,0.1,0.2},q[n + 1] = {0.05,0.1,0.05,0.05,0.05,0.1};
	//e[1..n+1, 0..n], w[1..n+1, 0..n] and root[1..n, 1..n]
	double e[7][6],w[7][6],root[6][6];
	for(int i = 1;i <= n + 1;i++){
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for(int l = 1;l <= n;l++)
		for(int i = 1;i <= n - l + 1;i++){
			int j = i + l - 1;
			e[i][j] = INF;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for(int r = i;r <= j;r++){
				double tmp = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if(tmp < e[i][j]){
					e[i][j] = tmp;
					root[i][j] = r;
				}
			}

		}
	std::cout << "excepted cost:\n";
	for(int i = 1;i <= n + 1;i++){
		for(int j = 0;j <= n;j++)
			std::cout << e[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << "\nw cost:\n";
	for(int i = 1;i <= n + 1;i++){
		for(int j = 0;j <= n;j++)
			std::cout << w[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << "\nroot:\n";
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++)
			std::cout << root[i][j] << ' ';
		std::cout << '\n';
	}
	return 0;
}