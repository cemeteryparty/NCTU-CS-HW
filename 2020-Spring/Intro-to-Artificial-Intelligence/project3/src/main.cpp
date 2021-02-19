#include <iostream>
#include <cstdlib> // random
#include <ctime> // time
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue> 
#include <set>

using namespace std;
class Minesweeper{
private:
	vector<vector<int> > gField; // GM field
	int unsolved;
public:
	vector<vector<int> > pField; // player field, KB0
	int n,m,NumofMines;
	Minesweeper(int level);
	void PrintField(bool auth); // if auth is true print gm field
	int GameStart(); // return a safe start grid x * 100 + y
	int Uncover(int x,int y); // player uncover the covered grid (x,y), GM modify player field
	void Manual(); // Manual module, for DEBUG or for fun
};
int dx[] = {-1,-1,-1,0,0,1,1,1},dy[] = {-1,0,1,-1,1,-1,0,1}; // direction
void Match(set<vector<int> > & KB);
void Clause_Generate(int x,int y,Minesweeper & Game,set<vector<int> > & KB);
bool Claim(int pos,Minesweeper & Game,set<vector<int> > & KB,vector<vector<bool> > & inKB);
int main(int argc, char const *argv[]){
	int lv;
	printf("Level selection 1~3 : ");
	scanf("%d",&lv);
	Minesweeper Game(lv);
	int pos = Game.GameStart(); // GM will tell player a safe initial place
	if(pos == -1){ // no safe position
		printf("Exception occurs, contact GM.\n");
		Game.PrintField(true);
		return 0;
	}
	printf("-----   Game start   -----\n");
	Game.PrintField(false);

	set<vector<int> > KB;
	vector<vector<bool> > inKB(Game.n,vector<bool>(Game.m,false));
	KB.insert(vector<int>(1,pos));
	while(!KB.empty()){
		set<vector<int> >::iterator it;
		for(it = KB.begin();it != KB.end();it++)
			if((*it).size() == 1){ // single literal clause exist
				if(!Claim((*it)[0],Game,KB,inKB))
					return 0; // game terminsted by GM
				break;
			}
		if(it == KB.end()) // single literal clause not exist
			Match(KB);
	}
	return 0;
}
Minesweeper::Minesweeper(int level){
	if(level == 1){
		gField = vector<vector<int> >(9,vector<int>(9));
		n = m = 9;
		NumofMines = 10;
	}
	else if(level == 2){
		gField = vector<vector<int> >(16,vector<int>(16));
		n = m = 16;
		NumofMines = 25;
	}
	else{
		gField = vector<vector<int> >(16,vector<int>(30));
		n = 16;
		m = 30;
		NumofMines = 99;
	}
	pField = gField;
	unsolved = n * m - NumofMines; // the remain blocks need to be uncovered
	// set mines
	srand(time(NULL));
	int remain_mine = NumofMines;
	while(remain_mine){
		int x = rand() % n,y = rand() % m;
		if(gField[x][y] == -1)
			continue;
		gField[x][y] = -1;
		for(int di = 0;di < 8;di++){
			int nx = x + dx[di],ny = y + dy[di];
			if(0 <= nx && nx < n && 0 <= ny && ny < m && gField[nx][ny] != -1)
				gField[nx][ny]++;
		}
		remain_mine--;
	}
}
void Minesweeper::PrintField(bool auth){
	vector<vector<int> > & Field = auth?gField:pField;
	printf("   ");
	for(int j = 0;j < m;j++)
		printf("%d ",j % 10);
	printf("\n  -");
	for(int j = 0;j < m;j++)
		printf("--");
	printf("\n");
	for(int i = 0;i < n;i++){
		printf("%d| ",i % 10);
		for(int j = 0;j < m;j++){
			if(Field[i][j] == -2)
				printf("? ");
			else if(Field[i][j] == -1)
				printf("x ");
			else
				printf("%d ",Field[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int Minesweeper::GameStart(){
	int position = -1;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < m;j++){
			pField[i][j] = -2; // covered
			if(gField[i][j] == 0 && position == -1)
				position = i * 100 + j;
		}
	return position; // claim it is safe
}
int Minesweeper::Uncover(int x,int y){ 
	// return 0: game is solved or player lose, terminates the game
	//        1: game should be continued
	printf("-----  Uncover (%d,%d)  -----\n",x,y);
	if(gField[x][y] == -1){ // fail case, shouldn't happen
		printf("Bang!!!!!!!\nYou Lose\n");
		PrintField(true);
		return 0;
	}
	else{
		queue<int> q;
		q.push(x * 100 + y);
		while(!q.empty()){
			x = q.front() / 100;
			y = q.front() % 100;
			q.pop();
			if(pField[x][y] != -2)
				continue;
			pField[x][y] = gField[x][y];
			unsolved--;
			if(!gField[x][y])
				for(int di = 0;di < 8;di++){
					int nx = x + dx[di],ny = y + dy[di];
					if(0 <= nx && nx < n && 0 <= ny && ny < m && gField[nx][ny] != -1 && pField[nx][ny] == -2)
						q.push(nx * 100 + ny);
				}
		}
	}
	// goal test
	if(!unsolved){ // game clear, player wins
		printf("Congratulation!!!!!!!\nYou Win\n");
		PrintField(true);
		return 0;
	}
	PrintField(false);
	return 1;
}
void Minesweeper::Manual(){
	int x,y;
	do{
		printf("Input the grid should be uncovered: ");
		scanf("%d%d",&x,&y);
		printf("Uncover (%d,%d)\n",x,y);
		if(!Uncover(x,y))
			break;
		PrintField(false);
	}while(true);
}
void Clause_Generate(int x,int y,Minesweeper & Game,set<vector<int> > & KB){
	if(Game.pField[x][y] == 0 || Game.pField[x][y] == -1)
		return;
	int N = Game.pField[x][y];
	vector<int> Var;
	for(int di = 0;di < 8;di++){
		int nx = x + dx[di],ny = y + dy[di];
		if(0 <= nx && nx < Game.n && 0 <= ny && ny < Game.m && Game.pField[nx][ny] == -2)
			Var.push_back(nx * 100 + ny);
		if(0 <= nx && nx < Game.n && 0 <= ny && ny < Game.m && Game.pField[nx][ny] == -1)
			N--;
	}
	if(N == Var.size()){ // all variable = -1
		for(int vi = 0;vi < Var.size();vi++)
			KB.insert(vector<int>(1,10000 + Var[vi]));
		return;
	}
	if(N == 0){ // all variable = 0
		for(int vi = 0;vi < Var.size();vi++)
			KB.insert(vector<int>(1,Var[vi]));
		return;
	}
	vector<int> clause(2,-1);
	if(Var.size() - N == 1){ // pos clause
		for(int vi = 0;vi < Var.size();vi++){
			clause[0] = Var[vi] + 10000;
			for(int vj = vi + 1;vj < Var.size();vj++){
				clause[1] = Var[vj] + 10000;
				sort(clause.begin(),clause.end());
				KB.insert(clause);
			}
		}
	}
	if(N == 1){ // neg clause
		for(int vi = 0;vi < Var.size();vi++){
			clause[0] = Var[vi];
			for(int vj = vi + 1;vj < Var.size();vj++){
				clause[1] = Var[vj];
				sort(clause.begin(),clause.end());
				KB.insert(clause);
			}
		}
	}
}
bool Claim(int pos,Minesweeper & Game,set<vector<int> > & KB,vector<vector<bool> > & inKB){
	bool isMine = false;
	if(pos / 10000){ // 
		pos %= 10000;
		isMine = true;
	}
	int x = pos / 100,y = pos % 100;
	if(isMine){
		printf("-----  Flag (%d,%d)  -----\n",x,y);
		Game.pField[x][y] = -1;
		Game.PrintField(false);
	}
	else{
		bool rt = Game.Uncover(x,y);
		if(!rt)
			return rt;
	}
	
	// matching KB with KB0
	set<vector<int> > nKB;
	for(auto nit = KB.begin();nit != KB.end();nit++){
		vector<int> clause;
		for(int vi = 0;vi < (*nit).size();vi++){
			bool M = false,Mp;
			int lit = (*nit)[vi];
			if(lit / 10000){
				M = true;
				lit %= 10000;
			}
			if(Game.pField[lit / 100][lit % 100] == -2){
				clause.push_back(lit + (M?10000:0));
				continue;
			}
			Mp = Game.pField[lit / 100][lit % 100] == -1;
			if(M == Mp){ // always true clause -> drop
				clause.clear();
				break;
			}
		}
		if(!clause.empty()){
			sort(clause.begin(),clause.end());
			nKB.insert(clause);
		}
	}
	KB = nKB; // replace

	// generating new clause
	queue<int> q;
	vector<vector<bool> > inQueue(Game.n,vector<bool>(Game.m,false));
	q.push(x * 100 + y);
	inQueue[x][y] = true;
	while(!q.empty()){
		x = q.front() / 100;
		y = q.front() % 100;
		q.pop();
		Clause_Generate(x,y,Game,KB);
		
		for(int di = 0;di < 8;di++){
			int nx = x + dx[di],ny = y + dy[di];
			if(0 <= nx && nx < Game.n && 0 <= ny && ny < Game.m && !inQueue[nx][ny] && Game.pField[nx][ny] != -2){
				q.push(nx * 100 + ny);
				inQueue[nx][ny] = true;
			}
		}
	}
	return true;
}
void Match(set<vector<int> > & KB){
	set<vector<int> > nKB;
	
	vector<vector<int> > vKB;
	for(auto it = KB.begin();it != KB.end();it++)
		vKB.push_back(*it);
	for(int i = 0;i < vKB.size();i++){
		for(int j = 0;j < vKB.size();j++){
			vector<int> clause;
			for(int vi = 0;vi < vKB[i].size();vi++){
				bool pass = true;
				for(int vj = 0;vj < vKB[j].size();vj++)
					if(abs(vKB[i][vi] - vKB[j][vj]) == 10000)
						pass = false;
				if(pass)
					clause.push_back(vKB[i][vi]);
			}
			for(int vj = 0;vj < vKB[j].size();vj++){
				bool pass = true;
				for(int vi = 0;vi < vKB[i].size();vi++)	
					if(abs(vKB[i][vi] - vKB[j][vj]) == 10000 || vKB[i][vi] - vKB[j][vj] == 0)
						pass = false;
				if(pass)	
					clause.push_back(vKB[j][vj]);
			}
			if(clause.size() == 1 || clause.size() == 2){
				sort(clause.begin(),clause.end());
				nKB.insert(clause);
			}
		}
	}
	KB = nKB; // replace
}