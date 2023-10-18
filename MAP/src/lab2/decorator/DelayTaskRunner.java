package lab2.decorator;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DelayTaskRunner extends AbstractTaskRunner {
    public DelayTaskRunner(TaskRunner runner) {
        super(runner);
    }

    @Override
    public void executeOneTask() {
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.executeOneTask();
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }
}

