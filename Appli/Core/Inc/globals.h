// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __cplusplus
extern "C" {
#endif

// Nur Deklaration, kein Speicher wird belegt:
extern char *json_data;


void show_nearby_SSIDs(void);

#ifdef __cplusplus
}
#endif

#endif // GLOBALS_H
