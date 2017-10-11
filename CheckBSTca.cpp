template <typename T>
struct ciclarray{
    ciclarray(unsigned int n):
    in_order{true}, lenght{n}, i{0}{
        array = new T* [n];
    };
    bool const& put(T* element){
        array[ i % lenght ] = element;
        if( i ) if( *array[ i % lenght ] < *array[ (i-1) % lenght ]) in_order = false;
        ++i;
        return in_order;
    };
    void reset(){ i = 0; in_order = true;}
    bool const& is_ordered() { return in_order; };
    ~ciclarray(){ delete[] array; };
private:
    unsigned int i;
    unsigned int lenght;
    bool in_order;
    T **array;
};

bool isBST_(Node* root, ciclarray<int>& check) {
    if( !root ) return true;
    if( !isBST_( root->left, check) ) return false;
    if( !check.put( &root->data ) ) return false;
    return isBST_( root->right, check );
}

bool isBST(Node* root){
    static ciclarray<int> check(2);
    bool yesitis = isBST_(root, check);
    check.reset();
    return yesitis;
}
