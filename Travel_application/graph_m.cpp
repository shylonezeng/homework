/*matrix method to create graph*/
#include <iostream>
#include <string>
// #include <
//
using namespace std;

class CGraph{
	private:
		int node_num; //number  of graph nodes
		int arc_num;	//number of graph arc
		int **mt; //matrix;
		bool ** ifVisited;
		CGraph();
		CGraph(int node_num,int arc_num);
		~CGraph();
	public:
		void init();
		// 		void addNode(int node_id);
		void addArc(int snode,int enode,int value);
		//void getNode(int row,int col);
		bool ifVisited(int row,int col);
		void visit(int row ,int col);
		void setNode(int node_num);
		void setArc(int **arcs);
		void destory();
		void show();
}

CGraph::~CGraph(){

	//reallocate memory resource;
	destory();
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
void CGrahp::setNode(int node_num)
{
	if(node_num==0)
	{
		mt=NULL;
		ifVisited=NULL;
		return ;
	}
	this->node_num=node_num;
	*mt=new int(this->node_num);
	ifVisited =new bool[this->node_num];
	for(int i=0;i<this->node_num;++i){

		mt[i]=new int[this->node_num];
		ifVisited=new bool[this->node_num];
	}
	memset(mt,sizeof(int)*node_num*node_num,0);
	memset(ifVisited,sizeof(bool)*node*node_num,0);
}
void CGraph::addArc(int snode,int enode,int value){
	mt[snode][enode]=value;
}

bool CGraph::ifVisited(int row,int col)
{

	if(ifVisited[row][col])
		return true;
	return false;
}
void CGraph::visit(int row , int col )
{
	//do something
	//...
	ifVisited[row][col]=true;
}
/*useless function*/
void CGraph::addNode(int node_id){
	cout<<"fail in adding node"<<endl;f
		node_num++;
}

void CGraph::show ()
{
	for(int i=0;i<node_num; ++i){
		for(int j=0;j<node_num; ++j)
			cout<<mt[i][j]<<"["<<ifVisited[i][j]<<"]\t";
		cout<<endl;
	}

}
/*TO DO*/
void CGraph::setArc(int **arcs){
}
void CGraph::destroy(){
	for(int i=0;i<node_num;++i){
		if(mt[i]])
			delete mt[i];
		if(ifVisited[i])
			delete ifVisited[i];
	}
	if(mt)
		delete mt;
	if(ifVisitedd)
		delete ifVisited;
}

int main()
{
	CGraph g(5);
	g.show();

}
