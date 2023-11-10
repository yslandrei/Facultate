package lab2.factory;


import lab2.model.container.Container;
import lab2.model.container.QueContainer;
import lab2.model.container.StackContainer;

public class ContainerFactory implements Factory {

    private static ContainerFactory instance = null;

    private ContainerFactory() {

    }

    public static ContainerFactory getInstance() {
        if (instance == null) {
            instance = new ContainerFactory();
            return instance;
        }

        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        if (strategy.equals(Strategy.LIFO)){
            return new StackContainer();
        }
        else if (strategy.equals(Strategy.FIFO)){
            return new QueContainer();
        }
        else {
            return null;
        }
    }
}
