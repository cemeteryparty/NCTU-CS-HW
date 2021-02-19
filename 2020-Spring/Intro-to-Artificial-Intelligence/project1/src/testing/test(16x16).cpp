#include <iostream>
#include <queue>
#include <vector>
#include <climits> // INT_MAX
#include <algorithm> // min
#include <cmath> //fabs

using namespace std;

// def. class structure
int GOAL = -1;
int h(int n){ // heuristic function
    int x = n / 100,y = n % 100;
    int gx = GOAL / 100,gy = GOAL % 100;
    return (int)floor((fabs((double)x - gx) + fabs((double)y - gy)) / 3.0);
}
class Block{
public:
    int coordinate_p,min_step,min_fval;
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
    int coordinate,coordinate_p,step,fval,gval;
    Frontier(int c,int cp,int s){
        coordinate = c;
        coordinate_p = cp;
        gval = step = s; // step = gval
        fval = gval + h(c); // f(c) = g(c) + g(c)
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
long long int Frontier_count = 0;
int main(int argc, char const *argv[]){
    vector<vector<Block> > table(16,vector<Block>(16));
    int toa,sx,sy,gx,gy;
    printf("type of algorithm: BFS(1),DFS(2),IDS(3),A*(4),IDA*(5)\ninput type of algorithm: ");
    scanf("%d",&toa);
    if(5 < toa || toa < 1){
        printf("[x] Unexpected input!!!\n");
        return -1;
    }
    printf("input starting_x starting_y goal_x goal_y: ");
    scanf("%d%d%d%d",&sx,&sy,&gx,&gy);
    if(15 < sx || sx < 0 || 15 < sy || sy < 0 || 15 < gx || gx < 0 || 15 < gy || gy < 0){
        printf("[x] Unexpected input!!!\n");
        return -1;
    }

    int start = sx * 100 + sy,goal = gx * 100 + gy;
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

    printf("\nFrontier_count =  %lld\n\n",Frontier_count);
    printf("Table:\n");
    for(int i = 0;i < 16;i++){
        for(int j = 0;j < 16;j++){
            if(table[i][j].coordinate_p >= 0)
                printf("(%d,%d)",table[i][j].coordinate_p / 100,table[i][j].coordinate_p % 100);
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
        pos = table[pos / 100][pos % 100].coordinate_p;
    }
    for(int i = path.size() - 1;i >= 0;i--)
        printf("step %d: (%d,%d)\n",path.size() - i - 1,path[i] / 100,path[i] % 100);

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
        int x = f.coordinate / 100,y = f.coordinate % 100;
        table[x][y].forward = false;
        table[x][y].coordinate_p = f.coordinate_p;
        if(f.coordinate == finish) // goal test
            break;
        for(int i = 0;i < 8;i++){
            int nx = x + dx[i],ny = y + dy[i];
            if(0 <= nx && nx <= 15 && 0 <= ny && ny <= 15 && table[nx][ny].forward){
                q.push(Frontier(nx * 100 + ny,f.coordinate,-1));
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
        int x = f.coordinate / 100,y = f.coordinate % 100;
        if(f.step < table[x][y].min_step){
            table[x][y].min_step = f.step;
            table[x][y].coordinate_p = f.coordinate_p;
            for(int i = 0;i < 8;i++){
                int nx = x + dx[i],ny = y + dy[i];
                if(0 <= nx && nx <= 15 && 0 <= ny && ny <= 15 && f.step + 1 < table[nx][ny].min_step){
                    s.push_back(Frontier(nx * 100 + ny,f.coordinate,f.step + 1));
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
        for(int i = 0;i < 256;i++)
            table[i / 16][i % 16] = Block(); // initial table
        vector<Frontier> s; // stack
        s.push_back(Frontier(start,-1,0)); // coordinate,coordinate_p,step = gval
        Frontier_count++;
        while(!s.empty()){
            Frontier f = s.back();
            s.pop_back();
            int x = f.coordinate / 100,y = f.coordinate % 100;
            if(f.step < table[x][y].min_step){
                table[x][y].min_step = f.step;
                table[x][y].coordinate_p = f.coordinate_p;
                if(f.coordinate == finish){ // goal test
                    goal = true;
                    break;
                }
                for(int i = 0;i < 8;i++){
                    int nx = x + dx[i],ny = y + dy[i];
                    if(0 <= nx && nx <= 15 && 0 <= ny && ny <= 15 && f.step + 1 < min(depth,table[nx][ny].min_step)){
                        s.push_back(Frontier(nx * 100 + ny,f.coordinate,f.step + 1));
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
        int x = f.coordinate / 100,y = f.coordinate % 100;
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
                if(0 <= nx && nx <= 15 && 0 <= ny && ny <= 15 && f.fval + 1 < table[nx][ny].min_fval){
                    q.push(Frontier(nx * 100 + ny,f.coordinate,f.gval + 1));
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
        for(int i = 0;i < 256;i++)
            table[i / 16][i % 16] = Block(); // initial table
        priority_queue<Frontier,vector<Frontier>,greater<Frontier> > q;
        q.push(Frontier(start,-1,0)); // coordinate,coordinate_p,gval = step
        Frontier_count++;
        while(!q.empty()){
            Frontier f = q.top();
            q.pop();
            int x = f.coordinate / 100,y = f.coordinate % 100;
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
                    if(0 <= nx && nx <= 15 && 0 <= ny && ny <= 15 && f.fval + 1 < table[nx][ny].min_fval && f.gval + 1 < depth){
                        q.push(Frontier(nx * 100 + ny,f.coordinate,f.gval + 1));
                        Frontier_count++;
                    }
                }
            }
        }
        printf(goal?"Depth%d: Success\n":"Depth%d: Failed\n",depth++);
    }
}
