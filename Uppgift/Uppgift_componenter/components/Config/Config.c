#include "Config.h"
#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"

// Funktion för att initiera konfigurationen
void initConfiguration(Config* config) {
    // Initiera fälten deviceName och serialNumber med nollor
    memset(config->deviceName, 0, MAX_STR_LEN);
    memset(config->serialNumber, 0, MAX_STR_LEN);

    // Initiera NVS (icke-flyktigt flashminne)
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // Om det inte finns några lediga sidor eller en ny version hittas, rensa NVS och starta om
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    nvs_handle_t nvsHandle;
    // Öppna NVS-namespace i läsläge
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvsHandle) == ESP_OK) {
        size_t required_size = MAX_STR_LEN;

        // Försök att hämta enhetsnamnet från NVS
        if (nvs_get_str(nvsHandle, DEVICE_NAME_KEY, config->deviceName, &required_size) != ESP_OK) {
            // Om det misslyckas, använd standardvärde
            strcpy(config->deviceName, "DefaultDevice");
        }

        required_size = MAX_STR_LEN;
        // Försök att hämta serienumret från NVS
        if (nvs_get_str(nvsHandle, SERIAL_NUMBER_KEY, config->serialNumber, &required_size) != ESP_OK) {
            // Om det misslyckas, använd standardvärde
            strcpy(config->serialNumber, "0000000000");
        }

        // Stäng NVS-hanteraren
        nvs_close(nvsHandle);
    }
}

// Funktion för att hämta enhetsnamnet
const char* getDeviceName(Config* config) {
    return config->deviceName;
}

// Funktion för att hämta serienumret
const char* getSerialNumber(Config* config) {
    return config->serialNumber;
}

// Funktion för att ställa in enhetsnamnet
esp_err_t setDeviceName(Config* config, const char* newName) {
    if (!newName) return ESP_ERR_INVALID_ARG; // Kontrollera att newName är giltigt

    // Kopiera det nya namnet till fältet deviceName, säkerställ att det inte överskrider längden
    strncpy(config->deviceName, newName, MAX_STR_LEN - 1);
    config->deviceName[MAX_STR_LEN - 1] = '\0';

    // Spara det nya namnet i NVS
    return saveToNVS(DEVICE_NAME_KEY, config->deviceName);
}

// Funktion för att ställa in serienumret
esp_err_t setSerialNumber(Config* config, const char* newSerial) {
    if (!newSerial) return ESP_ERR_INVALID_ARG; // Kontrollera att newSerial är giltigt

    // Kopiera det nya serienumret till fältet serialNumber
    strncpy(config->serialNumber, newSerial, MAX_STR_LEN - 1);
    config->serialNumber[MAX_STR_LEN - 1] = '\0';

    // Spara det nya serienumret i NVS
    return saveToNVS(SERIAL_NUMBER_KEY, config->serialNumber);
}

// Funktion för att spara ett värde i NVS
esp_err_t saveToNVS(const char* key, const char* value) {
    nvs_handle_t nvsHandle;
    // Öppna NVS-namespace i läs- och skrivläge
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvsHandle);

    if (err == ESP_OK) {
        // Spara värdet som en sträng associerad med nyckeln
        err = nvs_set_str(nvsHandle, key, value);
        if (err == ESP_OK) {
            // Utför en commit för att säkerställa persistens
            err = nvs_commit(nvsHandle);
        }
        // Stäng NVS-hanteraren
        nvs_close(nvsHandle);
    } else {
        // Visa ett felmeddelande om det inte gick att skriva till NVS
        printf(" Failed to write '%s' to NVS: %s\n", key, esp_err_to_name(err));
    }
    return err;
}
