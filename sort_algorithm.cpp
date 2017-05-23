/*
 插入排序
 */
/*
最坏时间复杂度	O(n^{2})
最优时间复杂度	O(n)
平均时间复杂度	O(n^{2})
空间复杂度	总共  O(n) ，需要辅助空间 O(1)
*/
//1 直接插入
void insert_sort(int arr[], int length) {
    int i, j, key;
    for(i=1;i<length;i++) {
        key = arr[i];
        j=i-1;
        
        while(j>=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j=j-1;
        }
        arr[j+1] = key;
    }
}
//2 希尔排序
/*
最坏时间复杂度	根据步长序列的不同而不同。已知最好的： O(nlog^2 n)
最优时间复杂度	O(n)
平均时间复杂度	根据步长序列的不同而不同。
空间复杂度	O(n)
*/
void shell_sort(int arr[], int length) {
    int gap, i, j;
    int temp;
    for(gap=length>>1;gap>0;gap>>=1) {
        for(i=gap;i<length;i++) {
            temp = arr[i];
            
            for(j=i-gap;j>=0 && arr[j]>temp;j-=gap) {
                arr[j+gap] = arr[j];
            }
            
            arr[j+gap] = temp;
        }
    }
}

/*
 选择排序
 */
//1 简单选择排序
/*
最坏时间复杂度	О(n²)
最优时间复杂度	О(n²)
平均时间复杂度	О(n²)
空间复杂度	О(n) total, O(1) auxiliary
*/
void select_sort(std::vector<int>& arr) {
    for(int i=0;i<arr.size()-1;i++) {
        int min = i;
        for(int j=i+1;j<arr.size();j++) {
            min = j;
        }
        
        std::swap(arr[i], arr[min]);
    }
}
//2 堆排序
/*
最坏时间复杂度	O(nlog n)
最优时间复杂度	O(nlog n)
平均时间复杂度	(nlog n)
空间复杂度	O(n) total,  O(1) auxiliary
*/
void max_heapify(int arr[], int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while(son <= end) {
        if(son + 1 <= end && arr[son] < arr[son+1]) {
            son ++;
        }
        if(arr[dad] > arr[son])
            return;
        else {
            std::swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
void heap_sort(int arr[], int len) {
    for(int i=len/2-1;i>=0;i--) {
        max_heapify(arr, i, len-1);
    }
    
    for(int i=len-1;i>0;i--) {
        std::swap(arr[0], arr[i]);
        max_heapify(arr, 0, i-1);
    }
}

/*
 交换排序
 */
//1 bubble sort
/*
最坏时间复杂度	O(n^{2})
最优时间复杂度	O(n)
平均时间复杂度	O(n^{2})
空间复杂度	总共 O(n)，需要辅助空间 O(1)
*/
void bubble_sort(int arr[], int len) {
    int i, j;
    for(i=0;i<len-1;i++) {
        for(j=0;j<len-1-i;j++) {
            if(arr[j] > arr[j+1]) //大的放到最后
                std::swap(arr[j], arr[j+1]);
        }
    }
}
//2 快速排序
/*
最坏时间复杂度	(n^{2})
最优时间复杂度	(nlog n)
平均时间复杂度	(nlog n)
*/
void quick_sort_recursive(int arr[], int start, int end) {
    if(start >= end) return;
    
    int mid = arr[end];
    int left = start;
    int right = end-1;
    while(left < right) {
        while(arr[left] < mid && left<right)
            left ++;
        while(arr[right] >= mid && left < right)
            right--;
        
        std::swap(arr[left], arr[right]);
    }
    
    if(arr[left] >= arr[end]) {
        std::swap(arr[left], arr[end]);
    }
    else
        left ++;
    
    quick_sort_recursive(arr, start, left-1);
    quick_sort_recursive(arr, left+1, end);
}
struct Range {
    int start, end;
    Range(int s=0, int e=0) {
        start = s;
        end = e;
    }
};
void quick_sort(int arr[], const int len) {
    if(len <=0) return ;
    Range r[len];
    int p = 0;
    r[p++] = Range(0, len-1);
    while(p) {
        Range range = r[--p];
        if(range.start >= range.end) continue;
        
        int mid = arr[range.end];
        int left = range.start;
        int right = range.end-1;
        while(left < right) {
            while(arr[left] < mid && left < right) left++;
            while(arr[right] >= mid && left < right) right--;
            
            std::swap(arr[left], arr[right]);
        }
        if(arr[left] >= arr[range.end])
            std::swap(arr[left], arr[range.end]);
        else
            left++;
        
        r[p++] = Range(range.start, left-1);
        r[p++] = Range(left+1, range.end);
    }
}

/*
 归并排序
 */
/*
最坏时间复杂度	(nlog n)
最优时间复杂度	(n)
平均时间复杂度	(nlog n)
空间复杂度	(n)
*/
void merge_sort(int arr[], int len) {
    int *a = arr;
    int *b = new int[len];
    
    for(int seg=1;seg<len;seg+=seg) {
        for(int start=0;start<len;start+=seg+seg) {
            int low = start;
            int mid = std::min(start+seg, len);
            int high = std::min(start+seg+seg, len);
            
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while(start1<end1 && start2 < end2)
                b[k++] = a[start1]<a[start2]?a[start1++]:a[start2++];
            while(start1 < end1)
                b[k++] = a[start1++];
            while(start2<end2)
                b[k++] = a[start2++];
        }
        int *tmp = a;
        a = b;
        b = tmp;
    }
    if(a != arr) {
        for(int i=0;i<len;i++)
            b[i] = a[i];
        
        b = a;
    }
    delete [] b;
}

/*
 基数排序
 */
//最坏时间复杂度 O(kN)
//空间复杂度	O(k+N)
int maxbit(int data[], int n) {
    int max = data[0];
    for(int i=1;i<n;++i) {
        if(max < data[i])
            max = data[i];
    }
    int d = 1;
    int p = 10;
    while(max >= p) {
        max /= 10;
        ++d;
    }
    
    return d;
}
void radix_sort(int data[], int n) {
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10];// 桶
    int i,j,k;
    int radix=1;
    for(i=1;i<=d;++i) {
        for(j=0;j<10;++j) {
            count[j] = 0;
        }
        for(j=0;j<n;++j) {
            k = (data[j]/radix) % 10;
            count[k]++;
        }
        for(j=1;j<10;++j) {
            count[j] = count[j-1] + count[j];
        }
        for(j=n-1;j>=0;--j) {
            k = (data[j]/radix) % 10;
            tmp[count[k]-1] = data[j];
            count[k]--;
        }
        for(j=0;j<n;++j) {
            data[j] = tmp[j];
        }
        
        radix = radix * 10;
    }
    
    delete [] tmp;
    delete [] count;
}
