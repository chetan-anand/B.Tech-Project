#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<strings.h>
#include<limits.h>
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
typedef vector <int> vi;
typedef pair <int,int> pii;
#define pb push_backCobie Smulders.
#define mp make_pair
#define gi(n) scanf("%d",&n)
#define gl(n) scanf("%lld",&n)
#define gs(n) scanf("%s",n);
#define pi(n) printf("%d\n",n)
#define pl(n) printf("%lld\n",n)
#define ps(n) printf("%s\n",n);
#define rep(i,n) for(int i=0;i<n;i++)
#define fi(i,a,n) for(int i=a;i<=n;i++)
#define fd(i,n,a) for(int i=n;i>=a;i--)
#define input(f) freopen("f.txt","r",stdin)
#define line cout<<"\n-----------------------------------------"<<endl
#define MAX 110000    // Maximum number of task nodes in DAG

///////////////////////////////////////////////////////////////////////////////
int n;                              //Number of nodes in DAG
int size_core;                      //Total number of core in machine

struct node                         // Structure of node in dag
{
    int key;
    int ranku;
    int cost;
    node()
    {
        key=0;
        ranku=0;
        cost=0;
    }
};

struct slist                        // sorted list structure of task node in dag according to their upward rank
{
    int ranku;
    int key;
};

struct core
{
    bool status;                // busy or ideal
    int EST;                    // Earliest start time
    int EFT;                    // Earliest finish time
};
////////////////////////////////////////////////////////////////////////////////////
node nodes[MAX];
vector<int> adj[MAX];
slist sorted_list[MAX];
core cores[MAX];
int task_to_core[MAX];              // Mapping Task->Processor
int core_to_task[MAX];              // Mapping Proccessor->Task
/////////////////////////////////////////////////////////////////////////////////////

///// this func will find the source task nodes in DAG: O(n)
vector<int> find_root()
{
    int visit[MAX];
    int root;
    memset(visit,0,sizeof(visit));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            visit[adj[i][j]]++;
        }
    }

    vector<int> roots;

    for(int i=1;i<=n;i++)
    {
        if(visit[i]==0)
        {
            roots.push_back(i);
        }
    }
    return roots;
}

////////////////////////////////////////////////////////////////////////////////
/*Compare two node according to their rank*/

bool comp(slist n1,slist n2)
{
    if(n1.ranku>n2.ranku)
    {
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////
/*Calculation upward rank of each task node: O(n)*/

int upward_rank(int root)
{
    if(adj[root].size()==0)
    {
        nodes[root].ranku=nodes[root].cost;
        return nodes[root].cost;
    }
    int maxv=INT_MIN;
    for(int i=0;i<adj[root].size();i++)
    {
        int temp=upward_rank(adj[root][i]);
        maxv=max(temp,maxv);
    }

    nodes[root].ranku=maxv+nodes[root].cost;
    return nodes[root].ranku;
}

//////////////////////////////////////////////////////////////////////////////////
void map_core(int idx)
{

}

void exec(int idx)
{
    cout<<"Key="<<nodes[idx].key<<" "<<"Cost="<<nodes[idx].ranku<<endl;
    //cout<<"time take="<<
    map_core(idx);
}
/////////////////////////////////////////////////////////////
/*Implementing HEFT heuristics algorithm*/

void heft_algo()
{
    vector<int> root;
    root=find_root();
    cout<<"Roots are:"<<endl;

    for(int i=0;i<root.size();i++)
    {
        cout<<root[i]<<endl;
    }

    line;
    for(int i=0;i<root.size();i++)
    {
        upward_rank(root[i]);
    }

    for(int i=1;i<=5;i++)
    {
        cout<<"Index="<<i<<" "<<nodes[i].ranku<<endl;
    }

    line;

    for(int i=1;i<=n;i++)
    {
        sorted_list[i].key=i;
        sorted_list[i].ranku=nodes[i].ranku;
    }

    sort(sorted_list+1,sorted_list+n,comp);

    for(int i=1;i<=n;i++)
    {
        exec(sorted_list[i].key);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    n=5;
    for(int i=1;i<=5;i++)
    {
        nodes[i].cost=1+rand()%5;
        nodes[i].key=i;
        cout<<"Index="<<i<<" "<<"Cost="<<nodes[i].cost<<endl;
    }
    //line;
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[3].push_back(5);
    adj[4].push_back(5);
    cout<<"\n-----------------------------------------"<<endl;;
    for(int i=1;i<=5;i++)
    {
        cout<<i<<": ";
        for(int j=0;j<adj[i].size();j++)
        {
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\n-----------------------------------------"<<endl;;


    heft_algo();

    return 0;
}
