namespace csharp.domain;

public abstract class Entity<T>(T id)
{
    public T Id { get; set; } = id;
}