package lab2.decorator;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner{
    public PrinterTaskRunner(TaskRunner runner) {
        super(runner);
    }

    @Override
    public void executeOneTask() {
        super.executeOneTask();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm");
        LocalDateTime  executionTime = LocalDateTime.now();
        System.out.println("Taskul a fost executat la ora "+executionTime.format(formatter));
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

}
