package com.example.sales_agents_backend.controller;

import com.example.sales_agents_backend.domain.dto.UserResponseDTO;
import com.example.sales_agents_backend.domain.dto.UserRequestDTO;
import com.example.sales_agents_backend.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/user")
@CrossOrigin
public class UserController {

    @Autowired
    private UserService userService;

    @GetMapping("/authorize")
    public ResponseEntity<UserResponseDTO> authorize(@RequestParam String email, @RequestParam String password) {
        return ResponseEntity.ok(userService.authorizeUser(email, password));
    }

    @PostMapping("/register")
    public ResponseEntity<UserResponseDTO> register(@RequestBody UserRequestDTO user) {
        return ResponseEntity.ok(userService.registerUser(user));
    }

}
