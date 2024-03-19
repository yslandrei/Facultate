using System.Data;
using csharp.domain;
using Npgsql;
namespace csharp.repository;


public class UserDatabaseRepositoryImpl : AbstractDatabaseRepository<long, User>, IUserRepository
{
    public UserDatabaseRepositoryImpl(string? url) : base(url)
    {
    }

    protected override User ExtractEntity(NpgsqlDataReader resultSet)
    {
        return new User(
            resultSet.GetInt64("id"),
            resultSet.GetString("name"),
            resultSet.GetString("email"),
            resultSet.GetString("password")
        );
    }

    protected override void PopulateStatement(NpgsqlCommand statement, User entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@name", entity.Name);
        statement.Parameters.AddWithValue("@email", entity.Email);
        statement.Parameters.AddWithValue("@password", entity.Password);
    }

    protected override string GetFindOneQuery()
    {
        return "select * from users where id = @id";
    }


    protected override string GetFindAllQuery()
    {
        return "select * from users";
    }


    protected override string GetSaveQuery()
    {
        return "insert into users (id, name, email, password) values (@id, @name, @email, @password)";
    }

    protected override void SetSaveQueryParameters(NpgsqlCommand statement, User entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@name", entity.Name);
        statement.Parameters.AddWithValue("@email", entity.Email);
        statement.Parameters.AddWithValue("@password", entity.Password);
    }

    protected override string GetDeleteQuery()
    {
        return "delete from users where id = @id";
    }

    protected override string GetUpdateQuery()
    {
        return "update users set name = @name, email = @email, password = @password where id = @id";
    }

    protected override void SetUpdateQueryParameters(NpgsqlCommand statement, User entity)
    {
        statement.Parameters.AddWithValue("@id", entity.Id);
        statement.Parameters.AddWithValue("@name", entity.Name);
        statement.Parameters.AddWithValue("@email", entity.Email);
        statement.Parameters.AddWithValue("@password", entity.Password);
    }
}