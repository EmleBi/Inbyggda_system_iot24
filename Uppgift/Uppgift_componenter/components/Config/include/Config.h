#ifndef CONFIG_H
#define CONFIG_H

#include "esp_err.h" // Inkluderar ESP-IDF-specifik felbibliotek

// Definiera konstanter för NVS 
#define NVS_NAMESPACE "storage"        // Namnrymd som används i NVS
#define DEVICE_NAME_KEY "device_name"  // Nyckel för att lagra enhetens namn
#define SERIAL_NUMBER_KEY "serial_number" // Nyckel för att lagra serienumret
#define MAX_STR_LEN 100                // Maximal längd för strängar (namn och serienummer)

// Strukturen för enhetskonfiguration
typedef struct {
    char deviceName[MAX_STR_LEN];      // Lagrar enhetens namn
    char serialNumber[MAX_STR_LEN];   // Lagrar enhetens serienummer
} Config;

// Deklaration av funktioner relaterade till enhetskonfiguration
void initConfiguration(Config* config);      // Initierar enhetskonfigurationen
const char* getDeviceName(Config* config);   // Returnerar enhetens namn
const char* getSerialNumber(Config* config); // Returnerar enhetens serienummer
esp_err_t setDeviceName(Config* config, const char* newName); // Ställer in ett nytt namn för enheten
esp_err_t setSerialNumber(Config* config, const char* newSerial); // Ställer in ett nytt serienummer
esp_err_t saveToNVS(const char* key, const char* value); // Sparar en nyckel och ett värde i NVS

#endif
