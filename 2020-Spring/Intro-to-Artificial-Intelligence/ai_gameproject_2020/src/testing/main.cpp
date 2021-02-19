#include <iostream>
#include <vector>
#include <climits> // INT_MAX, INT_MIN
#include <cstdlib> // random
#include <ctime> // time
// v612.20.30-beta_003
// [*] dynamic max_depth for different step condition

class Reversi{
// [0: unoccupied]; [1: occupied by Black]; [2: occupied by White]; [-1: the four corners]
private:
	bool Blackturn;
	std::vector<std::vector<int> > Board;
public:
	Reversi();
	bool GetBoard(std::vector<std::vector<int> > & board);
	void SendStep(int player,std::vector<int> & step);
	void printBoard();
};
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
std::vector<std::vector<int> > Filp_piece(std::vector<std::vector<int> > board,std::vector<int> & step,bool is_black){
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
int Min_value(std::vector<std::vector<int> > board,bool is_black,int alpha,int beta,int depth,int max_depth);
int Max_value(std::vector<std::vector<int> > board,bool is_black,int alpha,int beta,int depth,int max_depth){
	if(depth == max_depth)
		return Utility(board,is_black);
	int max_val = INT_MIN;
	std::vector<int> step_n(2);
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			step_n[0] = i;
			step_n[1] = j;
			if(isStepLegal(board,step_n,is_black)){
				int utility = Min_value(Filp_piece(board,step_n,is_black),is_black,alpha,beta,depth + 1,max_depth);
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
int Min_value(std::vector<std::vector<int> > board,bool is_black,int alpha,int beta,int depth,int max_depth){
	if(depth == max_depth)
		return Utility(board,is_black);
	int min_val = INT_MAX;
	std::vector<int> step_n(2);
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			step_n[0] = i;
			step_n[1] = j;
			if(isStepLegal(board,step_n,!is_black)){
				int utility = Max_value(Filp_piece(board,step_n,!is_black),is_black,alpha,beta,depth + 1,max_depth);
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
std::vector<int> GetStep(std::vector<std::vector<int> >& board,bool is_black){
	std::vector<int> step;
	step.resize(2);
	step[0] = step[1] = -1; // step[0]: row, step[1]: column
	if(!is_black){
		scanf("%d%d",&step[0],&step[1]);
		return step;
	}
	std::vector<std::vector<int> > step_arr,optimal_step_arr;
	int max_val = INT_MIN,pieces = 0;
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			step[0] = i;
			step[1] = j;
			if(board[i][j] == 1 || board[i][j] == 2)
				pieces++;
			if(isStepLegal(board,step,is_black)){ // first step of Max_val()
				if(score[step[0]][step[1]] == 100)
					return step;
				step_arr.push_back(step);
			}
		}
	int max_depth = 2;
	if(pieces >= 50)
		max_depth = 6;
	else if(pieces >= 40)
		max_depth = 5;
	else if(pieces >= 30)
		max_depth = 4;
	else if(pieces >= 8)
		max_depth = 3;
	for(int si = 0;si < step_arr.size();si++){
		step = step_arr[si];
		int utility = Min_value(Filp_piece(board,step,is_black),is_black,INT_MIN,INT_MAX,0,max_depth);
		if(utility > max_val){
			max_val = utility;
			optimal_step_arr.clear();
			optimal_step_arr.push_back(step);
		}
		else if(utility == max_val)
			optimal_step_arr.push_back(step);
	}
	srand(time(NULL));
	int index = rand() % optimal_step_arr.size();
	return optimal_step_arr[index];
}
// AI, to here
int main(int argc, char const *argv[]){
	Reversi game;
	// p1: black, p2: white
	std::vector<std::vector<int> > board;
	std::vector<int> step;
	while(true){
		bool is_black = game.GetBoard(board);
		printf(is_black?"Black's Turn\n":"White Turn\n");
		step = GetStep(board,is_black);
		game.SendStep(is_black?1:2,step);
	}
	return 0;
}
Reversi::Reversi(){
	Board = std::vector<std::vector<int> >(8,std::vector<int>(8));
	Board[0][0] = Board[0][7] = Board[7][0] = Board[7][7] = -1; // corner
	Blackturn = true; 
}
bool Reversi::GetBoard(std::vector<std::vector<int> > & board){
	// return 1: black turns, 0: white turns
	// usually return Blackturn if player(Blackturn?1:2) has legal move
	printBoard();
	board = Board;
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++){
			if(i == 0 || i == 7 || j == 0 || j == 7){
				// edge case, legal if flip event exists
				if(Board[i][j] == 0)
					for(int di = 0;di < 8;di++){
						int nx = i + dx[di],ny = j + dy[di];
						while(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && Board[nx][ny] == (Blackturn?2:1)){
							nx += dx[di];
							ny += dy[di];
							if(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && Board[nx][ny] == (Blackturn?1:2))
								return Blackturn;
						}
					}
			}
			else if(!Board[i][j])
				return Blackturn; // legal if empty square in central 6x6 exists
		}
	// No legal move for present player
	return Blackturn ^ true;
}
void Reversi::SendStep(int player,std::vector<int> & step){
	// check if the position player choose is legal
	int x = step[0],y = step[1];
	if(0 > x || x >= 8 || 0 > y || y >= 8){
		printf("(%d,%d) ILEGAL MOVE DETECT\n",x,y);
		return; // outside board
	}
	if(Board[x][y] != 0){
		printf("(%d,%d) ILEGAL MOVE DETECT\n",x,y);
		return; // has been occupied
	}
	bool legal = (x != 0 && x != 7 && y != 0 && y != 7);
	for(int di = 0;di < 8;di++){
		int nx = x + dx[di],ny = y + dy[di];
		while(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && Board[nx][ny] == (player == 1?2:1)){
			nx += dx[di];
			ny += dy[di];
			if(0 <= nx && nx < 8 && 0 <= ny && ny < 8 && Board[nx][ny] == player){
				legal = true;
				while(nx != x || ny != y){
					Board[nx][ny] = player;
					nx -= dx[di];
					ny -= dy[di]; 
				}
				break;
			}
		}
	}
	if(!legal){
		printf("(%d,%d) ILEGAL MOVE DETECT\n",x,y);
		return;
	}
	Board[x][y] = player;

	Blackturn ^= true; // change turn
}
void Reversi::printBoard(){
	int unoccupied = 60,white = 0,black = 0;
	printf("   ");
	for(int j = 0;j < 8;j++)
		printf("%d ",j % 10);
	printf("\n  -");
	for(int j = 0;j < 8;j++)
		printf("--");
	printf("\n");
	for(int i = 0;i < 8;i++){
		printf("%d| ",i % 10);
		for(int j = 0;j < 8;j++){
			if(Board[i][j] == 1){
				unoccupied--;
				black++;
				printf("x ");
			}
			else if(Board[i][j] == 2){
				unoccupied--;
				white++;
				printf("o ");
			}
			else 
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
	printf("--- black:white = %d:%d ---\n",black,white);
	if(!unoccupied){
		printf("----- Game End -----\n");
		if(black == white)
			printf("------- Draw -------\n");
		else
			printf(black > white?"----- Black wins -----\n":"----- White wins -----\n");
		exit(0);
	}
}