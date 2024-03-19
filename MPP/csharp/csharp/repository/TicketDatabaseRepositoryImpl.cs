using System.Data;
using csharp.domain;
using Npgsql;
namespace csharp.repository;

public class TicketDatabaseRepositoryImpl : AbstractDatabaseRepository<long, Ticket>, ITicketRepository
{

    private ConcertDatabaseRepositoryImpl concertDatabaseRepository;
    
    public TicketDatabaseRepositoryImpl(string? url) : base(url)
    {
        concertDatabaseRepository = new ConcertDatabaseRepositoryImpl(url);
    }

    protected override Ticket ExtractEntity(NpgsqlDataReader resultSet)
    {
        return new Ticket(
            resultSet.GetInt64("id"),
            concertDatabaseRepository.FindOne(resultSet.GetInt64("concert_id")),
            resultSet.GetString("buyer"),
            resultSet.GetInt32("seats")
        );
    }

    protected override void PopulateStatement(NpgsqlCommand statement, Ticket entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@concert_id", entity.Concert.Id);
        statement.Parameters.AddWithValue("@buyer", entity.Buyer);
        statement.Parameters.AddWithValue("@seats", entity.Seats);
    }

    protected override string GetFindOneQuery()
    {
        return "select * from tickets where id = @id";
    }


    protected override string GetFindAllQuery()
    {
        return "select * from tickets";
    }


    protected override string GetSaveQuery()
    {
        return "insert into tickets (id, concert_id, buyer, seats) values (@id, @concert_id, @buyer, @seats)";
    }

    protected override void SetSaveQueryParameters(NpgsqlCommand statement, Ticket entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@concert_id", entity.Concert.Id);
        statement.Parameters.AddWithValue("@buyer", entity.Buyer);
        statement.Parameters.AddWithValue("@seats", entity.Seats);
    }

    protected override string GetDeleteQuery()
    {
        return "delete from tickets where id = @id";
    }

    protected override string GetUpdateQuery()
    {
        return "update tickets set concert_id = @concert_id, buyer = @buyer, seats = @seats where id = @id";
    }

    protected override void SetUpdateQueryParameters(NpgsqlCommand statement, Ticket entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@concert_id", entity.Concert.Id);
        statement.Parameters.AddWithValue("@buyer", entity.Buyer);
        statement.Parameters.AddWithValue("@seats", entity.Seats);
    }
}