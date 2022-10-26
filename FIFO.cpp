#include <bits/stdc++.h> 
using namespace std; 
 
const int N=100005; 
 
void fifo_page_replacement(int frame_size, int n,int pages[]) 
{ 
 	int mark[N];     queue<int> Q; 
    int page_faults=0; 
 
    for(int i=0; i<n; i++) 
    { 
        if(mark[pages[i]]==true) 
        { 
        }         else 
        { 
            Q.push(pages[i]);             mark[pages[i]]=true; 
            if(Q.size()>frame_size) 
            { 
                int p= Q.front();                 mark[p]=false; 
                Q.pop(); 
            } 
            page_faults++; 
             
        } 
 
    }    
    cout<<"Frame size          Page faults          Page Hits\n"; 
    cout<<"     "<<frame_size<<"                     "<<page_faults<<"                "<<n-page_faults<<"\n"; 
 	return; 
} 
int main() 
{ 
 	int frame_size=4; int pages[N]; 
int n;    
    cout<<"Page Reference Stream Length: ";     cin>>n; 
 cout<<"Page Reference Stream:\n";     for(int i=0; i<n; i++)         cin>>pages[i]; 
  	fifo_page_replacement(frame_size,n,pages);  	return 0; 
} 
