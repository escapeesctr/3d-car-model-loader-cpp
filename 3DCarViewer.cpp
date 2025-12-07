#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

struct Vector3 {
	float x, y, z;

	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

	Vector3 normalized() const {
		float length = std::sqrt(x * x + y * y + z * z);
		if (length > 0) {
			return Vector3(x / length, y / length, z / length);
		}

		return *this;
	}
};

class OBJModel {
private:
	std::vector<Vector3> vertices;
	std::vector<std::vector<int>> faces;
	std::string modelName;

public:
	bool load(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "❌ Cannot open file: " << filename << std::endl;
			return false;
		}

		vertices.clear();
		faces.clear();

		std::string line;
		int lineNum = 0;

		while (std::getline(file, line)) {
			lineNum++;
			std::istringstream iss(line);
			std::string prefix;
			iss >> prefix;

			if (prefix == "#") {
				continue;
			}
			else if (prefix == "o") {
				iss >> modelName;
				std::cout << "📦 Object name: " << modelName << std::endl;
			}
			else if (prefix == "v") {
				float x, y, z;
				if (iss >> x >> y >> z) {
					vertices.push_back(Vector3(x, y, z));
				}
			}
			else if (prefix == "f") {
				std::vector<int> faceIndices;
				std::string vertexToken;

				while (iss >> vertexToken) {
					size_t slashPos = vertexToken.find('/');
					if (slashPos != std::string::npos) {
						vertexToken = vertexToken.substr(0, slashPos);
					}
					
					try {
						int idx = std::stoi(vertexToken);
						faceIndices.push_back(idx - 1);
					}
					catch (...) {

					}
				}

				if (faceIndices.size() >= 3) {
					faces.push_back(faceIndices);
				}
			}
		}

		file.close();

		std::cout << "✅ Successfully loaded: " << filename << std::endl;
		return true;
	}

	void printStatistics() const {
		std::cout << "\n📊 MODEL STATISTICS:\n";
		std::cout << "====================\n";
		std::cout << "Name: " << (modelName.empty() ? "Unnamed" : modelName) << "\n";
		std::cout << "Vertices: " << vertices.size() << "\n";
		std::cout << "Faces: " << faces.size() << "\n";

		if (!vertices.empty()) {
			Vector3 min = vertices[0];
			Vector3 max = vertices[0];

			for (const auto& v : vertices) {
				if (v.x < min.x) min.x = v.x;
				if (v.y < min.y) min.y = v.y;
				if (v.z < min.z) min.z = v.z;

				if (v.x > max.x) max.x = v.x;
				if (v.y > max.y) max.y = v.y;
				if (v.z > max.z) max.z = v.z;
			}

			std::cout << "\n📐 Bounding Box:\n";
			std::cout << "Min: (" << min.x << ", " << min.y << ", " << min.z << ")\n";
			std::cout << "Max: (" << max.x << ", " << max.y << ", " << max.z << ")\n";
			std::cout << "Size: " << (max.x - min.x) << " x "
				<< (max.y - min.y) << " x "
				<< (max.z - min.z) << "\n";
		}

		if (!vertices.empty()) {
			std::cout << "\n📍 Sample vertices (first 5):\n";
			for (int i = 0; i < 5 && i < vertices.size(); i++) {
				std::cout << "v" << i + 1 << ": (" << vertices[i].x << ", "
					<< vertices[i].y << ", " << vertices[i].z << ")\n";
			}
		}
	
		if (!faces.empty()) {
			std::cout << "\n🔺 Sample faces (first 3):\n";
			for (int i = 0; i < 3 && i < faces.size(); i++) {
				std::cout << "f" << i + 1 << ": ";
				for (int idx : faces[i]) {
					std::cout << idx + 1 << " ";
				}
				std::cout << "\n";
			}
		}
	}

	Vector3 calculateCenter() const {
		if (vertices.empty()) return Vector3();

		Vector3 center;
		for (const auto& v : vertices) {
			center.x += v.x;
			center.y += v.y;
			center.z += v.z;
		}

		center.x /= vertices.size();
		center.y /= vertices.size();
		center.z /= vertices.size();

		return center;
	}

	void renderTopDown() const {
		if (vertices.empty()) return;

		std::cout << "\n🖼️ TOP-DOWN VIEW (ASCII Approximation):\n";
		std::cout << "==================================\n";

		const int width = 40;
		const int height = 20;

		Vector3 min = vertices[0];
		Vector3 max = vertices[0];

		for (const auto& v : vertices) {
			if (v.x < min.x) min.x = v.x;
			if (v.z < min.z) min.z = v.z;
			if (v.x > max.x) max.x = v.x;
			if (v.z > max.z) max.z = v.z;
		}

		std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));

		for (const auto& v : vertices) {
			int col = static_cast<int>((v.x - min.x) / (max.x - min.x) * (width - 1));
			int row = static_cast<int>((v.z - min.z) / (max.z - min.z) * (height - 1));

			if (col >= 0 && col < width && row >= 0 && row < height) {
				grid[row][col] = '*';
			}
		}

		for (int row = 0; row < height; row++) {
			std::cout << "|";
			for (int col = 0; col < width; col++) {
				std::cout << grid[row][col];
			}
			std::cout << "|\n";
		}

		std::cout << "\nLegend: * = vertex (view from top)\n";
	}
};

int main() {
	std::cout << "🚗 3D CAR MODEL VIEWER\n";
	std::cout << "======================\n\n";

	OBJModel carModel;

	std::string filename = "car.obj";
	std::cout << "Attempting to load: " << filename << "\n";

	if (carModel.load(filename)) {
		carModel.printStatistics();

		Vector3 center = carModel.calculateCenter();
		std::cout << "\n🎯 Model Center : (" << center.x << ", "
			<< center.y << ", " << center.z << ")\n";

		carModel.renderTopDown();

		std::cout << "\n🎉 SUCCESS! Your 3D car model is loaded in C++!\n";
		std::cout << "This demonstrates 3D file parsing and data structure skills.\n";
	}
	else {
		std::cout << "\nCreating a sample cube for demonstration...\n";

		std::ofstream sampleObj("sample_cube.obj");
		sampleObj << "# Sample Cube\n";
		sampleObj << "v 1 1 1\nv 1 1 -1\nv 1 -1 1\nv 1 -1 -1\n";
		sampleObj << "v -1 1 1\nv -1 1 -1\nv -1 -1 1\nv -1 -1 -1\n";
		sampleObj << "f 1 2 4 3\nf 5 6 8 7\nf 1 5 7 3\n";
		sampleObj << "f 2 6 8 4\nf 1 2 6 5\nf 3 4 8 7\n";
		sampleObj.close();

		if (carModel.load("sample_cube.obj")) {
			carModel.printStatistics();
		}

		std::cout << "\n💡 Tip: Export your car model as OBJ and place in project folder.\n";
	}

	return 0;
}