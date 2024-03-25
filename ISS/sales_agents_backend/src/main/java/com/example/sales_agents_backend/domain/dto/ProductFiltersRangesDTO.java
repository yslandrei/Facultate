package com.example.sales_agents_backend.domain.dto;

public record ProductFiltersRangesDTO(Integer minPrice, Integer maxPrice, Integer minQuantity, Integer maxQuantity) {
}
