package com.example.repository.file;


import com.example.domain.Entity;
import com.example.domain.validators.Validator;
import com.example.repository.in_memory.InMemoryRepository;

import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;


public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID,E> {

    String fileName;

    public AbstractFileRepository(String fileName, Validator<ID, E> validator) {
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

    private void writeData() {
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
    public Optional<E> save(E entity) {
        Optional<E> result = super.save(entity);
        if (result.isEmpty())
            writeData();

        return result;
    }

    @Override
    public Optional<E> delete(ID id) {
        Optional<E> result = super.delete(id);
        if (result.isPresent())
            writeData();

        return result;
    }

    @Override
    public Optional<E> update(E entity) {
        Optional<E> result = super.update(entity);
        if (result.isEmpty())
            writeData();

        return result;
    }

}
