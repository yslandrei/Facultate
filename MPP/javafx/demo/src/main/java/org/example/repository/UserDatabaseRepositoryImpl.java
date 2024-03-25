package org.example.repository;

import org.example.domain.User;

import java.sql.*;
import java.util.Optional;
import java.util.Properties;

import static java.lang.Math.toIntExact;

public class UserDatabaseRepositoryImpl extends AbstractDatabaseRepository<Long, User> implements UserRepository {

    public UserDatabaseRepositoryImpl(Properties properties) {
        super(properties);
    }

    @Override
    protected User extractEntity(ResultSet resultSet) throws SQLException {
        return new User(
                resultSet.getLong("id"),
                resultSet.getString("name"),
                resultSet.getString("email"),
                resultSet.getString("password")
        );
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from users where id = ?";
    }

    @Override
    protected void setIdParameter(PreparedStatement statement, Long aLong) throws SQLException {
        statement.setLong(1, aLong);
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from users";
    }

    @Override
    protected String getSaveQuery() {
        return "insert into users (name, email, password) values (?, ?, ?)";
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, User entity) throws SQLException {
        statement.setString(1, entity.getName());
        statement.setString(2, entity.getEmail());
        statement.setString(3, entity.getPassword());
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from users where id = ?";
    }

    @Override
    protected String getUpdateQuery() {
        return "update users set name = ?, email = ?, password = ? where id = ?";
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, User entity) throws SQLException {
        statement.setString(1, entity.getName());
        statement.setString(2, entity.getEmail());
        statement.setString(3, entity.getPassword());
        statement.setInt(4, toIntExact(entity.getId()));
    }

    @Override
    public Optional<User> findByEmailAndPass(String email, String pass) {
        logger.info("Se incerca conexiunea la baza de date");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from users where email = ? and password = ?")
        ) {
            statement.setString(1, email);
            statement.setString(2, pass);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                User user1 = extractEntity(resultSet);
                logger.info("Entitatea a fost gasita: " + user1);
                return Optional.of(user1);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    @Override
    public Optional<User> findByEmail(String email) {
        logger.info("Se incerca conexiunea la baza de date");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from users where email = ?")
        ) {
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                User user1 = extractEntity(resultSet);
                logger.info("Entitatea a fost gasita: " + user1);
                return Optional.of(user1);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }
}
