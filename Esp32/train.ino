#include <EloquentTinyML.h>
#include "student_model_data101.h"  
#define NUMBER_OF_INPUTS 34         
#define NUMBER_OF_OUTPUTS 1         
#define TENSOR_ARENA_SIZE 20 * 1024 

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200);
    ml.begin(student_model);  
}


float studentInput1[] = { 1, 8, 5, 2, 1, 1, 1, 13, 10, 6, 10, 1, 0, 0, 1, 1, 0, 20, 0, 0, 0, 0, 0, 0.0, 0, 0, 0, 0, 0, 0.0, 0, 10.8, 1.4, 1.74 };
float studentInput2[] = { 1, 6, 1, 11, 1, 1, 1, 1, 3, 4, 4, 1, 0, 0, 0, 1, 0, 19, 0, 0, 6, 6, 6, 14.0, 0, 0, 6, 6, 6, 13.666666666666700, 0, 13.9, -0.3, 0.79 };

void loop() {
    classifyAndDisplayResult(studentInput1, "Student 1", "Dropout");
    classifyAndDisplayResult(studentInput2, "Student 2", "Graduated");
    delay(5000);
}

void classifyAndDisplayResult(float *input, const char *label, const char *expected_class) {
    float fResult[NUMBER_OF_OUTPUTS]; 
    initfResult(fResult);
    ml.predict(input, fResult);


    bool predicted_class = fResult[0] > 0.5;

    Serial.print("\nClassification for ");
    Serial.println(label);
    Serial.print("Expected class: ");
    Serial.println(expected_class);
    Serial.print("Predicted class: ");
    if (predicted_class) {
        Serial.println("Graduated");
    } else {
        Serial.println("Dropout");
    }

    displayOutput(fResult);
}

void initfResult(float *fResult) {
    for (int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        fResult[i] = 0.0f;
    }
}

void displayOutput(float *fResult) {
    Serial.print("Class probability (Graduated): ");
    Serial.println(fResult[0]);
}
