package com.example.domain.graph;

import com.example.domain.Tuple;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicReference;

public class GraphAlgorithmsExecuter<T> {

    private final Graph<T> graph;

    private List<Tuple<List<T>, Integer>> components;

    public GraphAlgorithmsExecuter(Graph<T> graph) {
        this.graph = graph;
        components = new ArrayList<>();
    }

    public Integer DFS(T vertex, Map<T, Boolean> visited) {
        visited.putIfAbsent(vertex, true);
        components.get(components.size() - 1).getLeft().add(vertex);
        Integer length = 1;

        for (T adjVertex : graph.getAdjacentVerticesOf(vertex)) {
            if (!visited.getOrDefault(adjVertex, false)) {
                length += DFS(adjVertex, visited);
            }
        }

        return length;
    }

    public void computeComponents() {
        components.clear();
        Map<T, Boolean> visited = new HashMap<>();
        for (T vertex : graph.getAllVertices()) {
            if (!visited.getOrDefault(vertex, false)) {
                components.add(new Tuple<>(new ArrayList<>(), 0));
                components.get(components.size() - 1).setRight(DFS(vertex, visited) - 1 );
            }
        }
    }

    public List<Tuple<List<T>, Integer>> getAllComponents() {
        return components;
    }

    public Tuple<List<T>, Integer> getLongestComponent() {
        int longestComponentSize = 0;
        AtomicReference<Tuple<List<T>, Integer>> longestComponent = new AtomicReference<>();
        components.forEach(component -> {
            if (component.getRight() > longestComponentSize) {
                longestComponent.set(component);
            }
        });

        return longestComponent.get();
    }

    public Integer getComponentsSize() {
        return components.size();
    }

}
