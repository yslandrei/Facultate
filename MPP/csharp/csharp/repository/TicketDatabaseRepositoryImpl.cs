using System.Data;
using csharp.domain;
using Npgsql;
namespace csharp.repository;

public class TicketDatabaseRepositoryImpl : AbstractDatabaseRepository<long, Ticket>, ITicketRepository
{

    private IConcertRepository _concertRepository;

    private IUserRepository _userRepository; 
    
    public TicketDatabaseRepositoryImpl(string url, IConcertRepository concertRepository, IUserRepository userRepository) : base(url)
    {
        _concertRepository = concertRepository;
        _userRepository = userRepository;
    }

    protected override Ticket ExtractEntity(NpgsqlDataReader resultSet)
    {
        return new Ticket(
            resultSet.GetInt64("id"),
            _concertRepository.FindOne(resultSet.GetInt64("concert_id")),
            resultSet.GetString("buyer"),
            resultSet.GetInt32("seats"),
            _userRepository.FindOne(resultSet.GetInt64("user_id"))
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