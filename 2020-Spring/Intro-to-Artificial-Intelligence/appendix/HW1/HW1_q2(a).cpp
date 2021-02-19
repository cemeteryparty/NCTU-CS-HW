#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Frontier{
public:
    int pos,pos_p;
    Frontier(int p,int p_p){
        pos = p;
        pos_p = p_p;
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
	queue<Frontier> q;
	q.push(Frontier(start,9999)); // no parent
	inq[start] = true;
	while(!q.empty()){
		Frontier node = q.front();
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
				q.push(Frontier(i,node.pos));
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