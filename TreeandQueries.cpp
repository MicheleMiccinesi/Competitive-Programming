#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>
#include <queue>

struct graphNode{
 int color;
 std::list<std::vector<graphNode>::iterator> links; 
 std::vector<int>::iterator prei,pref; 
};

struct dirGraph{
 dirGraph( int &n ){
  nodes = std::vector<graphNode> (n);
  tNodes = nodes.begin() -1;
 };
 typedef std::vector<graphNode>::iterator Node;
 std::vector<graphNode> nodes;
 Node tNodes;
 inline graphNode& operator[] (int i){ return tNodes[i]; };

 void addLink ( int& a, int& b ){
  tNodes[a].links.push_back( tNodes+b );
  tNodes[b].links.push_back( tNodes+a );
 };

 void makeTree( int root ){
  std::queue<Node> procNodes;
  procNodes.push( tNodes+root );
  while( !procNodes.empty() ){
   for( auto& x: procNodes.front()->links ) {
    x->links.remove( procNodes.front() );
    procNodes.push( x );
   }
   procNodes.pop();
  }
 };

 void writePreorder( int root, std::vector<int>& preorder ){ 
  pmPreorder( root + tNodes, preorder );
 };
private:
 void pmPreorder( Node root, std::vector<int>& preorder ){
  root->prei = preorder.end();
  preorder.push_back( root->color );
  for( auto &child: root->links )
   pmPreorder( child, preorder );
  root->pref = preorder.end(); 
 };
};

struct query{
 int v,k;
 int sol{0};
};

int main(){
 std::ios_base::sync_with_stdio( false );
 std::cin.tie( nullptr );
 std::cout.tie( nullptr );

 int n,m; //vertices, queries
 std::cin >> n >> m;

 std::vector<int> colorFreq(n);
 std::vector<int> colorOrder(n);
 for( auto x = colorOrder.begin(); x!=colorOrder.end(); *x = x-colorOrder.begin()+1, x++);
 auto tcolorFreq = colorFreq.begin()-1;

 dirGraph tree(n);
 int maxRep{0};
 for(auto &x: tree.nodes) std::cin >> x.color;
 std::sort( colorOrder.begin(), colorOrder.end(), [&tree](const int& a, const int& b){return tree[a].color < tree[b].color; } );
 int color = 1;
 auto xt = colorOrder.begin();
 while( xt != colorOrder.end()-1){
  if( ++tcolorFreq[color] > maxRep ) ++maxRep;
  if( tree[*xt].color == tree[*(xt+1)].color )   
   tree[*(xt++)].color = color;
  else tree[*(xt++)].color = color++;
 }
 if( ++tcolorFreq[color] > maxRep ) ++maxRep;
 tree[*xt].color = color;
 
 int i,j;
 while(--n) {
  std::cin >> i >> j;
  tree.addLink(i,j);
 }
 tree.makeTree( 1 );
 std::vector<int> preTree;
 preTree.reserve( tree.nodes.size() );
 tree.writePreorder( 1, preTree );

 std::vector<query> queries(m);
 for(auto &x: queries) std::cin >> x.v >> x.k;

 std::vector<std::vector<query>::iterator> order(m);
 for(auto x = order.begin(); x != order.end(); x++) *x = queries.begin() + (x-order.begin());

/* Mo */
/* queries with k > maxRep should not be in the processed query order */
 std::sort( order.begin(), order.end(), [](const auto& a, const auto &b){ return a->k < b->k; } );
 auto lastQuery = std::upper_bound( order.begin(), order.end(), maxRep, [](const auto &a, const auto &b){ return a < b->k; } );

 if( lastQuery - order.begin() ){
  std::sort( order.begin(), lastQuery, [&tree](const auto &a, const auto& b){ return tree[a->v].prei < tree[b->v].prei; } );
  int nn = tree[lastQuery[-1]->v].prei - tree[order[0]->v].prei + 1;
  int sqnn = sqrt( nn );
  int MoStep = sqnn;
  auto in = order.begin();
  auto fi = order.begin();
  auto preStart = tree[order[0]->v].prei;
  if( MoStep ){
   while( MoStep < nn ){
    while( tree[(*fi)->v].prei - preStart < MoStep )
     fi++;
    std::stable_sort( in, fi, [&tree](const auto& a, const auto& b){ return tree[a->v].pref < tree[b->v].pref; } );
    in = fi;
    MoStep += sqnn;
   }
  }
  if( fi != lastQuery )
   std::stable_sort( in, lastQuery, [&tree](const auto& a, const auto &b){ return tree[a->v].pref < tree[b->v].pref; } );   

  std::vector<int> colorsbyFreq(maxRep,0);
  auto tcolorsbyFreq = colorsbyFreq.begin()-1;
  std::fill(colorFreq.begin(), colorFreq.end(), 0);
  auto ri = tree[order[0]->v].prei;
  auto rf = tree[order[0]->v].prei;   

  for( auto x = order.begin(); x != lastQuery; x++ ){
   while( rf < tree[(*x)->v].pref )
    ++tcolorsbyFreq[ ++tcolorFreq[ *(rf++) ] ];
   while( ri > tree[(*x)->v].prei )
    ++tcolorsbyFreq[ ++tcolorFreq[ *(--ri) ] ];
   while( rf > tree[(*x)->v].pref )
    --tcolorsbyFreq[ tcolorFreq[ *(--rf) ]-- ];
   while( ri < tree[(*x)->v].prei )
    --tcolorsbyFreq[ tcolorFreq[ *(ri++) ]-- ];
   (*x)->sol = tcolorsbyFreq[ (*x)->k ];
  }
 }
 for( auto &x: queries ) std::cout << x.sol << '\n';
 std::cout << std::flush;
}
