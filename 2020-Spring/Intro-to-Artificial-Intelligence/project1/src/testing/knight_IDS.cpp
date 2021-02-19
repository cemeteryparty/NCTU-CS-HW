#include <iostream>
#include <vector>
#include <climits> //INT_MAX
#include <algorithm> //std::min

using namespace std;
class Block{
public:
    int coordinate_p,min_step;
    Block(int cp = -1,int ms = INT_MAX){
        coordinate_p = cp;
        min_step = ms;
    }
};
class Frontier{
public:
    int coordinate,coordinate_p,step;
    Frontier(int c,int cp,int s){
        coordinate = c;
        coordinate_p = cp;
        step = s;
    }
};
int dx[] = {1,2,1,-2,-1,2,-1,-2};
int dy[] = {2,1,-2,1,2,-1,-2,-1};
int main(int argc,char const *argv[]){
    //int sx = 0,sy = 0,tx = 7,ty = 7;// start:(0,0) goal:(7,7)
    bool goal = false;
    Block table[8][8];
    int depth = 1; // depth limit
    int Frontier_count = 0;
    while(!goal){
        for(int i = 0;i < 64;i++)
            table[i / 8][i % 8] = Block(); // initial table
        vector<Frontier> s; // stack
        s.push_back(Frontier(0,-1,0));
        Frontier_count++;
        while(!s.empty()){
            Frontier f = s.back();
            s.pop_back();
            int x = f.coordinate / 10,y = f.coordinate % 10;
            if(f.step < table[x][y].min_step){
                table[x][y].min_step = f.step;
                table[x][y].coordinate_p = f.coordinate_p;
                if(f.coordinate == 77){ // goal test
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
    printf("Frontier_count =  %d\n",Frontier_count);
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
    int pos = 77;
    while(pos >= 0){
        path.push_back(pos);
        pos = table[pos / 10][pos % 10].coordinate_p;
    }
    for(int i = path.size() - 1;i >= 0;i--)
        printf("step %d: (%d,%d)\n",path.size() - i - 1,path[i] / 10,path[i] % 10);

    return 0;
}