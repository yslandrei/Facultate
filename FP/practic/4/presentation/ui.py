from buisness.bookService import bookService


class ui:
    def __init__(self):
        self.bService = bookService()

    def printFilteredBooks(self):
        filters = self.bService.getFilters()
        print(filters)
        print()
        bFilteredList = self.bService.getFilteredBooks()
        for book in bFilteredList:
            print(book)

    def printMenu(self):
        print("\nComenzi:")
        print("• Adaugare carte - add [id], [title], [author], [year]")
        print("• Sterge carti - pop [digit]")
        print("• Filtrare carti - fil [titleFilter], [yearFilter]")
        print("• Undo - und")
        print()

    def clearScreen(self):
        print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")

    def menu(self):
        self.clearScreen()
        while(True):
            self.printFilteredBooks()
            self.printMenu()
            com = input(f"Introduceti comanda(q = quit): ")
            self.clearScreen()

            if com[:3] == 'add':
                try:
                    args = com[4:].split(', ')
                    self.bService.addBook(args[0], args[1], args[2], args[3])
                except ValueError as err:
                    print(err)

            elif com[:3] == 'pop':
                try:
                    args = com[4:]
                    self.bService.popBooks(args)
                except ValueError as err:
                    print(err)

            elif com[:3] == 'fil':
                try:
                    args = com[4:].split(', ')
                    self.bService.filterBooks(args[0], args[1])
                except ValueError as err:
                    print(err)

            elif com[:3] == 'und':
                try:
                    self.bService.undo()
                except ValueError as err:
                    print(err)

            elif com == 'q':
                return 0

            else:
                print('Comanda nu exista!')

            

