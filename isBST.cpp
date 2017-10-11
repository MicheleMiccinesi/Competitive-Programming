bool isBSTrec(Node* root, int *mami){
    int left[2], right[2];
    
    if( root->left )
        if( isBSTrec( root->left, left ) )
            if( root->data < left[1] ) return false;
            else mami[0] = left[0];
        else return false;
    else mami[0] = root->data;
    if( root->right )
        if( isBSTrec( root->right, right ) )
            if( root->data > right[0] ) return false;
            else mami[1] = right[1];
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
