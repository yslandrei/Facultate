using System;
using System.Collections.Generic;
using System.Data;
using csharp.domain;
using Npgsql;
using Serilog;
using Serilog.Core;

namespace csharp.repository;

public abstract class AbstractDatabaseRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
{
    private readonly string url;

    public AbstractDatabaseRepository(string url)
    {
        this.url = url;
    }

    protected abstract E ExtractEntity(NpgsqlDataReader resultSet);

    protected abstract void PopulateStatement(NpgsqlCommand statement, E entity);

    public virtual E FindOne(ID id)
    {
        Log.Information("Se incearca conexiunea cu baza de date");
        using (NpgsqlConnection connection = new NpgsqlConnection(url))
        {
            connection.Open();
            using (NpgsqlCommand statement = connection.CreateCommand())
            {
                statement.CommandText = GetFindOneQuery();
                statement.Parameters.AddWithValue("@id", id);
                using (NpgsqlDataReader resultSet = statement.ExecuteReader())
                {
                    if (resultSet.Read())
                    {
                        Log.Information("S-a gasit entitatea cu id-ul: " + id);
                        return ExtractEntity(resultSet);
                    }
                }
            }
        }
        return default;
    }

    protected abstract string GetFindOneQuery();

    public virtual List<E> FindAll()
    {
        List<E> entities = new List<E>();
        Log.Information("Se incearca conexiunea cu baza de date");
        using (NpgsqlConnection connection = new NpgsqlConnection(url))
        {
            connection.Open();
            using (NpgsqlCommand statement = connection.CreateCommand())
            {
                statement.CommandText = GetFindAllQuery();
                using (NpgsqlDataReader resultSet = statement.ExecuteReader())
                {
                    while (resultSet.Read())
                    {
                        E entity = ExtractEntity(resultSet);
                        Log.Information("S-a gasit entitatea cu id-ul: " + entity.Id);
                        entities.Add(entity);
                    }
                }
            }
        }
        return entities;
    }

    protected abstract string GetFindAllQuery();

    public virtual E Save(E entity)
    {
        Log.Information("Se incearca conexiunea cu baza de date");
        using (NpgsqlConnection connection = new NpgsqlConnection(url))
        {
            connection.Open();
            using (NpgsqlCommand statement = connection.CreateCommand())
            {
                statement.CommandText = GetSaveQuery();
                PopulateStatement(statement, entity);
                int rowsInserted = statement.ExecuteNonQuery();
                if (rowsInserted == 0)
                {
                    Log.Information("S-a gasit entitatea cu id-ul: " + entity.Id);
                    return entity;
                }
            }
        }
        return default;
    }

    protected abstract string GetSaveQuery();
    
    protected abstract void SetSaveQueryParameters(NpgsqlCommand statement, E entity);

    public virtual E Delete(ID id)
    {
        Log.Information("Se incearca conexiunea cu baza de date");
        E entity = FindOne(id);
        if (entity != null)
        {
            using (NpgsqlConnection connection = new NpgsqlConnection(url))
            {
                connection.Open();
                using (NpgsqlCommand statement = connection.CreateCommand())
                {
                    statement.CommandText = GetDeleteQuery();
                    statement.Parameters.AddWithValue("@id", id);
                    Log.Information("S-a sters entitatea cu id-ul: " + id);
                    statement.ExecuteNonQuery();
                }
            }
        }
        return entity;
    }

    protected abstract string GetDeleteQuery();
    
    public virtual E Update(E entity)
    {
        Log.Information("Se incearca conexiunea cu baza de date");
        using (NpgsqlConnection connection = new NpgsqlConnection(url))
        {
            connection.Open();
            using (NpgsqlCommand statement = connection.CreateCommand())
            {
                statement.CommandText = GetUpdateQuery();
                PopulateStatement(statement, entity);
                int rowsUpdated = statement.ExecuteNonQuery();
                if (rowsUpdated == 0)
                {
                    Log.Information("S-a updatat entitatea cu id-ul: " + entity.Id);
                    return entity;
                }
            }
        }
        return default;
    }

    protected abstract string GetUpdateQuery();
    
    protected abstract void SetUpdateQueryParameters(NpgsqlCommand statement, E entity);

}
