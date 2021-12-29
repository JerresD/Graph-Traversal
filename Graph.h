#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <stack>
#include <iostream>
#include <bits/stdc++.h>
//#include "Graph.h"
using namespace std;
 
class Graph
{
    int V;    
    vector <pair<int,int> >*adj1;
    vector <pair<int,int> >*transpose;
    bool isCyclicUtil(vector<pair<int,int> > adj1[], int v, bool visited[], bool *rs);  
public:
    Graph(int V);   
    void addEdge(vector<pair<int,int> > adj1[], int v, int w, int wt);   
    bool isCyclic(vector<pair<int,int> > adj1[]);  
    void randEdges(int V, vector<pair<int,int> > adj1[]);  
	//void randEdges(int V, vector<pair<int,int> > adj1[]);  
	bool isAvailable(int &v1, int &v2);
	void PrintGraph(vector<pair<int,int> > adj1[], int V);
	void initialize(Graph &g, vector<pair<int,int> > adj1[]);
	void clear(vector<pair<int,int> > adj1[], int V);
	Graph getTranspose(vector<pair<int, int>  > adj1[], vector<pair<int, int>  > transpose[], int V );
	bool isSC(vector<pair<int,int> > adj1[],vector<pair<int,int> > transpose[], int V);
    void DFSUtil(vector<pair<int,int> > adj1[], int v, bool visited[]);
    void minimumEdges(vector<pair<int,int> > adj1[],vector<pair<int, int>  > transpose[],int V);
	bool isReachable(vector<pair<int,int> > adj1[], int V, int start, int destination) ;
	void dijkstra(Graph &g, vector<pair<int,int> > adj1[], int V);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj1 = new vector< pair<int,int> >;
    //adj=new list<int>[V];
}
 
void Graph::addEdge(vector<pair<int,int> > adj1[], int v, int w, int wt)
{
    adj1[v].push_back(make_pair(w, wt));
}
 
bool Graph::isCyclicUtil(vector<pair<int,int> > adj1[], int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;
 
        vector<pair<int,int> >::iterator i;
        for(i = adj1[v].begin(); i != adj1[v].end(); ++i)
        {	
            if ( !visited[(*i).first] && isCyclicUtil(adj1, (*i).first, visited, recStack) )
                return true;
            else if (recStack[(*i).first])
                return true;
        }
 
    }
    recStack[v] = false;  
    return false;
}
 
bool Graph::isCyclic(vector<pair<int,int> > adj1[])
{	
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
 
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(adj1, i, visited, recStack))
            return true;
 
    return false;
}

bool Graph::isAvailable(int &v1, int &v2) {
    for(auto it = adj1[v1].begin(); it != adj1[v1].end(); it++){	
		int v = it->first;
		if ( v2 == v  ) {
        	return true;
    }
	return false;
	}
}
	
void Graph::randEdges(int V, vector<pair<int,int> > adj1[])  {
	int wt[5][5]={
    {0,13171,17653,3453,2327},
    {13171,0,4490,12998,10916},
    {17653,4490,0,16257,15347},
    {3453,12998,16257,0,4755},
    {2327,10916,15347,4755,0}};
    int v1;
    int v2;
    //srand(time(0));
 	v1 = rand() % V;
    v2 = rand() % V;
    while (v1 == v2 || isAvailable(v1, v2)) {
        v1 = rand() % V;
        v2 = rand() % V;
    }
    int Temp_Weight = wt[v1][v2];
    addEdge(adj1, v1, v2, Temp_Weight);
    cout<<"EDGE "<<v1<<v2<<" IS CREATED "<<endl<<endl;
}

void Graph::PrintGraph(vector<pair<int, int> > adj1[], int V)  
{
	int v, w ;
	cout << "\nPrint Graph (Adjacency List): " << endl;
    for (int u = 0; u < V; u++)
    {
        
        for (auto it = adj1[u].begin(); it!=adj1[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "(" << u << ", ";
            cout << v << ", "
                 << w << ")\t";
        }
        cout << "\n\n";
    }
}

Graph Graph::getTranspose(vector<pair<int,int> > adj1[],vector<pair<int,int> > transpose[], int V){
    for (int v = 0; v < V; v++)
    {
    	for(int j = 0; j<adj1->size(); j++)
    		addEdge(transpose, adj1[v][j].first,v,adj1[v][j].second);
    	}
}

// The main function that returns true if graph is strongly connected
bool Graph::isSC(vector<pair<int,int> > adj1[],vector<pair<int,int> > transpose[], int V)
{

	
    // St1p 1: Mark all the vertices as not visited (For first DFS)
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Step 2: Do DFS traversal starting from first vertex.
    DFSUtil(adj1, 0, visited);
 
     // If DFS traversal doesn’t visit all vertices, then return false.
    for (int i = 0; i < V; i++){
        if (visited[i] == false)
             return false;
         }
 
  
    // Step 3: Create a reversed graph
    getTranspose(adj1, transpose, V);

 
    // Step 4: Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++){
    
        visited[i] = false;}
 
    // Step 5: Do DFS for reversed graph starting from first vertex.
    // Staring Vertex must be same starting point of first DFS
    DFSUtil(transpose, 0, visited);
    // If all vertices are not visited in second DFS, then
    // return false
    for (int i = 0; i < V; i++){
        if (visited[i] == false)
             return false;
         }
             
 
    return true;
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(vector<pair<int,int> > adj1[], int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    vector<pair<int,int> > ::iterator i;
    for (i = adj1[v].begin(); i != adj1[v].end(); ++i)
        if (!visited[(*i).first])
            DFSUtil(adj1, (*i).first, visited);
}

void Graph::minimumEdges(vector<pair<int,int> > adj1[],vector<pair<int, int>  > transpose[],int V){
stack<int> inD,outD;
int inDSize,outDSize,min;
//delete [] transpose;
getTranspose(adj1, transpose, V);

for(int i=0; i<V; i++){
		if(adj1[i].empty()){
			//cout<<"out "<<i<<endl;
			outD.push(i);
		}
		
		if(transpose[i].empty()){
			//cout<<"in "<<i<<endl;
			inD.push(i);		
	}
		
	}
	
	inDSize = inD.size();
	outDSize = outD.size();
	if(inDSize==outDSize)
		min = inDSize;
		
	else
		min=(inDSize+outDSize+1)/2;
	
	cout<<"\nMinimum edes required to make graph strongly connected is "<<min<<"\n";
} 

void Graph::initialize(Graph &g, vector<pair<int,int> > adj1[])
{
    g.addEdge(adj1, 2, 0, 17653);
    g.addEdge(adj1, 3, 0, 3453);
    g.addEdge(adj1, 1, 3, 12998);
    g.addEdge(adj1, 4, 1, 10916);
    g.addEdge(adj1, 2, 4, 15347);
}

void Graph::clear(vector<pair<int,int> > adj1[], int V)
{

	for(int i = 0; i < V; i++)
		adj1[i].clear();
}

bool Graph::isReachable(vector<pair<int,int> > adj1[], int V, int start, int destination) 
{
	// Base case
	if(start == destination)
		return true;
	
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	
	// Create a queue for BFS	
	queue<int> queue;
	
	// Mark the current node as visited and enqueue it
    visited[start] = true;
    queue.push(start);
    
    while (!queue.empty())
    {
		// dequeue front node and print it
        int v = queue.front();
        queue.pop();
        
        if (v == destination) 
            return true;
        
        for (auto u = adj1[v].begin(); u != adj1[v].end(); ++u)
        {
            if (!visited[u->first])
            {
                // mark it as discovered and enqueue it
                visited[u->first] = true;
                queue.push(u->first);
            }
        }
    }     
    // If BFS is complete without visiting d
    return false;
}

void Graph::dijkstra(Graph &g, vector<pair<int,int> > adj1[], int V)
{
	priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> > > pq;
	vector<int> dist;
	int start, destination;
	
	cout << "Please key in the starting point: ";
	cin >> start;
	while(start < 0 || start > 4)
    {
	    cout << "Wrong input. Try again (0-4) : ";
	    cin>> start;
	}
	cout << "Please key in the ending point: ";
	cin >> destination;
	while(destination < 0 || destination > 4)
    {
	    cout << "Wrong input. Try again (0-4) : ";
	    cin>> destination;
	}

	if(isReachable(adj1, V, start, destination))
		cout << "\nPath is existed. \n";
	else
		cout << "\nPath is not existed. \n\n";
	

	while(!isReachable(adj1, V, start, destination))	
	{
		int a;	
		++a;	
		g.randEdges(V, adj1);
		cout << "A path is created for "<< a << " times. \n\n";
	} 
	
	// Initialize all source->vertex as infinite.
	for(int i = 0; i < V; i++)
    {
        dist.push_back(1111111111); // Define "infinity" as necessary by constraints.
    }
    
    // Add source to pq, where distance is 0.
    pq.push(make_pair(start, 0));
    dist[start] = 0;
    
    while (!pq.empty())
    {
    	// Get min distance vertex from pq. (Call it u.)
    	int u = pq.top().first;
        pq.pop();
        
        // Visit all of u's friends. For each one (called v)
        for(int i = 0; i < adj1[u].size(); i++)
        {
        	int v = adj1[u][i].first;
        	int weight = adj1[u][i].second;
        	
        	// If the distance to v is shorter by going through u.
        	if(dist[v] > dist[u] + weight)
            {
                // Update the distance of v.
                dist[v] = dist[u] + weight;
                // Insert v into the pq. 
                pq.push(make_pair(v, dist[v]));
            }
    	}
	}
	
	//Print shortest path
    cout << "\nThe shortest distance is " << start << " -> " << destination << " = " << dist[destination] << endl;
	
	cout << "\n\nOverall: " << endl;
    for(int i = 0; i < dist.size(); i++)
    {
        cout << "The distance from node " << start << " to node " << i << " is: " << dist[i] << endl;
	}
}

#endif

