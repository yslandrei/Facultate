package lab3_social_network.repository;


import lab3_social_network.domain.Entity;
import lab3_social_network.domain.validators.Validator;

import java.io.*;
import java.util.Arrays;
import java.util.List;


public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID,E> {

    String fileName;

    public AbstractFileRepository(String fileName, Validator<E> validator) {
        super(validator);
        this.fileName = fileName;
        readData();
    }

    /**
     * extract entity  - template method design pattern
     * creates an entity of type E having a specified list of @code attributes
     *
     * @param attributes
     * @return an entity of type E
     */
    public abstract E extractEntity(List<String> attributes);  //Template Method

    protected abstract String createEntityAsString(E entity); //Template Method

    private void readData() {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String newLine;
            while ((newLine = reader.readLine()) != null) {
                E entity = extractEntity(Arrays.asList(newLine.split(",")));
                super.save(entity);
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void writeData() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            super.findAll().forEach(entity -> {
                try {
                    writer.write(createEntityAsString(entity));
                    writer.newLine();
                } catch (IOException e) {
                    e.printStackTrace();

                }
            });

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null)
            writeData();

        return result;
    }

    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null)
            writeData();

        return result;
    }

    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if (result == null)
            writeData();

        return result;
    }

}
