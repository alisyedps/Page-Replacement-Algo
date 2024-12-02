#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Page_Replacement{
    public:
        int capacity;
        vector<int> memory;
    Page_Replacement(int capacity){
        this->capacity=capacity;
    }
};

void FIFO_Algo(const vector<int> pages, int capacity){
    Page_Replacement FIFO(capacity);
    int pageFaults=0, pageHits=0;
    for (int page : pages) {
            if (find(FIFO.memory.begin(), FIFO.memory.end(), page) == FIFO.memory.end()) {
                if (FIFO.memory.size() == capacity) {
                    FIFO.memory.erase(FIFO.memory.begin()); 
                }
                FIFO.memory.push_back(page);
                pageFaults++;
                for(int mem_pages : FIFO.memory){
                    cout << mem_pages << " ";
                }
                cout << endl;
            }
            else{
                pageHits++;
                cout << endl;
            }
    }
    cout << "Page Faults : " << pageFaults << endl;
    cout << "Page Hits : " << pageHits << endl;
}

void LRU_Algo(const vector<int> pages, int capacity){
    Page_Replacement LRU(capacity);
    int pageFaults=0, pageHits=0;
    for(int i=0 ; i<pages.size() ; i++){
        bool flag=true;
        if (find(LRU.memory.begin(), LRU.memory.end(), pages[i]) == LRU.memory.end()) {
            if (LRU.memory.size() == capacity) {
                int min=999;
                for(int memory_page : LRU.memory){
                    // cout << "Memory Page : " << memory_page << endl;
                    auto index=find(pages.rbegin() + (pages.size() - 1 - i), pages.rbegin() + (pages.size() - 1), memory_page);
                    // cout << "Min : " << min << endl;
                    // cout << "Index : " << distance(pages.begin(),index) << endl;
                    if(pages[pages.rend() - index - 1]==memory_page){
                        if(pages.rend() - index - 1<min){
                            // cout << "Index is less then min so swapping\n";
                            min=pages.rend() - index - 1;
                        }
                    }
                    else{
                        auto temp=find(LRU.memory.begin(), LRU.memory.end(), memory_page);
                        // int mem_page_change=distance(LRU.memory.begin(), temp);
                        LRU.memory.erase(temp);
                        flag=false;
                        break;
                    }
                }
                if(flag){
                    auto temp=find(LRU.memory.begin(), LRU.memory.end(), pages[min]);
                    // int mem_page_change=distance(LRU.memory.begin(), temp);
                    LRU.memory.erase(temp);
                }
            }
            LRU.memory.push_back(pages[i]);
            pageFaults++;
            for(int mem_pages : LRU.memory){
                    cout << mem_pages << " ";
                }
                cout << endl;
        }
        else{
            pageHits++;
            cout << endl;
        }
    }
    cout << "Page Faults : " << pageFaults << endl;
    cout << "Page Hits : " << pageHits << endl;
}

void Optimal_Algo(const vector<int> pages, int capacity){
    Page_Replacement Optimal(capacity);
    int pageFaults=0, pageHits=0;
    for(int i=0 ; i<pages.size() ; i++){
        bool flag=true;
        if (find(Optimal.memory.begin(), Optimal.memory.end(), pages[i]) == Optimal.memory.end()) {
            if (Optimal.memory.size() == capacity) {
                int max=-999;
                for(int memory_page : Optimal.memory){
                    // cout << "Memory Page : " << memory_page << endl;
                    auto index=find(pages.begin()+i, pages.end(), memory_page);
                    // cout << "Min : " << min << endl;
                    // cout << "Index : " << distance(pages.begin(),index) << endl;
                    if(pages[distance(pages.begin(),index)]==memory_page){
                        if(distance(pages.begin(),index)>max){
                            // cout << "Index is less then min so swapping\n";
                            max=distance(pages.begin(),index);
                        }
                    }
                    else{
                        // cout << "Hello im in else\n";
                        auto temp=find(Optimal.memory.begin(), Optimal.memory.end(), memory_page);
                        // int mem_page_change=distance(Optimal.memory.begin(), temp);
                        Optimal.memory.erase(temp);
                        flag=false;
                        break;
                    }
                }
                if(flag){
                    auto temp=find(Optimal.memory.begin(), Optimal.memory.end(), pages[max]);
                    // int mem_page_change=distance(Optimal.memory.begin(), temp);
                    Optimal.memory.erase(temp);
                }
            }
            Optimal.memory.push_back(pages[i]);
            pageFaults++;
            for(int mem_pages : Optimal.memory){
                    cout << mem_pages << " ";
                }
                cout << endl;
        }
        else{
            pageHits++;
            cout << endl;
        }
        // cout << "Hello\n";
    }
    cout << "Page Faults : " << pageFaults << endl;
    cout << "Page Hits : " << pageHits << endl;
}

int main(){
    vector<int> pages = {2,6,9,2,4,2,1,7,3,0,5,2,1,2,9,5,7,3,8,5};
    
    cout << "FIFO Algorithm : \n";
    FIFO_Algo(pages,3);
    cout << "LRU Algorithm : \n";
    LRU_Algo(pages,3);
    cout << "Optimal Algorithm : \n";
    Optimal_Algo(pages,3);
}
