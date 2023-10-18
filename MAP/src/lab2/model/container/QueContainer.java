package lab2.model.container;

import lab2.model.task.Task;

public class QueContainer extends AbstractContainer {

    @Override
    public Task remove() {
        return removeTaskAtIndex(0);
    }
}
