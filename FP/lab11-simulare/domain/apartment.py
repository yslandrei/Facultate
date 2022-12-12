class apartment:
    def __init__(self, nr, type, price, rentPrice):
        self.nr = nr
        self.type = type
        self.price = price
        self.rentPrice = rentPrice
    
    def getNr(self):
        return self.nr

    def getType(self):
        return self.type

    def getPrice(self):
        return self.price

    def getRentPrice(self):
        return self.rentPrice

    def __str__(self):
        return f'Apartament {self.nr}(camere: {self.type}, pret: {self.price}, pret chirie: {self.rentPrice})'

    def __eq__(self, other):
        return self.nr == other.nr and self.type == other.type and self.price == other.price and self.rentPrice == other.rentPrice