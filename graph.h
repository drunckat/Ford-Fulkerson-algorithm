
#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#define MAX_INT 2147483647
using namespace std;

struct adjacencyMatrix
{
	int vertex;
	int **relation;

	void showMatrix()
	{
		cout << endl;
		cout << "     ";
		for (int x = 0; x < vertex; x++)
		{
			cout << "  x";
			printf("%-2i", x);
			cout << " ";
		}
		for (int x = 0; x < vertex; x++)
		{
			cout << endl << " x" << x << " ";
			for (int j = 0; j < vertex; j++)
			{
				cout << "  ";
				printf("%3i", relation[j][x]);
				cout << " ";
			}
		}
	}
	void fillRandom(int n)
	{
		srand(time(NULL));
		int sum;
		relation = new int* [n];
		for (int x = 0; x < n; x++)
			relation[x] = new int[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;

		for (int i=0; i<n; i++)
			for (int j = 0; j < i; j++)
			{
					relation[i][j] = rand() % 100;
					relation[j][i] = relation[i][j];
			}
		for (int i=0; i<n; i++)
		{
			sum=0;
			for (int j=0; j<n; j++)
			{
				if (relation[i][j])
					sum++;
			}
			
			while(!sum)
			{
				for (int j = 0; j < n; j++)
				{
					relation[i][j] = rand() % 100;
					relation[j][i] = relation[i][j];
					if (relation[i][j])
						sum++;
				}
				
			}
		}
		vertex = n;
	}
	void testFill()
	{
		vertex=4;
		int n=vertex;
		relation = new int* [n];
		for (int x = 0; x < n; x++)
			relation[x] = new int[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;
		relation[0][3]=1;
		relation[1][3]=2;
		relation[2][3]=4;
		
	}
	void fillManual()
	{
		string line;
		int sum=0, n;
		int x, y, flow, i;
		cout<<"Enter dimension: ";
		cin>>n;
		relation = new int* [n];
		for (int x = 0; x < n; x++)
			relation[x] = new int[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;
		
		cout<<"Enter value of edge by this template (press \"!\" to stop cycle)\n1->2:10\n";
		do
		{
		
			line.clear();
			cin>>line;
			if (line[0]=='!')
			{
				break;
			}
			else
			{
				i=0;
				x=0; 
				y=0;
				flow=0;
				for (;(int(line[i]) - 48 < 10) and (int(line[i]) - 48 >=0 ); i++)
				{
					x*=10;
					x+= (int(line[i]) - 48);
				}
				if (x>=n)
					continue;
				for (;(int(line[i]) - 48 >= 10) or (int(line[i]) - 48 < 0 ); i++);
				for (;(int(line[i]) - 48 < 10) and (int(line[i]) - 48 >=0 ); i++)
				{
					y*=10;
					y+= (int(line[i]) - 48);
				}
				if (y>=n)
					continue;
				for (;(int(line[i]) - 48 >= 10) or (int(line[i]) - 48 < 0 ); i++);
				for (;i<line.size(); i++)
				{
					flow*=10;
					flow+= (int(line[i]) - 48);
				}
				relation[x][y]=flow;
			}
		}while(1);
		vertex = n;
	}
	
	vector<int> adjacents(int i)
	{
		vector<int> neigs;
		for (int j=0; j<vertex; j++)
		{
			if (relation[i][j] and i!=j)
				neigs.push_back(j);
		}
		return neigs;
	}
	
	int sumRelation()
	{
		int counter = 0;
		for (int i=0; i<vertex; i++)
			for (int j = 0; j <= i; j++)
				if (relation[i][j])
					counter++;
		return counter;
	}
	
	vector<int> DFS(int x, int y)
	{
		vector<int> maxFlow(2);
		maxFlow[0]=MAX_INT;
		maxFlow[1]=x;
		maxFlow=chain(maxFlow, y);
		return maxFlow;
	}
	vector<int> chain(vector<int> before, int y)
	{
		bool key;
		bool foundY=0;
		vector<int> maxChain(before);
		vector<int> t;
		maxChain[0]=-1;
		for (int i=0; i<vertex; i++)
		{
			key=1;
			if (relation[before[before.size()-1]][i])
			{
				if (i==y)
				{
					foundY=1;
					continue;
				}
				key=0;
				for (int j=1; j<before.size(); j++)	
				{
					if (before[j]==i)
					{
						key=1;
						break;
					}
				}
			}
			if (!key) 
			{
				t=before;
				t[0]= before[0] < relation[before[before.size()-1]][i] ? before[0] : relation[before[before.size()-1]][i];
				t.push_back(i);
				t = chain(t, y);
				maxChain = maxChain[0] > t[0] ? maxChain:t;
			}
		}
		if (foundY)
		{
			t=before;
			t.push_back(y);
			t[0]= t[0] < relation[before[before.size()-1]][y] ? t[0] : relation[before[before.size()-1]][y];
			
			if (maxChain[0]<t[0])
			{
				return t;
			}
		}
		return maxChain;	
		
	}
	~adjacencyMatrix()
	{
		for (int i = 0; i < vertex; i++)
		{
			delete[] relation[i];
		}
	}

};
