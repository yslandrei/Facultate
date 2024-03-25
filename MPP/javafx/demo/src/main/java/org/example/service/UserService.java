package org.example.service;

import org.example.domain.User;

public interface UserService {

    User registerUser(User user);

    User logInUser(String email, String pass);

}
