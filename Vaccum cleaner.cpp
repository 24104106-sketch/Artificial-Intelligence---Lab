#include <iostream>
using namespace std;

int room[10][10];
bool visited[10][10];
int n;

int dx[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
int dy[] = {0, 0, -1, 1};

void vacuum(int x, int y)
{
    visited[x][y] = true;

    cout << "Vacuum moved to (" << x << "," << y << ")" << endl;

    if(room[x][y] == 1)
    {
        cout << "Dirty -> Cleaning..." << endl;
        room[x][y] = 0;
    }
    else
    {
        cout << "Already Clean." << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx >= 0 && nx < n &&
           ny >= 0 && ny < n &&
           !visited[nx][ny])
        {
            cout << "Moving from (" << x << "," << y << ") to ("
                 << nx << "," << ny << ")" << endl;

            vacuum(nx, ny);

          
          
        }
    }
}

int main()
{
    cout << "Enter the Size of the Room: ";
    cin >> n;

    cout << "Enter Room States (0-Clean, 1-Dirty):" << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> room[i][j];
            visited[i][j] = false;
        }
    }

    int r, c;
    cout << "Enter Starting Position: ";
    cin >> r >> c;

    if(r < 0 || r >= n || c < 0 || c >= n)
    {
        cout << "Invalid Position";
        return 0;
    }

    cout << "\n===== Vacuum Cleaning Started =====\n\n";

    vacuum(r, c);

    cout << "\n===== Final Room State =====\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << room[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}