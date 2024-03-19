package org.example.repository;

import org.example.domain.Concert;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class ConcertDatabaseRepositoryImpl extends AbstractDatabaseRepository<Long, Concert> implements ConcertRepository {

    public ConcertDatabaseRepositoryImpl(Properties properties) {
        super(properties);
    }

    @Override
    protected Concert extractEntity(ResultSet resultSet) throws SQLException {
        return new Concert(
                resultSet.getLong("id"),
                resultSet.getString("artist"),
                resultSet.getTimestamp("date").toLocalDateTime(),
                resultSet.getString("location"),
                resultSet.getInt("available_tickets")
        );
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from concerts where id = ?";
    }

    @Override
    protected void setIdParameter(PreparedStatement statement, Long aLong) throws SQLException {
        statement.setLong(1, Math.toIntExact(aLong));
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from concerts";
    }

    @Override
    protected String getSaveQuery() {
        return "insert into concerts (artist, date, location, available_tickets) values (?, ?, ?, ?)";
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, Concert entity) throws SQLException {
        statement.setString(1, entity.getArtist());
        statement.setTimestamp(2, java.sql.Timestamp.valueOf(entity.getDate()));
        statement.setString(3, entity.getLocation());
        statement.setInt(4, entity.getAvailableTickets());
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from concerts where id = ?";
    }

    @Override
    protected String getUpdateQuery() {
        return "update concerts set artist = ?, date = ?, location = ?, available_tickets = ? where id = ?";
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, Concert entity) throws SQLException {
        statement.setString(1, entity.getArtist());
        statement.setTimestamp(2, java.sql.Timestamp.valueOf(entity.getDate()));
        statement.setString(3, entity.getLocation());
        statement.setInt(4, entity.getAvailableTickets());
        statement.setLong(5, entity.getId());
    }

    @Override
    public List<Concert> findAllByDate(LocalDateTime date) {
        logger.info("Se incearca conexiunea la baza de date");
        List<Concert> concerts = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from concerts where cast(date as DATE) = ?")
        ) {
            statement.setDate(1, Date.valueOf(date.toLocalDate()));
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Concert concert = extractEntity(resultSet);
                logger.info("Entitatea a fost gasita: " + concert);
                concerts.add(concert);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return concerts;
    }
}
