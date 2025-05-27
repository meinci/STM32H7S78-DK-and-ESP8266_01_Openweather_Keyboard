#include "weather.h"
#include <stdio.h>
#include <string.h>
#include "cJSON.h"

WeatherData parse_weather_data(const char *json_response) {
    WeatherData data;
    data.humidity = 0;
    data.temperature = 0.0;
    strcpy(data.city_name, "Unknown");

    if (json_response == NULL || strlen(json_response) == 0) {
        printf("JSON-Daten sind leer oder NULL!\n");
        return data;
    }

    cJSON *root = cJSON_Parse(json_response);
    if (root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("JSON Parsing Error before: %s\n", error_ptr);
        }
        return data;
    }

    cJSON *main_object = cJSON_GetObjectItem(root, "main");
    if (main_object) {
        cJSON *temp = cJSON_GetObjectItem(main_object, "temp");
        if (cJSON_IsNumber(temp)) {
            data.temperature = temp->valuedouble;
        }
        cJSON *humidity = cJSON_GetObjectItem(main_object, "humidity");
        if (cJSON_IsNumber(humidity)) {
            data.humidity = humidity->valueint;
        }
    }

    cJSON *name = cJSON_GetObjectItem(root, "name");
    if (cJSON_IsString(name)) {
        strncpy(data.city_name, name->valuestring, sizeof(data.city_name) - 1);
        data.city_name[sizeof(data.city_name) - 1] = '\0';
    }

    cJSON_Delete(root);
    return data;
}
