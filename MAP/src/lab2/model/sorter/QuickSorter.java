package lab2.model.sorter;

import java.util.ArrayList;

public class QuickSorter implements  AbstractSorter {

    private Integer partition(ArrayList<Integer> numere, Integer st, Integer dr) {
        Integer pivot = numere.get(dr);
        Integer i = st - 1;

        for (Integer j = st; j < dr; j ++) {
            if(numere.get(j) < pivot) {
                i ++;
                Integer temp = numere.get(j);
                numere.set(j, numere.get(i));
                numere.set(i, temp);
            }
        }

        Integer temp = numere.get(i + 1);
        numere.set(i + 1, numere.get(dr));
        numere.set(dr, temp);

        return i + 1;
    }

    private void quickSort(ArrayList<Integer> numere, Integer st, Integer dr) {
        if (st < dr) {
            Integer p = partition(numere, st, dr);

            quickSort(numere, st, p - 1);
            quickSort(numere, p + 1, dr);
        }
    }

    @Override
    public ArrayList<Integer> sort(ArrayList<Integer> numere) {
        quickSort(numere, 0, numere.size() - 1);
        return numere;
    }

}
