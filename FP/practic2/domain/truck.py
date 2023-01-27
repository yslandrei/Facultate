class truck:
    def __init__(self, id, name, price, model, date):
        self.id = id
        self.name = name
        self.price = price
        self.model = model
        self.date = date

    def __eq__(self, other):
        return self.id == other.id and self.name == other.name and self.price == other.price and self.model == other.model and self.date == other.date

    def getId(self):
        return self.id

    def getName(self):
        return self.name

    def getPrice(self):
        return self.price

    def getModel(self):
        return self.model

    def getDate(self):
        return self.date

    def setName(self, newName):
        self.name = newName