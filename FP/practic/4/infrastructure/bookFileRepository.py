from domain.book import book


class bookFileRepository:
    def __init__(self):
        self.fileName = 'infrastructure/books.txt'
        self.bList = list()
        self.loadFile()
        
    def __len__(self):
        return len(self.bList)

    def getAll(self):
        return self.bList

    def saveFile(self):
        with open(self.fileName, 'w') as f:
            for Book in self.bList:
                line = str(Book.getId()) + ';' + Book.getTitle() + ';' + Book.getAuthor() + ';' + Book.getYear() + '\n'
                f.write(line)

    def loadFile(self):
        with open(self.fileName, 'r') as f:
            for line in f:
                args = line.strip('\n').split(';')
                Book = book(int(args[0]), args[1], args[2], args[3])
                self.bList.append(Book)

    def addBook(self, newBook):
        for book in self.bList:
            if book.getId() == newBook.getId():
                raise ValueError('ID-ul Cartii este deja prezent in Repository!')

        self.bList.append(newBook)

    def popBook(self, oldBook):
        for i in range(len(self.bList)):
            if self.bList[i] == oldBook:
                self.bList.pop(i)
                return

        raise ValueError('Cartea nu este prezenta in Repository!')