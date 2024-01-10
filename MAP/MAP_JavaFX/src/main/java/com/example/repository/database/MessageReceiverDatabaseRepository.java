package com.example.repository.database;

import com.example.domain.Message;
import com.example.domain.MessageReceiver;
import com.example.domain.Tuple;
import com.example.domain.validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MessageReceiverDatabaseRepository extends AbstractDatabaseRepository<Long, MessageReceiver> {

    public MessageReceiverDatabaseRepository(String url, String username, String password, Validator<Long, MessageReceiver> validator) {
        super(url, username, password, validator);
    }

    @Override
    protected MessageReceiver extractEntity(ResultSet resultSet) throws SQLException {
        long id = resultSet.getLong("id");
        long toId = resultSet.getLong("to_id");
        long messageId = resultSet.getLong("message_id");

        return new MessageReceiver(id, toId, messageId);
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from messages_receivers where id = ?";
    }

    @Override
    protected void setFindOneParameters(PreparedStatement statement, Long id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id));
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from messages_receivers";
    }

    @Override
    protected String getSaveQuery() {
        return "insert into messages_receivers (to_id, message_id) values (?, ?)";
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, MessageReceiver entity) throws SQLException {
        statement.setInt(1, Math.toIntExact(entity.getToId()));
        statement.setInt(2, Math.toIntExact(entity.getMessageId()));
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from messages_receivers where id = ?";
    }

    @Override
    protected void setDeleteParameters(PreparedStatement statement, Long id) throws SQLException {
        statement.setInt(1, Math.toIntExact(id));
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, MessageReceiver entity) throws SQLException {
        statement.setInt(1, Math.toIntExact(entity.getToId()));
        statement.setInt(2, Math.toIntExact(entity.getMessageId()));
        statement.setInt(3, Math.toIntExact(entity.getId()));
    }

    @Override
    protected String getUpdateQuery() {
        return "update messages_receivers set to_id = ?, message_id = ? where id = ?";
    }

    @Override
    protected String getCountQuery() {
        return "select count(*) as count from messages_receivers";
    }

    @Override
    protected String getFindAllPagedQuery() {
        return "select * from messages_receivers limit ? offset ?";
    }

}
