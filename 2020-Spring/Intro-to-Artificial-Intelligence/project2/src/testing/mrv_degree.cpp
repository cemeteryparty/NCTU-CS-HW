#include <iostream>
#include <queue>
#include <vector>
#include <climits> // INT_MAX

using namespace std;
class Variable{
public:
    bool isVar;
    int value,degree,position;
    Variable(int val = -1){
        value = val; 
        position = -1;
        degree = 1; // number of Constrain the Variable associates, min_degree = 1, num of bomb
        isVar = false; // isVAR-> value = -1: unassigned variable,0: clear,1: bomb
    }
    friend bool operator>(const Variable & v1,const Variable & v2){
        return v1.degree > v2.degree; // v2 FO, Degree heuristic
    }
};
class Constrain{
public:
    int value;
    vector<int> variable;
    Constrain(int val = -1):value(val){}
};
void print_solution(vector<Variable> & solution,int n,int m){
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++)
            printf(solution[i * m + j].isVar?"(%d)":"[%d]",solution[i * m + j].value);
        printf("\n");
    }
}
int main(int argc, char const *argv[]){
    int n,m,NumofMines;
    scanf("%d%d%d",&n,&m,&NumofMines);
    vector<Variable> board(n * m);
    vector<Constrain> cons; // 
    cons.push_back(Constrain(NumofMines)); // Num of Mines constrain
    for(int pos = 0;pos < n * m;pos++){
        scanf("%d",&board[pos].value);
        board[pos].position = pos;
        if(board[pos].value == -1){ // var record
            cons[0].variable.push_back(pos);
            board[pos].isVar = true;
        }
        else
            cons.push_back(Constrain(pos));
    }
    int dx[] = {-1,-1,-1,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,1,-1,0,1};
    for(int i = 1;i < cons.size();i++){
        int x = cons[i].value / m,y = cons[i].value % m;
        for(int di = 0;di < 8;di++){
            int nx = x + dx[di],ny = y + dy[di];
            if(0 <= nx && nx < n && 0 <= ny && ny < m && board[nx * m + ny].value == -1){
                cons[i].variable.push_back(nx * m + ny);
                board[nx * m + ny].degree++;
            }
        }
        cons[i].value = board[x * m + y].value; // replace hint pos into value
    }

    int Frontier_count = 1,iteration = 0;
    bool SolutionExist = false;
    vector<vector<Variable> > stack;
    stack.push_back(board);
    while(!stack.empty()){
        iteration++;
        vector<Variable> node = stack.back(); // board in current node
        stack.pop_back();
        bool goal = true,drop_node = false;
        for(int i = 0;i < cons.size();i++){ 
            // check all constrain upper and lower bound and do goal test(all constrains are satified)
            // MRV is also implemented in this for loop,
            // domain_size = 1 can be assigned at current state directly
            int lower = 0,upper = cons[i].variable.size();
            for(int j = 0;j < cons[i].variable.size();j++){
                if(node[cons[i].variable[j]].value == 0)
                    upper--;
                else if(node[cons[i].variable[j]].value == 1)
                    lower++;
            }
            if(lower == cons[i].value && upper == cons[i].value)
                continue; // check next constrain
            else if(lower > cons[i].value || upper < cons[i].value){
                drop_node = true; // A constrain can't be satisfied
                break;
            }
            else if(lower == cons[i].value || upper == cons[i].value){
                for(int j = 0;j < cons[i].variable.size();j++){
                    if(node[cons[i].variable[j]].value == -1) // var's domain has become singletons 
                        node[cons[i].variable[j]].value = lower == cons[i].value?0:1;
                }
            }
            else
                goal = false; // NOT goal node
        }
        if(drop_node)
            continue; //
        if(goal){
            SolutionExist = true;
            printf("Solution:\n");
            print_solution(node,n,m);
            printf("\nFrontier_count =  %d\n",Frontier_count);
            printf("Iteration =  %d\n\n",iteration);
            break;
        }

        // cons[0].variable has all variable
        priority_queue<Variable,vector<Variable>,greater<Variable> > q;
        for(int i = 0;i < cons[0].variable.size();i++)
            if(node[cons[0].variable[i]].value == -1) // unassigned node
                q.push(node[cons[0].variable[i]]);
        while(!q.empty()){
            int pos = q.top().position;
            q.pop();
            node[pos].value = 0;
            stack.push_back(node);
            node[pos].value = 1;
            stack.push_back(node);
            node[pos].value = -1;
            Frontier_count += 2;
        }

    }
    if(!SolutionExist)
        printf("No solution\n");
    return 0;
}