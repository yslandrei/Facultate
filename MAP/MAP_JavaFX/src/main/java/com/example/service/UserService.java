package com.example.service;

import com.example.domain.*;
import com.example.domain.exceptions.EntityAlreadyExistsException;
import com.example.domain.exceptions.EntityDoesNotExistException;
import com.example.repository.Repository;
import com.example.repository.database.FriendshipDatabaseRepository;
import com.example.repository.database.UserDatabaseRepository;
import com.example.utils.observer.Observable;
import com.example.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicReference;

public class UserService implements Observable {

    private final UserDatabaseRepository userRepository;

    private final FriendshipDatabaseRepository friendshipRepository;

    private List<Observer> observers = new ArrayList<>();

    public UserService(UserDatabaseRepository userRepository, FriendshipDatabaseRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    public void registerUser(User user) {
        if (userRepository.save(user).isPresent())
            throw new EntityAlreadyExistsException(user);
    }

    public User checkUser(String username, String password) {
        AtomicReference<Boolean> found = new AtomicReference<>(false);
        AtomicReference<User> foundUser = new AtomicReference<>(null);
        userRepository.findAll().forEach(user -> {
            if (Objects.equals(user.getUsername(), username) && Objects.equals(user.getPassword(), password)) {
                found.set(true);
                foundUser.set(user);
            }
        }); 

        if (!found.get())
            throw new RuntimeException("Username or password incorrect!");

        return foundUser.get();
    }

    public User getUserByUsername(String username) {
        AtomicReference<Boolean> found = new AtomicReference<>(false);
        AtomicReference<User> foundUser = new AtomicReference<>(null);
        userRepository.findAll().forEach(user -> {
            if (Objects.equals(user.getUsername(), username)) {
                found.set(true);
                foundUser.set(user);
            }
        });

        if (!found.get())
            throw new RuntimeException("No user with this username!");

        return foundUser.get();
    }

    public void removeUser(Long id) {
        User deletedUser = userRepository.delete(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));

        friendshipRepository.findAll().forEach(friendship -> {
            if (Objects.equals(friendship.getId().getLeft(), id)) {
                friendshipRepository.delete(friendship.getId());
            }
            else if (Objects.equals(friendship.getId().getRight(), id)) {
                friendshipRepository.delete(friendship.getId());
            }
        });

        notifyObservers();
    }

    public void updateUser(User user) {
        if (userRepository.update(user).isPresent())
            throw new EntityDoesNotExistException(user.getId());

        notifyObservers();
    }

    public List<User> getAllUsers() {
        List<User> users = new ArrayList<>();
        userRepository.findAll().forEach(users::add);
        return users;
    }

    public User getUserById(Long id) {
        return userRepository.findOne(id)
                .orElseThrow(() -> new EntityDoesNotExistException(id));
    }

    @Override
    public void addObserver(Observer e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers() {
        observers.forEach(x -> x.update());
    }
}
