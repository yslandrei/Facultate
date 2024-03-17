using System;
using System.Collections.Generic;
using System.Data;
using csharp.domain;
using Npgsql;

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
                    statement.ExecuteNonQuery();
                }
            }
        }
        return entity;
    }

    protected abstract string GetDeleteQuery();
    
    public virtual E Update(E entity)
    {
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
                    return entity;
                }
            }
        }
        return default;
    }

    protected abstract string GetUpdateQuery();
    
    protected abstract void SetUpdateQueryParameters(NpgsqlCommand statement, E entity);

}
