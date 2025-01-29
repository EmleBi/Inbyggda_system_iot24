#include <stdio.h>
#include "esp_log.h"

const static char *const TAG = "MAIN";

void app_main(void)
{
    ESP LOGI(TAG, "Hello World for my %d time", 1);
}