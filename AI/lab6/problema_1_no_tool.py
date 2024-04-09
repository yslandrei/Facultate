import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def read_csv(file_path, columns, y_column):
    csv = pd.read_csv(file_path)
    csv = csv.dropna()
    X = np.array(csv[columns].values)
    Y = np.array(csv[y_column].values)

    return X, Y

def split(X, Y):
    training_size = int(0.8 * X.shape[0])
    X_train = X[:training_size]
    X_test = X[training_size:]
    Y_train = Y[:training_size]
    Y_test = Y[training_size:]

    return X_train, X_test, Y_train, Y_test

class SGDRegressor:
    def __init__(self, task):
        self._coef = None
        self.intercept_ = 0.0
        self.errors = []
        self.task = task
    
    def fit(self, X, Y, learning_rate, noEpochs, batch_size):
        self._coef = np.random.random((1, X.shape[1]))
        self._intercept = np.random.random()

        for epoch in range(noEpochs):
            # shuffle the samples
            indices = np.arange(X.shape[0])
            np.random.shuffle(indices)
            X = X[indices, :]
            Y = Y[indices]
            batch_error = 0.0
            # for each batch of training data
            for i in range(0, X.shape[0], batch_size):
                X_batch = X[i:i+batch_size]
                Y_batch = Y[i:i+batch_size]
                prediction = self.predict(X_batch)
                error = 1 / 2 * np.mean((prediction - Y_batch) ** 2)
                batch_error += error
                # compute the gradients
                gradients = np.dot(prediction - Y_batch, X_batch) / X_batch.shape[0]
                # update the weights
                self._coef -= learning_rate * gradients
                self._intercept -= learning_rate * np.mean(prediction - Y_batch)
            self.errors.append(batch_error / (X.shape[0] / batch_size))

    def plot_error(self):
        plt.plot(self.errors)
        plt.savefig(f'error{self.task}.png')
        plt.clf()

    def predict(self, X):
        return np.dot(self._coef, X.T) + self._intercept
    
    def compute_error(self, X, Y):
        prediction = self.predict(X)
        return 1 / 2 * np.mean((prediction - Y) ** 2)

def solve_task(task, x_columns, y_column, file_path):
    X, Y = read_csv(file_path, x_columns, y_column)
    X_train, X_test, Y_train, Y_test = split(X, Y)
    print(f'Based on {x_columns}')
    model = SGDRegressor(task)
    model.fit(X_train, Y_train, 0.01, 100, 32)
    print()
    model.plot_error()
    model.compute_error(X_test, Y_test)
    print(f'Error on test set {model.compute_error(X_test, Y_test)}')
    print()

if __name__ == '__main__':
    solve_task('GDP-per-capita', ['GDP per capita'], 'Score', 'C:/Users/andre/Documents/GitHub/Facultate/AI/lab6/data/2019.csv')
    solve_task('GDP-per-capita-and-freedom-to-make-life-choices', ['GDP per capita', 'Freedom to make life choices'], 'Score', 'C:/Users/andre/Documents/GitHub/Facultate/AI/lab6/data/2019.csv')

    