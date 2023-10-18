package lab2.model.task;

import lab2.model.sorter.AbstractSorter;

import java.util.ArrayList;

public class SortingTask extends Task {

    private ArrayList<Integer> numere;

    private AbstractSorter sorter;

    public SortingTask(String taskId, String descriere, ArrayList<Integer> numere, AbstractSorter sorter) {
        super(taskId, descriere);
        this.numere = numere;
        this.sorter = sorter;
        sorter.sort(numere);
    }

    @Override
    public void execute() {
        numere.forEach(numar -> System.out.printf("%d ", numar));
        System.out.println();
    }
}
