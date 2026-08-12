# Photoshop - Image Filtering Application

A command-line image editing tool written in C++ that applies various professional filters and effects to images. Supports common image formats (JPG, JPEG, BMP, PNG) with a user-friendly interface for image manipulation.

## Features

- **Blur Filter** - Gaussian blur effect with adjustable intensity (10-30%)
- **Rotate Filter** - Image rotation in 90°, 180°, and 270° increments
- **Frame Filter** - Add decorative or plain frames with custom RGB colors
- **TV Filter** - Vintage retro TV static and scanline effects
- **Invert Colors Filter** - RGB color inversion for artistic effects

## Supported Image Formats

- JPEG (.jpg, .jpeg)
- Bitmap (.bmp)
- PNG (.png)

## Technologies Used

- **Language**: C++ (C++11 or later)
- **Image Library**: Custom Image_Class (included)
- **Graphics Processing**: Pixel-level manipulation
- **Standard Library**: STL (vectors, strings, file I/O)

## Project Structure

```
photoshop/
├── Image_Class.h              # Image class header (custom library)
├── blur_filter.cpp            # Blur filter implementation
├── rotate_filter.cpp          # Rotation filter implementation
├── frame_filter.cpp           # Frame addition implementation
├── tvfinal_filter.cpp         # TV effect filter implementation
├── invertcolors_filter.cpp    # Color inversion implementation
└── README.md                  # This file
```

## Installation

### Prerequisites

- C++ compiler (g++, clang, or MSVC)
- C++11 or later support
- Image_Class library (included in repository)

### Setup

1. **Clone the repository**

   ```bash
   git clone https://github.com/marames25/photoshop.git
   cd photoshop
   ```

2. **Verify Image_Class.h is present**

   ```bash
   ls Image_Class.h  # Linux/macOS
   dir Image_Class.h # Windows
   ```

3. **Compile individual filters**

   For Blur Filter:

   ```bash
   g++ -o blur_filter blur_filter.cpp
   ```

   For Rotation Filter:

   ```bash
   g++ -o rotate_filter rotate_filter.cpp
   ```

   For Frame Filter:

   ```bash
   g++ -o frame_filter frame_filter.cpp
   ```

   For TV Effect:

   ```bash
   g++ -o tv_filter tvfinal_filter.cpp
   ```

   For Invert Colors:

   ```bash
   g++ -o invert_colors invertcolors_filter.cpp
   ```

4. **Or compile all at once**
   ```bash
   g++ -o blur_filter blur_filter.cpp
   g++ -o rotate_filter rotate_filter.cpp
   g++ -o frame_filter frame_filter.cpp
   g++ -o tv_filter tvfinal_filter.cpp
   g++ -o invert_colors invertcolors_filter.cpp
   ```

## Usage

### Running Filters

Each filter is a standalone executable with an interactive interface.

#### 1. Blur Filter

```bash
./blur_filter
```

**Steps**:

1. Enter the input image file path
2. Enter desired blur intensity (10-30%, where 30 is strongest)
3. Enter output filename with extension
4. Result saved to specified file

**Example**:

```
Enter the file path you want to include: photo.jpg
Please enter the percentage of the blur you want (10 : 30): 20
Enter the filename to save the image with frame: blurred_photo.jpg
Image saved as blurred_photo.jpg
```

#### 2. Rotate Filter

```bash
./rotate_filter
```

**Steps**:

1. Enter the input image file path
2. Choose rotation angle:
   - 1 = 180 degrees
   - 2 = 90 degrees
   - 3 = 270 degrees
3. Enter output filename

**Example**:

```
Enter the file path you want to include: photo.jpg
Choose rotation:
1. 180 degrees
2. 90 degrees
3. 270 degrees
Enter your choice: 2
Enter the filename to save the filtered image: rotated_photo.jpg
```

#### 3. Frame Filter

```bash
./frame_filter
```

**Steps**:

1. Enter the input image file path
2. Enter RGB color values for the frame (0-255 each)
   - Red: 0-255
   - Green: 0-255
   - Blue: 0-255
3. Choose frame type:
   - 1 = Plain solid frame
   - 2 = Decorative checkered pattern
4. Enter output filename

**Example**:

```
Enter the file path you want to include: photo.jpg
Enter the RGB values for the frame color (0-255):
Red: 255
Green: 100
Blue: 50
Choose the frame type:
1. Plain
2. Decorative
Enter your choice: 1
Enter the filename to save the image with frame: framed_photo.jpg
```

#### 4. TV Effect Filter

```bash
./tv_filter
```

**Steps**:

1. Enter the input image file path
2. Enter output filename
3. The TV filter is applied automatically with random scanline and noise effects

**Example**:

```
Enter the file path you want to include: photo.jpg
Enter the filename to save the filtered image: vintage_photo.jpg
Image saved as vintage_photo.jpg
```

#### 5. Invert Colors Filter

```bash
./invert_colors
```

**Steps**:

1. Enter the input image file path
2. Enter output filename
3. Color inversion applied to RGB channels (255 - original_value)

**Example**:

```
Enter the file path you want to include: photo.jpg
Enter the filename to save the filtered image: inverted_photo.jpg
Image saved as inverted_photo.jpg
```

## Filter Descriptions

### Blur Filter

Applies a Gaussian blur using a prefix sum algorithm for efficient processing.

**Algorithm**:

- Uses 2D prefix sum for fast neighborhood calculations
- Adjustable radius based on blur intensity percentage
- Average neighboring pixel values within radius

**Parameters**:

- Blur intensity: 10-30 (percentage)
- Processing time: O(width × height)

### Rotate Filter

Rotates images without cropping by adjusting dimensions.

**Supported Rotations**:

- 90° clockwise: Creates new image with swapped dimensions
- 180°: Full rotation with original dimensions
- 270° clockwise: Equivalent to 90° counter-clockwise

**Properties**:

- No image cropping
- Automatic dimension adjustment
- Lossless rotation

### Frame Filter

Adds decorative borders around images.

**Frame Types**:

1. **Plain**: Solid color frame with uniform width
2. **Decorative**: Checkered pattern with alternating colors

**Features**:

- Custom RGB color selection
- Frame width calculated as 5% of image dimensions
- Pattern frequency adjustable (currently 40 pixels)

### TV Effect Filter

Creates a vintage TV effect with scanlines and random noise.

**Effects Applied**:

- Horizontal scanlines (alternating brightness)
- Random pixel noise (10% of pixels)
- Color distortion for retro appearance
- Creates nostalgic CRT monitor look

### Invert Colors Filter

Inverts all RGB color channels for negative-like effects.

**Algorithm**:

```
new_red = 255 - old_red
new_green = 255 - old_green
new_blue = 255 - old_blue
```

**Use Cases**:

- Artistic effects
- Negative images
- Dark theme conversion

## Color Reference (RGB Values)

| Color   | Red | Green | Blue |
| ------- | --- | ----- | ---- |
| Red     | 255 | 0     | 0    |
| Green   | 0   | 255   | 0    |
| Blue    | 0   | 0     | 255  |
| White   | 255 | 255   | 255  |
| Black   | 0   | 0     | 0    |
| Yellow  | 255 | 255   | 0    |
| Cyan    | 0   | 255   | 255  |
| Magenta | 255 | 0     | 255  |
| Gray    | 128 | 128   | 128  |

## Troubleshooting

| Issue                         | Solution                                                      |
| ----------------------------- | ------------------------------------------------------------- |
| "Unable to load the image"    | Verify file path, ensure image exists and is supported format |
| "File does not exist"         | Check file path is correct, use absolute path if needed       |
| "Unsupported file extension"  | Use .jpg, .jpeg, .png, or .bmp format                         |
| Compilation errors            | Update compiler, ensure C++11 or later                        |
| Output file not created       | Verify write permissions in output directory                  |
| Memory errors on large images | May need to increase heap size for very large images          |

## Performance Characteristics

| Filter        | Complexity | Notes                                 |
| ------------- | ---------- | ------------------------------------- |
| Blur          | O(w×h)     | Linear in image size                  |
| Rotate        | O(w×h)     | Efficient dimension swapping          |
| Frame         | O(w+h)     | Only border pixels modified           |
| TV Effect     | O(w×h)     | Full image processing with randomness |
| Invert Colors | O(w×h×3)   | All RGB channels processed            |

## Image Size Considerations

- **Maximum recommended**: 4000×4000 pixels (depends on available RAM)
- **Typical processing**:
  - Small (640×480): < 1 second
  - Medium (1920×1080): 1-5 seconds
  - Large (4000×3000): 5-10 seconds

## Batch Processing

To apply filters to multiple images:

**Linux/macOS**:

```bash
for image in *.jpg; do
  ./blur_filter "$image" 20 "blurred_$image"
done
```

**Windows**:

```batch
for %i in (*.jpg) do (
  blur_filter.exe %i
)
```

## Output Naming Convention

Suggested output naming patterns:

- Blurred: `original_blurred.jpg`
- Rotated: `original_rotated.jpg`
- Framed: `original_framed.jpg`
- TV Effect: `original_vintage.jpg`
- Inverted: `original_inverted.jpg`

## Future Enhancements

- GUI interface with real-time preview
- Batch processing mode
- Additional filters (sharpen, sepia, grayscale)
- Undo/redo functionality
- Image cropping and resizing
- Multiple filter chaining
- Performance optimization for large images
- Support for GIF and TIFF formats

## Known Limitations

- Command-line only (no graphical interface)
- Single filter per execution
- No filter preview before saving
- Limited image format support
- No metadata preservation

## Contributing

Contributions are welcome! Areas for improvement:

- Additional filter types
- GUI implementation
- Performance optimization
- Extended format support
- Better error handling

## License

This project is open source and available under the MIT License.

## Contact

For questions, bug reports, or feature requests, please open an issue on GitHub.

## References

- Image Processing Algorithms: Gaussian blur, pixel manipulation
- C++ STL Documentation
- Custom Image_Class implementation details

---

**Enjoy creating amazing filtered images!** 📸✨
