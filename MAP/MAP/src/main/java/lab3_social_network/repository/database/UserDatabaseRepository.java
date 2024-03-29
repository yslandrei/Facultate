package lab3_social_network.repository.database;
import lab3_social_network.domain.User;
import lab3_social_network.domain.validators.UserValidator;
import lab3_social_network.domain.validators.Validator;
import lab3_social_network.repository.database.AbstractDatabaseRepository;

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
    protected void populateStatement(PreparedStatement statement, User entity) throws SQLException {
        statement.setInt(1, toIntExact(entity.getId()));
        statement.setString(2, entity.getFirstName());
        statement.setString(3, entity.getLastName());
        statement.setString(4, entity.getUsername());
        statement.setString(5, entity.getPassword());
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
        return "insert into users (id, first_name, last_name, username, password) values (?, ?, ?, ?, ?)";
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
}
