package lab2.decorator;



import lab2.factory.ContainerFactory;
import lab2.factory.Strategy;
import lab2.model.container.Container;
import lab2.model.task.Task;

public class StrategyTaskRunner implements TaskRunner {

//    Creaţi clasa StrategyTaskRunner care implementează interfața TaskRunner și care conţine:
//    Un atribut privat de tipul Container;
//    Un constructor ce primeşte ca parametru o strategie prin care se specificǎ în ce ordine
//    se vor executa task-urile (LIFO sau FIFO);

    private Container container;

    public StrategyTaskRunner(Strategy strategy) {
        ContainerFactory containerFactory = ContainerFactory.getInstance();
        container = containerFactory.createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        if (hasTask()) {
            Task removedTask = container.remove();
            removedTask.execute();
        }
        else {
            System.out.println("<emoji>");
        }
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
