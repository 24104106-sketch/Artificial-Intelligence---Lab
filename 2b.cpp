#include <stdio.h>

#define MAX 10

int board[MAX][MAX];
int visited[MAX][MAX];

int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int n, totalCells;

int isSafe(int x, int y)
{
    return (x >= 0 && x < n &&
            y >= 0 && y < n &&
            board[x][y] != -1 &&
            !visited[x][y]);
}

int dfs(int x, int y, int count)
{
    visited[x][y] = 1;
    board[x][y] = count;

    if (count == totalCells)
        return 1;

    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isSafe(nx, ny))
        {
            if (dfs(nx, ny, count + 1))
                return 1;
        }
    }

    visited[x][y] = 0;
    board[x][y] = 0;

    return 0;
}

int main()
{
    printf("Enter board size: ");
    scanf("%d", &n);

    if (n > MAX)
    {
        printf("Maximum board size is %d.\n", MAX);
        return 0;
    }

    // Initialize board
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    // Block the center cell if board size is odd
    if (n % 2 == 1)
    {
        board[n / 2][n / 2] = -1;
        totalCells = n * n - 1;
    }
    else
    {
        totalCells = n * n;
    }

    if (dfs(0, 0, 1))
    {
        printf("\nKnight's Tour Found:\n\n");

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == -1)
                    printf(" XX ");
                else
                    printf("%3d ", board[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("\nNo complete Knight's Tour exists.\n");
    }

    return 0;
}
