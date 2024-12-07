// Test file for testing common functions of JSON/XML Simple Library. Created by Oleksandr Shchur.

#include "jxsl_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_tests_console();
void run_tests_file(const char* filename);

int main() {
    int mode;
    printf("Select test mode:\n");
    printf("1 - Input from console\n");
    printf("2 - Input from test file\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    if (mode == 1) {
        run_tests_console();
    } else if (mode == 2) {
        char filename[256];
        printf("Enter the test file name: ");
        scanf("%s", filename);
        run_tests_file(filename);
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    return 0;
}

// Test functionality using console input
void run_tests_console() {
    char filename[256];
    printf("Enter the filename to test (JSON or XML): ");
    scanf("%s", filename);

    char key[256], value[256];
    printf("Adding data to the file.\n");
    printf("Enter key: ");
    scanf("%s", key);
    printf("Enter value: ");
    scanf("%s", value);
    if (strstr(filename, ".json")) {
        add_data_json(filename, key, value);
    } else if (strstr(filename, ".xml")) {
        add_data_xml(filename, key, value);
    } else {
        printf("Unsupported file type.\n");
        return;
    }
    printf("Data added successfully.\n");

    printf("Reading data for key '%s'.\n", key);
    char result[256];
        if (read_data(filename, key, result)) {
            printf("Value: %s\n", result);
        } else {
            printf("Key not found.\n");
    }
}

// Test functionality using a test file
void run_tests_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s.\n", filename);
        return;
    }

    char operation[256], filetype[256], key[256], value[256];
    while (fscanf(file, "%s %s %s %s", operation, filetype, key, value) != EOF) {
        if (strcmp(operation, "add") == 0) {
            if (strcmp(filetype, "json") == 0) {
                add_data_json("test.json", key, value);
            } else if (strcmp(filetype, "xml") == 0) {
                add_data_xml("test.xml", key, value);
            }
        } else if (strcmp(operation, "edit") == 0) {
            if (strcmp(filetype, "json") == 0) {
                edit_data_json("test.json", key, value);
            } else if (strcmp(filetype, "xml") == 0) {
                edit_data_xml("test.xml", key, value);
            }
        }
    }

    fclose(file);
    printf("Test file processed successfully.\n");
}
