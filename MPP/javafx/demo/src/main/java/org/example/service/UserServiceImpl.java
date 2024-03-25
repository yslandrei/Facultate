package org.example.service;

import org.example.domain.User;
import org.example.repository.UserRepository;

public class UserServiceImpl implements UserService {

    private final UserRepository userRepository;

    public UserServiceImpl(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public User registerUser(User user) {
        userRepository.findByEmail(user.getEmail())
                .ifPresent(u -> {
                    throw new RuntimeException("User already exists");
                });
        userRepository.save(new User(user.getName(), user.getEmail(), user.getPassword()));
        return userRepository.findByEmail(user.getEmail()).get();
    }

    @Override
    public User logInUser(String email, String pass) {
        return userRepository.findByEmailAndPass(email, pass)
                .orElseThrow(() -> new RuntimeException("User not found"));
    }
}
