#include <cstdio>
#include <iostream>
using namespace std;

int Set[1000];
int religiao;


int Find(int x){
    if (x == Set[x])
        return x;
    return Set[x] = Find(Set[x]);
}

void Union(int x, int y){
    x = Find(x);
    y = Find(y);
    if (x != y) {
        Set[x] = y;
        religiao--;
    }
}

int main()
{
    int K, N, Caso = 1;
   
    while (scanf("%d %d", &N, &K) && (N || K)) {
        for (int i = 1; i <= N; ++i)
            Set[i] = i;
        int x, y;
        religiao = N;
        while (K--) {
            scanf("%d%d", &x, &y);
            Union(x, y);
        }
        printf("Case %d: %d\n", Caso++, religiao);
    }
    return 0;
}