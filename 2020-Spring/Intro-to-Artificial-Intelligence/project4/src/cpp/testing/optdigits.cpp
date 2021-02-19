#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std;
struct Sample{
	int pic[64];
	int value;
};
class Node{
public:
	Node *branch_t, *branch_f;
	vector<Sample> dataset;
	float impurity, threshold;
	int index;
	int attr, leaf; // index of pic, if impurity = 0.0 leaf != -1 
	Node();
	Node(vector<Sample> & DataSet);
};
struct SampleSorter{
	int attribute;
	SampleSorter(int ATTR) : attribute(ATTR) {}
  	bool operator() (Sample s1, Sample s2) { return (s1.pic[attribute] < s2.pic[attribute]);}
};
struct Children{
	float impurity_t, impurity_f; // branch_true_gini_impurity,branch_false_gini_impurity
	vector<Sample> sample_t, sample_f;
	int attribute;
	float threshold;
};

void ReadDataset(const char* filename, vector<Sample> & dest);
void SampleBagging(vector<vector<Sample> > & dest, vector<Sample> & train_set, float sample_rate);
int Predict(Node* node, int picture[64]);
void PrintTree(Node* node);
void BuildDecisionTree(Node* node);
Children Partition(vector<Sample> & dataset, int & attribute, float & threshold);
float GiniImpurity(int digit_count[10], int node_size);
float InfoGain(float & parent_impurity, Children & children);

int main(int argc, char const *argv[]){
	int ToA = 1;
	printf("DecisionTreeClassifier(1),RandomForestClassifier(2): ");
	scanf("%d",&ToA);
	if(2 < ToA || ToA < 1){
        printf("[x] Unexpected input!!!\n");
        return -1;
    }
	vector<Sample> digits_train,digits_test;
	ReadDataset("optdigits.tra",digits_train);

	int n_tree = 1;
	float sample_rate = 1.0;
	if(ToA == 1)
		printf("DecisionTreeClassifier selected\n");
	else{
		printf("RandomForestClassifier selected\nInput number of tree: ");
		scanf("%d",&n_tree);
		printf("Input sample_rate(subset_size = train_set_size * sample_rate): ");
		scanf("%f",&sample_rate);
	}
	// Sample bagging
	vector<vector<Sample> > sets(n_tree);
	SampleBagging(sets, digits_train, sample_rate);

	// Build tree
	printf("Progress of Build Tree starts, it takes some time, don't kill the program\n");
	Node *DT[n_tree];
	for(int ni = 0;ni < n_tree;ni++){
		DT[ni] = new Node(sets[ni]);
		BuildDecisionTree(DT[ni]);
	}
	
	// Predict result by the tree
	ReadDataset("optdigits.tes",digits_test);
	int hit = 0;
	for(int i = 0;i < digits_test.size();i++){
		int vote[10] = {0};
		for(int ni = 0;ni < n_tree;ni++)
			vote[Predict(DT[ni], digits_test[i].pic)]++;
		int ans = digits_test[i].value, res = 0, highest_vote = 0;
		for(int vi = 0;vi < 10;vi++)
			if(vote[vi] > highest_vote){
				highest_vote = vote[vi];
				res = vi;
			}
		if(res == ans)
			hit++;
		printf("ans = %d, res = %d\n",ans,res);
	}
	printf("\nHit rate = %d / %d = %f\n",hit,digits_test.size(),(float)hit/digits_test.size());

	printf("Exit(0),PrintTree(1): ");
	scanf("%d",&ToA);
	for(int ni = 0;ni < n_tree && ToA;ni++){
		printf("Tree %d:\n",ni);
		PrintTree(DT[ni]); // Print the tree by DFS
	}
	return 0;
}

void SampleBagging(vector<vector<Sample> > & dest, vector<Sample> & train_set, float sample_rate){
	int subset_size = train_set.size() * sample_rate;
	srand(time(NULL));
	for(int ni = 0;ni < dest.size();ni++){
		if(subset_size == train_set.size()){
			dest[ni] = train_set;
			continue;
		}
		vector<bool> selected_sample(train_set.size());
		int hit = 0;
		while(hit < subset_size){
			int index = rand() % train_set.size();
			if(!selected_sample[index]){
				selected_sample[index] = true;
				hit++;
			}
		}
		for(int si = 0;si < selected_sample.size();si++)
			if(selected_sample[si])
				dest[ni].push_back(train_set[si]);
	}
}
void BuildDecisionTree(Node* node){
	if(node->impurity == 0.0){
		node->leaf = node->dataset[0].value;
		return; // pure node: leaf node
	}
	// find optimal partition
	float optimal_infogain = 0.0;
	Children optimal_children;
	for(int attribute = 0;attribute < 64;attribute++){
		sort(node->dataset.begin(), node->dataset.end(), SampleSorter(attribute));
		// calculate possible threshold
		vector<float> thres_arr;
		for(int di = 0;di < node->dataset.size() - 1;di++){
			float threshold = (float)(node->dataset[di].pic[attribute] + node->dataset[di + 1].pic[attribute]) / 2.0;
			if(thres_arr.empty() || threshold != thres_arr.back())
				thres_arr.push_back(threshold);
		}
		
		for(int ti = 0;ti < thres_arr.size();ti++){
			Children children = Partition(node->dataset, attribute, thres_arr[ti]);
			if(children.sample_t.empty() || children.sample_f.empty())
				continue;
			//printf("attr = %d, threshold = %f\n%d %d\n", attribute, thres_arr[ti], children.sample_t.size(), children.sample_f.size());
			//printf("%f %f\n", children.impurity_t, children.impurity_f);
			float infogain = InfoGain(node->impurity, children);
			//printf("infogain = %f\n",infogain);
			if(infogain > optimal_infogain){
				optimal_infogain = infogain;
				optimal_children = children;
			}
		}
	}
	//printf("\n\nOptimal Partition:\n");
	//printf("attr = %d, threshold = %f\n", optimal_children.attribute, optimal_children.threshold);
	//printf("infogain = %f\n",optimal_infogain);
	
	// Construct child nodes
	Node *child_t = new Node(), *child_f = new Node();
	child_t->dataset = optimal_children.sample_t;
	child_f->dataset = optimal_children.sample_f;
	child_t->impurity = optimal_children.impurity_t;
	child_f->impurity = optimal_children.impurity_f;
	child_t->index = node->index << 1;
	child_f->index = (node->index << 1) + 1;
	// Update present node info
	node->attr = optimal_children.attribute;
	node->threshold = optimal_children.threshold;
	node->branch_t = child_t;
	node->branch_f = child_f;
	// Recursively call the function BuildDecisionTree()
	BuildDecisionTree(node->branch_t);
	BuildDecisionTree(node->branch_f);
}
Children Partition(vector<Sample> & dataset, int & attribute, float & threshold){
	Children children;
	children.attribute = attribute;
	children.threshold = threshold;
	int count_t[10] = {0}, count_f[10] = {0};
	for(int di = 0;di < dataset.size();di++){
		if(dataset[di].pic[attribute] <= threshold){
			children.sample_t.push_back(dataset[di]);
			count_t[dataset[di].value]++;
		}
		else{
			children.sample_f.push_back(dataset[di]);
			count_f[dataset[di].value]++;
		}
	}
	children.impurity_t = GiniImpurity(count_t,children.sample_t.size());
	children.impurity_f = GiniImpurity(count_f,children.sample_f.size());
	return children;
}
float GiniImpurity(int digit_count[10], int node_size){
	float impurity = 1.0;
	for(int i = 0;i < 10;i++){
		float prob = (float)digit_count[i] / node_size;
		impurity -= (prob * prob);
	}
	return impurity;
}
float InfoGain(float & parent_impurity, Children & children){
	float infogain = parent_impurity, impurity_t = children.impurity_t, impurity_f = children.impurity_f;
	int sample_t_size = children.sample_t.size(), sample_f_size = children.sample_f.size();
	int parent_size = sample_t_size + sample_f_size;
	infogain -= (((float)sample_t_size * impurity_t + (float)sample_f_size * impurity_f) / parent_size);
	return infogain;
}
int Predict(Node* node, int picture[64]){
	if(node->leaf != -1)
		return node->leaf;
	if(picture[node->attr] <= node->threshold)
		return Predict(node->branch_t, picture);
	return Predict(node->branch_f, picture);
}
void PrintTree(Node* node){
	queue<Node*> q;
	q.push(node);
	while(!q.empty()){
		Node *n = q.front();
		q.pop();
		printf("index, attr, thres, val = %d, (%d,%d), %f, %d\n",n->index,n->attr / 8,n->attr % 8,n->threshold,n->leaf);
		if(n->branch_t)
			q.push(n->branch_t);
		if(n->branch_f)
			q.push(n->branch_f);
	}
}
void ReadDataset(const char* filename, vector<Sample> & dest){
	ifstream file(filename);
	Sample tmp;
	if(file.is_open()){
		string line;
    	while(std::getline(file, line)){
        	line += ',';
        	int i = 0,value = 0;
        	for(int li = 0;li < line.length();li++){
        		if(line[li] == ','){
        			if(i < 64){
        				tmp.pic[i] = value;
        				i++;
        			}
        			else{
        				tmp.value = value;
        				i = 0;
        				dest.push_back(tmp);
        			}
        			value = 0;
        		}
        		else if('0' <= line[li] && line[li] <= '9')
        			value = value * 10 + (line[li] - '0');
        	}
    	}
    	file.close();
	}
	else{
		printf("E: File open failed\n");
		exit(1);
	}
}
Node::Node(){
	impurity = 1.0;
	threshold = 0.0;
	attr = -1;
	leaf = -1;
	branch_t = branch_f = NULL;	
}
Node::Node(vector<Sample> & DataSet){
	threshold = -1.0;
	attr = -1;
	leaf = -1;
	index = 1; // root
	dataset = DataSet;
	int count[10] = {0};
	for(int di = 0;di < dataset.size();di++)
		count[dataset[di].value]++;
	impurity = GiniImpurity(count, dataset.size());
	branch_t = branch_f = NULL;
}