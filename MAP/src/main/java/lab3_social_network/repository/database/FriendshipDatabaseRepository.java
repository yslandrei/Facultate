package lab3_social_network.repository.database;

import lab3_social_network.domain.Friendship;
import lab3_social_network.domain.Tuple;
import lab3_social_network.domain.validators.Validator;
import lab3_social_network.repository.database.AbstractDatabaseRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;


public class FriendshipDatabaseRepository extends AbstractDatabaseRepository<Tuple<Long, Long>, Friendship> {

    public FriendshipDatabaseRepository(String url, String username, String password, Validator<Tuple<Long, Long>, Friendship> validator) {
        super(url, username, password, validator);
    }

    @Override
    protected Friendship extractEntity(ResultSet resultSet) throws SQLException {
        long user1Id = resultSet.getLong("user1_id");
        long user2Id = resultSet.getLong("user2_id");
        Tuple<Long, Long> friendshipId = new Tuple<>(user1Id, user2Id);

        LocalDateTime createdDate = resultSet.getTimestamp("created_date").toLocalDateTime();

        return new Friendship(friendshipId, createdDate);
    }

    @Override
    protected void populateStatement(PreparedStatement statement, Friendship entity) throws SQLException {
        statement.setInt(1, Math.toIntExact(entity.getId().getLeft()));
        statement.setInt(2, Math.toIntExact(entity.getId().getRight()));
        statement.setTimestamp(3, java.sql.Timestamp.valueOf(entity.getCreatedDate()));
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from friendships where user1_id = ? and user2_id = ?";
    }

    @Override
    protected void setFindOneParameters(PreparedStatement statement, Tuple<Long, Long> id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id.getLeft()));
        statement.setInt(2, Math.toIntExact(id.getRight()));
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from friendships";
    }

    @Override
    protected String getSaveQuery() {
        return "insert into friendships (user1_id, user2_id, created_date) values (?, ?, ?)";
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from friendships where user1_id = ? and user2_id = ?";
    }

    @Override
    protected void setDeleteParameters(PreparedStatement statement, Tuple<Long, Long> id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id.getLeft()));
        statement.setInt(2, Math.toIntExact(id.getRight()));
    }

    @Override
    protected String getUpdateQuery() {
        return "update friendships set created_date = ? where user1_id = ? and user2_id = ?";
    }
}
