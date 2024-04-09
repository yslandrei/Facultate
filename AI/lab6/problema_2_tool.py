from ucimlrepo import fetch_ucirepo 
from problema_1_tool import normalize_data, train_model, split_and_shuffle_data
from sklearn.neural_network import MLPClassifier
import numpy as np
from sklearn.metrics import accuracy_score

def get_dataset():
    breast_cancer_wisconsin_diagnostic = fetch_ucirepo(id=17) 

    X = breast_cancer_wisconsin_diagnostic.data.features[['radius1', 'texture1']].values
    Y = breast_cancer_wisconsin_diagnostic.data.targets.values

    return X, Y

def build_model(hidden_layer_sizes, batch_size, max_iter):
    return MLPClassifier(hidden_layer_sizes=hidden_layer_sizes, batch_size=batch_size, max_iter=max_iter, activation='relu', solver='adam')

def convert_to_binary(Y):
    return np.array([1 if y == 'M' else 0 for y in Y])

def predict_and_evaluate(model, X_test, Y_test):
    Y_pred = model.predict(X_test)
    return accuracy_score(Y_test, Y_pred)

def predict(model, X_test):
    y = model.predict(X_test)
    if y[0] > 0.5:
        return 'M'
    return 'B'

def train_and_evaluate(X, Y):
    X, x_mean, x_std = normalize_data(X)
    Y = convert_to_binary(Y)
    model = build_model((100, 100), 32, 1000)
    X_train, X_test, Y_train, Y_test = split_and_shuffle_data(X, Y)
    train_model(model, X_train, Y_train)
    score = predict_and_evaluate(model, X_test, Y_test)
    print(f'Accuracy on test: {score}')
    score = predict_and_evaluate(model, X_train, Y_train)
    print(f'Accuracy on train: {score}')

    return model, x_mean, x_std

if __name__ == '__main__':
    X, Y = get_dataset()
    model, x_mean, x_std = train_and_evaluate(X, Y)

    # predict on a given sample
    sample = np.array([[18.0, 10.0]])
    sample = sample - x_mean / x_std
    print(f'Prediction for sample: {predict(model, sample)}')