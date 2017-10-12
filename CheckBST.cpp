#include <limits>
/* In the specific case we wouldn't need limits because we get only strictly positive integers! Just set to 0... */
bool isBST_(Node *root, int& last_seen) {
    if( !root ) return true;
    if( !isBST_( root->left, last_seen ) ) return false;
    if( root->data < last_seen ) return false;
    last_seen = root->data;
    return isBST_( root->right, last_seen );
}

bool isBST(Node* root){
    static int last_seen;
    last_seen = std::numeric_limits<int>::min();
    return isBST_(root, last_seen);    
}
