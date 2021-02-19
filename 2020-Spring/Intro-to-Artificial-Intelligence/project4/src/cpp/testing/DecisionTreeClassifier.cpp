#include <iostream>
#include <vector>
#include <algorithm>
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
	int attribute, threshold;
};

void ReadDataset(const char* filename, vector<Sample> & dest);
int Predict(Node* node, int picture[64]);
void PrintTree(Node* node);
void BuildDecisionTree(Node* node);
Children Partition(vector<Sample> & dataset, int & attribute, float & threshold);
float GiniImpurity(int digit_count[10], int node_size);
float InfoGain(float & parent_impurity, Children & children);

int main(int argc, char const *argv[]){
	vector<Sample> digits_train,digits_test;
	ReadDataset("optdigits.tra",digits_train);
	
	// Build tree
	Node *DT = new Node(digits_train);
	BuildDecisionTree(DT);

	// Predict result by the tree
	ReadDataset("optdigits.tes",digits_test);
	int hit = 0;
	for(int i = 0;i < digits_test.size();i++){
		int ans = digits_test[i].value, res = Predict(DT, digits_test[i].pic);
		printf("ans = %d, res = %d\n",ans,res);
		if(res == ans)
			hit++;
	}
	printf("\nHit rate = %d / %d = %f\n",hit,digits_test.size(),(float)hit/digits_test.size());
	
	// Print the tree by DFS
	PrintTree(DT);
	return 0;
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
	printf("index, attr, thres, val = %d, (%d,%d), %f, %d\n",node->index,node->attr / 8,node->attr % 8,node->threshold,node->leaf);
	if(node->branch_t)
		PrintTree(node->branch_t);
	if(node->branch_f)
		PrintTree(node->branch_f);
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
