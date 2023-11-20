package lab2.model.sorter;

import java.util.ArrayList;

public class BubbleSorter implements AbstractSorter {

    @Override
    public ArrayList<Integer> sort(ArrayList<Integer> numere) {
        Boolean sorted = Boolean.FALSE;
        while (!sorted) {
            sorted = Boolean.TRUE;
            for (int i = 0; i < numere.size() - 1; i ++) {
                if (numere.get(i) > numere.get(i + 1)) {
                    Integer temp = numere.get(i);
                    numere.set(i, numere.get(i + 1));
                    numere.set(i + 1, temp);
                    sorted = Boolean.FALSE;
                }
            }
        }
        return numere;
    }

}
