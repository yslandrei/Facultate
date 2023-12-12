package com.example.repository.database;

import com.example.domain.Friendship;
import com.example.domain.FriendshipRequest;
import com.example.domain.FriendshipRequestStatus;
import com.example.domain.Tuple;
import com.example.domain.validators.Validator;
import com.example.repository.database.AbstractDatabaseRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;


public class FriendshipRequestDatabaseRepository extends AbstractDatabaseRepository<Tuple<Long, Long>, FriendshipRequest> {

    public FriendshipRequestDatabaseRepository(String url, String username, String password, Validator<Tuple<Long, Long>, FriendshipRequest> validator) {
        super(url, username, password, validator);
    }

    @Override
    protected FriendshipRequest extractEntity(ResultSet resultSet) throws SQLException {
        long user1Id = resultSet.getLong("user1_id");
        long user2Id = resultSet.getLong("user2_id");
        Tuple<Long, Long> friendshipRequestId = new Tuple<>(user1Id, user2Id);
        LocalDateTime createdDate = resultSet.getTimestamp("created_date").toLocalDateTime();
        FriendshipRequestStatus status = FriendshipRequestStatus.valueOf(resultSet.getString("status"));

        return new FriendshipRequest(friendshipRequestId, createdDate, status);
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from friendship_requests where user1_id = ? and user2_id = ?";
    }

    @Override
    protected void setFindOneParameters(PreparedStatement statement, Tuple<Long, Long> id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id.getLeft()));
        statement.setInt(2, Math.toIntExact(id.getRight()));
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from friendship_requests";
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, FriendshipRequest entity) throws SQLException {
        statement.setInt(1, Math.toIntExact(entity.getId().getLeft()));
        statement.setInt(2, Math.toIntExact(entity.getId().getRight()));
        statement.setTimestamp(3, java.sql.Timestamp.valueOf(entity.getCreatedDate()));
        statement.setString(4, entity.getStatus().toString());
    }

    @Override
    protected String getSaveQuery() {
        return "insert into friendship_requests (user1_id, user2_id, created_date, status) values (?, ?, ?, ?)";
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from friendship_requests where user1_id = ? and user2_id = ?";
    }

    @Override
    protected void setDeleteParameters(PreparedStatement statement, Tuple<Long, Long> id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id.getLeft()));
        statement.setInt(2, Math.toIntExact(id.getRight()));
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, FriendshipRequest entity) throws SQLException {
        statement.setTimestamp(1, java.sql.Timestamp.valueOf(entity.getCreatedDate()));
        statement.setString(2, entity.getStatus().toString());
        statement.setInt(3, Math.toIntExact(entity.getId().getLeft()));
        statement.setInt(4, Math.toIntExact(entity.getId().getRight()));
    }

    @Override
    protected String getUpdateQuery() {
        return "update friendship_requests set created_date = ?, status = ? where user1_id = ? and user2_id = ?";
    }
}
