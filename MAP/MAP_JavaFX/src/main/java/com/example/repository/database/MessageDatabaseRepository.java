package com.example.repository.database;

import com.example.domain.Message;
import com.example.domain.validators.Validator;

import java.sql.*;
import java.time.LocalDateTime;

public class MessageDatabaseRepository extends AbstractDatabaseRepository<Long, Message> {

    public MessageDatabaseRepository(String url, String username, String password, Validator<Long, Message> validator) {
        super(url, username, password, validator);
    }

    @Override
    protected Message extractEntity(ResultSet resultSet) throws SQLException {
        long id = resultSet.getLong("id");
        long fromId = resultSet.getLong("from_id");
        String message = resultSet.getString("message");
        LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();
        long replyId = resultSet.getLong("reply_id");

        if (replyId == 0)
            return new Message(id, fromId, message, date, null);
        else

        return new Message(id, fromId, message, date, replyId);
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from messages where id = ?";
    }

    @Override
    protected void setFindOneParameters(PreparedStatement statement, Long id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id));
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from messages";
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, Message entity) throws SQLException {
        statement.setInt(1, Math.toIntExact(entity.getFromId()));
        statement.setString(2, entity.getMessage());
        statement.setTimestamp(3, java.sql.Timestamp.valueOf(entity.getDate()));
        if (entity.getReplyId() == null)
            statement.setNull(4, java.sql.Types.NULL);
        else
            statement.setInt(4, Math.toIntExact(entity.getReplyId()));
    }

    @Override
    protected String getSaveQuery() {
        return "insert into messages (from_id, message, date, reply_id) values (?, ?, ?, ?)";
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from messages where id = ?";
    }

    @Override
    protected void setDeleteParameters(PreparedStatement statement, Long id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id));
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, Message entity) throws SQLException {
        statement.setInt(1, Math.toIntExact(entity.getFromId()));
        statement.setString(2, entity.getMessage());
        statement.setTimestamp(3, java.sql.Timestamp.valueOf(entity.getDate()));
        if (entity.getReplyId() == null)
            statement.setNull(4, java.sql.Types.NULL);
        else
            statement.setInt(4, Math.toIntExact(entity.getReplyId()));
        statement.setInt(5, Math.toIntExact(entity.getId()));

    }

    @Override
    protected String getUpdateQuery() {
        return "update messages set from_id = ?, message = ?, date = ?, reply_id = ? where id = ?";
    }

}
