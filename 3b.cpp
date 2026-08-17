import java.util.*;

public class MapColoring {

    static int[][] graph;
    static int[] color;
    static String[] colors;
    static int n, m;

    // Check whether we can give 'c' to 'state'
    static boolean isSafe(int state, int c) {

        for (int i = 0; i < n; i++) {

            // If state and i are neighbors
            // and i already has the same color
            if (graph[state][i] == 1 && color[i] == c) {
                return false;
            }
        }

        return true;
    }

    // Backtracking function
    static boolean solve(int state) {

        // All states are colored
        if (state == n) {
            return true;
        }

        // Try every available color
        for (int c = 0; c < m; c++) {

            // Check if this color is safe
            if (isSafe(state, c)) {

                // Assign color
                color[state] = c;

                // Color the next state
                if (solve(state + 1)) {
                    return true;
                }

                // BACKTRACK
                color[state] = -1;
            }
        }

        // No color worked
        return false;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        // Number of states
        System.out.print("Enter the number of states: ");
        n = sc.nextInt();

        // Number of colors
        System.out.print("Enter the number of colors: ");
        m = sc.nextInt();

        // Read colors
        colors = new String[m];

        System.out.print("Enter the colors: ");

        for (int i = 0; i < m; i++) {
            colors[i] = sc.next();
        }

        // Adjacency matrix
        graph = new int[n][n];

        System.out.println("Enter the connections (-1 for end):");

        while (true) {

            int a = sc.nextInt();

            if (a == -1) {
                break;
            }

            int b = sc.nextInt();

            // Convert state number to array index
            a--;
            b--;

            // Undirected graph
            graph[a][b] = 1;
            graph[b][a] = 1;
        }

        // Color array
        color = new int[n];

        // Initially no state has a color
        Arrays.fill(color, -1);

        // Start backtracking
        boolean result = solve(0);

        if (result) {

            System.out.println("Output:");

            for (int i = 0; i < n; i++) {
                System.out.println((i + 1) + " - " + colors[color[i]]);
            }

        } else {
            System.out.println("No solution exists.");
        }

        sc.close();
    }
}
