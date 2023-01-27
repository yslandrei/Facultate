from infrastructure.bookFileRepository import bookFileRepository
from domain.book import book

class bookService():
    def __init__(self):
        self.titleFilter = ''
        self.yearFilter = -1
        self.bRepo = bookFileRepository()
        self.undoStack = list()
        self.undoStackTop = -1
        
    def addBook(self, id, title, author, year):
        Book = book(int(id), title, author, year)
        #validate book
        self.bRepo.addBook(Book)
        self.bRepo.saveFile()

    def popBooks(self, digit):
        #validate digit
        self.undoStack.append(list())
        self.undoStackTop += 1
        bList = self.bRepo.getAll()

        offset = 0
        for i in range(len(bList)):
            if digit in bList[i - offset].getYear():
                self.undoStack[self.undoStackTop].append(bList[i - offset])
                self.bRepo.popBook(bList[i - offset])
                offset += 1
        self.bRepo.saveFile()

    def filterBooks(self, newTitleFilter, newYearFilter):
        self.titleFilter = newTitleFilter
        self.yearFilter = int(newYearFilter)

    def getFilteredBooks(self):
        bList = self.bRepo.getAll()
        bListFiltered = []

        for book in bList:
            if self.titleFilter in book.getTitle() or self.titleFilter == '':
                if self.yearFilter > int(book.getYear()) or self.yearFilter == -1:
                    bListFiltered.append(book)

        return bListFiltered

    def getFilters(self):
        return f'Filtre active(Titlu: {self.titleFilter}, An: {self.yearFilter}):'

    def undo(self):
        removedBooks = self.undoStack.pop()
        self.undoStackTop -= 1

        for Book in removedBooks:
            self.bRepo.addBook(Book)

