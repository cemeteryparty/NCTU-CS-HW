#include <iostream>
#include <queue>
#include <vector>
#include <climits> //INT_MAX
#include <cmath>

using namespace std;
int h(int n){ // heuristic function
    int x = n / 10,y = n % 10;
    return (int)floor((fabs((double)x - 7.0) + fabs((double)y - 7.0)) / 3.0);
}
class Block{
public:
    int coordinate_p,min_fval;
    Block(int cp = -1,int mf = INT_MAX){
        coordinate_p = cp;
        min_fval = mf;
    }
};
class Frontier{
public:
    int coordinate,coordinate_p,fval,gval;
    Frontier(int c,int cp,int g){
        coordinate = c;
        coordinate_p = cp;
        gval = g;
        fval = gval + h(c); // f(c) = g(c) + g(c)
    }
    friend bool operator>(const Frontier & obj1,const Frontier & obj2){
        return obj1.fval > obj2.fval;
    }
};
int dx[] = {1,2,1,-2,-1,2,-1,-2};
int dy[] = {2,1,-2,1,2,-1,-2,-1};
int main(int argc,char const *argv[]){
    //int sx = 0,sy = 0,tx = 7,ty = 7;// start:(0,0) goal:(7,7)
    Block table[8][8];
    priority_queue<Frontier,vector<Frontier>,greater<Frontier> > q;
    q.push(Frontier(0,-1,0));
    int Frontier_count = 1;
    while(!q.empty()){
        Frontier f = q.top();
        q.pop();
        int x = f.coordinate / 10,y = f.coordinate % 10;
        if(x == 7 && y == 7){ // goal test
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