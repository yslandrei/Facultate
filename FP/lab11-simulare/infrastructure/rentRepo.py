class rentRepo:
    def __init__(self):
        self.rList = []

    def __len__(self):
        return len(self.rList)

    def get(self, i):
        return self.rList[i]

    def addRent(self, rent):
        for i in range(len(self.rList)):
            if self.rList[i] == rent:
                return ValueError('Chirie deja existenta!')
        self.rList.append(rent)