package org.example.repository;

import org.example.domain.User;

import java.util.Optional;

public interface UserRepository extends Repository<Long, User>{
    Optional<User> findByEmailAndPass(String email, String pass);

    Optional<User> findByEmail(String email);

}
