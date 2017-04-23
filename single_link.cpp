typedef struct node_t node_t;
struct node_t
{
    int     m_value;
    node_t* m_next;
};

node_t* createNode(int value)
{
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode)
    {
        newNode->m_value = value;
        newNode->m_next = NULL;
    }
    return newNode;
}

void addNode(node_t** list, int value)
{
    if (!*list)
    {
        *list = createNode(value);
        return;
    }
    node_t* listPtr = *list;
    while (listPtr->m_next)
    {
        listPtr = listPtr->m_next;
    }
    listPtr->m_next = createNode(value);
}

void printList(node_t* list)
{
    while (list)
    {
        printf("%d\n", list->m_value);
        list = list->m_next;
    }
    printf("\n");
}

node_t* reverseList(node_t* head)
{
    node_t* cursor = NULL;
    node_t* next;
    while (head)
    {
        next = head->m_next;
        head->m_next = cursor;
        cursor = head;
        head = next;
    }
    return cursor;
}

//找到倒数第N个数据
node_t *findkthToLast(node_t *head, int k) {
    node_t *fast = head;
    node_t *slow = head;
    for(int i=0;i<k;++i) {
        fast = fast->m_next;
    }
    
    while(fast) {
        fast = fast->m_next;
        slow = slow->m_next;
    }
    
    return slow;
}

//找到链表的中间元素 奇数偶数情况
node_t *findMidItem(node_t *head) {
    node_t *fast = head;
    node_t *slow = head;
    
    while (fast != nullptr && fast->m_next != nullptr) {
        fast = fast ->m_next -> m_next;
        slow = slow -> m_next;
    }
    if(fast) {
        //偶数有两个中间数
        std::cout << "第二个是 ： " << slow->m_next->m_value << "\n";
    }
    
    return  slow;
}

//O(1) 删除一个节点，已知该节点是cur
void deleteItemO1(node_t *head, node_t *cursor) {
    node_t *next = cursor->m_next;
    
    if(next) {
        cursor->m_next = next->m_next;
        cursor->m_value = next->m_value;
        
        free(next);
    }
    else {
        //如果是最后一个元素
        node_t *_2th = findkthToLast(head, 2);
        _2th->m_next = nullptr;
        
        free(cursor);
    }
}

//两个不交叉的有序链表的合并
node_t *mergeTwolink(node_t *head1, node_t *head2) {
    node_t *head = (node_t *)malloc(sizeof(node_t));
    node_t *pre = head;
    node_t *curr = head->m_next;
    node_t *cur1 = head1;
    node_t *cur2 = head2;
    while(cur1->m_next != nullptr && cur2->m_next != nullptr) {
        if(cur1->m_next->m_value < cur2->m_next->m_value) {
            curr = (node_t *)malloc(sizeof(node_t));
            curr->m_value = cur1->m_next->m_value;
            curr->m_next = nullptr;
            
            cur1 = cur1->m_next;
        }
        else {
            curr = (node_t *)malloc(sizeof(node_t));
            curr->m_value = cur2->m_next->m_value;
            curr->m_next = nullptr;
            
            cur2 = cur2->m_next;
        }
        
        pre->m_next = curr;
        pre = pre->m_next;
    }
    
    while(cur1 -> m_next != nullptr) {
        curr = (node_t *)malloc(sizeof(node_t));
        curr->m_value = cur1->m_next->m_value;
        curr->m_next = nullptr;
        
        pre->m_next = curr;
        pre=pre->m_next;
    }
    
    while(cur2 ->m_next != nullptr) {
        curr = (node_t *)malloc(sizeof(node_t));
        curr->m_value = cur2->m_next->m_value;
        curr->m_next = nullptr;
        
        pre->m_next = curr;
        pre = pre->m_next;
    }
    
    return head;
}

//两个单链表相交，计算相交点
node_t *getIntersect(node_t *head1, node_t *head2) {
    node_t *cur1 = head1;
    node_t *cur2 = head2;
    
    int m = 0;
    int n = 0;
    
    while(cur1->m_next) {
        cur1 = cur1->m_next;
        m++;
    }
    while(cur2->m_next) {
        cur2 = cur2->m_next;
        n++;
    }
    
    cur1 = head1;
    cur2 = head2;
    if(m > n) {
        for(int i=0;i<m-n;++i) {
            cur1 = cur1->m_next;
        }
    }
    else if(m < n) {
        for(int i=0;i<n-m;++i) {
            cur2 = cur2->m_next;
        }
    }
    
    while(cur1->m_next) {
        if(cur1->m_value == cur2->m_value) {
            return cur1;
        }
        
        cur1 = cur1->m_next;
        cur2 = cur2->m_next;
    }
    
    return nullptr;
}

//两个交叉的有序链表的合并
node_t *mergeTwoIntersectLink(node_t *head1, node_t *head2) {
    node_t *head = (node_t *)malloc(sizeof(node_t));
    head->m_value = -1;
    head->m_next = nullptr;
    
    node_t *pre = head;
    
    node_t *cur = head;
    node_t *cur1 = head1;
    node_t *cur2 = head2;
    
    node_t *intersect = getIntersect(head1, head2);
    while(cur1->m_next != intersect && cur2->m_next != intersect) {
        if(cur1->m_next->m_value < cur2->m_next->m_value) {
            cur = (node_t *)malloc(sizeof(node_t));
            cur->m_value = cur1->m_next->m_value;
            cur->m_next = nullptr;
            
            cur1 = cur1->m_next;
        }
        else {
            cur = (node_t *)malloc(sizeof(node_t));
            cur->m_value = cur2->m_next->m_value;
            cur->m_next = nullptr;
            
            cur2 = cur2->m_next;
        }
        
        pre->m_next = cur;
        pre = pre->m_next;
    }
    
    if(cur1->m_next == intersect) {
        while(cur2->m_next) {
            cur = (node_t *)malloc(sizeof(node_t));
            cur->m_value = cur2->m_next->m_value;
            cur->m_next = nullptr;
            
            cur2 = cur2->m_next;
            
            pre->m_next = cur;
            pre=pre->m_next;
        }
    }
    else if(cur2->m_next == intersect) {
        while(cur1->m_next) {
            cur = (node_t *)malloc(sizeof(node_t)) ;
            cur->m_value = cur1->m_next->m_value;
            cur->m_next = nullptr;
            
            cur1  = cur1->m_next;
            
            pre->m_next = cur;
            pre=pre->m_next;
        }
    }
    
    return head;
}

//单链表交换任意两个元素
void swap(node_t *head, node_t *p, node_t *q) {
    node_t *cur1 = head;
    node_t *cur2 = head;
    while(cur1->m_next != p) {
        cur1 = cur1->m_next;
    }
    while(cur2->m_next != q) {
        cur2 = cur2->m_next;
    }
    
    std::swap(cur1, cur2);
}

//判断单链表是否有环？
bool hasCircle(node_t *head) {
    node_t *fast = head;
    node_t *slow = head;
    while(fast && fast->m_next) {
        fast = fast -> m_next ->m_next;
        slow = slow->m_next;
        
        if(fast == slow) {
            return true;
        }
    }
    
    return false;
}

//如何找到环的“起始”点？如何知道环的长度？
/*
 当 fast 与 slow 相遇时，slow 肯定没有遍历完链表，而 fast 已经在环内循环了 n 圈 (1 ≤ n)。假 设 slow 走了 s 步，则 fast 走了 2s 步(fast 步数还等于 s 加上在环上多转的 n 圈)，设环长为 r，则:
 2s = s+nr s = nr
 设整个链表长 L，环入口点与相遇点距离为 a，起点到环入口点的距离为 x，则 x+a = nr=(n–1)r+r=(n−1)r+L−x
 x = (n−1)r+(L–x–a)
 L–x–a 为相遇点到环入口点的距离，由此可知，从链表头到环入口点等于 n − 1 圈内环 + 相遇 点到环入口点，于是我们可以从 head 开始另设一个指针 slow2，两个慢指针每次前进一步，它俩 一定会在环入口点相遇。
 */
node_t *detectCycle(node_t *head) {
    node_t *slow = head;
    node_t *fast = head;
    while(fast && fast->m_next) {
        fast = fast->m_next->m_next;
        slow = slow->m_next;
        if(slow == fast) {
            node_t *slow2 = head;
            while(slow2 != slow) {
                slow2 = slow2->m_next;
                slow = slow -> m_next;
            }
            
            return slow2;
        }
    }
    
    return nullptr;
}

//判断两个单链表是否相交
//A头 接到 B尾， 从A头开始遍历，能回到A头，则表示又环，是相交的
bool hasInterect(node_t *head1, node_t *head2) {
    bool has = false;
    node_t *cur1 = head1;
    node_t *cur2 = head2;
    while(cur1->m_next) {
        cur1 = cur1->m_next;
    }
    cur1->m_next = head2;// 链接
    while(cur2->m_next) {
        if(cur2->m_next == head2) {
            has = true;
            break;
        }
        
        cur2  = cur2->m_next;
    }
    
    cur1->m_next = nullptr;
    return has;
}

//删除单链表中重复的元素
node_t *deleteDupItem(node_t *head) {
    std::unordered_map<int, int> map;
    
    node_t *p = head;
    while(p) {
        map[p->m_value] ++;
        p = p->m_next;
    }
    
    p = head;
    node_t *next = head->m_next;
    while(p && next) {
        if(map[next->m_value] > 1) {
            p ->m_next = next->m_next;
            next = next->m_next;
        }
        else {
            p = p->m_next;
            next = next->m_next;
        }
    }
    
    //head节点单独处理
    if(map[head->m_value] > 1) {
        head = head->m_next;
    }
    
    return head;
}

//链表有环，如何判断相交
//如果有环且两个链表相交，则两个链表都有共同一个环，即环上的任意一个节点都存在于两个链表上
bool isIntersectLoop(node_t *head1, node_t *head2) {
    node_t *cur1;
    node_t *cur2;
    if(!hasCircle(head1, cur1))
        return false;
    if(!hasCircle(head2, cur2))
        return false;
    
    node_t *t = cur2->m_next;
    while(t != cur2) {
        if(t == cur1) {
            return true;
        }
        
        t = t->m_next;
    }
    
    return false;
}

//二叉排序树转换成双向链表
todo
/*
 遍历的时候，不要在while循环中head=head.Next;这样会改变原先的数据结构。我们要这么写：Link curr=head;然后curr=curr.Next;
 有时我们需要临时把环切开，有时我们需要临时把单链表首尾相连成一个环。
 究竟是玩curr还是curr.Next，根据不同题目而各有用武之地，没有定论，不必强求。
 */
