package org.example.repository;

import org.example.domain.Entity;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.*;
import java.util.*;


public abstract class AbstractDatabaseRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {

    protected String url;

    protected String username;

    protected String password;

    protected static final Logger logger = LoggerFactory.getLogger(AbstractDatabaseRepository.class);

    public AbstractDatabaseRepository(Properties properties) {
        url = properties.getProperty("jdbc.url");
        username = properties.getProperty("jdbc.user");
        password = properties.getProperty("jdbc.pass");
    }

    protected abstract E extractEntity(ResultSet resultSet) throws SQLException;

    protected abstract String getFindOneQuery();

    protected abstract void setIdParameter(PreparedStatement statement, ID id) throws SQLException;

    @Override
    public Optional<E> findOne(ID id) {
        logger.info("Se incearca conexiunea la baza de date");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getFindOneQuery())
        ) {
            setIdParameter(statement, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                E entity = extractEntity(resultSet);
                logger.info("S-a gasit entitatea: " + entity);
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    protected abstract String getFindAllQuery();

    @Override
    public List<E> findAll() {
        List<E> entities = new ArrayList<>();

        logger.info("Se incearca conexiunea la baza de date");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getFindAllQuery());
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next()) {
                E entity = extractEntity(resultSet);
                logger.info("S-a gasit entitatea: " + entity);
                entities.add(entity);
            }
            return entities;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    protected abstract String getSaveQuery();

    protected abstract void setSaveParameters(PreparedStatement statement, E entity) throws SQLException;

    @Override
    public Optional<E> save(E entity) {
        logger.info("Se incearca conexiunea la baza de date");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getSaveQuery())
        ) {
            setSaveParameters(statement, entity);
            int rowsInserted = statement.executeUpdate();
            if (rowsInserted == 1) {
                logger.info("S-a inserat entitatea: " + entity);
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }


    protected abstract String getDeleteQuery();

    @Override
    public Optional<E> delete(ID id) {
        logger.info("Se incearca conexiunea la baza de date");
        Optional<E> entityOptional = findOne(id);

        entityOptional.ifPresent(entity -> {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement(getDeleteQuery())
            ) {
                setIdParameter(statement, id);
                int rowsDeleted = statement.executeUpdate();
                if (rowsDeleted == 0) {
                    logger.info("S-a sters entitatea:" + entity);
                }

            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        });

        return entityOptional;
    }

    protected abstract String getUpdateQuery();

    protected abstract void setUpdateParameters(PreparedStatement statement, E entity) throws SQLException;

    @Override
    public Optional<E> update(E entity) {

        logger.info("Se incearca conexiunea la baza de date");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getUpdateQuery())
        ) {
            setUpdateParameters(statement, entity);
            int rowsUpdated = statement.executeUpdate();
            if (rowsUpdated == 0) {
                logger.info("S-a updatat entitatea :" + entity);
                return Optional.of(entity);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }


}