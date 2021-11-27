#include <iostream>
#include "graph.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int sum=0, x, y;
	adjacencyMatrix graph;
	graph.fillManual();
	//graph.testFill();
	graph.showMatrix();
	vector<int> chain;
	do
	{
		cout<<"\nEnter start point>> ";
		cin>>x;
	}while(x<0 or x>=graph.vertex);
	do
	{
		cout<<"\nEnter final point>> ";
		cin>>y;
	}while(y<0 or y>=graph.vertex or y==x);
	do
	{
		chain.clear();
		chain = graph.DFS(x, y);
		cout<<endl;
		if (chain[0]==-1)
			break;
		for(int i=1; i<chain.size(); i++)
		{
			if (i!=1)
				cout<<" -> ";
			cout<<chain[i];
			if (i>1)
			{
				graph.relation[chain[i-1]][chain[i]]-=chain[0];
				graph.relation[chain[i]][chain[i-1]]+=chain[0];
			}
		}
		cout<<" : "<<chain[0];
		sum+=chain[0];
	}while(1);
	cout<<"FLOW: "<<sum;
	return 0;
}
