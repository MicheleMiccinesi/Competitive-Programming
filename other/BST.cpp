/* various BSTs with a unique interface */
/* Simple, just to understand the moves, so unrefined... */
/* By now I've only been implementing the AVL balancing with */
/* order statistics (is this the name?) which is useful in */
/* certain problems such as the construction of a permutation */
/* with given lexycographic order */

#include <iostream>
#include <queue>		//for dynamic ~BST destructor

template <class V, class CMP>
struct AVL_order_stat{
	struct node{
		node() {}
		node( V& vv ): v(vv){}
		V v;			//v: value stored in the node
		int d, h;		//d: dimension, h: height
		node *c[2], *p;	//c: children, p: parent
	};
	//operation: 1=emplace, -1=erase, 
	static node *update(node * const&_n, int operation){
		int h[2];
		int d[2];		//for order statistics, not for balancing!
		int ch[2];
		if( _n==nullptr )
			return nullptr;

		for( node *n=_n; ; ){
			for( char i=0; i!=2; ++i ){
				if(n->c[i]!=nullptr){
					h[i]=n->c[i]->h;
					d[i]=n->c[i]->d;
				} else {
					h[i]=-1;
					d[i]=0;
				}
			}

			char i=2;
			if( h[0]>h[1]+1 ) 
				i=0;
			else if( h[1]>h[0]+1 )
				i=1;

			if( i!=2 ){
				ch[0] = n->c[i]->c[0]!=nullptr?n->c[i]->c[0]->h:-1;
				ch[1] = n->c[i]->c[1]!=nullptr?n->c[i]->c[1]->h:-1;
				char j = ch[0]>ch[1]?0:1;

				if( i==j ){		//1 rotation
					j=i^1;
					node *a{n}, *b{n->c[i]}, *p{n->p};

					b->p=a->p;
					if( p!=nullptr )
						p->c[p->c[0]==a?0:1]=b;
					
					if( (a->c[i]=b->c[j])!=nullptr )
						a->c[i]->p=a;
					b->c[j]=a;
					a->p=b;

					a->h = 1+std::max((a->c[0]!=nullptr?a->c[0]->h:-1),(a->c[1]!=nullptr?a->c[1]->h:-1));
					a->d = 1+(a->c[0]!=nullptr?a->c[0]->d:0)+(a->c[1]!=nullptr?a->c[1]->d:0);

					b->h = 1+std::max((b->c[0]!=nullptr?b->c[0]->h:-1),(b->c[1]!=nullptr?b->c[1]->h:-1));
					b->d = 1+(b->c[0]!=nullptr?b->c[0]->d:0)+(b->c[1]!=nullptr?b->c[1]->d:0);

					n=b;
					if( operation==1 ){
						while(n->p!=nullptr)
							++(n=n->p)->d;
						return n;
					}
				} else {			//2 rotations
					node *a{n}, *b{n->c[i]}, *c{n->c[i]->c[j]}, *p{a->p};
					b->c[j]=c->c[i];
					c->c[i]=b;
					b->p=c;
					a->c[i]=c->c[j];
					c->c[j]=a;
					c->p=a->p;
					if( p!=nullptr )
						p->c[a==p->c[0]?0:1]=c;
					a->p=c;

					//for operation==1 we could have simpler updates but...
					b->d=1+(b->c[0]!=nullptr?b->c[0]->d:0)+(b->c[1]!=nullptr?b->c[1]->d:0);
					b->h=1+std::max((b->c[0]!=nullptr?b->c[0]->h:-1),(b->c[1]!=nullptr?b->c[1]->h:-1));
					a->d=1+(a->c[0]!=nullptr?a->c[0]->d:0)+(a->c[1]!=nullptr?a->c[1]->d:0);
					a->h=1+std::max((a->c[0]!=nullptr?a->c[0]->h:-1),(a->c[1]!=nullptr?a->c[1]->h:-1));
					c->d=1+a->d+b->d;
					c->h=1+std::max(a->h, b->h);
					n=c;
					if( operation==1 ){
						while(n->p!=nullptr)
							++(n=n->p)->d;
						return n;
					}
				}
			} else{
				n->h=1+std::max(h[0], h[1]);
				n->d=1+d[0]+d[1];
			}
			if( n->p==nullptr )
				return n;
			n=n->p;
		}
	}
	static node const *at_index(node* root, int i){
		if( root==nullptr )
			return nullptr;
		if( i>=root->d || i<0 )
			return nullptr;		//TODO: up traversal for i negative or bigger than root->d

		while(1){
			int c = root->c[0]!=nullptr?root->c[0]->d:0;
			if( c<i ){
					i-=c+1;
					root=root->c[1];
			} else if( c==i ){
					break;
			}
			else{
				root=root->c[0];
			}
		}
		return root;
	}

	static int get_index(node* root, V &v, const CMP &cmp){
		if( root==nullptr )
			return -1;

		int i{0};
		while(1){
			if(cmp(root->v, v)){
				i+=1+(root->c[0]!=nullptr?root->c[0]->d:0);
				if((root=root->c[1])==nullptr)
					return i;
			}else if(cmp(v, root->v)){
				if((root=root->c[0])==nullptr)
					return i;
			}
			else {
				i+=(root->c[0]!=nullptr?root->c[0]->d:0);
				return i;
			}
		}			
	}
};

//I'm putting node structure inside AUGMENT class..
template <class V, template <class _V, class _CMP>class AUGMENT, template <class _VV> class CMP>
struct BST{
	typedef typename AUGMENT<V, CMP<V>>::node NODE;

	BST(): _root(nullptr), _size{0}{};
	void emplace( V& v ){
		if( _root==nullptr ){
			_root = new NODE(v);
			_root->p=_root->c[0]=_root->c[1]=nullptr;
			update(_root, 1);
		} else {
			char i;
			for( auto *n=_root;;){		//n: the node which we are traversing
				i = cmp(n->v, v);
				if( n->c[i]==nullptr ){
					auto &nn=n->c[i];
					nn=new NODE(v);
					nn->p=n;
					nn->c[0]=n->c[i]->c[1]=nullptr;
					_root=update(nn, 1);
					break;
				} else 
					n = n->c[i];
			} 
		}
		++_size;
	}
	void emplace( V&& v ){
		if( _root==nullptr ){
			_root = new NODE(std::forward(v));
			_root->p=_root->c[0]=_root->c[1]=nullptr;
			update(_root, 1);
		} else {
			char i;
			for( auto *n=_root;;){		//n: the node which we are traversing
				i = cmp(n->v, v);
				if( n->c[i]==nullptr ){
					auto &nn=n->c[i];
					nn=new NODE(std::forward(v));
					nn->p=n;
					nn->c[0]=nn->c[1]=nullptr;
					_root=update(nn, 1);
					break;
				} else 
					n = n->c[i];
			} 
		}
		++_size;
	}
	void erase( V& v ){
		NODE *n{_get_node(v)};
		if( n==nullptr )
			return;

		NODE *p=n->p;
		char cs=(n->c[0]!=nullptr?1:0)+(n->c[1]!=nullptr?2:0);
		switch(cs){
		case 0:
			p->c[p->c[0]==n?0:1]=nullptr;
			delete(n);
			_root=update(p, -1);
			break;
		case 1:{
			NODE *c=n->c[0];
			c->p=p;
			if( p!=nullptr )
				p->c[n==p->c[0]?0:1]=c;
			delete(n);
			_root=update(p, -1);
			break;
		}
		case 2:{
			NODE *c=n->c[1];
			c->p=p;
			if( p!=nullptr )
				p->c[n==p->c[0]?0:1]=c;
			delete(n);
			_root=update(p, -1);
			break;
		}
		case 3:
			if( n->c[1]->c[0]==nullptr ){
				n->c[0]->p=n->c[1];
				n->c[1]->c[0]=n->c[0];
				n->c[1]->p=p;
				if( p!=nullptr )
					p->c[n==p->c[0]?0:1]=n->c[1];
				_root=update(n->c[1], -1);
				delete(n);
				break;
			}
			if( n->c[0]->c[1]==nullptr ){
				n->c[1]->p=n->c[0];
				n->c[0]->c[1]=n->c[1];
				n->c[0]->p=p;
				if( p!=nullptr )
					p->c[n==p->c[0]?0:1]=n->c[0];
				_root=update(n->c[0], -1);
				delete(n);
				break;
			}

			NODE *m = n->c[1];
			while( m->c[0]!=nullptr )
				m=m->c[0];
			NODE *pm=m->p;

			if( p!=nullptr )
				p->c[n==p->c[0]?0:1]=m;
			m->p=p;
			pm->c[0]=m->c[1];
			if(m->c[1]!=nullptr)
				m->c[1]->p=pm;
			m->c[1]=n->c[1];
			m->c[0]=n->c[0];
			m->c[1]->p=m;
			m->c[0]->p=m;
			delete(n);
			_root=update(pm, -1);
			break;
		}
		--_size;
	}
	int const &size(){
		return _size;
	}
	bool empty(){
		return _size==0;
	}
	NODE const *operator[](int i){
		return at_index(_root, i);
	}
	int operator()(V& value){
		return get_index(_root, value, cmp);
	}
	NODE const *next(NODE *const&n){
		return next(n);
	}
	NODE const *prev(NODE *const&n){
		return prev(n);
	}
	NODE const *lower_bound(){}
	bool find(){
		return _get_node!=nullptr;
	}
	void print_in_order(NODE const *n){
		if( n==nullptr )
			return;
		print_in_order(n->c[0]);
		std::cout << n->v <<  ' ';
		print_in_order(n->c[1]);
	}
	NODE const *get_root(){
		return _root;
	}
	~BST(){
		std::queue<NODE *> Q;
		Q.emplace(_root);
		NODE *n;
		while(!Q.empty()){
			n=Q.front(); 
			Q.pop();
			if( n->c[0]!=nullptr )
				Q.emplace(n->c[0]);
			if( n->c[1]!=nullptr )
				Q.emplace(n->c[1]);
			delete(n);
		}
	}
protected:
	constexpr static auto update = AUGMENT<V, CMP<V>>::update;
	static constexpr auto at_index = AUGMENT<V, CMP<V>>::at_index;
	static constexpr auto get_index = AUGMENT<V, CMP<V>>::get_index;
	NODE *_root;
	CMP<V> cmp;
	int _size;
	NODE *_get_node( const V& v ){
		for( NODE *n = _root; n!=nullptr; n = cmp(n->v, v)?n->c[1]:n->c[0] )
			if( n->v==v )
				return n;
		return nullptr;
	}
	NODE *_next(NODE *n){
		return _advance(n, true);
	}
	NODE *_prev(NODE *n){
		return _advance(n, false);
	}
	NODE *& _advance(NODE *&n, bool go_next){
		if( n==nullptr )
			return n;

		char nxt, prv;
		if(go_next){
			nxt=1;
			prv=0;
		} else{
			nxt=0;
			prv=1;
		}

		if( n->c[nxt]==nullptr ){
			while( n->p!=nullptr ){
				if(n->p->c[prv]==n)
					return n=n->p;
				n=n->p;
			}
			return n;
		} else {
			n=n->c[nxt];
			while( n->c[prv]!=nullptr )
				n=n->c[prv];
			return n;
		}
	}
};

int main(){
	BST<int, AVL_order_stat, std::less> Tree;  
	int v[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	for( int i=9; i!=-1; --i )
		Tree.emplace(v[i]);

	return 0;
}
