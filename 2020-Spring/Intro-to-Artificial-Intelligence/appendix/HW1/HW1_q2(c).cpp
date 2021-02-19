#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int h(string s1,string s2){ // heuristic function
    int n = s1.size();
    for(int i = 0;i < s1.length();i++)
    	if(s1[i] == s2[i])
    		n--;
    return n;
}
class Frontier{
public:
    int pos,pos_p,fval,gval;
    Frontier(int p,int p_p,int f){
        pos = p;
        pos_p = p_p;
        fval = f;
    }
    friend bool operator>(const Frontier & obj1,const Frontier & obj2){
        return obj1.fval > obj2.fval;
    }
};
int main(int argc,char const *argv[]){
	string sa[] = {"AN","AM","AS","AT","AX","BE","BY","GO","HE","HI","IT","IS","IN","IF","ME","MY","NO","OF","OH","OK","ON","OR","OX","SO","TO","UP","US","WE"};
	vector<string> v(sa,sa + sizeof(sa) / sizeof(string));
	sort(v.begin(), v.end());
	vector<int> parent(v.size(),-1);
	vector<bool> inq(v.size(),false);
	int start,goal;
	for(int i = 0;i < v.size();i++){
		if(v[i] == "AT")
			start = i;
		else if(v[i] == "IN")
			goal = i;
	}
	priority_queue<Frontier,vector<Frontier>,greater<Frontier> > q;
	q.push(Frontier(start,9999,h(v[start],v[goal]))); // no parent
	inq[start] = true;
	while(!q.empty()){
		Frontier node = q.top();
		q.pop();
		parent[node.pos] = node.pos_p;
		string s = v[node.pos];
		cout << "choose: " << s << '\n';
		if(s == v[goal])
			break;
		cout << "expand: ";
		for(int i = 0;i < v.size();i++)
			if(!inq[i] && (s[0] == v[i][0] || s[1] == v[i][1])){
				inq[i] = true;
				cout << v[i] << ' ';
				q.push(Frontier(i,node.pos,h(v[i],v[goal])));
			}
		cout << '\n';
	}
	vector<int> path;
    int pos = goal;
    while(true){
    	if(pos == 9999)
    		break;
        path.push_back(pos);
        pos = parent[pos];
    }
    cout << v[path[path.size() - 1]];
    for(int i = path.size() - 2;i >= 0;i--)
    	cout << " => " << v[path[i]];
    cout << '\n';
   	return 0;
}