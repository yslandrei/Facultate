package com.example.sales_agents_backend.service;

import com.example.sales_agents_backend.domain.dto.OrderRequestDTO;
import com.example.sales_agents_backend.domain.dto.OrderResponseDTO;
import com.example.sales_agents_backend.domain.entities.Order;
import com.example.sales_agents_backend.domain.entities.Product;
import com.example.sales_agents_backend.domain.entities.User;
import com.example.sales_agents_backend.exceptions.ResourceNotFoundException;
import com.example.sales_agents_backend.repository.OrderRepository;
import com.example.sales_agents_backend.repository.ProductRepository;
import com.example.sales_agents_backend.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;

@Service
public class OrderService {

    @Autowired
    private ProductRepository productRepository;

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private OrderRepository orderRepository;

    public OrderResponseDTO placeOrder(OrderRequestDTO order, Long userId) {
        Product product = productRepository.findById(order.productId())
                .orElseThrow(() -> new ResourceNotFoundException("Product not found"));
        if (product.getQuantity() < order.quantity()) {
            throw new RuntimeException("Not enough quantity");
        }
        product.setQuantity(product.getQuantity() - order.quantity());
        productRepository.save(product);
        User user = userRepository.findById(userId)
                .orElseThrow(() -> new ResourceNotFoundException("User not found"));
        Order newOrder = new Order(product, user, order.quantity(), LocalDateTime.now());
        orderRepository.save(newOrder);
        return new OrderResponseDTO(newOrder.getId(), newOrder.getProduct().getId(), newOrder.getUser().getId(), newOrder.getQuantity(), newOrder.getDate());
    }

}
