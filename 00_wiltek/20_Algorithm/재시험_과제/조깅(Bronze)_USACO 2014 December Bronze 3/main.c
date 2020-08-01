#include <stdio.h>

#define MAX_N 	  (100000 + 10)
#define MIN(a, b) ((a < b)? a : b)

int main() 
{
  int n;
  freopen("input.txt", "r", stdin);
  scanf("%d", &n);
  int data[MAX_N];

  for(int i = 0; i < n; i++) 
  {
    int x, s;
    scanf("%d %d\n", &x, &s);
    data[i] = s;
  }

  int ans = 1;
  int slow = data[n-1];

  for(int i = n-2; i >= 0; i--) 
  {
    if(data[i] > slow) { } 
    else{	//data[i] <= slow
    	printf("data[%d]: %d, slow: %d\n", i, data[i], slow);
    	ans++;
    	slow = data[i];
    }
  }
  printf("ans: %d\n", ans);
}