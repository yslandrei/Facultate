package com.example.repository.database;
import com.example.domain.User;
import com.example.domain.validators.UserValidator;
import com.example.domain.validators.Validator;
import com.example.repository.database.AbstractDatabaseRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import static java.lang.Math.toIntExact;

public class UserDatabaseRepository extends AbstractDatabaseRepository<Long, User> {

    public UserDatabaseRepository(String url, String username, String password, Validator<Long, User> validator) {
        super(url, username, password, validator);
    }

    @Override
    protected User extractEntity(ResultSet resultSet) throws SQLException {
        return new User(
                resultSet.getLong("id"),
                resultSet.getString("first_name"),
                resultSet.getString("last_name"),
                resultSet.getString("username"),
                resultSet.getString("password")
        );
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, User entity) throws SQLException {
        statement.setString(1, entity.getFirstName());
        statement.setString(2, entity.getLastName());
        statement.setString(3, entity.getUsername());
        statement.setString(4, entity.getPassword());
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, User entity) throws SQLException {
        statement.setString(1, entity.getFirstName());
        statement.setString(2, entity.getLastName());
        statement.setString(3, entity.getUsername());
        statement.setString(4, entity.getPassword());
        statement.setInt(5, toIntExact(entity.getId()));
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from users where id = ?";
    }

    @Override
    protected void setFindOneParameters(PreparedStatement statement, Long id) throws SQLException {
        statement.setInt(1, toIntExact(id));
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from users";
    }

    @Override
    protected String getSaveQuery() {
        return "insert into users (first_name, last_name, username, password) values (?, ?, ?, ?)";
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from users where id = ?";
    }

    @Override
    protected void setDeleteParameters(PreparedStatement statement, Long id) throws SQLException {
        statement.setInt(1, toIntExact(id));
    }

    @Override
    protected String getUpdateQuery() {
        return "update users set first_name = ?, last_name = ?, username = ?, password = ? where id = ?";
    }

    @Override
    protected String getCountQuery() {
        return "select count(*) as count from users";
    }

    @Override
    protected String getFindAllPagedQuery() {
        return "select * from users limit ? offset ?";
    }

}
