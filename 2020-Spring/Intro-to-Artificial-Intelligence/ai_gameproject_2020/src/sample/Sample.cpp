#include "STcpClient.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

std::vector<int> GetStep(std::vector<std::vector<int>>& board,bool is_black){
	std::vector<int> step;
	step.resize(2);
	std::vector<int> step;
	step.resize(2);

	step[0] = rand() % (7 + 1 - 0) + 0;
	step[1] = rand() % (7 + 1 - 0) + 0;
	return step;
}

int main() {
	int id_package;
	std::vector<std::vector<int>> board;
	std::vector<int> step;
	
	bool is_black;
	while (true) {
		if (GetBoard(id_package, board, is_black))
			break;
		step = GetStep(board, is_black);
		SendStep(id_package, step);
	}
}