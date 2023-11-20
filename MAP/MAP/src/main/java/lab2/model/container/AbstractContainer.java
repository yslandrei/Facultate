package lab2.model.container;

import lab2.model.task.Task;

import java.util.ArrayList;

public abstract class AbstractContainer implements Container {

    private ArrayList<Task> tasks;

    public AbstractContainer() {
        this.tasks = new ArrayList<>();
    }

    @Override
    public abstract Task remove();

    @Override
    public void add(Task task) {
        tasks.add(task);
    }

    @Override
    public int size() {
        return tasks.size();
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    protected Task removeTaskAtIndex(int i) {
        return isEmpty() ? null : tasks.remove(i);
    }
}
