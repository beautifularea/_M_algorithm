/*
给定一个有序数组a，长度为len，和一个数x，判断A数组里面是否存在两个数，
他们的和为x，bool judge(int *a, int len, int x)，存在返回true，不存在则返回false。
*/

/*
分析：
考察数组两端元素和是否等于指定的X，如和大于X，则抛弃大端元素，形成一个新数组；如和小于X，则抛弃小端元素形成一个新数组。形成新数组后，重复前面步骤继续考察，直到数组两端元素和等于X或数组中元素不足2个。

　　由于题目没指定升序还是降序，所以一共有下面4种情况：

升序(0) 	   升序(0)	       降序(1)	      降序(1) 
和>X(1)	          和<X(0)	      和>X(1)	      和<X(0)
抛弃最右元素(1)	 抛弃最左元素(0)	 抛弃最左元素(0)	 抛弃最右元素(1)
*/

//认真观察一下不难发现，如果升序用0表示，降序用1表示；和>X 用1表示，
//和<X 用0表示；抛弃最右元素用1表示，抛弃最左元素用0表示的话，很显然上面表中第3行的值与前两行的值的异或运算的结果。

bool judge( int a[] , size_t n , int x ) 
{ 
   while ( n > 1u ) 
   { 
      if ( x == a[0] + a[n-1] ) 
         return true ; 
            
      if ( (x > a[0] + a[n-1]) ^ ( a[0] > a[n-1]) ) 
         a ++ ; 
      n -- ; 
   } 
      
   return false ; 
} 
