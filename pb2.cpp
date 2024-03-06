#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define inf 100000000
std::ifstream f("in.txt");
std::ofstream g("out.txt");
int n,m,d[10005],viz[10005],h[10005];
std::vector<std::pair<int,int>>v[10005],vnou[10005];
std::priority_queue< std::pair<int,int>, std::vector<std:: pair<int,int> >,std:: greater<std::pair<int,int> > >q;
struct bellman
{
    int x,y,c;
}muchie[10005];

void relax(int u, int v, int c)
{
    if(d[v]>d[u]+c)
        d[v]=d[u]+c;
}

bool bellman_ford(int s)
{
    for(int i=0;i<n;i++) d[i]=inf;
    d[s]=0;
    for(int i=0;i<n;i++)
        for(int j=1;j<=m;j++)
            relax(muchie[j].x, muchie[j].y, muchie[j].c);
    for(int j=1;j<=m;j++)
    {
        if(d[muchie[j].y]>d[muchie[j].x]+muchie[j].c)
            return false;
    }
    return true;
}

void dijkstra(int s)
{
    int i,nod,cost;
    for(i=0;i<=n;i++) {d[i]=inf;viz[i]=0;}
    //am un priority queue in care am nodurile sortate in funcite de costul de ajunge la ele;
    q.push({0,s});
    d[s]=0;
    while(!q.empty())
    {
        nod=q.top().second;
        cost=q.top().first;
        q.pop();
        if(!viz[nod])
        {
            viz[nod]=1;
            for(int i=0;i<vnou[nod].size();i++)
            {
                //daca costul muchiei adunat cu costul de pana atunci este mai mic decat costul vecinului
                if(vnou[nod][i].second+cost<d[vnou[nod][i].first])
                {
                    d[vnou[nod][i].first]=vnou[nod][i].second+cost;
                    q.push({d[vnou[nod][i].first],vnou[nod][i].first});
                }
            }
        }

    }

}

void johnson()
{
    int M=m;
    //adaug noul arc cu ponderi 0
    for(int i=0;i<n;i++)
    {
        v[n].push_back({i,0});
        muchie[++m].x=n;
        muchie[m].y=i;
        muchie[m].c=0;
    }
    //aplic bellman ford pentru noul nod adaugat si verific sa nu am cicluri negative
    if(!bellman_ford(n)) {g<<"-1";exit(0);}
    else
    {
        //copiez rezultatele din bellman ford
        for(int i=0;i<n;i++) h[i]=d[i];
        for(int j=1;j<=M;j++) {
            //reponderez
            muchie[j].c = muchie[j].c + h[muchie[j].x] - h[muchie[j].y];
            g<<muchie[j].x<<" "<<muchie[j].y<<" "<<muchie[j].c<<'\n';
            vnou[muchie[j].x].push_back({muchie[j].y,muchie[j].c});
        }
        //dijkstra din fiecare nod
        for(int i=0;i<n;i++)
        {
            dijkstra(i);
            for(int j=0;j<n;j++) {
                if(d[j]==inf) g<<"INF"<<" ";
                else
                {
                    //renunt la reponderare
                    d[j]=d[j]+h[j]-h[i];
                    g << d[j] << " ";
                }
            }
            g<<'\n';
        }

    }

}
int main() {


    //citesc datele si construiesc lista de vecini
    f>>n>>m;
    for(int i=1;i<=m;i++)
    {
        f>>muchie[i].x>>muchie[i].y>>muchie[i].c;
        v[muchie[i].x].push_back({muchie[i].y,muchie[i].c});
    }
    johnson();
    return 0;
}

