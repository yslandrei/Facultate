package com.example.sales_agents_backend.service;

import com.example.sales_agents_backend.domain.dto.UserResponseDTO;
import com.example.sales_agents_backend.domain.dto.UserRequestDTO;
import com.example.sales_agents_backend.domain.entities.User;
import com.example.sales_agents_backend.domain.enums.RoleType;
import com.example.sales_agents_backend.exceptions.ResourceAlreadyExistsException;
import com.example.sales_agents_backend.exceptions.ResourceNotFoundException;
import com.example.sales_agents_backend.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class UserService {

    @Autowired
    private UserRepository userRepository;

    public UserResponseDTO authorizeUser(String email, String password) {
        User user = userRepository.findByEmailAndPassword(email, password)
                .orElseThrow(() -> new ResourceNotFoundException("Credentials don't match any user in the system"));
        return new UserResponseDTO(user.getId(), user.getName(), user.getEmail(), user.getPassword(), user.getRole());
    }

    public UserResponseDTO authorizeAdmin(String email, String password) {
        User admin = userRepository.findByEmailAndPassword(email, password)
                .orElseThrow(() -> new ResourceNotFoundException("Credentials don't match any user in the system"));
        if (admin.getRole() != RoleType.ADMIN) {
            throw new RuntimeException("User is not an admin");
        }
        return new UserResponseDTO(admin.getId(), admin.getName(), admin.getEmail(), admin.getPassword(), admin.getRole());
    }

    public UserResponseDTO registerUser(UserRequestDTO user) {
        Optional<User> existingUser = userRepository.findByEmail(user.email());
        if (existingUser.isPresent()) {
            throw new ResourceAlreadyExistsException("Email already in use by another user");
        }
        User newUser = new User(user.name(), user.email(), user.password(), user.role());
        userRepository.save(newUser);
        return new UserResponseDTO(newUser.getId(), newUser.getName(), newUser.getEmail(), newUser.getPassword(), newUser.getRole());
    }

}
