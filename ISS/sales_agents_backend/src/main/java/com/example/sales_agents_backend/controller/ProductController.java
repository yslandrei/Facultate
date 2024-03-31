package com.example.sales_agents_backend.controller;

import com.example.sales_agents_backend.domain.dto.*;
import com.example.sales_agents_backend.domain.entities.User;
import com.example.sales_agents_backend.service.OrderService;
import com.example.sales_agents_backend.service.ProductService;
import com.example.sales_agents_backend.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/product")
@CrossOrigin
public class ProductController {

    @Autowired
    private ProductService productService;

    @Autowired
    private UserService userService;

    @Autowired
    private OrderService orderService;

    @PostMapping("/add")
    public ResponseEntity<ProductResponseDTO> addProduct(@RequestParam String email, @RequestParam String password, @RequestBody ProductRequestDTO product) {
        userService.authorizeAdmin(email, password);
        return ResponseEntity.ok(productService.addProduct(product));
    }

    @PatchMapping("/update")
    public ResponseEntity<ProductResponseDTO> updateProduct(@RequestParam String email, @RequestParam String password, @RequestParam Long id, @RequestBody ProductRequestDTO product) {
        userService.authorizeAdmin(email, password);
        return ResponseEntity.ok(productService.updateProduct(id, product));
    }

    @DeleteMapping("/delete")
    public ResponseEntity<Void> deleteProduct(@RequestParam String email, @RequestParam String password, @RequestParam Long id) {
        userService.authorizeAdmin(email, password);
        productService.deleteProduct(id);
        return ResponseEntity.ok().build();
    }

    @PostMapping("/filter")
    public ResponseEntity<Page<ProductResponseDTO>> filterProducts(@RequestBody ProductFiltersDTO filters) {
        return ResponseEntity.ok(productService.filterProducts(filters));
    }

    @GetMapping("/ranges")
    public ResponseEntity<ProductFiltersRangesDTO> getFilterRanges() {
        return ResponseEntity.ok(productService.getFilterRanges());
    }

    @PostMapping("/place")
    public ResponseEntity<OrderResponseDTO> placeOrder(@RequestParam String email, @RequestParam String password, @RequestBody OrderRequestDTO order) {
        UserResponseDTO user = userService.authorizeUser(email, password);
        return ResponseEntity.ok(orderService.placeOrder(order, user.id()));
    }

    @MessageMapping("/changes")
    @SendTo("/topic/updates")
    public String broadcastChanges(String message) {
        return message;
    }

}
