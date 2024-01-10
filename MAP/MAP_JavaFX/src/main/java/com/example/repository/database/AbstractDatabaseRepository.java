package com.example.repository.database;

import com.example.domain.Entity;
import com.example.domain.validators.Validator;
import com.example.repository.Repository;
import com.example.repository.paging.Page;
import com.example.repository.paging.Pageable;

import java.sql.*;
import java.util.*;

public abstract class AbstractDatabaseRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {

    protected final String url;

    protected final String username;

    protected final String password;

    private final Validator<ID, E> validator;

    public AbstractDatabaseRepository(String url, String username, String password, Validator<ID, E> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    protected abstract E extractEntity(ResultSet resultSet) throws SQLException;


    @Override
    public Optional<E> findOne(ID id) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getFindOneQuery())
        ) {
            setFindOneParameters(statement, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(extractEntity(resultSet));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    protected abstract String getFindOneQuery();

    protected abstract void setFindOneParameters(PreparedStatement statement, ID id) throws SQLException;

    @Override
    public Iterable<E> findAll() {
        List<E> entities = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getFindAllQuery());
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next()) {
                E entity = extractEntity(resultSet);
                entities.add(entity);
            }
            return entities;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    protected abstract String getFindAllQuery();

    @Override
    public Optional<E> save(E entity) {
        validator.validate(entity);
        if (entity.getId() != null) {
            Optional<E> entityOptional = findOne(entity.getId());
            if (entityOptional.isPresent()) {
                return entityOptional;
            }
        }

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getSaveQuery())
        ) {
            setSaveParameters(statement, entity);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted == 0) {
                return Optional.of(entity);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    protected abstract String getSaveQuery();

    protected abstract void setSaveParameters(PreparedStatement statement, E entity) throws SQLException;

    @Override
    public Optional<E> delete(ID id) {
        Optional<E> entityOptional = findOne(id);

        entityOptional.ifPresent(entity -> {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement(getDeleteQuery())
            ) {
                setDeleteParameters(statement, id);
                int rowsDeleted = statement.executeUpdate();

            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        });

        return entityOptional;
    }

    protected abstract String getDeleteQuery();

    protected abstract void setDeleteParameters(PreparedStatement statement, ID id) throws SQLException;

    @Override
    public Optional<E> update(E entity) {
        validator.validate(entity);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getUpdateQuery())
        ) {
            setUpdateParameters(statement, entity);
            int rowsUpdated = statement.executeUpdate();
            if (rowsUpdated == 0) {
                return Optional.of(entity);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    protected abstract void setUpdateParameters(PreparedStatement statement, E entity) throws SQLException;


    protected abstract String getUpdateQuery();

    public Iterable<E> executeQuery(String query) {
        List<E> entities = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query);
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next()) {
                E entity = extractEntity(resultSet);
                entities.add(entity);
            }
            return entities;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }

    protected abstract String getCountQuery();

    protected abstract String getFindAllPagedQuery();

    @Override
    public Page<E> findAll(Pageable pageable) {
        int numberOfElements = 0;

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getCountQuery());
             ResultSet resultSet = statement.executeQuery()
        ) {
            resultSet.next();
            numberOfElements = resultSet.getInt(1);

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        int limit = pageable.getPageSize();
        int offset = pageable.getPageSize() * pageable.getPageNumber();
        if(offset >= numberOfElements)
            return new Page<>(new ArrayList<>(), numberOfElements);
        List<E> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            PreparedStatement statement = connection.prepareStatement(getFindAllPagedQuery());
            statement.setInt(2, offset);
            statement.setInt(1, limit);
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                E entity = extractEntity(resultSet);
                entities.add(entity);
            }
        }
        catch (SQLException e){
            System.out.println(e.getMessage());
        }

        return new Page<>(entities, numberOfElements);
    }

}
