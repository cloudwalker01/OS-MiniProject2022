#include <iostream>

using namespace std;
#include <bits/stdc++.h>



void showstack(stack<int> st)
{
    
    if (st.empty())
        return;
     
 
    int x = st.top();
 
    
    st.pop();
 
    
    showstack(st);
 
    
    cout << x << "\t";
 
   
    st.push(x);
}
 

void display(int pages,stack<int>&st ,int &capacity,int n,unordered_set<int> &s)
{
   
        
        
        for (int i=0; i<n; i++)
    {
        
        if (s.size() < capacity)
        {
            
            if (s.find(pages)==s.end())
            {
               
                s.insert(pages);
 
                
               
 
                
                st.push(pages);
            }
        }
 
        
        else
        {
            
            if (s.find(pages) == s.end())
            {
                
                int val = st.top();
                 
                
                st.pop();
 
               
                s.erase(val);
 
                
                s.insert(pages);
                
                st.push(pages);
                
 
            }
            else if(s.find(pages)!=s.end())
            {   
                continue;
            }
        }
        
        
    }
    cout<<pages<<"\t";
    showstack(st);
   
    cout<<endl;
    }
    
int main()
{
    int pages[] = {3,1,2,1,6,5,1,3};
    int n = sizeof(pages)/sizeof(pages[0]);
    int capacity = 3;
    string arr[capacity][5];
  
 stack<int>st;
   unordered_set<int> s;
    
    cout<<"PAGE NO\t  PAGE FRAMES\t\t\t\t"<<endl;
    for(int i=0;i<capacity;i++)
    {
        cout<<"\tf"<<i;
    }
    cout<<endl;
    cout<<"-----------------------------------------------------\n";
    
   for(int i=0;i<n;i++)
   {
       display(pages[i],st,capacity,n,s);
   }
    return 0;
}
