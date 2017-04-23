int Josephus_problem(int n, int m) {
    if(n < 1 || m < 1) return -1;
    
    std::vector<int> list;
    for(int i=0;i<n;++i) {
        list.push_back(i);
    }
    
    int idx = 0;
    while(list.size() > 1) {
        for(int i=1;i<m;++i)
            idx = (idx + 1) % list.size();
        
        list.erase(list.begin()+idx);
    }
    
    return list.front();
}
