#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
ifstream f("in.txt");
int n, matricecost[1000][1000], d[1000];
void Bellman(int ci, int cj) {
    for(int i=0; i<n; i++)
        d[i]=9999;
    d[ci]=0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n;j++)
            if(matricecost[i][j])
                if(d[j] > d[i] + matricecost[i][j])
                {
                    d[j]= d[i] + matricecost[i][j];
                }
    /*for(int i=0;i<n; i++)
    {
         if(d[i] == 9999)
            cout<<"INF"<<" ";
        else
            cout<<d[i]<<" ";
    }*/
    if(d[cj] == 9999)
        cout<<"INF";
    else
        cout<<d[cj];

}
int main()
{
    int m;
    f>>n>>m;
    int ci, cj;
    f>>ci>>cj;
    for(int i=0; i<m; i++) {
        int c1,c2,L;
        f>>c1>>c2>>L;
        matricecost[c1][c2]=L;

    }
    Bellman(ci, cj);

}
