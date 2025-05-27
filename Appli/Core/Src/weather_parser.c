#include <stdio.h>
#include <time.h>

// Struktur zur Darstellung von Datum und Zeit
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} DateTime;

// Funktion zur Konvertierung eines UNIX-Timestamps
DateTime convert_unix_timestamp(long timestamp, int timezone) {
    DateTime dt;

    // Zeitzonenanpassung
    timestamp += timezone;

    // Konvertiere den Timestamp in time_t
    time_t adjusted_timestamp = (time_t)timestamp;
    struct tm *timeinfo = gmtime(&adjusted_timestamp);

    // Fülle die Struktur
    dt.year = timeinfo->tm_year + 1900;
    dt.month = timeinfo->tm_mon + 1;
    dt.day = timeinfo->tm_mday;
    dt.hour = timeinfo->tm_hour;
    dt.minute = timeinfo->tm_min;
    dt.second = timeinfo->tm_sec;

    return dt; // Rückgabe der Struktur
}

