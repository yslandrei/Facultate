package com.example.sales_agents_backend.domain.dto;

import com.example.sales_agents_backend.domain.enums.SortType;

public record ProductFiltersDTO(Integer page, SortType sortType, String name, Integer minPrice, Integer maxPrice, Integer minQuantity, Integer maxQuantity) {

}
