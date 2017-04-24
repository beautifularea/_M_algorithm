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
