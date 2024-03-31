using System;
using WindowsFormsApp1.domain;

namespace WindowsFormsApp1.repository;

public interface IUserRepository : IRepository<long, User>
{
    User FindUserByEmailAndPass(String email, String pass);

    User FindUserByEmail(String email);

}