using csharp.domain;

namespace csharp.repository;

public interface IConcertRepository : IRepository<long, Concert>
{
    List<Concert> FindAllByDate(DateTime dateTime);
    
}