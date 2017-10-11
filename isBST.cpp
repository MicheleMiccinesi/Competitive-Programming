bool isBSTrec(Node* root, int *mami){
    int mami_child[2];
    
    if( root->left )
        if( isBSTrec( root->left, mami_child ) )
            if( root->data < mami_child[1] ) return false;
            else mami[0] = mami_child[0];
        else return false;
    else mami[0] = root->data;
    if( root->right )
        if( isBSTrec( root->right, mami_child ) )
            if( root->data > mami_child[0] ) return false;
            else mami[1] = mami_child[1];
        else return false;
    else mami[1] = root->data;
    return true;
}   

bool isBST(Node* root) {
 int mami[2];
 if( root )
    return( isBSTrec( root, mami ) );
 else return true; 
}
