#include <vector>
#include <queue>
#include <algorithm>

bool isBipartite(int G[][MAX],int V)
{
    static std::vector<bool> groupMark;
    groupMark.reserve(15);
    groupMark.resize(V);
    static std::vector<bool> marked;
    marked.reserve(15);
    marked.resize(V);
    std::fill(marked.begin(),marked.end(),false);
    static std::queue<int> visiting;
    while( !visiting.empty() ) visiting.pop();

    static int i,j,k;
    for( i=0; i!=V; i++){
        if( !marked[i] ){
            groupMark[i]=0;
            marked[i]=1;
            for(j=0;j!=V;j++) if(G[i][j]) {
                if(marked[j]){ 
                    if(groupMark[i]==groupMark[j]) return false; 
                }
                else {
                    groupMark[j]=!groupMark[i];
                    marked[j]=1;
                    visiting.push(j);
                }
            }
            while( !visiting.empty() ){
                k=visiting.front();
                for(j=0;j!=V;j++) if(G[k][j]) {
                    if(marked[j]){ 
                        if(groupMark[k]==groupMark[j]) return false; 
                    }
                    else {
                        groupMark[j]=!groupMark[k];
                        marked[j]=1;
                        visiting.push(j);
                    }
                }
                visiting.pop();
            }
        }
    }
    return true;
}
