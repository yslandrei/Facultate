package com.example.sales_agents_backend.domain.specification;

import com.example.sales_agents_backend.domain.entities.Product;
import org.springframework.data.jpa.domain.Specification;

public class ProductSpecifications {

    public static Specification<Product> priceInRange(int min, int max) {
        return (root, query, cb) -> cb.between(root.get("price"), min, max);
    }

    public static Specification<Product> quantityInRange(int min, int max) {
        return (root, query, cb) -> cb.between(root.get("quantity"), min, max);
    }

    public static Specification<Product> nameContains(String name) {
        return (root, query, cb) -> cb.like(cb.lower(root.get("name")), "%" + name.toLowerCase() + "%");
    }

}
