//bst search : recursion
node_t *bst_search(node_t *root, int x) {
    if(root == nullptr || root->c == x) {
        return root;
    }
    
    if(x < root->c) {
        return bst_search(root->lchild, x);
    }
    else {
        return bst_search(root->rchild, x);
    }
}
//bst search : iterator
node_t *bst_search_iterator(node_t *root, int x) {
    while(root && root->c != x) {
        if(x < root->c)
            root = root->lchild;
        else
            root = root->rchild;
    }
    
    return root;
}
//bst : max
node_t *max(node_t *root) {
    if(root == nullptr) return nullptr;
    
    while(root->rchild) {
        root = root->rchild;
    }
    
    return root;
}
//bst : min
node_t *min(node_t *root) {
    if(root == nullptr) return nullptr;
    
    while (root->lchild) {
        root = root -> lchild;
    }
    
    return root;
}

//bst : insert
node_t *insert(node_t *root, int key) {
    if(root == nullptr) return new node_t(key);
    
    if(key < root->c) {
        root->lchild = insert(root->lchild, key);
    }
    else
        root->rchild = insert(root->rchild, key);
    
    return root;
}
//bst : delete
node_t *deleteNode(node_t *root, int key) {
    if(root == nullptr) return root;
    
    if(key < root->c)
        root->lchild = deleteNode(root->lchild, key);
    else if(key > root->c)
        root->rchild = deleteNode(root->rchild, key);
    else {
        //node with only one or no child
        if(root->lchild == nullptr) {
            node_t *t = root->rchild;
            free(root);
            return t;
        }
        else if(root->rchild == nullptr) {
            node_t *t = root->lchild;
            free(root);
            return t;
        }
        
        node_t *t = min(root->rchild);
        root->c = t -> c;
        
        root->rchild = deleteNode(root->rchild, t->c);
    }
    
    return root;
}
