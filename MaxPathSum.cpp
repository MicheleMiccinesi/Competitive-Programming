//Disclaimer: this solution was suggested in class by the professor

int maxPathSum_(struct Node *root, int& max){
    if(!root) return 0;
    int maxL = maxPathSum_(root->left, max);
    int maxR = maxPathSum_(root->right, max);
    if(maxR + root->data + maxL > max) max = maxL + root->data + maxR;
    if(maxR > maxL) return maxR + root->data;
    return maxL + root->data;
}

int maxPathSum(struct Node *root)
{
 static int max_path_sum;
 max_path_sum = 0;
 maxPathSum_(root, max_path_sum);
 return max_path_sum;
}
