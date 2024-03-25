package com.example.sales_agents_backend.controller;

import com.example.sales_agents_backend.domain.dto.OrderRequestDTO;
import com.example.sales_agents_backend.domain.dto.OrderResponseDTO;
import com.example.sales_agents_backend.domain.dto.UserResponseDTO;
import com.example.sales_agents_backend.service.OrderService;
import com.example.sales_agents_backend.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/order")
@CrossOrigin
public class OrderController {

    @Autowired
    private UserService userService;

    @Autowired
    private OrderService orderService;

    @PostMapping("/place")
    public ResponseEntity<OrderResponseDTO> placeOrder(@RequestParam String email, @RequestParam String password, @RequestBody OrderRequestDTO order) {
        UserResponseDTO user = userService.authorizeUser(email, password);
        return ResponseEntity.ok(orderService.placeOrder(order, user.id()));
    }

}
