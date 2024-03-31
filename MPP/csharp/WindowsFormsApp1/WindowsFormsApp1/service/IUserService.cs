using System;
using WindowsFormsApp1.domain;

namespace WindowsFormsApp1.service;

public interface IUserService
{
    User RegisterUser(User user);

    User LogInUser(String email, String pass);
}