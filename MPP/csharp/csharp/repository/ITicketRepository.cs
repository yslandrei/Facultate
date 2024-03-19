using csharp.domain;

namespace csharp.repository;

public interface ITicketRepository : IRepository<long, Ticket>
{
    
}