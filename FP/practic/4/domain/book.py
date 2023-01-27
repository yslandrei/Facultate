class book:
    def __init__(self, id, title, author, year):
        self.id = id
        self.title = title
        self.author = author
        self.year = year

    def getId(self):
        return self.id

    def getTitle(self):
        return self.title

    def getAuthor(self):
        return self.author

    def getYear(self):
        return self.year
    
    def set(self, other):
        self = other

    def __eq__(self, other):
        return self.id == other.id and self.title == other.title and self.author == other.author and self.year == other.year

    def __str__(self):
        return f'{self.title}(id: {self.id}, author: {self.author}, year: {self.year})'
