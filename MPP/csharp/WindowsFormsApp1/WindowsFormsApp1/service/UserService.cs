using System;
using WindowsFormsApp1.domain;
using WindowsFormsApp1.repository;

namespace WindowsFormsApp1.service;

public class UserService(IUserRepository userRepository) : IUserService
{
    private IUserRepository _userRepository = userRepository;
    
    public User RegisterUser(User user)
    {
        if (_userRepository.FindUserByEmail(user.Email) != null)
        {
            throw new Exception("User already exists");
        }

        _userRepository.Save(user);
        return _userRepository.FindUserByEmail(user.Email);
    }

    public User LogInUser(string email, string pass)
    {
        User user = _userRepository.FindUserByEmailAndPass(email, pass);
        if (user == null)
        {
            throw new Exception("User not found");
        }

        return user;
    }
}