package lab3_social_network.domain.graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GraphAlgorithmsExecuter<T> {

    private final Graph<T> graph;

    private List<List<T>> components;

    public GraphAlgorithmsExecuter(Graph<T> graph) {
        this.graph = graph;
        components = new ArrayList<>();
    }

    public List<T> DFS(T vertex, Map<T, Boolean> visited) {
        visited.putIfAbsent(vertex, true);
        components.get(components.size() - 1).add(vertex);
        List<T> traversalOrder = new ArrayList<>();
        traversalOrder.add(vertex);

        for (T adjVertex : graph.getAdjacentVerticesOf(vertex)) {
            if (!visited.getOrDefault(adjVertex, false)) {
                traversalOrder.addAll(DFS(adjVertex, visited));
            }
        }
        //System.out.println(traversalOrder);
        return traversalOrder;
    }

    public void computeComponents() {
        Map<T, Boolean> visited = new HashMap<>();
        for (T vertex : graph.getAllVertices()) {
            if (!visited.getOrDefault(vertex, false)) {
                components.add(new ArrayList<>());
                DFS(vertex, visited);
            }
        }
    }

    public List<List<T>> getAllComponents() {
        return components;
    }

    public Integer getComponentsSize() {
        return components.size();
    }

}
