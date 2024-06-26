using System.Data;
using csharp.domain;
using Npgsql;
using Serilog;

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

    protected override string GetFindOneQuery()
    {
        return "select * from users where id = @id";
    }

    protected override void SetIdParameter(NpgsqlCommand statement, long id)
    {
        statement.Parameters.AddWithValue("@id", id);
    }


    protected override string GetFindAllQuery()
    {
        return "select * from users";
    }


    protected override string GetSaveQuery()
    {
        return "insert into users (name, email, password) values (@name, @email, @password)";
    }

    protected override void SetSaveQueryParameters(NpgsqlCommand statement, User entity)
    {
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

    public User FindUserByEmailAndPass(string email, string pass)
    {
        Log.Information("Se incearca conexiunea cu baza de date");
        using (NpgsqlConnection connection = new NpgsqlConnection(url))
        {
            connection.Open();
            using (NpgsqlCommand statement = connection.CreateCommand())
            {
                statement.CommandText = "select * from users where email = @email and password = @password";
                statement.Parameters.AddWithValue("@email", email);
                statement.Parameters.AddWithValue("@password", pass);
                using (NpgsqlDataReader resultSet = statement.ExecuteReader())
                {
                    if (resultSet.Read())
                    {
                        return ExtractEntity(resultSet);
                    }
                }
            }
        }
        return null;
    }

    public User FindUserByEmail(string email)
    {
        Log.Information("Se incearca conexiunea cu baza de date");
        using (NpgsqlConnection connection = new NpgsqlConnection(url))
        {
            connection.Open();
            using (NpgsqlCommand statement = connection.CreateCommand())
            {
                statement.CommandText = "select * from users where email = @email";
                statement.Parameters.AddWithValue("@email", email);
                using (NpgsqlDataReader resultSet = statement.ExecuteReader())
                {
                    if (resultSet.Read())
                    {
                        return ExtractEntity(resultSet);
                    }
                }
            }
        }
        return null;
    }
}