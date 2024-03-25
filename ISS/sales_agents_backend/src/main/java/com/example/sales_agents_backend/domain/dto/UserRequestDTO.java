package com.example.sales_agents_backend.domain.dto;

import com.example.sales_agents_backend.domain.enums.RoleType;

public record UserRequestDTO(String name, String email, String password, RoleType role) {
}
