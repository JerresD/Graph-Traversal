#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <vector>
#include "Graph.h"
using namespace std;


int main()
{
	srand(time(0));
    Graph g(5);
    vector<pair<int, int> > adj[5];
    vector<pair<int, int> > transpose[5];
    int weight[5][5]={
    {0,13171,17653,3453,2327},
    {13171,0,4490,12998,10916},
    {17653,4490,0,16257,15347},
    {3453,12998,16257,0,4755},
    {2327,10916,15347,4755,0}};
	int option;
	
	g.initialize(g, adj);
   	cout<<"GRAPH HAS BEEN INITIALIZED..."<<endl<<endl;
   	
   	do{
   		cout<<"PRESS 1 TO PRINT GRAPH"<<endl;
   		cout<<"PRESS 2 TO ADD EDGES"<<endl;
   		cout<<"PRESS 3 TO CHECK IF GRAPH IS STRONGLY CONNECTED"<<endl;
   		cout<<"PRESS 4 TO DETECT CYCLE IN GRAPH"<<endl;
   		cout<<"PRESS 5 TO FIND SHORTEST PATH BETWEEN 2 VERTEX"<<endl;
   		cout<<"PRESS 6 TO RESET TO DEFAULT GRAPH"<<endl;
   		cout<<"PRESS 7 TO EXIT"<<endl<<endl;
   		cin>>option;cin.ignore();
   	
   		switch(option) {
    		case 1 :
        		g.PrintGraph(adj,5);
     	 	  	break;
     	 	  	
 	     	case 2 :
 	     		int v1, v2, wt;
 	     		cout<<"0 - HANOI"<<endl<<"1 - COLUMBUS"<<endl<<"2 - QUITO"<<endl<<"3 - MUMBAI"<<endl<<"4 - BEIJING"<<endl;
 	     		cout<<"ENTER VERTEX 1: ";cin>>v1;cin.ignore(); 
				while(v1>5 || v1<0 ){
					cout<<"PLEASE ENTER THE CORRECT CODE FOR THE COUNTRY!!!"<<endl;
					cout<<"0 - HANOI"<<endl<<"1 - COLUMBUS"<<endl<<"2 - QUITO"<<endl<<"3 - MUMBAI"<<endl<<"4 - BEIJING"<<endl;
					cin>>v1;cin.ignore();
				}	
				cout<<"ENTER VERTEX 2: ";cin>>v2;cin.ignore();
 	     		while(v2>5 || v2<0 ){
					cout<<"PLEASE ENTER THE CORRECT CODE FOR THE COUNTRY!!!"<<endl;
					cout<<"0 - HANOI"<<endl<<"1 - COLUMBUS"<<endl<<"2 - QUITO"<<endl<<"3 - MUMBAI"<<endl<<"4 - BEIJING"<<endl;
					cin>>v1;cin.ignore();
				}
 	     		wt=weight[v1][v2];
	      		g.addEdge(adj,v1,v2,wt);
  	 	   	
				  
			case 3 :
				
				if(g.isSC(adj,transpose,5))
        			cout << "STRONGLY CONNECTED"<<endl;
    			else
        			cout << "NOT STRONGLY CONNECTED"<<endl<<endl;
        
        
			    while(!g.isSC(adj,transpose,5)){
			        g.randEdges(5,adj);
			        if(g.isSC(adj,transpose,5))
			            cout << "GRAPH IS STRONGLY CONNECTED !!!"<<endl;
			    }
			    //cout<<"\n"<<count<<" Edges added to make graph strongly connected\n";
			    
			    g.minimumEdges(adj,transpose,5);
				g.PrintGraph(adj,5);
				cout<<endl;
  	 	   		break;	  
				  	
    	  	case 4 :
    	    	if(g.isCyclic(adj))
	        		cout << "CYCLE DETECTED"<<endl;
	    		else
					cout << "NO CYCLE DETECTED"<<endl<<endl;
	    		while(!g.isCyclic(adj)){
	    			g.randEdges(5,adj);
	        		if(g.isCyclic(adj))
	        			cout << "CYCLE CREATED !!!"<<endl;
				}
				g.PrintGraph(adj,5);
				cout<<endl;
  	 	   		break;
        		
      		case 5 :
      			g.dijkstra(g, adj, 5);
    	    	cout<<endl;
        		break;
         	
         	case 6 :
         		g.clear(adj, 5);
				g.initialize(g, adj);
				cout << "GRAPH HAS BEEN RESET TO DEFAULT \n";
				cout<<endl;
         		break;
         		
         	case 7 :
         		cout<<"THANK YOU AND COME AGAIN"<<endl;
				break;	
         		
      		default :
         		cout << "INVALID CHOICE!!!"<< endl<<"PLEASE PRESS AGAIN. "<<endl;
   }}while(option!=7 );
   
    return 0;
}





