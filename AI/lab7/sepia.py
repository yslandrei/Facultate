import os
from PIL import Image
directory = "DataBikes"
def apply_sepia(image_path, output_path):
    # Load the image
    image = Image.open(image_path)
    # Convert image to RGB (just in case)
    image = image.convert("RGB")
    
    # Define sepia conversion matrix
    width, height = image.size
    pixels = image.load()  # Create the pixel map

    for py in range(height):
        for px in range(width):
            r, g, b = image.getpixel((px, py))

            # Apply sepia filter
            tr = int(0.393 * r + 0.769 * g + 0.189 * b)
            tg = int(0.349 * r + 0.686 * g + 0.168 * b)
            tb = int(0.272 * r + 0.534 * g + 0.131 * b)

            # Check if any value is out of range (0-255)
            tr = min(255, tr)
            tg = min(255, tg)
            tb = min(255, tb)

            # Set the pixel to the new value
            pixels[px, py] = (tr, tg, tb)

    # Save the modified image
    image.save(output_path)

files = os.listdir(directory)
file_index = 0

while file_index < len(files):
    file_name = files[file_index]
    # Check for file extension to process only images
    if file_name.lower().endswith(('.png', '.jpg', '.jpeg')):
        input_path = os.path.join(directory, file_name)
        output_path = os.path.join(directory, "sepia_" + file_name)
        apply_sepia(input_path, output_path)
        print(f"Converted {file_name} to sepia tone.")
    file_index += 1