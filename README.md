# 3D Car Model Loader in C++

A C++ application that loads and analyzes 3D OBJ models, featuring my own car model with over 1 million vertices.

## 🚗 Project Highlights
- **My own 3D car model** loaded and processed
- **1,089,174 vertices**, **1,082,114 faces** 
- **38 components** (wiper, wheels, interior, spoiler, etc.)
- Real-time statistics and visualization
- ASCII art top-down view

## 📊 Model Statistics (My Car)
- **Dimensions:** 1.69m × 1.23m × 4.06m
- **Center:** (0.0015, 0.5905, -0.5251)
- **Components:** 38 named objects
- **File Size:** [Your OBJ file size] MB

## 🛠️ Technical Implementation
### OBJ Parser Features:
- Vertex and face data extraction
- Multiple object support (38 objects in one file)
- Bounding box calculation
- Model center computation
- Error handling and validation

### 3D Mathematics:
- Vector3 operations (normalization, arithmetic)
- Min/max calculations for bounding
- Coordinate system transformations

### Visualization:
- Console-based statistics display
- ASCII art top-down projection
- Sample data preview

## 🎨 3D Art + Code Integration
This project demonstrates my unique combination of skills:
- **3D Modeling:** Created the car model in [Your 3D Software]
- **C++ Programming:** Implemented the OBJ loader from scratch
- **Technical Art:** Bridging the gap between art and code

## 📈 What I Learned
- 3D file format structure (OBJ)
- Memory management for large datasets
- 3D mathematics for game development
- Parsing complex real-world data
- Debugging large-scale applications

## 🔧 How to Compile
```bash
g++ -std=c++17 CarModelLoader.cpp -o CarModelLoader
```

### 🖼️ ASCII Visualization Example
```bash
     *****************************      
  ***********************************   
 *************************************  
 *************************************  
 **************** *** ****************  
 *************************************  
*************************************** 
*************************************** 
****************************************
*************************************** 
*************************************** 
*************************************** 
*************************************** 
*************************************** 
*************************************** 
*************************************** 
*************************************** 
*************************************** 
  ***********************************   
    *******************************     
                   *
```

## 🎯 Real-World Applications
- Game engine asset pipelines
- 3D model optimization tools
- CAD software integration
- Technical art tool development

## 🔗 Connect
- Portfolio: https://escapeesctr.github.io/my-portfolio/
- GitHub: @escapeesctr
