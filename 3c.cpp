import java.util.*;

public class AlphaBeta {

    static ArrayList<Integer>[] tree;
    static int[] value;
    static boolean[] leaf;

    // Alpha-Beta Pruning
    static int alphaBeta(int node, int alpha, int beta, boolean maximizingPlayer) {

        // If node is a leaf, return its utility value
        if (leaf[node]) {
            return value[node];
        }

        if (maximizingPlayer) {

            int best = Integer.MIN_VALUE;

            for (int child : tree[node]) {

                int result = alphaBeta(child, alpha, beta, false);

                best = Math.max(best, result);
                alpha = Math.max(alpha, best);

                // Beta cutoff
                if (beta <= alpha) {
                    break;
                }
            }

            return best;

        } else {

            int best = Integer.MAX_VALUE;

            for (int child : tree[node]) {

                int result = alphaBeta(child, alpha, beta, true);

                best = Math.min(best, result);
                beta = Math.min(beta, best);

                // Alpha cutoff
                if (beta <= alpha) {
                    break;
                }
            }

            return best;
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of Nodes: ");
        int n = sc.nextInt();

        tree = new ArrayList[n + 1];
        value = new int[n + 1];
        leaf = new boolean[n + 1];

        for (int i = 1; i <= n; i++) {
            tree[i] = new ArrayList<>();
            leaf[i] = true;
        }

        System.out.println("Enter the connections (-1 for end):");

        while (true) {

            int parent = sc.nextInt();

            if (parent == -1) {
                break;
            }

            int child = sc.nextInt();

            tree[parent].add(child);
            leaf[parent] = false;
        }

        // Read utility values of leaf nodes
        System.out.println("Enter utility values for leaf nodes:");

        for (int i = 1; i <= n; i++) {

            if (leaf[i]) {
                System.out.print("Node " + i + ": ");
                value[i] = sc.nextInt();
            }
        }

        // Find the best move for MAX
        int bestValue = Integer.MIN_VALUE;
        int bestMove = -1;

        int alpha = Integer.MIN_VALUE;
        int beta = Integer.MAX_VALUE;

        // Root is MAX
        for (int child : tree[1]) {

            int currentValue =
                    alphaBeta(child, alpha, beta, false);

            if (currentValue > bestValue) {
                bestValue = currentValue;
                bestMove = child;
            }

            alpha = Math.max(alpha, bestValue);

            // Alpha-Beta pruning at root
            if (beta <= alpha) {
                break;
            }
        }

        System.out.println();
        System.out.println("Best Move for MAX: Node 1 -> Node " + bestMove);
        System.out.println("MAX Val: " + bestValue);

        sc.close();
    }
}
