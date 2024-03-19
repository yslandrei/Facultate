package org.example.repository;

import org.example.domain.Ticket;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;

public class TicketDatabaseRepositoryImpl extends AbstractDatabaseRepository<Long, Ticket> implements TicketRepository {

    private final UserRepository userRepository;

    private final ConcertRepository concertRepository;

    public TicketDatabaseRepositoryImpl(UserRepository userRepository, ConcertRepository concertRepository, Properties properties) {
        super(properties);
        this.userRepository = userRepository;
        this.concertRepository = concertRepository;
    }

    @Override
    protected Ticket extractEntity(ResultSet resultSet) throws SQLException {
        return new Ticket(
                resultSet.getLong("id"),
                concertRepository.findOne(resultSet.getLong("concert_id")).orElseThrow(),
                userRepository.findOne(resultSet.getLong("user_id")).orElseThrow(),
                resultSet.getString("buyer"),
                resultSet.getInt("seats")
        );
    }

    @Override
    protected String getFindOneQuery() {
        return "select * from tickets where id = ?";
    }

    @Override
    protected void setIdParameter(PreparedStatement statement, Long aLong) throws SQLException {
        statement.setLong(1, aLong);
    }

    @Override
    protected String getFindAllQuery() {
        return "select * from tickets";
    }

    @Override
    protected String getSaveQuery() {
        return "insert into tickets (concert_id, user_id, buyer, seats) values (?, ?, ?, ?)";
    }

    @Override
    protected void setSaveParameters(PreparedStatement statement, Ticket entity) throws SQLException {
        statement.setLong(1, entity.getConcert().getId());
        statement.setLong(2, entity.getUser().getId());
        statement.setString(3, entity.getBuyer());
        statement.setInt(4, entity.getSeats());
    }

    @Override
    protected String getDeleteQuery() {
        return "delete from tickets where id = ?";
    }

    @Override
    protected String getUpdateQuery() {
        return "update tickets set concert_id = ?, user_id = ?, buyer = ?, seats = ? where id = ?";
    }

    @Override
    protected void setUpdateParameters(PreparedStatement statement, Ticket entity) throws SQLException {
        statement.setLong(1, entity.getConcert().getId());
        statement.setLong(2, entity.getUser().getId());
        statement.setString(3, entity.getBuyer());
        statement.setInt(4, entity.getSeats());
        statement.setLong(5, entity.getId());
    }
}
