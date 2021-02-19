#include "STcpClient.h"
#include <stdlib.h>
#include <iostream>
#include <climits> // INT_MAX, INT_MIN
#include <cstdlib> // random
#include <ctime> // time

// AI, from here
int dx[] = {-1,-1,-1,0,0,1,1,1},dy[] = {-1,0,1,-1,1,-1,0,1}; // direction
int score[8][8] = {
	{0,100,1,1,1,1,100,0},
	{100,1,1,1,1,1,1,100},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{100,1,1,1,1,1,1,100},
	{0,100,1,1,1,1,100,0}
};
std::vector<std::vector<int>> Filp_piece(std::vector<std::vector<int>> board,std::vector<int> & step,bool is_black){
	int x = step[0],y = step[1];
	board[x][y] = (is_black?1:2);
	for(int di = 0;di < 8;di++){
		int nx = x + dx[di],ny = y + dy[di];
		while(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && board[nx][ny] == (is_black?2:1)){
			nx += dx[di];
			ny += dy[di];
			if(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && board[nx][ny] == (is_black?1:2)){
				while(nx != x || ny != y){
					board[nx][ny] = (is_black?1:2);
					nx -= dx[di];
					ny -= dy[di]; 
				}
				break;
			}
		}
	}
	return board;
}
int Utility(std::vector<std::vector<int> > board,bool is_black){
	// piece difference utility (can prevent nearby death move)
	int utility = 0;
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			if(board[i][j] == (is_black?1:2))
				utility += score[i][j];
			else if(board[i][j] == (is_black?2:1))
				utility -= score[i][j];
		}
	return utility; // return the utility
}
bool isStepLegal(std::vector<std::vector<int> > & board,std::vector<int> & step,bool is_black){
	int x = step[0],y = step[1];
	if(board[x][y] != 0)
		return false;
	if(x != 0 && x != 7 && y != 0 && y != 7)
		return true;
	for(int di = 0;di < 8;di++){
		int nx = x + dx[di],ny = y + dy[di];
		while(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && board[nx][ny] == (is_black?2:1)){
			nx += dx[di];
			ny += dy[di];
			if(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && board[nx][ny] == (is_black?1:2))
				return true;
		}
	}
	return false;
}
int Min_value(std::vector<std::vector<int> > board,bool is_black,int alpha,int beta,int depth);
int Max_value(std::vector<std::vector<int> > board,bool is_black,int alpha,int beta,int depth){
	if(depth == 3)
		return Utility(board,is_black);
	int max_val = INT_MIN;
	std::vector<int> step_n(2);
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			step_n[0] = i;
			step_n[1] = j;
			if(isStepLegal(board,step_n,is_black)){
				int utility = Min_value(Filp_piece(board,step_n,is_black),is_black,alpha,beta,depth + 1);
				if(utility > max_val)
					max_val = utility;
				if(max_val >= beta)
					return max_val;
				if(max_val > alpha)
					alpha = max_val;
			}
		}
	if(max_val == INT_MIN)
		return Utility(board,is_black);
	return max_val;
}
int Min_value(std::vector<std::vector<int> > board,bool is_black,int alpha,int beta,int depth){
	if(depth == 3)
		return Utility(board,is_black);
	int min_val = INT_MAX;
	std::vector<int> step_n(2);
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			step_n[0] = i;
			step_n[1] = j;
			if(isStepLegal(board,step_n,!is_black)){
				int utility = Max_value(Filp_piece(board,step_n,!is_black),is_black,alpha,beta,depth + 1);
				if(utility < min_val)
					min_val = utility;
				if(min_val <= alpha)
					return min_val;
				if(min_val < beta)
					beta = min_val;
			}
		}
	if(min_val == INT_MAX)
		return Utility(board,is_black);
	return min_val;
}
std::vector<int> GetStep(std::vector<std::vector<int>>& board,bool is_black){
	std::vector<int> step;
	step.resize(2);
	step[0] = step[1] = -1; // step[0]: row, step[1]: column
	std::vector<std::vector<int> > step_arr;
	int max_val = INT_MIN;
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			step[0] = i;
			step[1] = j;
			if(isStepLegal(board,step,is_black)){ // first step of Max_val()
				if(score[step[0]][step[1]] == 100)
					return step;
				int utility = Min_value(Filp_piece(board,step,is_black),is_black,INT_MIN,INT_MAX,0);
				if(utility > max_val){
					max_val = utility;
					step_arr.clear();
					step_arr.push_back(step);
				}
				else if(utility == max_val)
					step_arr.push_back(step);
			}
		}
	srand(time(NULL));
	int index = rand() % step_arr.size();
	return step_arr[index];
}
// AI, to here

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