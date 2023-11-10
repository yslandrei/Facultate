package lab3_social_network.repository.database;

import lab3_social_network.domain.Entity;
import lab3_social_network.domain.validators.Validator;
import lab3_social_network.repository.Repository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public abstract class AbstractDatabaseRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {

    private final String url;

    private final String username;

    private final String password;

    private final Validator<ID, E> validator;

    public AbstractDatabaseRepository(String url, String username, String password, Validator<ID, E> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    protected abstract E extractEntity(ResultSet resultSet) throws SQLException;

    protected abstract void populateStatement(PreparedStatement statement, E entity) throws SQLException;

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
        Set<E> entities = new HashSet<>();

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

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(getSaveQuery())
        ) {
            populateStatement(statement, entity);

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
            populateStatement(statement, entity);
            int rowsUpdated = statement.executeUpdate();
            if (rowsUpdated == 0) {
                return Optional.of(entity);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    protected abstract String getUpdateQuery();

}
