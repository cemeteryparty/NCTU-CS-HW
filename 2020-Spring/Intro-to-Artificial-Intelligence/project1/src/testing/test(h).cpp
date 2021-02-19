#include <iostream>
#include <queue>
#include <vector>
#include <climits> // INT_MAX
#include <algorithm> // min
#include <cmath> //fabs

using namespace std;

// def. class structure
int GOAL = -1;
double h(int n){ // heuristic function
    int x = n / 10,y = n % 10;
    int gx = GOAL / 10,gy = GOAL % 10;
    double dx = (double)x - gx,dy = (double)y - gy;
    return sqrt(dx * dx + dy * dy);
}
class Block{
public:
    double min_fval;
    int coordinate_p,min_step;
    bool forward;
    Block(int cp = -1,bool f = true,int ms = INT_MAX,int mf = INT_MAX){
        coordinate_p = cp;
        forward = f;
        min_step = ms;
        min_fval = mf;
    }
};
class Frontier{
public:
    double fval;
    int coordinate,coordinate_p,step,gval;
    Frontier(int c,int cp,int s){
        coordinate = c;
        coordinate_p = cp;
        gval = step = s; // step = gval
        fval = (double)gval + h(c); // f(c) = g(c) + g(c)
    }
    friend bool operator>(const Frontier & obj1,const Frontier & obj2){
        return obj1.fval > obj2.fval;
    }
};
void BFS(int start,int finish,vector<vector<Block> > & table);
void DFS(int start,int finish,vector<vector<Block> > & table);
void IDS(int start,int finish,vector<vector<Block> > & table);
void A_star(int start,int finish,vector<vector<Block> > & table);
void IDA_star(int start,int finish,vector<vector<Block> > & table);
int Frontier_count = 0;
int main(int argc, char const *argv[]){
    vector<vector<Block> > table(8,vector<Block>(8));
    int toa,sx,sy,gx,gy;
    printf("type of algorithm: BFS(1),DFS(2),IDS(3),A*(4),IDA*(5)\ninput type of algorithm: ");
    scanf("%d",&toa);
    if(5 < toa || toa < 1){
        printf("[x] Unexpected input!!!\n");
        return -1;
    }
    printf("input starting_x starting_y goal_x goal_y: ");
    scanf("%d%d%d%d",&sx,&sy,&gx,&gy);
    if(7 < sx || sx < 0 || 7 < sy || sy < 0 || 7 < gx || gx < 0 || 7 < gy || gy < 0){
        printf("[x] Unexpected input!!!\n");
        return -1;
    }

    int start = sx * 10 + sy,goal = gx * 10 + gy;
    GOAL = goal;
    if(toa == 1)
        BFS(start,goal,table);
    else if(toa == 2)
        DFS(start,goal,table);
    else if(toa == 3)
        IDS(start,goal,table);
    else if(toa == 4)
        A_star(start,goal,table);
    else if(toa == 5)
        IDA_star(start,goal,table);

    printf("\nFrontier_count =  %d\n\n",Frontier_count);
    printf("Table:\n");
    for(int i = 0;i < 8;i++){
        for(int j = 0;j < 8;j++){
            if(table[i][j].coordinate_p >= 0)
                printf("(%d,%d)",table[i][j].coordinate_p / 10,table[i][j].coordinate_p % 10);
            else
                printf("(-,-)");
        }
        printf("\n");
    }
    printf("\n");
    vector<int> path;
    int pos = goal;
    while(pos >= 0){
        path.push_back(pos);
        pos = table[pos / 10][pos % 10].coordinate_p;
    }
    for(int i = path.size() - 1;i >= 0;i--)
        printf("step %d: (%d,%d)\n",path.size() - i - 1,path[i] / 10,path[i] % 10);

    return 0;
}

int dx[] = {1,2,1,-2,-1,2,-1,-2};
int dy[] = {2,1,-2,1,2,-1,-2,-1};
// BFS
void BFS(int start,int finish,vector<vector<Block> > & table){
    queue<Frontier> q;
    q.push(Frontier(start,-1,-1)); // coordinate,coordinate_p,step = gval
    Frontier_count++;
    while(!q.empty()){
        Frontier f = q.front();
        q.pop();
        int x = f.coordinate / 10,y = f.coordinate % 10;
        table[x][y].forward = false;
        table[x][y].coordinate_p = f.coordinate_p;
        if(f.coordinate == finish) // goal test
            break;
        for(int i = 0;i < 8;i++){
            int nx = x + dx[i],ny = y + dy[i];
            if(0 <= nx && nx <= 7 && 0 <= ny && ny <= 7 && table[nx][ny].forward){
                q.push(Frontier(nx * 10 + ny,f.coordinate,-1));
                Frontier_count++;
            }
        }
    }
}
// DFS
void DFS(int start,int finish,vector<vector<Block> > & table){
    vector<Frontier> s; // stack
    s.push_back(Frontier(start,-1,0)); // coordinate,coordinate_p,step = gval
    Frontier_count++;
    while(!s.empty()){
        Frontier f = s.back();
        s.pop_back();
        int x = f.coordinate / 10,y = f.coordinate % 10;
        if(f.step < table[x][y].min_step){
            table[x][y].min_step = f.step;
            table[x][y].coordinate_p = f.coordinate_p;
            for(int i = 0;i < 8;i++){
                int nx = x + dx[i],ny = y + dy[i];
                if(0 <= nx && nx <= 7 && 0 <= ny && ny <= 7 && f.step + 1 < table[nx][ny].min_step){
                    s.push_back(Frontier(nx * 10 + ny,f.coordinate,f.step + 1));
                    Frontier_count++;
                }
            }
        } 
    }
}
// IDS
void IDS(int start,int finish,vector<vector<Block> > & table){
    bool goal = false;
    int depth = 1; // depth limit
    while(!goal){
        for(int i = 0;i < 64;i++)
            table[i / 8][i % 8] = Block(); // initial table
        vector<Frontier> s; // stack
        s.push_back(Frontier(start,-1,0)); // coordinate,coordinate_p,step = gval
        Frontier_count++;
        while(!s.empty()){
            Frontier f = s.back();
            s.pop_back();
            int x = f.coordinate / 10,y = f.coordinate % 10;
            if(f.step < table[x][y].min_step){
                table[x][y].min_step = f.step;
                table[x][y].coordinate_p = f.coordinate_p;
                if(f.coordinate == finish){ // goal test
                    goal = true;
                    break;
                }
                for(int i = 0;i < 8;i++){
                    int nx = x + dx[i],ny = y + dy[i];
                    if(0 <= nx && nx <= 7 && 0 <= ny && ny <= 7 && f.step + 1 < min(depth,table[nx][ny].min_step)){
                        s.push_back(Frontier(nx * 10 + ny,f.coordinate,f.step + 1));
                        Frontier_count++;
                    }
                }
            } 
        }
        printf(goal?"Depth%d: Success\n":"Depth%d: Failed\n",depth++);
    }
}
// A*
void A_star(int start,int finish,vector<vector<Block> > & table){
    priority_queue<Frontier,vector<Frontier>,greater<Frontier> > q;
    q.push(Frontier(start,-1,0)); // coordinate,coordinate_p,gval = step
    Frontier_count++;
    while(!q.empty()){
        Frontier f = q.top();
        q.pop();
        int x = f.coordinate / 10,y = f.coordinate % 10;
        if(f.coordinate == finish){ // goal test
            table[x][y].min_fval = f.fval;
            table[x][y].coordinate_p = f.coordinate_p;
            break;
        }
        if(f.fval < table[x][y].min_fval){
            table[x][y].min_fval = f.fval;
            table[x][y].coordinate_p = f.coordinate_p;
            for(int i = 0;i < 8;i++){
                int nx = x + dx[i],ny = y + dy[i];
                if(0 <= nx && nx <= 7 && 0 <= ny && ny <= 7 && f.fval + 1 < table[nx][ny].min_fval){
                    q.push(Frontier(nx * 10 + ny,f.coordinate,f.gval + 1));
                    Frontier_count++;
                }
            }
        }
    }
}
// IDA*
void IDA_star(int start,int finish,vector<vector<Block> > & table){
    bool goal = false;
    int depth = 1; // depth limit
    while(!goal){
        for(int i = 0;i < 64;i++)
            table[i / 8][i % 8] = Block(); // initial table
        priority_queue<Frontier,vector<Frontier>,greater<Frontier> > q;
        q.push(Frontier(start,-1,0)); // coordinate,coordinate_p,gval = step
        Frontier_count++;
        while(!q.empty()){
            Frontier f = q.top();
            q.pop();
            int x = f.coordinate / 10,y = f.coordinate % 10;
            if(f.coordinate == finish){ // goal test
                table[x][y].min_fval = f.fval;
                table[x][y].coordinate_p = f.coordinate_p;
                goal = true;
                break;
            }
            if(f.fval < table[x][y].min_fval){
                table[x][y].min_fval = f.fval;
                table[x][y].coordinate_p = f.coordinate_p;
                for(int i = 0;i < 8;i++){
                    int nx = x + dx[i],ny = y + dy[i];
                    if(0 <= nx && nx <= 7 && 0 <= ny && ny <= 7 && f.fval + 1 < table[nx][ny].min_fval && f.gval + 1 < depth){
                        q.push(Frontier(nx * 10 + ny,f.coordinate,f.gval + 1));
                        Frontier_count++;
                    }
                }
            }
        }
        printf(goal?"Depth%d: Success\n":"Depth%d: Failed\n",depth++);
    }
}
