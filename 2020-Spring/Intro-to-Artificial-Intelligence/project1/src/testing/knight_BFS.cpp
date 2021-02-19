#include <iostream>
#include <queue>
#include <vector>

using namespace std;
class Block{
public:
    int coordinate_p;
    bool forward;
    Block(int cp = -1,bool f = true){
        coordinate_p = cp;
        forward = f;
    }
};
class Frontier{
public:
    int coordinate,coordinate_p;
    Frontier(int c,int cp){
        coordinate = c;
        coordinate_p = cp;
    }
};
int dx[] = {1,2,1,-2,-1,2,-1,-2};
int dy[] = {2,1,-2,1,2,-1,-2,-1};
int main(int argc,char const *argv[]){
    //int sx = 0,sy = 0,tx = 7,ty = 7;// start:(0,0) goal:(7,7)
    Block table[8][8];
    queue<Frontier> q;
    q.push(Frontier(0,-1));
    int Frontier_count = 1;
    while(!q.empty()){
        Frontier f = q.front();
        q.pop();
        int x = f.coordinate / 10,y = f.coordinate % 10;
        table[x][y].forward = false;
        table[x][y].coordinate_p = f.coordinate_p;
        if(x == 7 && y == 7) // goal test
            break;
        for(int i = 0;i < 8;i++){
            int nx = x + dx[i],ny = y + dy[i];
            if(0 <= nx && nx <= 7 && 0 <= ny && ny <= 7 && table[nx][ny].forward){
                q.push(Frontier(nx * 10 + ny,f.coordinate));
                Frontier_count++;
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