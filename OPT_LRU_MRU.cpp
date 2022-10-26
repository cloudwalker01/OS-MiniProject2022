#include <bits/stdc++.h>
using namespace std;

class OPT{  
        unordered_map<int, list<int>::iterator>cached_page_loc;
        int cache_cap;
    public:
        list<int>cache;
        int page_fault_cnt;

        OPT(int cap){   
            cache_cap=cap;
            page_fault_cnt=0;
        }
    
        void request(int page_num, int req_num, vector<int>&page_requests){
            if(cached_page_loc.find(page_num)==cached_page_loc.end()){
                page_fault_cnt++;
                if(cache.size()==cache_cap){
                    int n=page_requests.size();
                    unordered_set<int>cur_pages;
                    for(const int &key:cache)
                        cur_pages.insert(key);
                    
                    if(cur_pages.size()!=1){
                        for(int i=req_num+1;i<n;i++){
                            if(cur_pages.find(page_requests[i])!=cur_pages.end())
                                cur_pages.erase(page_requests[i]);
                            if(cur_pages.size()==1)
                                break;
                        }
                    }

                    cache.erase(cached_page_loc[*cur_pages.begin()]);
                    cached_page_loc.erase(*cur_pages.begin());
                }
                cache.push_front(page_num);
                cached_page_loc.insert({page_num, cache.begin()});
            }
        }
};

class MRU{
        unordered_map<int, list<int>::iterator>cached_page_loc;
        int cache_cap;
    public: 
        list<int>cache;
        int page_fault_cnt;
        
        MRU(int cap){
            cache_cap=cap;
            page_fault_cnt=0;
        }

        void request(int page_num){
            if(cached_page_loc.find(page_num)!=cached_page_loc.end())
                cache.erase(cached_page_loc[page_num]);
            else{
                page_fault_cnt++;
                if(cache.size()==cache_cap){
                    cached_page_loc.erase(cache.front());
                    cache.pop_front();
                }
            }
            cache.push_front(page_num);
            cached_page_loc.insert({page_num, cache.begin()});
        }    
};

class LRU{
        unordered_map<int, list<int>::iterator>cached_page_loc;
        int cache_cap;
    public: 
        list<int>cache;
        int page_fault_cnt;

        LRU(int cap){
            cache_cap=cap;
            page_fault_cnt=0;
        }

        void request(int page_num){
            if(cached_page_loc.find(page_num)!=cached_page_loc.end())
                cache.erase(cached_page_loc[page_num]);
            else{
                page_fault_cnt++;
                if(cache.size()==cache_cap){
                    cached_page_loc.erase(cache.back());
                    cache.pop_back();
                }
            }
            cache.push_front(page_num); 
            cached_page_loc.insert({page_num, cache.begin()});
        }
};

void displayCache(list<int>&cache){
    for(const int &key:cache)
        cout<<key<<" -> ";
    cout<<"NULL\n";
}

void displayStats(int page_fault_cnt, int n){
    cout<<"\nPage Faults: \t"<<page_fault_cnt<<'\n';
    cout<<"Page Hits: \t"<<n-page_fault_cnt<<'\n';
    cout<<"Miss Ratio: \t"<<(float)page_fault_cnt/n<<'\n';
}

int main(){
    const int cache_size=3;
    vector<int>page_requests={3,2,1,4,0,2,3,5,0,2,1};
    int n=page_requests.size();

    cout<<"\n\n------OPT Cache------\n\n";
    OPT opt_cache(cache_size);
    for(int i=0;i<n;i++){
        opt_cache.request(page_requests[i], i, page_requests);
        displayCache(opt_cache.cache);
    }
    displayStats(opt_cache.page_fault_cnt, n);
  

    cout<<"\n\n------LRU Cache------\n\n";
    LRU lru_cache(cache_size);
    for(int i=0;i<n;i++){
        lru_cache.request(page_requests[i]);
        displayCache(lru_cache.cache);
    }
    displayStats(lru_cache.page_fault_cnt, n);


    cout<<"\n\n-------MRU Cache------\n\n";
    MRU mru_cache(cache_size);
    for(int i=0;i<n;i++){
        mru_cache.request(page_requests[i]);
        displayCache(mru_cache.cache);
    }
    displayStats(mru_cache.page_fault_cnt, n);
}   