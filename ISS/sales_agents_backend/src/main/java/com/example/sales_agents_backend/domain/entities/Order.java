package com.example.sales_agents_backend.domain.entities;

import jakarta.persistence.*;

import java.time.LocalDateTime;

@Entity
@Table(name = "orders")
public class Order {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne()
    @JoinColumn(name = "product_id")
    private Product product;

    @ManyToOne()
    @JoinColumn(name = "user_id")
    private User user;

    private Integer quantity;

    private LocalDateTime date;

    public Order(Long id, Product product, User user, Integer quantity, LocalDateTime date) {
        this.id = id;
        this.product = product;
        this.user = user;
        this.quantity = quantity;
        this.date = date;
    }

    public Order(Product product, User user, Integer quantity, LocalDateTime date) {
        this.id = null;
        this.product = product;
        this.user = user;
        this.quantity = quantity;
        this.date = date;
    }

    public Order() {

    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Integer getQuantity() {
        return quantity;
    }

    public void setQuantity(Integer quantity) {
        this.quantity = quantity;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Product getProduct() {
        return product;
    }

    public void setProduct(Product product) {
        this.product = product;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
