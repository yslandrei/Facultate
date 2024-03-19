package org.example.service;

import org.example.domain.User;

public interface UserService {

    User registerUser(String name, String email, String pass);

    User logInUser(String user, String pass);

}
