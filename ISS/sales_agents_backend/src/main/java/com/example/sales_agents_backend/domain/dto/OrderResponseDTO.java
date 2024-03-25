package com.example.sales_agents_backend.domain.dto;

import java.time.LocalDateTime;

public record OrderResponseDTO(Long id, Long productId, Long userId, Integer quantity, LocalDateTime date) {
}
