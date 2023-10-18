package lab2.factory;


import lab2.model.container.Container;

public interface Factory {
    Container createContainer(Strategy strategy);
}
