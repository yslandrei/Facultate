from ucimlrepo import fetch_ucirepo 
from sklearn.neural_network import MLPClassifier
import numpy as np
from problema_1_tool import normalize_data, train_model, split_and_shuffle_data
from sklearn.metrics import accuracy_score

def get_data():
    iris = fetch_ucirepo(id=53) 
    X = iris.data.features.values
    Y = iris.data.targets.values

    return X, Y

def build_model(hidden_layer_sizes, batch_size, max_iter):
    return MLPClassifier(hidden_layer_sizes=hidden_layer_sizes, batch_size=batch_size, max_iter=max_iter, activation='relu', solver='adam')

def convert_to_one_hot(Y):
    classes = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']
    one_hot_y = np.zeros((len(Y), len(classes)))
    for i in range(len(Y)):
        one_hot_y[i][classes.index(Y[i])] = 1
    
    return one_hot_y

def predict_and_evaluate(model, X_test, Y_test):
    Y_pred = model.predict(X_test)
    return accuracy_score(Y_test, Y_pred)

def train_and_evaluate(X, Y):
    X, x_mean, x_std = normalize_data(X)
    Y = convert_to_one_hot(Y)
    model = build_model((100, 100), 32, 1000)
    X_train, X_test, Y_train, Y_test = split_and_shuffle_data(X, Y)
    train_model(model, X_train, Y_train)
    score = predict_and_evaluate(model, X_test, Y_test)
    print(f'Accuracy on test: {score}')
    score = predict_and_evaluate(model, X_train, Y_train)
    print(f'Accuracy on train: {score}')

    return model, x_mean, x_std

if __name__ == '__main__':
    X, Y = get_data()
    model, x_mean, x_std = train_and_evaluate(X, Y)

    # predict on one sample
    sample = np.array([[5.35, 3.85, 1.25, 0.4]])
    sample = (sample - x_mean) / x_std
    prediction = model.predict(sample)
    if prediction[0][0] == 1:
        print('Iris-setosa')
    elif prediction[0][1] == 1:
        print('Iris-versicolor')
    else:
        print('Iris-virginica')

