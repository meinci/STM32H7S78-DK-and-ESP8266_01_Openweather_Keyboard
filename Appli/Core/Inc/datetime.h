// datetime.h

#ifndef DATETIME_H
#define DATETIME_H

typedef struct {
    int year;    // Jahr (z.B. 2023)
    int month;   // Monat (1-12)
    int day;     // Tag (1-31)
    int hour;    // Stunde (0-23)
    int minute;  // Minute (0-59)
    int second;  // Sekunde (0-59)
} DateTime;

// Funktion zur Konvertierung des UNIX-Timestamps
DateTime convert_unix_timestamp(long timestamp, int timezone);

#endif // DATETIME_H
