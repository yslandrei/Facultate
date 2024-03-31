using csharp.domain;

namespace csharp.repository;

public interface IUserRepository : IRepository<long, User>
{
    User FindUserByEmailAndPass(String email, String pass);

    User FindUserByEmail(String email);

}