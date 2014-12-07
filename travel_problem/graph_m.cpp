/*matrix method to create graph*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#define debug
// #include <
//
using namespace std;

class CGraph{
	private:
		int node_num; //number  of graph nodes
		int arc_num;	//number of graph arc
		int **mt; //matrix;
		bool ** visit_flag;
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
		bool ifVisited(int row,int col);
		void visit(int row ,int col);
		void setNode(int node_num);
		void setArc(int **arcs);
		void show();
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
	visit_flag =new bool*[this->node_num];
	for(int i=0;i<this->node_num;++i){

		mt[i]=new int[this->node_num];
		visit_flag[i]=new bool[this->node_num];
	}
	memset(mt,sizeof(int)*node_num*node_num,0);
	memset(visit_flag,sizeof(bool)*node_num*node_num,0);
}
void CGraph::addArc(int snode,int enode,int value){
	mt[snode][enode]=value;
}

bool CGraph::ifVisited(int row,int col)
{

	if(visit_flag[row][col])
		return true;
	return false;
}
void CGraph::visit(int row , int col )
{
	//do something
	//...
	visit_flag[row][col]=true;
}
/*useless function*/
// void CGraph::addNode(int node_id){
// 	cout<<"fail in adding node"<<endl;f
// }

void CGraph::show ()
{
	for(int i=0;i<node_num; ++i){
		for(int j=0;j<node_num; ++j)
			cout<<mt[i][j]<<"["<<visit_flag[i][j]<<"]\t";
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
		if(visit_flag[i])
			delete visit_flag[i];
	}
// 	if(mt)
// 		delete mt;
// 	if(visit_flag)
// 		delete visit_flag;
}

template <typename MylistType>
void printArray(MylistType list){
	typename MylistType::iterator iter=list.begin();
	while(iter!=list.end())
		cout<<*iter<<" ";
	cout<<endl;
}
/*search path function*/
vector<int>& search_path(CGraph g){//maybe some erro can happen when it returns a reference type
 	#ifdef debug
		cout<<"call function  search_path"<<endl;
	#endif
	

}



/*main function*/ 
int main(int argc,char** argv)
{
#ifdef debug
	 ifstream cin("input");
#endif
	int node_num,arc_num;
	CGraph g;
	/*create graph*/
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
		typedef vector<int> ivector;
		ivector path=search_path(g);
//		printArray<ivector>(path);
	}
	return 0;
	/*reallocate new resource*/
	//descontrutor function do complete this task
}
/*end main*/
