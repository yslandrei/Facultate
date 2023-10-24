package lab3_social_network.domain.graph;

import java.util.List;

public interface Graph<T> {

    void addVertex(T vertex);

    void removeVertex(T vertex);

    void addEdge(T vertex1, T vertex2);

    void removeEdge(T vertex1, T vertex2);

    List<T> getAllVertices();

    List<T> getAdjacentVerticesOf(T vertex);

}
