package com.example.sales_agents_backend.repository;


import com.example.sales_agents_backend.domain.entities.Order;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface OrderRepository extends JpaRepository<Order, Long> {
    List<Order> findAllByProductId(Long productId);
}
