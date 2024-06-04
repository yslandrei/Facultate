from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score
import numpy as np
from PIL import Image
import os
def loadImageData(folder_path):
    image_files = os.listdir(folder_path)
    inputs = []
    outputs = []
    
    for image_file in image_files:
        image_path = os.path.join(folder_path, image_file)
        image = Image.open(image_path)
        common_size = (100,100) 
        image= image.resize(common_size) 
        image = image.convert("RGB")
        image_array = np.array(image)
        
        if "sepia" in image_file:
            label = "Sepia"
        else:
            label = "Photo"
            
        inputs.append(image_array)
        outputs.append(label)
    
    return inputs, outputs

inputs, outputs = loadImageData("Data")
all_images = np.array(inputs)
all_labels = np.array(outputs)


# Split dataset into training and testing
X_train, X_test, y_train, y_test = train_test_split(all_images, all_labels, test_size=0.2, random_state=42)

# Initialize MLPClassifier
mlp = MLPClassifier(hidden_layer_sizes=(100,), max_iter=500,
                    solver='sgd', verbose=10, random_state=1,
                    learning_rate_init=.1)

# Train the model
print(y_train)
mlp.fit(X_train, y_train)

# Predict on the test set
y_pred = mlp.predict(X_test)

# Evaluate the model
print("Accuracy: ", accuracy_score(y_test, y_pred))
print(classification_report(y_test, y_pred))