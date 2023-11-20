package com.example.domain.graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BidirectedGraph<T> implements Graph<T> {

    private Map<T, List<T>> adjMap;

    public BidirectedGraph() {
        adjMap = new HashMap<>();
    }

    @Override
    public void addVertex(T vertex) {
        adjMap.putIfAbsent(vertex, new ArrayList<>());
    }

    @Override
    public void removeVertex(T vertex) {
        adjMap.values().forEach(adjList -> {
            adjList.remove(vertex);
        });
        adjMap.remove(vertex);
    }

    @Override
    public void addEdge(T vertex1, T vertex2) {
        adjMap.get(vertex1).add(vertex2);
        adjMap.get(vertex2).add(vertex1);
    }

    @Override
    public void removeEdge(T vertex1, T vertex2) {
        if (adjMap.get(vertex1) != null)
            adjMap.get(vertex1).remove(vertex2);
        if (adjMap.get(vertex2) != null)
            adjMap.get(vertex1).remove(vertex2);
    }

    @Override
    public List<T> getAllVertices() {
        return adjMap.keySet().stream().toList();
    }

    @Override
    public List<T> getAdjacentVerticesOf(T vertex) {
        return adjMap.get(vertex);
    }

}
