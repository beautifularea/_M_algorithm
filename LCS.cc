
#include <iostream>
#include <cstring> 
using namespace std;
char sz1[1000];//字符数组1 
char sz2[1000];//字符数组2 
int maxLen[1000][1000];
//MaxLen(i,j)表示s1的左边i个字符形成的子串，
//与s2左边的j个字符形成的子串的最长公共子序列的长度(i,j从0开始算） 
int main(){
    freopen("in.txt","r",stdin); 
    while(cin>>sz1>>sz2){
        int length1=strlen(sz1);//求字符数组1的长度 
        int length2=strlen(sz2);//求字符数组2的长度
        int nTmp;
        int i,j;
        //初始化边界情况 
        for(i=0;i<=length1;i++)
            maxLen[i][0]=0;
        for(j=0;j<=length2;j++)
            maxLen[0][j]=0; 

        //动态规划求解最长公共子序列  
        for(i=1;i<=length1;i++){
            for(j=1;j<=length2;j++){
                if(sz1[i-1]==sz2[j-1]){//字符数组从0开始存数据的 
                    //当s1和s2的最后一个字符相同时，MaxLen(i,j)=MaxLen(i-1,j-1)+1; 
                    maxLen[i][j]=maxLen[i-1][j-1]+1;
                }    
                else{
                    //当s1和s2的最后一个字符不同时，MaxLen(i,j) = Max(MaxLen(i,j-1),MaxLen(i-1,j) );  
                     maxLen[i][j]=max(maxLen[i][j-1],maxLen[i-1][j]);
                }
            } 
                        
        }
        /*
        for(i=1;i<=length1;i++){
            for(j=1;j<=length2;j++){
                cout<<maxLen[i][j]<<" ";
            }
            cout<<endl;
        }
        */ 
        //cout<<length1<<" "<<length2<<endl;
        cout<<maxLen[length1][length2]<<endl;
    }
    return 0;
}

#include <iostream>
#include <cstring>
#define MAXLEN 100
using namespace std;
//求s1和s2的最长公共子序列 
void LCSLength(char *s1,char *s2,int length1,int length2,int dp[][MAXLEN],int pre[][MAXLEN]){
    int i,j;

    //初始化边界情况 
    for(i=0;i<=length1;i++)
        dp[i][0]=0;
    for(j=0;j<=length2;j++)
        dp[0][j]=0; 
    
    for(i=1;i<=length1;i++){
        for(j=1;j<=length2;j++){
            if(s1[i-1]==s2[j-1]){//字符数组从0开始存数据的 
                //当s1和s2的最后一个字符相同时，dp(i,j)=dp(i-1,j-1)+1; 
                dp[i][j]=dp[i-1][j-1]+1;
                pre[i][j]=0;//记录来的位置信息为0，表示从(i-1,j-1)位置而来 
            }    
            //当s1和s2的最后一个字符不同时，dp(i,j) = Max(dp(i,j-1),dp(i-1,j) ); 
            else if(dp[i-1][j]>=dp[i][j-1]){//比较(i-1,j)位置和(i,j-1)位置最长公共子序列的长度 
                 dp[i][j]=dp[i-1][j];
                 pre[i][j]=1;//记录来的位置信息为1，表示从(i-1,j)位置而来 
            }
            else{
                dp[i][j]=dp[i][j-1];
                pre[i][j]=-1;//记录来的位置信息为-1，表示从(i,j-1)位置而来 
            }
        } 
                        
    }
}
//打印s1和s2的最长公共子序列 
void PrintLCS(int pre[][MAXLEN],char *s1,int i,int j){
    if(i==0||j==0)//到达了边界 
        return ;
    if(pre[i][j]==0){
        //查询记录来的位置信息为0，表示从(i-1,j-1)位置而来 
        PrintLCS(pre,s1,i-1,j-1);
        //从(i-1,j-1)位置来表示字符相等，故打印 
        printf("%c",s1[i-1]);
    }
    else if(pre[i][j]==1){
        //查询记录来的位置信息为1，表示从(i-1,j)位置而来 
        PrintLCS(pre,s1,i-1,j);
    }
    else{
        //查询记录来的位置信息为-1，表示从(i,j-1)位置而来 
        PrintLCS(pre,s1,i,j-1);
    }
} 

int main(){
    char s1[MAXLEN]={"ABCBDAB"};
    char s2[MAXLEN]={"BDCABA"};
    /*
    dp[MAXLEN][MAXLEN]表示进行动态规划运算的数组，
    dp(i,j)表示s1的左边i个字符形成的子串，
    与s2左边的j个字符形成的子串的最长公共子序列的长度(i,j从0开始算） 
    */ 
    int dp[MAXLEN][MAXLEN]; 
    //pre[i][j]用于记录ij位置的最长公共子序列是从哪个位置推导出来的 
    int pre[MAXLEN][MAXLEN];
    int length1=strlen(s1);//求字符数组s1的长度 
    int length2=strlen(s2);//求字符数组s2的长度
    LCSLength(s1,s2,length1,length2,dp,pre);//求s1和s2的最长公共子序列 
    cout<<dp[length1][length2]<<endl; //输出s1和s2的最长公共子序列的长度 
    PrintLCS(pre,s1,length1,length2);//打印s1和s2的最长公共子序列 
    cout<<endl;
    return 0;
}
