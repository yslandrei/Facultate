#pragma once 
#include "product.h"
#include <vector>
#include <fstream>
#include <sstream>

class ProductRepository {
private:
	vector<Product> pList;
	
public:
	ProductRepository() {
		loadFromFile();
	}

	//getters
	vector<Product> getAll() {
		return pList;
	}

	//add a product to the list and check if it already exists
	void addProduct(Product p) {
		for (int i = 0; i < pList.size(); i++) {
			if (pList[i].getId() == p.getId()) {
				throw exception("Product already exists!");
			}
		}
		pList.push_back(p);
		saveToFile();
	}

	//modify a product from the list given the and check if it exists
	void modProduct(Product p) {
		for (int i = 0; i < pList.size(); i++) {
			if (pList[i].getId() == p.getId()) {
				pList[i] = p;
				saveToFile();
				return;
			}
		}
		throw exception("Product does not exist!");
	}


	//load products from file "products.csv"
	void loadFromFile() {
		ifstream f("products.csv");
		string line;
		while (getline(f, line)) {
			Product p(-1, "", "", -1);
			stringstream ss(line);
			string token;
			getline(ss, token, ',');
			p.setId(stoi(token));
			getline(ss, token, ',');
			p.setName(token);
			getline(ss, token, ',');
			p.setType(token);
			getline(ss, token, ',');
			p.setPrice(stod(token));
			pList.push_back(p);
		}
		f.close();
	}

	//save product to file "products.csv"
	void saveToFile() {
		ofstream f("products.csv");
		for (int i = 0; i < pList.size(); i++)
			f << pList[i].getId() << "," << pList[i].getName() << "," << pList[i].getType() << "," << pList[i].getPrice() << endl;
		f.close();
	}
};