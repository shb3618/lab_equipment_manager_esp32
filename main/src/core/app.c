/*
 * app.c
 *
 *  Created on: 2018-04-05 19:09
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <string.h>

#include "esp_log.h"
#include "esp_ota_ops.h"

#include "nvs.h"
#include "nvs_flash.h"

#define TAG "app"

const char *app_get_version(void)
{
    const esp_app_desc_t *app_desc = esp_ota_get_app_description();

    return (const char *)app_desc->version;
}

void app_print_info(void)
{
    ESP_LOGW(TAG, "current version: %s", app_get_version());
}

esp_err_t app_getenv(const char *key, void *out_value, size_t *length)
{
    nvs_handle_t handle;

    esp_err_t err = nvs_open("storage", NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "open nvs failed");
        return err;
    }

    err = nvs_get_blob(handle, key, out_value, length);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(TAG, "env \"%s\" not found", key);
        nvs_close(handle);
        return err;
    } else if (err != ESP_OK) {
        ESP_LOGE(TAG, "read env \"%s\" failed", key);
        nvs_close(handle);
        return err;
    }

    nvs_close(handle);

    return ESP_OK;
}

esp_err_t app_setenv(const char *key, const void *value, size_t length)
{
    nvs_handle_t handle;

    esp_err_t err = nvs_open("storage", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "open nvs failed");
        return err;
    }

    err = nvs_set_blob(handle, key, value, length);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "set nvs blob failed");
        nvs_close(handle);
        return err;
    }

    err = nvs_commit(handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "write env \"%s\" failed", key);
        nvs_close(handle);
        return err;
    }

    nvs_close(handle);

    return ESP_OK;
}
