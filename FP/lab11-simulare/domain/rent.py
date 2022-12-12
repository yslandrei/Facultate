class rent:
    def __init__(self, apartment, months):
        self.apartment = apartment
        self.months = months
        self.pay = self.apartment.getRentPrice() * self.months

    def __str__(self):
        return f'{self.apartment} -> {self.months} luni, pret: {self.pay}'

    def __eq__(self, other):
        return self.apartment == other.apartment and self.months == other.months and self.pay == other.pay

    def getApartment(self):
        return self.apartment

    def getMonths(self):
        return self.months

    def getPay(self):
        return self.pay