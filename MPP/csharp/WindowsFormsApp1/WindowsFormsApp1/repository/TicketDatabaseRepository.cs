using System.Data;
using WindowsFormsApp1.domain;
using Npgsql;
namespace WindowsFormsApp1.repository;

public class TicketDatabaseRepository : AbstractDatabaseRepository<long, Ticket>, ITicketRepository
{

    private IConcertRepository _concertRepository;

    private IUserRepository _userRepository; 
    
    public TicketDatabaseRepository(string url, IConcertRepository concertRepository, IUserRepository userRepository) : base(url)
    {
        _concertRepository = concertRepository;
        _userRepository = userRepository;
    }

    protected override Ticket ExtractEntity(NpgsqlDataReader resultSet)
    {
        return new Ticket(
            resultSet.GetInt64(0),
            _concertRepository.FindOne(resultSet.GetInt64(1)),
            resultSet.GetString(2),
            resultSet.GetInt32(3),
            _userRepository.FindOne(resultSet.GetInt64(4))
        );
    }

    protected override string GetFindOneQuery()
    {
        return "select * from tickets where id = @id";
    }

    protected override void SetIdParameter(NpgsqlCommand statement, long id)
    {
        statement.Parameters.AddWithValue("@id", id);
    }


    protected override string GetFindAllQuery()
    {
        return "select * from tickets";
    }


    protected override string GetSaveQuery()
    {
        return "insert into tickets (concert_id, buyer, seats, user_id) values (@concert_id, @buyer, @seats, @user_id)";
    }

    protected override void SetSaveQueryParameters(NpgsqlCommand statement, Ticket entity)
    {
        statement.Parameters.AddWithValue("@concert_id", entity.Concert.Id);
        statement.Parameters.AddWithValue("@buyer", entity.Buyer);
        statement.Parameters.AddWithValue("@seats", entity.Seats);
        statement.Parameters.AddWithValue("@user_id", entity.User.Id);
    }

    protected override string GetDeleteQuery()
    {
        return "delete from tickets where id = @id";
    }

    protected override string GetUpdateQuery()
    {
        return "update tickets set concert_id = @concert_id, buyer = @buyer, seats = @seats, user_id = @user_id where id = @id";
    }

    protected override void SetUpdateQueryParameters(NpgsqlCommand statement, Ticket entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@concert_id", entity.Concert.Id);
        statement.Parameters.AddWithValue("@buyer", entity.Buyer);
        statement.Parameters.AddWithValue("@seats", entity.Seats);
        statement.Parameters.AddWithValue("@user_id", entity.User.Id);
    }
}