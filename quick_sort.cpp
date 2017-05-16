int partition(int arr[], int s, int e) {
    int x = arr[e];
    int i = s-1;
    
    for(int j=s; j<e;++j) {
        if(arr[j] <= x) {
            i = i+1;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[e]);
    
    return i+1;
}

int random_index(int s, int e) {
    int w = e-s;
    if(w == 0) return 0;
    
    srand((unsigned) time(NULL));
    return rand() % w;
}

int random_partition(int arr[], int s, int e) {
    int i = random_index(0, 7);
    std::swap(arr[i], arr[e]);
    return partition(arr, s, e);
}

void quick_sort(int arr[], int s, int e) {
    if(s < e) {
        int q = random_partition(arr, s, e);
        
        quick_sort(arr, s, q-1);
        quick_sort(arr, q+1, e);
    }
}
