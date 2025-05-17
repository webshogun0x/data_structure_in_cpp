#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstring>
#include <map>

// Simulates a hardware temperature sensor
class TemperatureSensor {
public:
    TemperatureSensor(int id) : sensorId(id) {}
    
    float readTemperature() const {
        return 20.0f + (sensorId * 1.5f) + (rand() % 10) / 10.0f;
    }
    
private:
    int sensorId;
};

// Using raw pointers and manual memory management (C-style)
void rawPointerExample(int numSensors, int numReadings) {
    std::cout << "\n--- Raw Pointer Example ---\n";
    
    TemperatureSensor** sensors = new TemperatureSensor*[numSensors]; // Dynamic allocation based on runtime values
    
    for (int i = 0; i < numSensors; i++) {
        sensors[i] = new TemperatureSensor(i);
    }
    
    // Allocate memory for readings
    float** readings = new float*[numSensors];
    for (int i = 0; i < numSensors; i++) {
        readings[i] = new float[numReadings];
        
        memset(readings[i], 0, numReadings * sizeof(float));
    }
    
    // Collect readings
    for (int i = 0; i < numSensors; i++) {
        for (int j = 0; j < numReadings; j++) {
            readings[i][j] = sensors[i]->readTemperature();
        }
    }
    
    float* averages = new float[numSensors];
    for (int i = 0; i < numSensors; i++) {
        float sum = 0.0f;
        for (int j = 0; j < numReadings; j++) {
            sum += readings[i][j];
        }
        averages[i] = sum / numReadings;
        std::cout << "Sensor " << i << " average: " << averages[i] << "°C\n";
    }
    
    // Manual cleanup - must be done carefully to avoid memory leaks
    for (int i = 0; i < numSensors; i++) {
        delete sensors[i];
        delete[] readings[i];
    }
    delete[] sensors;
    delete[] readings;
    delete[] averages;
}

// Using RAII and C++ containers
void raiiBased(int numSensors, int numReadings) {
    std::cout << "\n--- RAII Example ---\n";
    
    std::vector<TemperatureSensor> sensors;
    
    sensors.reserve(numSensors); // Reserve space to avoid reallocations
    
    // Initialize sensors
    for (int i = 0; i < numSensors; i++) {
        sensors.emplace_back(i);
    }
    
    std::vector<std::vector<float>> readings(numSensors, std::vector<float>(numReadings, 0.0f)); // 2D vector for readings - automatic memory management
    
    // Collect readings
    for (int i = 0; i < numSensors; i++) {
        for (int j = 0; j < numReadings; j++) {
            readings[i][j] = sensors[i].readTemperature();
        }
    }
    
    std::vector<float> averages(numSensors);
    for (int i = 0; i < numSensors; i++) {
        float sum = 0.0f;
        for (float reading : readings[i]) {
            sum += reading;
        }
        averages[i] = sum / numReadings;
        std::cout << "Sensor " << i << " average: " << averages[i] << "°C\n";
    }
    
}

// Using smart pointers
void smartPointerExample(int numSensors, int numReadings) {
    std::cout << "\n--- Smart Pointer Example ---\n";
    
    std::vector<std::unique_ptr<TemperatureSensor>> sensors; // Vector of unique_ptr for exclusive ownership
    
    // Initialize sensors
    for (int i = 0; i < numSensors; i++) {
        sensors.push_back(std::make_unique<TemperatureSensor>(i));
    }
    
    // Create a DataLogger that will share ownership of temperature data
    class DataLogger {
    public:
        void logReading(int sensorId, float reading) {
            if (m_data.find(sensorId) == m_data.end()) {
                m_data[sensorId] = std::make_shared<std::vector<float>>();
            }
            m_data[sensorId]->push_back(reading);
        }
        
        std::shared_ptr<std::vector<float>> getReadings(int sensorId) {
            return m_data[sensorId];
        }
        
    private:
        std::map<int, std::shared_ptr<std::vector<float>>> m_data;
    };
    
    DataLogger logger;
    
    // Collect readings
    for (int j = 0; j < numReadings; j++) {
        for (int i = 0; i < numSensors; i++) {
            logger.logReading(i, sensors[i]->readTemperature());
        }
    }
    
    // Another class that needs access to the same data
    class DataAnalyzer {
    public:
        explicit DataAnalyzer(DataLogger& logger, int sensorId) 
            : m_readings(logger.getReadings(sensorId)), m_sensorId(sensorId) {}
        
        float calculateAverage() const {
            if (m_readings->empty()) return 0.0f;
            
            float sum = 0.0f;
            for (float reading : *m_readings) {
                sum += reading;
            }
            return sum / m_readings->size();
        }
        
        void displayResult() const {
            std::cout << "Sensor " << m_sensorId << " average: " << calculateAverage() << "°C\n";
        }
        
    private:
        std::shared_ptr<std::vector<float>> m_readings;
        int m_sensorId;
    };
    
    // Create analyzers for each sensor
    std::vector<DataAnalyzer> analyzers;
    for (int i = 0; i < numSensors; i++) {
        analyzers.emplace_back(logger, i);
    }
    
    // Display results
    for (const auto& analyzer : analyzers) {
        analyzer.displayResult();
    }
    
}

int main() {
    const int NUM_SENSORS = 3;
    const int NUM_READINGS = 10;
    
    rawPointerExample(NUM_SENSORS, NUM_READINGS);
    raiiBased(NUM_SENSORS, NUM_READINGS);
    smartPointerExample(NUM_SENSORS, NUM_READINGS);
    
    return 0;
}