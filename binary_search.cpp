int binary_search(const int arr[], int start, int end, int target) {
    if(start > end) return -1;
    
    int mid = start + (end-start)/2;
    if(arr[mid] > target) {
        return binary_search(arr, start, mid-1, target);
    }
    if(arr[mid] < target) {
        return binary_search(arr, mid+1, end, target);
    }
    
    return mid;
}
