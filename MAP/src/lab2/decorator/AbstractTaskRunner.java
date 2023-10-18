package lab2.decorator;


import lab2.model.task.Task;

public class AbstractTaskRunner implements TaskRunner{

//    Definiti clasa abstractă AbstractTaskRunner [Decorator Pattern]
//    care implementează interfața TaskRunner si care conține
//    ca și atribut privat o referință la un obiect de tipul Task Runner,
//    referința primită ca parametrul prin intermediul constructorului.
    private TaskRunner taskRunner;

    public AbstractTaskRunner(TaskRunner runner){
        taskRunner = runner;
    }

    @Override
    public void executeOneTask() {
        taskRunner.executeOneTask();
    }

    @Override
    public void executeAll() {
        taskRunner.executeAll();
    }

    @Override
    public void addTask(Task t) {
        taskRunner.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return taskRunner.hasTask();
    }
}
