//AVL
int height(node_t *n) {
    if(n == nullptr) return 0;
    return n->height;
}
int Max(int a, int b) {
    return a > b ? a : b;
}
node_t *new_node(int key) {
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->c = key;
    node->lchild = nullptr;
    node->rchild = nullptr;
    node->height = 1;
    return node;
}
node_t *rightRotate(node_t *y) {
    node_t *x = y->lchild;
    node_t *t2 = x->rchild;
    
    x->rchild = y;
    y->lchild = t2;
    
    y->height = Max(height(y->lchild), height(y->rchild)) + 1;
    x->height = Max(height(x->lchild), height(x->rchild)) + 1;
    
    return x;
}
node_t *leftRotate(node_t *x) {
    node_t *y = x->rchild;
    node_t *t2 = y->lchild;
    
    y->lchild = x;
    x->rchild = t2;
    
    x->height = Max(height(x->lchild), height(x->rchild)) + 1;
    y->height = Max(height(y->lchild), height(y->rchild)) + 1;
    
    return y;
}
int getBalance(node_t *n) {
    if(n == nullptr) return  0;
    
    return height(n->lchild) - height(n->rchild);
}
node_t *insert(node_t *node, int key) {
    if(node == nullptr) return new_node(key);
    
    if(key < node->c)
        node->lchild = insert(node->lchild, key);
    else if(key > node->c)
        node->rchild = insert(node->rchild, key);
    else
        return node;
    
    //update height
    node->height = Max(height(node->lchild), height(node->rchild)) + 1;
    
    //get balance
    int balance = getBalance(node);
    if(balance > 1 && key < node->lchild->c) { // left left case
        return rightRotate(node);
    }
    if(balance < -1 && key > node->rchild->c) { //right right case
        return leftRotate(node);
    }
    if(balance > 1 && key > node->lchild->c) { // left right case
        node->lchild = leftRotate(node->lchild);
        return rightRotate(node);
    }
    if(balance < -1 && key < node->rchild->c) { // right left case
        node->rchild = rightRotate(node->rchild);
        return leftRotate(node);
    }
    
    return node;
}

node_t *minValueNode(node_t *node) {
    node_t *current = node;
    while(current->lchild) {
        current = current->lchild;
    }
    
    return current;
}

node_t *DeleteNode(node_t *root, int key) {
    if(root == nullptr) return root;
    
    if(key < root->c)
        root->lchild = DeleteNode(root->lchild, key);
    else if(key > root->c)
        root->rchild = DeleteNode(root->rchild, key);
    else {
        if(root->lchild == nullptr || root->rchild == nullptr) {
            node_t *t = root->lchild ? root->lchild : root->rchild;
            
            if(t == nullptr) {
                t = root;
                root = nullptr;
            }
            else {
                *root = *t;
            }
            free(t);
        }
        else {
            node_t *t = minValueNode(root->rchild);
            root->c = t->c;
            root->rchild = DeleteNode(root->rchild, t->c);
        }
    }
    
    if(root == nullptr) return root;
    
    root->height = Max(height(root->lchild), height(root->rchild)) + 1;
    
    int balance = getBalance(root);
    if(balance > 1 && getBalance(root->lchild) >= 0) { //left left case
        return rightRotate(root);
    }
    if(balance > 1 && getBalance(root->lchild) < 0) { // left right case
        root->lchild = leftRotate(root->lchild);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->rchild) <= 0) {// right right case
        return leftRotate(root);
    }
    if(balance < -1 && getBalance(root->rchild) > 0) { // right left case
        root->rchild = rightRotate(root->rchild);
        return leftRotate(root);
    }
    
    return root;
}
