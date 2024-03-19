using System.Data;
using csharp.domain;
using Npgsql;
namespace csharp.repository;

public class ConcertDatabaseRepositoryImpl : AbstractDatabaseRepository<long, Concert>, IConcertRepository
{
    public ConcertDatabaseRepositoryImpl(string? url) : base(url)
    {
    }

    protected override Concert ExtractEntity(NpgsqlDataReader resultSet)
    {
        return new Concert(
            resultSet.GetInt64("id"),
            resultSet.GetString("artist"),
            resultSet.GetDateTime("date"),
            resultSet.GetString("location"),
            resultSet.GetInt32("available_tickets")
        );
    }

    protected override void PopulateStatement(NpgsqlCommand statement, Concert entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@artist", entity.Artist);
        statement.Parameters.AddWithValue("@date", entity.Date);
        statement.Parameters.AddWithValue("@location", entity.Location);
        statement.Parameters.AddWithValue("@available_tickets", entity.AvailableTickets);
    }

    protected override string GetFindOneQuery()
    {
        return "select * from concerts where id = @id";
    }


    protected override string GetFindAllQuery()
    {
        return "select * from concerts";
    }


    protected override string GetSaveQuery()
    {
        return "insert into concerts (id, artist, date, location, available_tickets) values (@id, @artist, @date, @location, @available_tickets)";
    }

    protected override void SetSaveQueryParameters(NpgsqlCommand statement, Concert entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@artist", entity.Artist);
        statement.Parameters.AddWithValue("@date", entity.Date);
        statement.Parameters.AddWithValue("@location", entity.Location);
        statement.Parameters.AddWithValue("@available_tickets", entity.AvailableTickets);
    }

    protected override string GetDeleteQuery()
    {
        return "delete from concerts where id = @id";
    }

    protected override string GetUpdateQuery()
    {
        return "update concerts set artist = @artist, date = @date, location = @location, available_tickets = @available_tickets where id = @id";
    }

    protected override void SetUpdateQueryParameters(NpgsqlCommand statement, Concert entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@artist", entity.Artist);
        statement.Parameters.AddWithValue("@date", entity.Date);
        statement.Parameters.AddWithValue("@location", entity.Location);
        statement.Parameters.AddWithValue("@available_tickets", entity.AvailableTickets);
    }
}