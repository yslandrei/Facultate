#pragma once
#include "productRepository.h"
#include "observer.h"

class ProductService : public observable {
private:
	ProductRepository& pRepo;

public:
	ProductService(ProductRepository& pRepo) : pRepo{ pRepo } {

	}

	//getters
	vector<Product> getAll() {
		return pRepo.getAll();
	}

	//function that validate product
	void validate(Product p) {
		if (p.getId() < 0) {
			throw exception("Id must be positive!");
		}
		if (p.getName().size() == 0) {
			throw exception("Name must have at least 1 character!");
		}
		if (p.getType().size() == 0) {
			throw exception("Type must have at least 1 character!");
		}
		if (!(p.getPrice() > 1 && p.getPrice() < 100)) {
			throw exception("Price must be between 1 and 100!");
		}
	}

	//add a product to the list and validate it
	void addProduct(int id, string name, string type, double price) {
		Product p(id, name, type, price);
		validate(p);
		pRepo.addProduct(p);
		notify();

	}

	//modify a product from the list and validate it
	void modProduct(int id, string name, string type, double price) {
		Product p(id, name, type, price);
		validate(p);
		pRepo.modProduct(p);
		notify();
	}

	vector<bool> filterByPrice(double price) {
		vector<bool> filtered;
		for (Product p : pRepo.getAll())
			filtered.push_back(p.getPrice() <= price);
		return filtered;
	}
};