#include <stdio.h>
#include "disk_convert.h"

void format_human_readable(unsigned long bytes, char *buffer) {
    double value = (double)bytes;

    if (bytes >= 1024UL * 1024 *1024) {
        value = value / (1024.0 * 1024.0 *1024.0);
        sprintf(buffer, "%.1fG", value);
    } else if (bytes >= 1024UL * 1024) {
        value = value / (1024.0 * 1024.0);
        sprintf(buffer, "%.1fM", value);
    } else if (bytes >= 1024UL) {
        value = value /1024.0;
        sprintf(buffer, "%.1fK", value);
    } else {
        sprintf(buffer, "%luB", bytes);
    }
}
