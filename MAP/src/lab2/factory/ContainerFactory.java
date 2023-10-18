package lab2.factory;


import lab2.model.container.Container;
import lab2.model.container.QueContainer;
import lab2.model.container.StackContainer;

public class ContainerFactory implements Factory{

    public static ContainerFactory getInstance() {
        return new ContainerFactory();
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
