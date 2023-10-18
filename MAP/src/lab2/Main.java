package lab2;


import lab2.decorator.DelayTaskRunner;
import lab2.decorator.PrinterTaskRunner;
import lab2.decorator.StrategyTaskRunner;
import lab2.decorator.TaskRunner;
import lab2.factory.Strategy;
import lab2.model.sorter.QuickSorter;
import lab2.model.task.MessageTask;
import lab2.model.task.SortingTask;
import lab2.model.task.Task;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        MessageTask mt = new MessageTask("Ai obtinut 9.60", "Gigel","Maria Ioana", LocalDateTime.of(2023,10,10,9,29),"1","super wow");

        SortingTask st = new SortingTask("sal",
                "sal",
                new ArrayList<Integer>(List.of(1, -2, 5, 2, 5)),
                new QuickSorter()
        );

        ArrayList<Task> listOfMessages = new ArrayList<>();
        listOfMessages.add(mt);
        listOfMessages.add(st);
        
//        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Strategy.FIFO);
//        listOfMessages.forEach(strategyTaskRunner::addTask);
//        strategyTaskRunner.executeAll();

        StrategyTaskRunner strategyTaskRunnerWithDecorator = new StrategyTaskRunner(Strategy.valueOf(args[0]));
        listOfMessages.forEach(strategyTaskRunnerWithDecorator::addTask);
        TaskRunner runner = new DelayTaskRunner(strategyTaskRunnerWithDecorator);
        runner.executeAll();

    }
}