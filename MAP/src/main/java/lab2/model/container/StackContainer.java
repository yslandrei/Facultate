package lab2.model.container;

import lab2.model.task.Task;

import java.util.ArrayList;

public class StackContainer extends AbstractContainer {

    @Override
    public Task remove() {
        return removeTaskAtIndex(size() - 1);
    }

}
