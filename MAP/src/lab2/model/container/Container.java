package lab2.model.container;

import lab2.model.task.Task;

public interface Container {
    Task remove();
    void add(Task task);
    int size();
    boolean isEmpty();
}
