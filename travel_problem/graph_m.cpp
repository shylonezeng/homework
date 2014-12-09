/*matrix method to create graph*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <map>
#include <utility>

#ifndef debug
	#define debug
#endif
#define ivector vector<int>
// typedef vector<int> ivector;

// #include <
//
using namespace std;

class CGraph{
	public:
		int node_num; //number  of graph nodes
		int arc_num;	//number of graph arc
		int **mt;	// use two halt triangle part to store arc infomation

		//

	private:
		bool * visit_flag;
		typedef vector<vector<int> >  adjNodes_type;
		adjNodes_type adjNodes;
		adjNodes_type back_adjNodes;
		int p_adj;
		void destroy();
	public:
		CGraph();
		CGraph(int node_num);
		~CGraph();
	public:
		void init();
		// 		void addNode(int node_id);
		void addArc(int snode,int enode,int value);
		void addArc(int snode,int enode){addArc(snode,enode,1);}
		//void getNode(int row,int col);
		bool ifVisited(int index);
		void visit(int index);
		bool setVisitFlag(int index,int visit_time);
		void setNode(int node_num);
		void setArc(int **arcs);
		void show();

		void setNextNodes();
		void resetNextNodes();
		int nextNode(int , int *,bool dir);
		int getWestest(){ return 0;}
		int getEastest(){ return node_num-1;}
};

CGraph::~CGraph(){

	//reallocate memory resource;
	destroy();
}
CGraph::CGraph()
{
	node_num=0;
	arc_num=0;
	setNode(0);
}
CGraph::CGraph(int node_num)
{
	this->node_num=node_num;
	this->arc_num=0;
	this->p_adj=0;
	setNode(node_num);

}
void CGraph::setNode(int node_num)
{
	if(node_num==0)
	{
		mt=NULL;
		visit_flag=NULL;
		return ;
	}
	this->node_num=node_num;
	mt=new int*[this->node_num];
	visit_flag =new bool[this->node_num];
	for(int i=0;i<this->node_num;++i){

		mt[i]=new int[this->node_num];
		// 		visit_flag[i]=new bool[this->node_num];
	}

	memset(mt,sizeof(int)*node_num*node_num,0);
	memset(visit_flag,sizeof(bool)*node_num*node_num,0);
}
void CGraph::addArc(int snode,int enode,int value){
	mt[snode][enode]=value;
	mt[enode][snode]=value;
}

bool CGraph::ifVisited(int index)
{

	if(visit_flag[index])
		return true;
	return false;
}
void CGraph::visit(int index )
{
	//do something
	//...
	visit_flag[index]=true;
}
bool CGraph::setVisitFlag(int index ,int visit_time){
	if(index>=node_num)
		return false;
	this->visit_flag[node_num]=visit_time;

}

/*useless function*/
// void CGraph::addNode(int node_id){
// 	cout<<"fail in adding node"<<endl;
// }

void CGraph::show ()
{
	for(int i=0;i<node_num; ++i){
		for(int j=0;j<node_num; ++j)
			cout<<mt[i][j]<<" ";
		cout<<endl;
	}

}
/*TO DO*/
void CGraph::setArc(int **arcs){
}

void CGraph::destroy(){
	for(int i=0;i<node_num;++i){
		if(mt[i])
			delete mt[i];
		// 		if(visit_flag[i])
		// 			delete visit_flag[i];
	}
	// 	if(mt)
	// 		delete mt;
	// 	if(visit_flag)
	// 		delete visit_flag;
}
void CGraph::setNextNodes(){
	for(int i=0;i<node_num;++i)
	{
		vector<int> oneNode_adj;
		for(int j=i+1;j<node_num;++j){

			if(!mt[i][j])
				continue;
			oneNode_adj.push_back(j);
		}
		this->adjNodes.push_back(oneNode_adj);
	}
}
void CGraph::resetNextNodes(){
	for(int i=0;i<node_num;++i)
	{
		vector<int> oneNode_adj;
		for(int j=i-1;j>=0;--j){

			if(!mt[i][j] )
				continue;
			oneNode_adj.push_back(j);
		}
		this->back_adjNodes.push_back(oneNode_adj);
	}
}
int CGraph::nextNode(int cur_node, int *which_one,bool dir){
	vector<int> oneNode_adj;
	//catch exception
	if(!dir)
		oneNode_adj=this->adjNodes[cur_node];
	else
		oneNode_adj=this->back_adjNodes[cur_node];

	if((*which_one)>=oneNode_adj.size())
		return -1;
	return oneNode_adj[(*which_one)++];
}

template <typename MylistType>
void printArray(MylistType list){
	typename MylistType::iterator iter=list.begin();
	while((iter++)!=list.end())
		cout<<*iter<<" ";
	cout<<endl;
}

class CLog{

}bestPath;

typedef vector<int> V;
void vcopy(V &des, V source){
	des.clear();
	V::iterator iter=source.begin();
	while(iter!=source.end())
	{
		des.push_back(*iter);
	}
}
// typedef vector<vector<int>> Log_t;
typedef pair<vector<int>,int> key_type;
typedef vector<int> value_of_path;
typedef map<key_type,value_of_path> Log_t;
// bool back_path=false;

bool recurse(CGraph &g,Log_t &log,vector<int> visited_flag,vector<int> &path,int cur_node,bool dir){
	//

	// 	if(back_path){
	// 		g.resetNextNodes();
	// 		back_path=false;
	// 	}
	//sf

	//cout<<"visiting node:"<<cur_node<<endl;
	// system("paus");

			cout<<"tempPath:"<<endl;
			printArray<ivector>(path);


	path.push_back(cur_node);
	visited_flag[cur_node]=1;
	//end recursion condition
	if(cur_node==g.getWestest()){
		return true;
	}
	if(cur_node==g.getEastest()){
		dir=1;
		//g.resetNextNodes();
	}

	//if loged then return;
	key_type key=key_type(visited_flag,cur_node);
	Log_t::iterator iter=log.find(key);
	if(iter!=log.end() ){
		cout<<"loged,need not continue"<<endl;
		vcopy(path,log[key]);
		return false;
	}
	// the best path
	int maxPsbyNodes=0;
	vector<int> bestPath;
	//
	int which_adj=0;

	int nNode=g.nextNode(cur_node,&which_adj,dir);

	while(nNode!=-1){
		if(!visited_flag[nNode]){
			vector<int> tempPath(path);	//copy of path. !!! may deallocted before referred
			recurse(g,log,visited_flag,tempPath,nNode,dir);
			int len=tempPath.size();
			if(len<=maxPsbyNodes){
				maxPsbyNodes=len;
				bestPath=tempPath;
			}

		}
		nNode=g.nextNode(cur_node,&which_adj,dir);
	}
// 	cout<<"bestPath:"<<endl;
// 	printArray<ivector>(bestPath);
	//deep copy the best
	path=bestPath;
	//if not loged, then log;
	log[key]=path;

	return false; //not returned  back
}
/*search path function*/
bool search_path(CGraph &g, ivector& bestPath){//maybe some erro can happen when it returns a reference type
#ifdef debug
	cout<<"call function  search_path"<<endl;
#endif
	int  node_num=g.node_num;
	if(g.node_num<=1)
		return false ;
	/*start node can be visited 2 times*/
	// 	g.setVisitFlag(0,2);
	// 	int max_passby=node_num-1;
	//each row index means number of nodes passed from source node to destination node
	//min number start with index 1;
	//log element logs next visit node
	// 	int log_length=(int)pow(2,n);
	Log_t log;
	vector<int> visited_flag(node_num,0);
	// 	vector<int> path;
	int maxPsbyNodes=0;
// 	vector<int> bestPath;

	g.setNextNodes();
	g.resetNextNodes();

	bool direction=0;
	int which_one=0;
	int nNode=g.nextNode(0,&which_one,direction);

	while(nNode!=-1){
		vector<int> path;
		recurse(g,log,visited_flag,path,nNode,direction);

		int len=path.size();
		if(len>maxPsbyNodes){
			maxPsbyNodes=len;
			bestPath=path;
		}
		nNode=g.nextNode(0,&which_one,direction);
	}
	// be sure to print out all elements
	return true;
	/*nodes passed by can be 1 to max_passby*/
	//when number of nodes passby is one;
}
/*end search function*/


// {
// 	int psby=1;
// 	for(int p_node=1;p_node<node_num;p_node++){
// 		log[psby]=new int[node_num];
// 		memset(log[psby],0,sizeof(int)*node_num);
//
// 		if(g.mt[0][p_node])
// 			log[psby][p_node]=1;
// 	}
// /*没有考虑每个节点只能访问一次的问题*/
// 	for(psby=1;psby<=max_passby;++psby){
// 		log[psby]=new int[node_num];
// 		memset(log[psby],0,sizeof(int)*node_num);
//
// 		for(int p_node=1;p_node<node_num;p_node++){
// 			//find Adjacent node and evalue weather can pass by it
// 			//can not be involed in visitd node set
// 			for(int adj=1;adj<node_num;adj++){
// 				if(is adjacent node ||  if involed in visited path){
// 					if(!canReach(adjnode))
//
// 				}
// 			}
// 		}
// 	}
// 	/*find longest path*/
//
// }


/*main function*/
int main(int argc,char** argv)
{
#ifdef debug
	ifstream cin("input");
#endif
	int node_num,arc_num;
	CGraph g;
	/*create graph*/
	ivector path;
	while(cin>>node_num>>arc_num)	{
		cout<<"arc_num: "<<arc_num<<endl;
		g.setNode(node_num);
		for(int i=0;i<arc_num;++i){
			int arc_value=0;
			int snode,enode;
			cin>>snode>>enode;
			g.addArc(snode,enode);
		}
		g.show();
		/*search the travel path*/
		search_path(g,path);
	}
	path.clear();

	// // path.push_back(0);
	// path.push_back(1);
	// path.push_back(2);
	// path.push_back(3);

	printArray<ivector>(path);


	cout<<"path size:"<<path.size()<<"\t end functoin main. "<<endl;
	return 0;
	/*reallocate new resource*/
	//descontrutor function do complete this task
}
/*end main*/
