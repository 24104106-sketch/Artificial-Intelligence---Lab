#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node
{
    int state[3][3];
    int x, y;
    string move;
    Node *parent;
};

int goal[3][3];

// Convert board to string
string boardToString(int board[3][3])
{
    string s = "";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            s += char(board[i][j] + '0');
    return s;
}

// Print board
void printBoard(int board[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==0)
                cout<<"_ ";
            else
                cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

// Check goal state
bool isGoal(int board[3][3])
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]!=goal[i][j])
                return false;

    return true;
}

// Print solution path
void printPath(Node *goalNode)
{
    Node *path[100];
    int count=0;

    while(goalNode!=NULL)
    {
        path[count++]=goalNode;
        goalNode=goalNode->parent;
    }

    reverse(path,path+count);

    cout<<"\nGoal State Reached!\n\n";

    for(int i=0;i<count;i++)
    {
        cout<<"Step "<<i<<endl;

        if(i==0)
            cout<<"Initial State\n";
        else
            cout<<"Move : "<<path[i]->move<<endl;

        printBoard(path[i]->state);
        cout<<"----------------------"<<endl;
    }

    cout<<"Total Moves = "<<count-1<<endl;
}

void BFS(int start[3][3])
{
    queue<Node*> q;
    set<string> visited;

    Node *root=new Node;

    int sx,sy;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            root->state[i][j]=start[i][j];

            if(start[i][j]==0)
            {
                sx=i;
                sy=j;
            }
        }

    root->x=sx;
    root->y=sy;
    root->move="";
    root->parent=NULL;

    q.push(root);
    visited.insert(boardToString(root->state));

    int dx[]={-1,1,0,0};
    int dy[]={0,0,-1,1};
    string dir[]={"Up","Down","Left","Right"};

    while(!q.empty())
    {
        Node *current=q.front();
        q.pop();

        if(isGoal(current->state))
        {
            printPath(current);
            return;
        }

        for(int k=0;k<4;k++)
        {
            int nx=current->x+dx[k];
            int ny=current->y+dy[k];

            if(nx>=0 && nx<3 && ny>=0 && ny<3)
            {
                Node *child=new Node;

                memcpy(child->state,current->state,sizeof(current->state));

                swap(child->state[current->x][current->y],
                     child->state[nx][ny]);

                string key=boardToString(child->state);

                if(visited.find(key)==visited.end())
                {
                    visited.insert(key);

                    child->x=nx;
                    child->y=ny;
                    child->move=dir[k];
                    child->parent=current;

                    q.push(child);
                }
                else
                {
                    delete child;
                }
            }
        }
    }

    cout<<"Puzzle is Unsolvable.";
}

int main()
{
    int start[3][3];

    cout<<"Enter Initial State:\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin>>start[i][j];

    cout<<"\nEnter Goal State:\n";
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin>>goal[i][j];

    BFS(start);

    return 0;
}
