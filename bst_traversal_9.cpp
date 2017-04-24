typedef struct node_t node_t;
struct node_t {
    int c;
    
    node_t *lchild;
    node_t *rchild;
    
    node_t(int i) : c(i), lchild(nullptr), rchild(nullptr) {}
};

//pre order recursion
void pre_order(node_t *root) {
    if(root) {
        std::cout << root->c << "\n";
        
        pre_order(root->lchild);
        pre_order(root->rchild);
    }
}
//pre order iterator
void pre_order_iterator(node_t *root) {
    std::stack<node_t *> s;
    node_t *p = root;
    
    while(p || !s.empty()) {
        while(p) {
            std::cout << p->c << "\n";
            
            s.push(p);
            p = p->lchild;
        }
        
        if(!s.empty()) {
            p = s.top();
            s.pop();
            
            p = p->rchild;
        }
    }
}

//in order recursion
void in_order(node_t *root) {
    if(root) {
        in_order(root->lchild);
        
        std::cout << root->c << "\n";
        
        in_order(root->rchild);
    }
}

//in order iterator
void in_order_iterator(node_t *root) {
    std::stack<node_t *> s;
    node_t *p = root;
    while(p || !s.empty()) {
        while(p) {
            s.push(p);
            p = p->lchild;
        }
        
        if(!s.empty()) {
            p = s.top();
            std::cout << p->c << "\n";
            
            s.pop();
            p = p->rchild;
        }
    }
}

//post order recursion
void post_order(node_t *root) {
    if(root) {
        post_order(root->lchild);
        post_order(root->rchild);
        
        std::cout << root->c << "\n";
    }
}
//post order iterator : one stack
void post_order_iterator_stack(node_t *root) {
    std::stack<node_t *> s;
    do {
        while(root) {
            if(root->rchild) {
                s.push(root->rchild);
            }
            s.push(root);
            
            root = root->lchild;
        }
        
        root = s.top();
        s.pop();
        
        if(root->rchild && !s.empty() && s.top() == root->rchild) {
            s.pop();
            s.push(root);
            root = root->rchild;
        }
        else {
            std::cout << root->c << "\n";
            root=nullptr;
        }
        
    }while(!s.empty());
}

//post order iterator : two stack
void post_order_iterator(node_t *root) {
    std::stack<node_t *> s1,s2;
    s1.push(root);
    
    while(!s1.empty()) {
        node_t *p = s1.top();
        s1.pop();
        
        s2.push(p);
        
        if(p->lchild) {
            s1.push(p->lchild);
        }
        if(p->rchild) {
            s1.push(p->rchild);
        }
    }
    
    while(!s2.empty()) {
        std::cout << s2.top()->c << "\n";
        s2.pop();
    }
}

//morris traversal : pre order
void pre_order_morris(node_t *root) {
    node_t *pre=nullptr;
    node_t *cur=root;
    while(cur) {
        if(cur->lchild == nullptr) {
            std::cout << cur->c << "\n";
            
            cur = cur->rchild;
        }
        else {
            pre = cur->lchild;
            while(pre->rchild && pre->rchild != cur) {
                pre = pre->rchild;
            }
            
            if(pre->rchild == nullptr) {
                std::cout << cur->c << "\n";
                
                pre -> rchild = cur;
                cur = cur->lchild;
            }
            else {
                pre->rchild = nullptr;
                cur = cur->rchild;
            }
        }
    }
}
//morris traversal : in order
void in_order_morris(node_t *root) {
    node_t *cur = root;
    node_t *pre = nullptr;
    
    while(cur) {
        if(cur->lchild == nullptr) {
            std::cout << cur->c << "\n";
            
            cur = cur->rchild;
        }
        else {
            pre = cur->lchild;
            while(pre->rchild && pre->rchild != cur) {
                pre = pre->rchild;
            }
            
            if(pre->rchild == nullptr) {
                pre->rchild = cur;
                cur = cur->lchild;
            }
            else {
                pre->rchild = nullptr;
                std::cout << cur->c << "\n";
                cur = cur->rchild;
            }
        }
    }
}
void reverse(node_t *from, node_t *to) {
    node_t *x, *y, *z;
    if(from == to) return;
    
    x = from;
    y = from->rchild;
    while(x != to) {
        z = y->rchild;
        y->rchild = x;
        x = y;
        y = z;
    }
}
void print_reverse(node_t *from, node_t *to) {
    node_t *p;
    reverse(from, to);
    p = to;
    
    while(1) {
        std::cout << p->c << "\n";
        
        if(p == from)
            break;
        
        p = p->rchild;
    }
    
    reverse(to, from);
}
//morris traversal : post order
void post_order_morris(node_t *root) {
    node_t *dump = (node_t *)malloc(sizeof(node_t));
    node_t *p, *temp;
    dump->lchild = root;
    p = dump;
    while(p) {
        if(p->lchild == nullptr) {
            p = p->rchild;
        }
        else {
            temp = p->lchild;
            while(temp->rchild && temp->rchild != p) {
                temp = temp->rchild;
            }
            
            if(temp->rchild == nullptr) {
                temp->rchild = p;
                p = p->lchild;
            }
            else {
                print_reverse(p->lchild, temp);
                
                temp->rchild = nullptr;
                p = p->rchild;
            }
        }
    }
    
    free(dump);
}
