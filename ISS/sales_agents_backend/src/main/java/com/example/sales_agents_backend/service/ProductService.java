package com.example.sales_agents_backend.service;

import com.example.sales_agents_backend.domain.dto.*;
import com.example.sales_agents_backend.domain.entities.Order;
import com.example.sales_agents_backend.domain.entities.Product;
import com.example.sales_agents_backend.domain.entities.User;
import com.example.sales_agents_backend.domain.enums.SortType;
import com.example.sales_agents_backend.domain.specification.ProductSpecifications;
import com.example.sales_agents_backend.exceptions.ResourceNotFoundException;
import com.example.sales_agents_backend.repository.OrderRepository;
import com.example.sales_agents_backend.repository.ProductRepository;
import com.example.sales_agents_backend.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;

@Service
public class ProductService {

    @Autowired
    private ProductRepository productRepository;

    @Autowired
    private OrderRepository orderRepository;

    @Autowired
    private SimpMessagingTemplate template;

    public ProductResponseDTO addProduct(ProductRequestDTO product) {
        Product newProduct = new Product(product.name(), product.quantity(), product.price());
        productRepository.save(newProduct);
        template.convertAndSend("/topic/updates", "Repository data changed, please refresh.");
        return new ProductResponseDTO(newProduct.getId(), newProduct.getName(), newProduct.getQuantity(), newProduct.getPrice());
    }

    public ProductResponseDTO updateProduct(Long id, ProductRequestDTO product) {
        Product updatedProduct = productRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("Product not found"));
        updatedProduct.setName(product.name());
        updatedProduct.setQuantity(product.quantity());
        updatedProduct.setPrice(product.price());
        productRepository.save(updatedProduct);
        template.convertAndSend("/topic/updates", "Repository data changed, please refresh.");
        return new ProductResponseDTO(updatedProduct.getId(), updatedProduct.getName(), updatedProduct.getQuantity(), updatedProduct.getPrice());
    }

    public void deleteProduct(Long id) {
        Product product = productRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("Product not found"));
        orderRepository.deleteAll(orderRepository.findAllByProductId(id));
        productRepository.delete(product);
        template.convertAndSend("/topic/updates", "Repository data changed, please refresh.");
    }

    public Page<ProductResponseDTO> filterProducts(ProductFiltersDTO filters) {
        int pageSize = 8;
        Pageable pageable = PageRequest.of(filters.page() - 1, pageSize);

        switch (filters.sortType()) {
            case ASC_PRICE -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("price").ascending());
            case DESC_PRICE -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("price").descending());
            case ASC_QUANTITY -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("quantity").ascending());
            case DESC_QUANTITY -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("quantity").descending());
            case ASC_NAME -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("name").ascending());
            case DESC_NAME -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("name").descending());
            case NONE -> pageable = PageRequest.of(filters.page() - 1, pageSize, Sort.by("id").ascending());
        }

        return productRepository.findAll(ProductSpecifications.nameContains(filters.name())
                .and(ProductSpecifications.priceInRange(filters.minPrice(), filters.maxPrice()))
                .and(ProductSpecifications.quantityInRange(filters.minQuantity(), filters.maxQuantity()))
                        , pageable)
                .map(product -> new ProductResponseDTO(product.getId(), product.getName(), product.getQuantity(), product.getPrice()));
    }

    public ProductFiltersRangesDTO getFilterRanges() {
        List<Product> products = productRepository.findAll();
        int minPrice = Integer.MAX_VALUE;
        int maxPrice = Integer.MIN_VALUE;
        int minQuantity = Integer.MAX_VALUE;
        int maxQuantity = Integer.MIN_VALUE;
        for (Product product : products) {
            minPrice = Math.min(minPrice, product.getPrice());
            maxPrice = Math.max(maxPrice, product.getPrice());
            minQuantity = Math.min(minQuantity, product.getQuantity());
            maxQuantity = Math.max(maxQuantity, product.getQuantity());
        }
        return new ProductFiltersRangesDTO(minPrice == Integer.MAX_VALUE ? 0 : minPrice,
                maxPrice == Integer.MIN_VALUE ? 0 : maxPrice,
                minQuantity == Integer.MAX_VALUE ? 0 : minQuantity,
                maxQuantity == Integer.MIN_VALUE ? 0 : maxQuantity);
    }
}
