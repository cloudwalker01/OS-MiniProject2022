combined_code.cpp
Details
Activity
combined_code.cpp
Sharing Info.
Who has access

A

p

Manage access
General Info.
System properties
Type
C++
Size
10 KB
Storage used
10 KB
Location

Programs
Owner
Aditya Ballabh
Modified
Oct 22, 2022 by Aditya Ballabh
Opened
2:28 PM by me
Created
Oct 22, 2022
Description.
Add a description
Download permissions.
Viewers can download
//compile with -DTERM flag to get output on terminal instead of files

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <iomanip>

using namespace std;

int findFreeFrame(vector<pair<int,int>>page_table);

class OPT{  
        map<pair<int,int>, list<pair<int,int>>::iterator>mem_page_locs;
        int page_table_size;
     
     public:
        list<pair<int,int>>mem_pages;//represents pages which have currently been allocated frames in memory
        int page_fault_cnt;

        OPT(int cap){   
            page_table_size=cap;
            page_fault_cnt=0;
        }

        void refer(vector<pair<int,int>>&page_table, pair<int,int> page_ref, int req_num, vector<pair<int,int>>&page_refs);     
};

void OPT::refer(vector<pair<int,int>>&page_table, pair<int,int> page_ref, int req_num, vector<pair<int,int>>&page_refs){
    if(mem_page_locs.find(page_ref)==mem_page_locs.end()){
        page_fault_cnt++;
        if(mem_pages.size()==page_table_size){
            int n=page_refs.size();
            set<pair<int,int>>cur_pages; //using set because unordered would require custom hash function
            for(const pair<int,int> &key:mem_pages)
                cur_pages.insert(key);
            
            if(cur_pages.size()!=1){
                for(int i=req_num+1;i<n;i++){
                    if(cur_pages.find(page_refs[i])!=cur_pages.end())
                        cur_pages.erase(page_refs[i]);
                    if(cur_pages.size()==1)
                        break;
                }
            }
            
            for(int i=0;i<page_table_size;i++)
                if(page_table[i]==*cur_pages.begin()){
                    page_table[i]=page_ref;
                    break;
                }
            
            mem_pages.erase(mem_page_locs[*cur_pages.begin()]);
            mem_page_locs.erase(*cur_pages.begin());

        }
        else{
            int free_frame=findFreeFrame(page_table);
            page_table[free_frame]=page_ref;
        }
        mem_pages.push_front(page_ref);
        mem_page_locs.insert({page_ref, mem_pages.begin()});
    }
}

class MRU{
        map<pair<int,int>, list<pair<int,int>>::iterator>mem_page_locs;
        int page_table_size;
    
    public: 
        list<pair<int,int>>mem_pages;
        int page_fault_cnt;
        
        MRU(int cap){
            page_table_size=cap;
            page_fault_cnt=0;
        }       

        void refer(vector<pair<int,int>>&page_table, pair<int,int> page_ref);    
};

void MRU::refer(vector<pair<int,int>>&page_table, pair<int,int> page_ref){
    if(mem_page_locs.find(page_ref)!=mem_page_locs.end())
        mem_pages.erase(mem_page_locs[page_ref]);
    else{
        page_fault_cnt++;
        if(mem_pages.size()==page_table_size){
            
            for(int i=0;i<page_table_size;i++)
                if(page_table[i]==mem_pages.front()){
                    page_table[i]=page_ref;
                    break;
                }

            mem_page_locs.erase(mem_pages.front());
            mem_pages.pop_front();
        }
        else{
            int free_frame=findFreeFrame(page_table);
            page_table[free_frame]=page_ref;
        }
    }
    mem_pages.push_front(page_ref);
    mem_page_locs.insert({page_ref, mem_pages.begin()});       
}

class LRU{
        map<pair<int,int>, list<pair<int,int>>::iterator>mem_page_locs;
        int page_table_size;
    
    public: 
        list<pair<int,int>>mem_pages;
        int page_fault_cnt;

        LRU(int cap){
            page_table_size=cap;
            page_fault_cnt=0;
        }
    
        void refer(vector<pair<int,int>>&page_table, pair<int,int> page_ref);
};

void LRU::refer(vector<pair<int,int>>&page_table, pair<int,int> page_ref){
    if(mem_page_locs.find(page_ref)!=mem_page_locs.end())
        mem_pages.erase(mem_page_locs[page_ref]);
    else{
        page_fault_cnt++;
        
        if(mem_pages.size()==page_table_size){
            for(int i=0;i<page_table_size;i++)
                if(page_table[i]==mem_pages.back()){
                    page_table[i]=page_ref;
                    break;
                }
            mem_page_locs.erase(mem_pages.back());
            mem_pages.pop_back();
        }
        else{
            int free_frame=findFreeFrame(page_table);
            page_table[free_frame]=page_ref;
        }
    }
    mem_pages.push_front(page_ref); 
    mem_page_locs.insert({page_ref, mem_pages.begin()});
}

class LIFO{
        set<pair<int,int>> mem_pages_set;
        int page_table_size;
    public:
        list<pair<int,int>>mem_pages;
        int page_fault_cnt;

        LIFO(int cap){
            page_table_size=cap;
            page_fault_cnt=0;
        }

        void refer(vector<pair<int,int>>&page_table, pair<int,int>page_ref);
};

void LIFO::refer(vector<pair<int,int>>&page_table, pair<int,int>page_ref){
    if (mem_pages_set.find(page_ref)==mem_pages_set.end()){
        page_fault_cnt++;

        if (mem_pages_set.size() == page_table_size){
            pair<int,int> del_ref = mem_pages.front();
            mem_pages.pop_front();
            mem_pages_set.erase(del_ref);

            for(int i=0;i<page_table_size;i++)
                if(page_table[i]==del_ref){
                    page_table[i]=page_ref;
                    break;
                }
        }   
        else{
            int free_frame=findFreeFrame(page_table);
            page_table[free_frame]=page_ref;
        }
        mem_pages_set.insert(page_ref);
        mem_pages.push_front(page_ref);
    }
}


class FIFO{
        set<pair<int,int>> mem_pages_set;
        int page_table_size;
    public:
        list<pair<int,int>>mem_pages;
        int page_fault_cnt;

        FIFO(int cap){
            page_table_size=cap;
            page_fault_cnt=0;
        }

        void refer(vector<pair<int,int>>&page_table, pair<int,int>page_ref);
};

void FIFO::refer(vector<pair<int,int>>&page_table, pair<int,int>page_ref){
    if (mem_pages_set.find(page_ref)==mem_pages_set.end()){
        page_fault_cnt++;

        if (mem_pages_set.size() == page_table_size){
            pair<int,int> del_ref = mem_pages.front();
            mem_pages.pop_front();
            mem_pages_set.erase(del_ref);

            for(int i=0;i<page_table_size;i++)
                if(page_table[i]==del_ref){
                    page_table[i]=page_ref;
                    break;
                }
        }   
        else{
            int free_frame=findFreeFrame(page_table);
            page_table[free_frame]=page_ref;
        }
        mem_pages_set.insert(page_ref);
        mem_pages.push_back(page_ref);
    }
}

int findFreeFrame(vector<pair<int,int>>page_table){ //will only be called if space is available
    for(int i=0;i<page_table.size();i++)
        if(page_table[i].first==-1)
            return i;
    return -1; 
}

void displayCache(list<pair<int,int>>mem_pages){
    cout<<"\nList:\n";
    for(const pair<int,int> &entry:mem_pages)
        cout<<'('<<entry.first << "," << entry.second<<") -> ";
    cout<<"NULL\n\n";
}

void displayPageTable(vector<pair<int,int>>page_table){
    cout<<"Page Table: \n\n";
    cout<<setw(10)<<"pid"<<setw(15)<<"page_num";
    cout<<'\n';
    for(const pair<int,int> &entry:page_table)
        cout<<setw(10)<<entry.first << setw(15)<<entry.second<<"\n";
    cout<<"\n";     
}

void displayStats(int page_fault_cnt, int n){
    cout<<"\nPage Faults: \t"<<page_fault_cnt<<'\n';
    cout<<"Page Hits: \t"<<n-page_fault_cnt<<'\n';
    cout<<"Miss Ratio: \t"<<(float)page_fault_cnt/n<<'\n';
}

void clearPageTable(vector<pair<int,int>>&page_table){
    for(int i=0;i<page_table.size();i++)
        page_table[i]={-1,-1};
}   


void reqDispUtil(int ref_num, vector<pair<int,int>>page_table, pair<int,int>page_ref, list<pair<int,int>>mem_pages){
    cout<<"\nPage Reference #"<<ref_num<<":\n"<<page_ref.first<<','<<page_ref.second<<'\n';
    displayCache(mem_pages);
    displayPageTable(page_table);
    cout<<"---------------\n";
}

void redirectOutput(string alg_name){
    const char* file_name=(alg_name+"_Output.txt").c_str();
    #ifndef TERM
		if(!freopen(file_name, "w", stdout))
			cerr<<"can't open 'opt.txt'\n";
	#endif
    cout<<"----------------------------------------------"<<alg_name;
    cout<<"----------------------------------------------\n";
}

template<class T>
void referUtil(T &alg,vector<pair<int,int>>&page_table, vector<pair<int,int>>page_refs,int i){
    alg.refer(page_table, page_refs[i]);
}

template<>
void referUtil<OPT>(OPT &alg,vector<pair<int,int>>&page_table, vector<pair<int,int>>page_refs,int i){
    alg.refer(page_table, page_refs[i],i,page_refs);
}

template<class T>
void replacementAlgUtil(T &alg, string alg_name, vector<pair<int,int>>&page_table, vector<pair<int,int>>page_refs){
    redirectOutput(alg_name);
    int page_ref_cnt=page_refs.size();

    for(int i=0;i<page_ref_cnt;i++){
        referUtil(alg, page_table, page_refs, i);
        reqDispUtil(i+1, page_table, page_refs[i], alg.mem_pages);
    }
    cout<<"\n "<<alg_name<<" Stats:\n";
    displayStats(alg.page_fault_cnt, page_ref_cnt);
    clearPageTable(page_table);
} 

int main(){
    int page_table_size;      
    cout<<"Enter the number of frames\n";
    cin>>page_table_size;
    vector<pair<int,int>>page_table(page_table_size,{-1,-1}); //inverted page table -> {pid,page_num}

    int page_ref_cnt;
    cout<<"Enter the number of page references\n";
    cin>>page_ref_cnt;
    vector<pair<int,int>>page_refs(page_ref_cnt);

    cout<<"Enter the pid and page number for each reference\n";
    for(int i=0;i<page_ref_cnt;i++)
        cin>>page_refs[i].first>>page_refs[i].second;
    
    OPT opt(page_table_size);
    replacementAlgUtil(opt, "OPT", page_table, page_refs);

    LRU lru(page_table_size);
    replacementAlgUtil(lru, "LRU", page_table, page_refs);

    MRU mru(page_table_size);
    replacementAlgUtil(mru, "MRU", page_table, page_refs);
    
    LIFO lifo(page_table_size);
    replacementAlgUtil(lifo, "LIFO", page_table, page_refs);
    
    FIFO fifo(page_table_size);
    replacementAlgUtil(fifo, "FIFO", page_table, page_refs);
}