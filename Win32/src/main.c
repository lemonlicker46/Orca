#define _WIN32_WINNT 0x0501
#define _WIN32_IE 0x0501
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <tchar.h>
#include <string.h>

static const unsigned char icon_image_0[] = {
    0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xEE, 0xEE, 0xEE, 0xFF, 0xFA, 0xFB, 0xFB, 0xFF, 0xFA, 0xFB, 0xFC, 0xFF, 0xA6, 0xA0, 0xA5, 0xFF,
    0xE0, 0xDF, 0xE0, 0xFF, 0xEC, 0xEC, 0xEC, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEB, 0xEB, 0xEB, 0xFF, 0xFC, 0xFE, 0xFD, 0xFF,
    0xF0, 0xF1, 0xF2, 0xFF, 0xC1, 0xBD, 0xC1, 0xFF, 0x6D, 0x5F, 0x62, 0xFF, 0x6E, 0x60, 0x64, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0xF5, 0xF5, 0xFF, 0xEA, 0xEA, 0xEA, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xE8, 0xFF, 0xE7, 0xE7, 0xE7, 0xFF,
    0xEA, 0xE9, 0xE9, 0xFF, 0xF5, 0xF6, 0xF6, 0xFF, 0xF6, 0xF8, 0xF9, 0xFF, 0xA1, 0x9A, 0x9F, 0xFF,
    0x53, 0x43, 0x49, 0xFF, 0x23, 0x08, 0x08, 0xFF, 0x2C, 0x15, 0x15, 0xFF, 0x8A, 0x81, 0x85, 0xFF,
    0xBB, 0xB6, 0xB9, 0xFF, 0xDA, 0xD9, 0xDC, 0xFF, 0xFB, 0xFC, 0xFC, 0xFF, 0xEE, 0xEE, 0xEE, 0xFF,
    0xE7, 0xE7, 0xE7, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEA, 0xEA, 0xEA, 0xFF, 0xEE, 0xED, 0xEE, 0xFF,
    0xE7, 0xE7, 0xE7, 0xFF, 0xD4, 0xD2, 0xD3, 0xFF, 0x6E, 0x60, 0x64, 0xFF, 0x10, 0x00, 0x00, 0xFF,
    0x2C, 0x1A, 0x1B, 0xFF, 0x5D, 0x54, 0x56, 0xFF, 0x35, 0x25, 0x2B, 0xFF, 0x16, 0x01, 0x07, 0xFF,
    0x1C, 0x05, 0x07, 0xFF, 0x2E, 0x1A, 0x1D, 0xFF, 0x7B, 0x6F, 0x74, 0xFF, 0xEF, 0xEF, 0xEE, 0xFF,
    0xF0, 0xF0, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xF1, 0xF1, 0xF1, 0xFF,
    0xE2, 0xE0, 0xE1, 0xFF, 0x70, 0x66, 0x69, 0xFF, 0x41, 0x30, 0x2E, 0xFF, 0x56, 0x43, 0x3E, 0xFF,
    0x9F, 0x99, 0x9A, 0xFF, 0xE7, 0xEA, 0xED, 0xFF, 0xCD, 0xCB, 0xCC, 0xFF, 0x5E, 0x52, 0x55, 0xFF,
    0x37, 0x26, 0x33, 0xFF, 0x36, 0x1F, 0x20, 0xFF, 0x38, 0x28, 0x32, 0xFF, 0x7A, 0x6F, 0x77, 0xFF,
    0xF3, 0xF3, 0xF2, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE7, 0xE7, 0xFF,
    0xEB, 0xEA, 0xEA, 0xFF, 0xEF, 0xF0, 0xF0, 0xFF, 0xF4, 0xF7, 0xF7, 0xFF, 0xED, 0xEF, 0xF0, 0xFF,
    0xF4, 0xF4, 0xF5, 0xFF, 0xF0, 0xEF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB, 0xDC, 0xDE, 0xFF,
    0x67, 0x61, 0x7A, 0xFF, 0x58, 0x4B, 0x5C, 0xFF, 0x5D, 0x54, 0x68, 0xFF, 0x5D, 0x57, 0x6C, 0xFF,
    0xBF, 0xBC, 0xBD, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xE8, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xEB, 0xEB, 0xEB, 0xFF, 0xED, 0xEC, 0xED, 0xFF, 0xA6, 0x9E, 0xA2, 0xFF, 0xE6, 0xE6, 0xE7, 0xFF,
    0xF4, 0xF4, 0xF4, 0xFF, 0xEF, 0xEF, 0xEF, 0xFF, 0xF9, 0xFA, 0xF7, 0xFF, 0x9C, 0x95, 0xA0, 0xFF,
    0x5B, 0x51, 0x6C, 0xFF, 0x4D, 0x3D, 0x4E, 0xFF, 0x39, 0x1F, 0x1E, 0xFF, 0x75, 0x75, 0x8A, 0xFF,
    0xBA, 0xBF, 0xC9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xF7, 0xF8, 0xF8, 0xFF, 0xBC, 0xB8, 0xBC, 0xFF, 0x0C, 0x00, 0x00, 0xFF, 0x53, 0x43, 0x46, 0xFF,
    0xF4, 0xF4, 0xF3, 0xFF, 0xEC, 0xEC, 0xEB, 0xFF, 0x90, 0x8A, 0x9A, 0xFF, 0x4A, 0x3D, 0x57, 0xFF,
    0x45, 0x2D, 0x30, 0xFF, 0x5A, 0x3D, 0x30, 0xFF, 0x47, 0x2F, 0x29, 0xFF, 0x6D, 0x6D, 0x78, 0xFF,
    0xC7, 0xCD, 0xD6, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE8, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xF6, 0xF6, 0xF6, 0xFF, 0xC1, 0xC0, 0xC3, 0xFF, 0x1B, 0x09, 0x10, 0xFF, 0x12, 0x00, 0x00, 0xFF,
    0x7C, 0x70, 0x76, 0xFF, 0x84, 0x7D, 0x92, 0xFF, 0x63, 0x5C, 0x7B, 0xFF, 0x47, 0x30, 0x33, 0xFF,
    0x5B, 0x3D, 0x2E, 0xFF, 0x5D, 0x49, 0x42, 0xFF, 0x32, 0x1C, 0x1B, 0xFF, 0x68, 0x62, 0x68, 0xFF,
    0xD8, 0xDA, 0xDF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x83, 0x82, 0x85, 0xFF, 0x18, 0x04, 0x0E, 0xFF,
    0x4C, 0x3C, 0x56, 0xFF, 0x6D, 0x66, 0x83, 0xFF, 0x47, 0x35, 0x3F, 0xFF, 0x52, 0x37, 0x2D, 0xFF,
    0x4D, 0x3C, 0x3E, 0xFF, 0x32, 0x1F, 0x24, 0xFF, 0x3F, 0x25, 0x1D, 0xFF, 0x8D, 0x86, 0x8A, 0xFF,
    0xF3, 0xF4, 0xF5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEA, 0xEA, 0xEA, 0xFF, 0xF6, 0xF6, 0xF4, 0xFF,
    0xE8, 0xE7, 0xE6, 0xFF, 0xB6, 0xAF, 0xB5, 0xFF, 0x89, 0x81, 0x92, 0xFF, 0x72, 0x6E, 0x89, 0xFF,
    0xA3, 0xAE, 0xCD, 0xFF, 0xA2, 0xB2, 0xC8, 0xFF, 0x38, 0x24, 0x24, 0xFF, 0x31, 0x1B, 0x20, 0xFF,
    0x30, 0x1B, 0x20, 0xFF, 0x45, 0x29, 0x22, 0xFF, 0x5F, 0x4C, 0x47, 0xFF, 0xD5, 0xD5, 0xD7, 0xFF,
    0xF3, 0xF3, 0xF3, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEF, 0xF0, 0xEF, 0xFF, 0xB6, 0xB4, 0xBF, 0xFF,
    0x7C, 0x79, 0x92, 0xFF, 0x89, 0x91, 0xAD, 0xFF, 0xA5, 0xB6, 0xD1, 0xFF, 0xAD, 0xBF, 0xD4, 0xFF,
    0x8A, 0x94, 0x9F, 0xFF, 0x56, 0x4F, 0x55, 0xFF, 0x2E, 0x19, 0x1C, 0xFF, 0x39, 0x22, 0x21, 0xFF,
    0x52, 0x35, 0x2B, 0xFF, 0x58, 0x44, 0x3D, 0xFF, 0x67, 0x5C, 0x62, 0xFF, 0xF9, 0xFB, 0xFC, 0xFF,
    0xEA, 0xEA, 0xEA, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xAC, 0xB2, 0xFF, 0x48, 0x3B, 0x47, 0xFF,
    0x51, 0x45, 0x4C, 0xFF, 0x4F, 0x46, 0x53, 0xFF, 0x65, 0x63, 0x71, 0xFF, 0x9F, 0xB1, 0xC0, 0xFF,
    0x8B, 0x96, 0xA5, 0xFF, 0x45, 0x34, 0x36, 0xFF, 0x46, 0x28, 0x20, 0xFF, 0x5E, 0x41, 0x30, 0xFF,
    0x73, 0x66, 0x59, 0xFF, 0x3F, 0x2E, 0x2D, 0xFF, 0x37, 0x22, 0x26, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xF5, 0xF6, 0xF6, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xBE, 0xBC, 0xBF, 0xFF, 0x55, 0x44, 0x3F, 0xFF,
    0x39, 0x1A, 0x0E, 0xFF, 0x32, 0x17, 0x17, 0xFF, 0x84, 0x87, 0x92, 0xFF, 0xA9, 0xB9, 0xC6, 0xFF,
    0x80, 0x7E, 0x82, 0xFF, 0x5E, 0x42, 0x32, 0xFF, 0x6B, 0x51, 0x3D, 0xFF, 0x95, 0x92, 0x90, 0xFF,
    0xA5, 0xA3, 0xA6, 0xFF, 0x5E, 0x4A, 0x45, 0xFF, 0x36, 0x21, 0x1D, 0xFF, 0x64, 0x56, 0x58, 0xFF,
    0xDA, 0xD9, 0xDB, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xFF, 0xD1, 0xD1, 0xD4, 0xFF,
    0x6C, 0x5E, 0x5A, 0xFF, 0x58, 0x40, 0x35, 0xFF, 0x50, 0x34, 0x28, 0xFF, 0x48, 0x2A, 0x1E, 0xFF,
    0x58, 0x3F, 0x33, 0xFF, 0x85, 0x7D, 0x77, 0xFF, 0xBD, 0xBF, 0xC3, 0xFF, 0xEF, 0xF0, 0xF3, 0xFF,
    0xF7, 0xF7, 0xF8, 0xFF, 0xE3, 0xE5, 0xE6, 0xFF, 0xC6, 0xC7, 0xC8, 0xFF, 0xAE, 0xAD, 0xAF, 0xFF,
    0xD4, 0xD3, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE8, 0xE9, 0xFF, 0xF3, 0xF4, 0xF4, 0xFF,
    0xE5, 0xE7, 0xEA, 0xFF, 0xBB, 0xBA, 0xBC, 0xFF, 0xA9, 0xA6, 0xA3, 0xFF, 0xAB, 0xA5, 0xA7, 0xFF,
    0xCA, 0xCA, 0xCD, 0xFF, 0xE9, 0xEB, 0xEE, 0xFF, 0xF5, 0xF5, 0xF6, 0xFF, 0xEC, 0xEC, 0xEC, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xEF, 0xEF, 0xEF, 0xFF, 0xF5, 0xF5, 0xF5, 0xFF, 0xF5, 0xF6, 0xF6, 0xFF,
    0xED, 0xED, 0xED, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned int icon_image_0_len = 1128;

static const unsigned char icon_image_1[] = {
    0x28, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xE7, 0xE7, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEA, 0xEA, 0xEB, 0xFF, 0xFC, 0xFE, 0xFD, 0xFF,
    0xC0, 0xBE, 0xC2, 0xFF, 0xD0, 0xCE, 0xD0, 0xFF, 0xEE, 0xEE, 0xEE, 0xFF, 0xEA, 0xE9, 0xE9, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF,
    0xE8, 0xE7, 0xE8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF,
    0xF1, 0xF1, 0xF1, 0xFF, 0xFA, 0xFB, 0xFB, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xC9, 0xC5, 0xC9, 0xFF,
    0x3D, 0x2C, 0x35, 0xFF, 0xC8, 0xC5, 0xC7, 0xFF, 0xF4, 0xF4, 0xF4, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0xEA, 0xEA, 0xEA, 0xFF, 0xF7, 0xF8, 0xF8, 0xFF, 0xFA, 0xFB, 0xFB, 0xFF,
    0xDE, 0xDD, 0xE0, 0xFF, 0xAA, 0xA4, 0xAA, 0xFF, 0x69, 0x5C, 0x62, 0xFF, 0x20, 0x09, 0x0C, 0xFF,
    0x55, 0x44, 0x46, 0xFF, 0xFC, 0xFE, 0xFE, 0xFF, 0xF2, 0xF2, 0xF2, 0xFF, 0xEA, 0xEA, 0xEA, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE8, 0xE8, 0xE9, 0xFF, 0xE9, 0xE8, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xED, 0xED, 0xED, 0xFF, 0xF6, 0xF6, 0xF7, 0xFF, 0xC9, 0xC6, 0xC9, 0xFF, 0xAB, 0xA5, 0xAA, 0xFF,
    0x2F, 0x1C, 0x23, 0xFF, 0x23, 0x0B, 0x0D, 0xFF, 0x2D, 0x13, 0x11, 0xFF, 0x41, 0x2B, 0x29, 0xFF,
    0xB5, 0xAF, 0xB3, 0xFF, 0xF0, 0xF1, 0xF2, 0xFF, 0xEB, 0xEB, 0xED, 0xFF, 0xFA, 0xFB, 0xFB, 0xFF,
    0xF7, 0xF8, 0xF7, 0xFF, 0xEB, 0xEA, 0xEA, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE8, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xE8, 0xE7, 0xE8, 0xFF, 0xE8, 0xE7, 0xE8, 0xFF, 0xED, 0xEE, 0xEE, 0xFF, 0xF6, 0xF7, 0xF7, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x91, 0x89, 0x8F, 0xFF, 0x18, 0x02, 0x09, 0xFF, 0x1C, 0x08, 0x10, 0xFF,
    0x30, 0x18, 0x17, 0xFF, 0x47, 0x2E, 0x28, 0xFF, 0x50, 0x41, 0x40, 0xFF, 0x38, 0x2A, 0x35, 0xFF,
    0x3C, 0x2B, 0x34, 0xFF, 0x37, 0x25, 0x29, 0xFF, 0x40, 0x2E, 0x36, 0xFF, 0x73, 0x67, 0x6E, 0xFF,
    0xC1, 0xBD, 0xC2, 0xFF, 0xFC, 0xFD, 0xFD, 0xFF, 0xF1, 0xF1, 0xF0, 0xFF, 0xE8, 0xE7, 0xE8, 0xFF,
    0xE8, 0xE8, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEF, 0xEF, 0xEF, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xF1, 0xF0, 0xF1, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xDD, 0xDB, 0xDC, 0xFF, 0xD5, 0xD2, 0xD5, 0xFF,
    0x71, 0x64, 0x6C, 0xFF, 0x1E, 0x06, 0x0B, 0xFF, 0x31, 0x19, 0x18, 0xFF, 0x34, 0x1E, 0x1E, 0xFF,
    0x57, 0x51, 0x53, 0xFF, 0x66, 0x67, 0x6D, 0xFF, 0x3A, 0x2D, 0x34, 0xFF, 0x20, 0x0A, 0x0F, 0xFF,
    0x1C, 0x07, 0x0C, 0xFF, 0x23, 0x0F, 0x13, 0xFF, 0x2A, 0x14, 0x13, 0xFF, 0x23, 0x0C, 0x0E, 0xFF,
    0x1C, 0x06, 0x0D, 0xFF, 0x6C, 0x5E, 0x64, 0xFF, 0xEF, 0xEF, 0xF0, 0xFF, 0xF2, 0xF3, 0xF2, 0xFF,
    0xE7, 0xE7, 0xE7, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE7, 0xE7, 0xFF, 0xE9, 0xE9, 0xEA, 0xFF,
    0xF0, 0xEF, 0xF0, 0xFF, 0xF4, 0xF5, 0xF5, 0xFF, 0x98, 0x8F, 0x93, 0xFF, 0x37, 0x27, 0x29, 0xFF,
    0x29, 0x12, 0x11, 0xFF, 0x3C, 0x25, 0x1F, 0xFF, 0x43, 0x2A, 0x23, 0xFF, 0x53, 0x41, 0x3F, 0xFF,
    0xAE, 0xAE, 0xB3, 0xFF, 0xE0, 0xE1, 0xE5, 0xFF, 0xD3, 0xD2, 0xD4, 0xFF, 0x9D, 0x99, 0x9C, 0xFF,
    0x3D, 0x2D, 0x2E, 0xFF, 0x2E, 0x1B, 0x24, 0xFF, 0x38, 0x25, 0x2E, 0xFF, 0x38, 0x22, 0x1F, 0xFF,
    0x3C, 0x27, 0x27, 0xFF, 0x28, 0x15, 0x1C, 0xFF, 0x55, 0x44, 0x4A, 0xFF, 0xF1, 0xF2, 0xF3, 0xFF,
    0xEF, 0xEF, 0xEF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEA, 0xEA, 0xEA, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE8, 0xE7, 0xE7, 0xFF, 0xEA, 0xEA, 0xEA, 0xFF, 0xEE, 0xEE, 0xEE, 0xFF, 0xC8, 0xC8, 0xC9, 0xFF,
    0xAB, 0xAB, 0xAD, 0xFF, 0x9E, 0x9F, 0x9C, 0xFF, 0xAB, 0xA6, 0xA7, 0xFF, 0xD7, 0xD7, 0xDA, 0xFF,
    0xF8, 0xF8, 0xF8, 0xFF, 0xF1, 0xF1, 0xF0, 0xFF, 0xF5, 0xF5, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xBB, 0xBA, 0xBC, 0xFF, 0x4F, 0x47, 0x55, 0xFF, 0x63, 0x58, 0x72, 0xFF, 0x51, 0x41, 0x4C, 0xFF,
    0x3D, 0x28, 0x27, 0xFF, 0x98, 0x9F, 0xBF, 0xFF, 0x44, 0x39, 0x48, 0xFF, 0x8D, 0x83, 0x86, 0xFF,
    0xFA, 0xFB, 0xFB, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEB, 0xEA, 0xEB, 0xFF, 0xF2, 0xF2, 0xF2, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0xF6, 0xF6, 0xFF, 0xF1, 0xF1, 0xF1, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEE, 0xEE, 0xEE, 0xFF,
    0xFA, 0xFB, 0xF9, 0xFF, 0x75, 0x71, 0x81, 0xFF, 0x69, 0x60, 0x7B, 0xFF, 0x74, 0x6C, 0x81, 0xFF,
    0x36, 0x23, 0x28, 0xFF, 0x6C, 0x66, 0x81, 0xFF, 0x6C, 0x68, 0x81, 0xFF, 0x61, 0x5A, 0x63, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEF, 0xF0, 0xF0, 0xFF,
    0xD6, 0xD4, 0xD6, 0xFF, 0xD3, 0xD1, 0xD4, 0xFF, 0xF9, 0xFA, 0xFA, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEA, 0xEA, 0xEA, 0xFF, 0xFE, 0xFF, 0xFD, 0xFF,
    0xC2, 0xBE, 0xC2, 0xFF, 0x54, 0x48, 0x5D, 0xFF, 0x76, 0x70, 0x8B, 0xFF, 0x5D, 0x53, 0x6C, 0xFF,
    0x27, 0x11, 0x1E, 0xFF, 0x39, 0x1E, 0x1A, 0xFF, 0x6B, 0x65, 0x79, 0xFF, 0x8A, 0x91, 0xA9, 0xFF,
    0xD4, 0xD3, 0xD4, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE8, 0xFF,
    0xE9, 0xE8, 0xE9, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xEE, 0xEE, 0xEE, 0xFF, 0xED, 0xED, 0xEE, 0xFF,
    0x43, 0x31, 0x38, 0xFF, 0x27, 0x12, 0x16, 0xFF, 0xC1, 0xBE, 0xC1, 0xFF, 0xFD, 0xFE, 0xFE, 0xFF,
    0xE8, 0xE7, 0xE7, 0xFF, 0xF0, 0xF0, 0xEF, 0xFF, 0xFA, 0xFB, 0xF8, 0xFF, 0xB7, 0xB2, 0xB6, 0xFF,
    0x52, 0x45, 0x5A, 0xFF, 0x4B, 0x3D, 0x56, 0xFF, 0x4B, 0x3A, 0x4B, 0xFF, 0x45, 0x2D, 0x2D, 0xFF,
    0x52, 0x36, 0x2C, 0xFF, 0x51, 0x3C, 0x37, 0xFF, 0x6D, 0x6A, 0x7B, 0xFF, 0xA5, 0xB6, 0xCD, 0xFF,
    0xCE, 0xCB, 0xCD, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEA, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE8, 0xFF,
    0xE9, 0xE8, 0xE8, 0xFF, 0xE9, 0xE8, 0xE9, 0xFF, 0xFA, 0xFA, 0xF9, 0xFF, 0xAB, 0xA7, 0xAD, 0xFF,
    0x17, 0x02, 0x0A, 0xFF, 0x26, 0x0F, 0x11, 0xFF, 0x2B, 0x16, 0x1A, 0xFF, 0xC0, 0xBC, 0xBE, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0xEA, 0xE9, 0xFF, 0x8A, 0x82, 0x8E, 0xFF, 0x60, 0x57, 0x71, 0xFF,
    0x57, 0x4C, 0x67, 0xFF, 0x41, 0x2C, 0x34, 0xFF, 0x51, 0x36, 0x2A, 0xFF, 0x58, 0x3B, 0x2E, 0xFF,
    0x68, 0x52, 0x47, 0xFF, 0x31, 0x1D, 0x20, 0xFF, 0x51, 0x44, 0x45, 0xFF, 0xA6, 0xB5, 0xC6, 0xFF,
    0xD7, 0xD4, 0xD5, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xE8, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF, 0xF6, 0xF7, 0xF6, 0xFF, 0xBB, 0xBA, 0xBE, 0xFF,
    0x1E, 0x0D, 0x15, 0xFF, 0x2A, 0x14, 0x18, 0xFF, 0x1F, 0x09, 0x0C, 0xFF, 0x54, 0x44, 0x47, 0xFF,
    0xD9, 0xD8, 0xDA, 0xFF, 0x67, 0x5C, 0x6D, 0xFF, 0x68, 0x60, 0x7D, 0xFF, 0x70, 0x6A, 0x87, 0xFF,
    0x40, 0x2C, 0x34, 0xFF, 0x53, 0x36, 0x2B, 0xFF, 0x54, 0x37, 0x2D, 0xFF, 0x6F, 0x58, 0x49, 0xFF,
    0x48, 0x38, 0x3B, 0xFF, 0x30, 0x17, 0x15, 0xFF, 0x5A, 0x4F, 0x50, 0xFF, 0x9E, 0xA5, 0xB3, 0xFF,
    0xEA, 0xE8, 0xE7, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF,
    0xE9, 0xE8, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF, 0xEF, 0xEE, 0xEE, 0xFF, 0xE6, 0xE7, 0xE8, 0xFF,
    0x4F, 0x4E, 0x57, 0xFF, 0x1A, 0x05, 0x0C, 0xFF, 0x22, 0x0C, 0x12, 0xFF, 0x27, 0x13, 0x20, 0xFF,
    0x5D, 0x52, 0x68, 0xFF, 0x75, 0x6E, 0x8A, 0xFF, 0x81, 0x7D, 0x9A, 0xFF, 0x43, 0x31, 0x40, 0xFF,
    0x46, 0x2B, 0x23, 0xFF, 0x58, 0x3C, 0x31, 0xFF, 0x66, 0x51, 0x48, 0xFF, 0x48, 0x3B, 0x40, 0xFF,
    0x33, 0x1E, 0x20, 0xFF, 0x41, 0x27, 0x1F, 0xFF, 0x65, 0x5F, 0x65, 0xFF, 0xB3, 0xB3, 0xBB, 0xFF,
    0xF6, 0xF5, 0xF4, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEA, 0xEA, 0xEA, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0xE8, 0xE8, 0xE9, 0xFF, 0xEA, 0xEA, 0xEA, 0xFF, 0xFC, 0xFC, 0xFA, 0xFF,
    0xDE, 0xE2, 0xE4, 0xFF, 0x52, 0x51, 0x57, 0xFF, 0x1C, 0x07, 0x12, 0xFF, 0x52, 0x44, 0x5B, 0xFF,
    0x71, 0x68, 0x83, 0xFF, 0x70, 0x68, 0x81, 0xFF, 0x3C, 0x2C, 0x3E, 0xFF, 0x41, 0x28, 0x24, 0xFF,
    0x5B, 0x3F, 0x36, 0xFF, 0x5B, 0x4B, 0x4B, 0xFF, 0x35, 0x27, 0x32, 0xFF, 0x2C, 0x16, 0x1B, 0xFF,
    0x43, 0x2C, 0x27, 0xFF, 0x4E, 0x32, 0x28, 0xFF, 0x71, 0x69, 0x6E, 0xFF, 0xEA, 0xEA, 0xEB, 0xFF,
    0xEF, 0xEF, 0xEF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE9, 0xE9, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xEA, 0xEA, 0xEB, 0xFF, 0xF4, 0xF5, 0xF4, 0xFF, 0xF7, 0xF8, 0xF6, 0xFF, 0xDB, 0xD9, 0xD9, 0xFF,
    0xB2, 0xAA, 0xB0, 0xFF, 0x61, 0x55, 0x66, 0xFF, 0x5A, 0x4E, 0x68, 0xFF, 0x7B, 0x75, 0x92, 0xFF,
    0x8B, 0x8D, 0xAA, 0xFF, 0xA1, 0xAF, 0xCA, 0xFF, 0x47, 0x3A, 0x3D, 0xFF, 0x3D, 0x24, 0x22, 0xFF,
    0x39, 0x24, 0x2A, 0xFF, 0x29, 0x16, 0x1F, 0xFF, 0x30, 0x1A, 0x1C, 0xFF, 0x43, 0x2C, 0x28, 0xFF,
    0x4E, 0x32, 0x29, 0xFF, 0x5F, 0x50, 0x4B, 0xFF, 0xBB, 0xBC, 0xC0, 0xFF, 0xF7, 0xF7, 0xF6, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xE7, 0xE7, 0xFF, 0xF3, 0xF2, 0xF1, 0xFF,
    0xF4, 0xF5, 0xF2, 0xFF, 0xC7, 0xC3, 0xC5, 0xFF, 0x80, 0x74, 0x82, 0xFF, 0x54, 0x47, 0x5E, 0xFF,
    0x65, 0x5F, 0x7C, 0xFF, 0x97, 0x9F, 0xBB, 0xFF, 0xAE, 0xBE, 0xD8, 0xFF, 0xBE, 0xD7, 0xF1, 0xFF,
    0xD3, 0xF5, 0xFF, 0xFF, 0xB8, 0xD1, 0xE2, 0xFF, 0x49, 0x3D, 0x42, 0xFF, 0x26, 0x0F, 0x14, 0xFF,
    0x2E, 0x1B, 0x1E, 0xFF, 0x3B, 0x25, 0x24, 0xFF, 0x4C, 0x33, 0x2E, 0xFF, 0x55, 0x39, 0x2E, 0xFF,
    0x5D, 0x46, 0x3B, 0xFF, 0x6B, 0x63, 0x6C, 0xFF, 0xF8, 0xF9, 0xFA, 0xFF, 0xEC, 0xEB, 0xEB, 0xFF,
    0xE6, 0xE5, 0xE6, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xF1, 0xF1, 0xFF, 0xD8, 0xD7, 0xD9, 0xFF,
    0x81, 0x7B, 0x8D, 0xFF, 0x69, 0x65, 0x83, 0xFF, 0x8A, 0x91, 0xAF, 0xFF, 0xB5, 0xC8, 0xE4, 0xFF,
    0xCD, 0xEA, 0xFF, 0xFF, 0xB3, 0xC9, 0xE1, 0xFF, 0xB0, 0xC6, 0xD8, 0xFF, 0x7B, 0x80, 0x88, 0xFF,
    0x53, 0x49, 0x4D, 0xFF, 0x2A, 0x14, 0x16, 0xFF, 0x2E, 0x17, 0x19, 0xFF, 0x39, 0x24, 0x25, 0xFF,
    0x43, 0x2D, 0x2A, 0xFF, 0x50, 0x35, 0x2E, 0xFF, 0x53, 0x34, 0x2B, 0xFF, 0x6F, 0x60, 0x58, 0xFF,
    0x35, 0x29, 0x2E, 0xFF, 0x82, 0x77, 0x7D, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF,
    0xE9, 0xE8, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE9, 0xE8, 0xE8, 0xFF, 0x77, 0x72, 0x84, 0xFF,
    0x55, 0x50, 0x67, 0xFF, 0x5F, 0x5A, 0x68, 0xFF, 0x63, 0x60, 0x68, 0xFF, 0x63, 0x5F, 0x6C, 0xFF,
    0x4A, 0x3E, 0x4A, 0xFF, 0x4F, 0x45, 0x4C, 0xFF, 0x78, 0x7C, 0x86, 0xFF, 0x64, 0x60, 0x69, 0xFF,
    0x5F, 0x5A, 0x62, 0xFF, 0x3F, 0x2C, 0x2E, 0xFF, 0x3D, 0x26, 0x25, 0xFF, 0x4D, 0x34, 0x2F, 0xFF,
    0x5A, 0x3C, 0x30, 0xFF, 0x66, 0x46, 0x34, 0xFF, 0x86, 0x7E, 0x71, 0xFF, 0x59, 0x51, 0x53, 0xFF,
    0x19, 0x02, 0x07, 0xFF, 0x61, 0x52, 0x54, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xED, 0xEE, 0xEE, 0xFF,
    0xE8, 0xE8, 0xE8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCC, 0xD0, 0xFF, 0x34, 0x23, 0x27, 0xFF,
    0x4C, 0x2F, 0x20, 0xFF, 0x4D, 0x31, 0x26, 0xFF, 0x2D, 0x14, 0x12, 0xFF, 0x1C, 0x03, 0x11, 0xFF,
    0x5A, 0x52, 0x64, 0xFF, 0xC4, 0xE1, 0xF2, 0xFF, 0xDB, 0xFF, 0xFF, 0xFF, 0xDD, 0xFF, 0xFF, 0xFF,
    0xB8, 0xD1, 0xE3, 0xFF, 0x59, 0x4A, 0x49, 0xFF, 0x52, 0x33, 0x28, 0xFF, 0x6B, 0x49, 0x35, 0xFF,
    0x6C, 0x53, 0x41, 0xFF, 0x7E, 0x81, 0x7D, 0xFF, 0x64, 0x5C, 0x57, 0xFF, 0x40, 0x21, 0x18, 0xFF,
    0x36, 0x1D, 0x1B, 0xFF, 0x28, 0x11, 0x13, 0xFF, 0xAA, 0xA2, 0xA5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xEC, 0xEC, 0xEB, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xEC, 0xEC, 0xFF, 0x9D, 0x9A, 0x9F, 0xFF,
    0x4F, 0x41, 0x3F, 0xFF, 0x46, 0x2A, 0x21, 0xFF, 0x4A, 0x2F, 0x29, 0xFF, 0x44, 0x2E, 0x2C, 0xFF,
    0x79, 0x76, 0x79, 0xFF, 0x91, 0x98, 0xA2, 0xFF, 0x87, 0x88, 0x8F, 0xFF, 0x68, 0x5C, 0x5B, 0xFF,
    0x48, 0x2C, 0x23, 0xFF, 0x62, 0x40, 0x2C, 0xFF, 0x7C, 0x5E, 0x42, 0xFF, 0x73, 0x67, 0x5B, 0xFF,
    0x8F, 0x93, 0x99, 0xFF, 0xD2, 0xD2, 0xD9, 0xFF, 0x9E, 0x96, 0x98, 0xFF, 0x6B, 0x5D, 0x58, 0xFF,
    0x59, 0x49, 0x43, 0xFF, 0x41, 0x2B, 0x26, 0xFF, 0x30, 0x1A, 0x18, 0xFF, 0x85, 0x7D, 0x82, 0xFF,
    0xE9, 0xEA, 0xEB, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xEB, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xA9, 0xA9, 0xAD, 0xFF, 0x52, 0x42, 0x3D, 0xFF, 0x55, 0x39, 0x2C, 0xFF, 0x51, 0x33, 0x29, 0xFF,
    0x48, 0x27, 0x1D, 0xFF, 0x44, 0x23, 0x18, 0xFF, 0x49, 0x28, 0x1A, 0xFF, 0x4E, 0x2D, 0x1E, 0xFF,
    0x61, 0x46, 0x35, 0xFF, 0x73, 0x67, 0x5B, 0xFF, 0x83, 0x84, 0x87, 0xFF, 0xB7, 0xB9, 0xC2, 0xFF,
    0xF1, 0xF1, 0xF2, 0xFF, 0xF5, 0xF5, 0xF4, 0xFF, 0xF8, 0xF9, 0xF9, 0xFF, 0xE3, 0xE5, 0xE7, 0xFF,
    0xBF, 0xC2, 0xC6, 0xFF, 0xAC, 0xAF, 0xB1, 0xFF, 0x99, 0x9D, 0x9B, 0xFF, 0xA1, 0x9F, 0xA3, 0xFF,
    0xE4, 0xE2, 0xE4, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xE7, 0xE7, 0xFF, 0xEA, 0xEA, 0xEB, 0xFF,
    0xF6, 0xF6, 0xF6, 0xFF, 0xC3, 0xC4, 0xC8, 0xFF, 0x86, 0x82, 0x85, 0xFF, 0x72, 0x68, 0x61, 0xFF,
    0x70, 0x61, 0x56, 0xFF, 0x65, 0x53, 0x4A, 0xFF, 0x60, 0x4F, 0x49, 0xFF, 0x71, 0x68, 0x66, 0xFF,
    0x94, 0x94, 0x98, 0xFF, 0xB8, 0xBB, 0xC2, 0xFF, 0xE9, 0xE9, 0xEB, 0xFF, 0xF6, 0xF6, 0xF5, 0xFF,
    0xEB, 0xEB, 0xEB, 0xFF, 0xE8, 0xE7, 0xE8, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xEF, 0xEF, 0xEF, 0xFF,
    0xF3, 0xF2, 0xF2, 0xFF, 0xF3, 0xF3, 0xF4, 0xFF, 0xF5, 0xF5, 0xF6, 0xFF, 0xF4, 0xF4, 0xF4, 0xFF,
    0xE9, 0xE9, 0xE9, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xEB, 0xEB, 0xEB, 0xFF, 0xE8, 0xE7, 0xE8, 0xFF,
    0xE8, 0xE8, 0xE9, 0xFF, 0xF5, 0xF6, 0xF6, 0xFF, 0xF0, 0xF1, 0xF3, 0xFF, 0xD8, 0xDA, 0xDE, 0xFF,
    0xCD, 0xD0, 0xD3, 0xFF, 0xC9, 0xCA, 0xCE, 0xFF, 0xD6, 0xD7, 0xDA, 0xFF, 0xE9, 0xEA, 0xED, 0xFF,
    0xF1, 0xF1, 0xF2, 0xFF, 0xF5, 0xF5, 0xF4, 0xFF, 0xEE, 0xEE, 0xED, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xE9, 0xE8, 0xE8, 0xFF, 0xEA, 0xE9, 0xE9, 0xFF, 0xE9, 0xE8, 0xE8, 0xFF, 0xE8, 0xE8, 0xE8, 0xFF,
    0xEA, 0xE9, 0xEA, 0xFF, 0xEA, 0xE9, 0xEA, 0xFF, 0xE9, 0xE9, 0xE9, 0xFF, 0xEA, 0xE9, 0xEA, 0xFF,
    0xEA, 0xEA, 0xEA, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned int icon_image_1_len = 2440;


#ifndef TCN_RCLICK
#define TCN_RCLICK (TCN_FIRST - 5)
#endif
#include <errno.h>

/* Control IDs */
#define IDC_CODE_INPUT     1001
#define IDC_CODE_OUTPUT    1002
#define IDC_TOOLBAR_MAIN   1003
#define IDC_TOOLBAR_CODE   1004
#define IDC_STATUSBAR      1005
#define IDC_PROJECT_TREE   1006
#define IDC_PROPERTIES     1007
#define IDC_CODE_TAB       1008
#define IDC_TAB_CLOSE      1009
/* Tab navigation buttons */
#define IDC_TAB_PREV       1010
#define IDC_TAB_NEXT       1011
#define IDC_CODE_SPLITTER  1012

/* Tab context menu IDs */
#define IDM_TAB_CLOSE_SINGLE 4001
#define IDM_TAB_CLOSE_OTHERS 4002
#define IDM_TAB_CLOSE_RIGHT  4003

/* Menu IDs */
#define IDM_FILE_NEW       1101
#define IDM_FILE_OPEN      1102
#define IDM_FILE_SAVE      1103
#define IDM_FILE_SAVEAS    1104
#define IDM_FILE_SAVEALL   1105
#define IDM_FILE_EXIT      1106
#define IDM_FILE_NEW_FILE  1107
#define IDM_FILE_OPEN_FILE 1108
#define IDM_EDIT_UNDO      1201
#define IDM_EDIT_REDO      1202
#define IDM_EDIT_CUT       1203
#define IDM_EDIT_COPY      1204
#define IDM_EDIT_PASTE     1205
#define IDM_EDIT_SELECTALL 1206
#define IDM_PROJECT_NEW    1301
#define IDM_PROJECT_SETTINGS 1302
#define IDM_BUILD_COMPILE  1401
#define IDM_BUILD_RUN      1402

#define IDI_MAINICON       201

/* Toolbar button IDs */
#define IDT_INSERT_FUNC    2001
#define IDT_INSERT_IF      2002
#define IDT_INSERT_FOR     2003
#define IDT_INSERT_WHILE   2004
#define IDT_INSERT_SWITCH  2005
#define IDT_INSERT_STRUCT  2006
#define IDT_INSERT_UNION   2007
#define IDT_INSERT_ENUM    2008
#define IDT_INSERT_TYPEDEF 2009
#define IDT_INSERT_INCLUDE 2010
#define IDT_INSERT_DEFINE  2011

/* Manipulation toolbar button IDs */
#define IDM_WRAP_IF        3001
#define IDM_WRAP_WHILE     3002
#define IDM_WRAP_FOR       3003
#define IDM_CONVERT_FUNC   3004
#define IDM_EXTRACT_FUNC   3005
#define IDM_ADD_COMMENT   3006
#define IDM_REMOVE_COMMENT 3007
#define IDM_FORMAT_CODE   3008
#define IDM_CONVERT_TO_MACRO 3009
#define IDM_EXTRACT_MACRO 3010

/* Global state */
static HWND hwndMain;
static HWND hwndInput, hwndOutput;
static HWND hwndToolbarMain, hwndToolbarCode;
static HWND hwndStatusBar;
static HWND hwndProjectTree;
static HWND hwndLineNumbers;
static HWND hwndProperties;
static HWND hwndCodeTab;
static HWND hwndTabClose;  /* Close button for tabs */
static HWND hwndTabPrev;   /* Previous-tab button */
static HWND hwndTabNext;   /* Next-tab button */
static HWND hwndCodeSplitter; /* Vertical splitter between code and properties */
static WNDPROC hwndOldEditorProc;
static HFONT g_codeFont;
static int g_lineNumberWidth = 35;
static int g_propertiesWidth = 150;
static int g_currentInputWidth = 0;
static int g_splitterWidth = 2;
static const int CONFIG_CODEPANE_MIN_WIDTH = 150;
static const int CONFIG_CODEPANE_MAX_WIDTH = 870;

static BOOL g_isDraggingSplitter = FALSE;
static int g_splitterDragStartX = 0;
static int g_splitterStartPropertiesWidth = 0;
static int g_dragInitialInputWidth = 0;
static char g_configPath[MAX_PATH] = "";
static int g_rightClickedTab = -1; /* last tab index right-clicked */

/* Layout helper functions */
void RepositionCodeArea(int clientWidth, int clientHeight);
void UpdateLineNumbers(HWND hwndEditor, HWND hwndGutter);
LRESULT CALLBACK EditorSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void InitializeConfigPath(void);
void LoadConfig(void);
void SaveConfig(void);

/* Debug console functions */
void InitDebugConsole() {
    /* Create a console window for debugging */
    if (AllocConsole()) {
        /* Redirect stdout to the new console */
        freopen("CONOUT$", "w", stdout);
        freopen("CONIN$", "r", stdin);
        
        printf("=== Orca Debug Console ===\n");
        printf("GUI interactions will be logged here.\n\n");
        fflush(stdout);
    }
}

void DebugLog(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    /* Print to console */
    printf("%s", buffer);
    fflush(stdout);
    
    /* Also write to debug.log file */
    /* Ensure debug.log is written into the root Orca folder */
    char modulePath[MAX_PATH];
    char logPath[MAX_PATH];
    GetModuleFileNameA(NULL, modulePath, MAX_PATH);
    /* Strip executable name */
    char* p = strrchr(modulePath, '\\');
    if (p) *p = '\0';
    /* Now modulePath is ..\...\Win32\build -> strip one more component to get Win32 */
    p = strrchr(modulePath, '\\');
    if (p) *p = '\0';
    /* Strip one more component to get to root Orca folder */
    p = strrchr(modulePath, '\\');
    if (p) *p = '\0';
    /* modulePath now points to root Orca folder */
    snprintf(logPath, MAX_PATH, "%s\\debug.log", modulePath);
    FILE* logFile = fopen(logPath, "a");
    if (logFile) {
        fprintf(logFile, "%s", buffer);
        fclose(logFile);
    }
}

void InitializeConfigPath(void) {
    char modulePath[MAX_PATH];
    if (GetModuleFileNameA(NULL, modulePath, MAX_PATH)) {
        char* p = strrchr(modulePath, '\\');
        if (p) *p = '\0';
        snprintf(g_configPath, MAX_PATH, "%s\\..\\..\\config.ini", modulePath);
    } else {
        strcpy(g_configPath, "config.ini");
    }
}

static int ClampCodePaneWidth(int width) {
    if (width < CONFIG_CODEPANE_MIN_WIDTH) return CONFIG_CODEPANE_MIN_WIDTH;
    if (width > CONFIG_CODEPANE_MAX_WIDTH) return CONFIG_CODEPANE_MAX_WIDTH;
    return width;
}

static int ParseConfigCodePaneWidth(const char* path) {
    char buffer[32] = {0};
    GetPrivateProfileStringA("Layout", "CodePaneWidth", "", buffer, sizeof(buffer), path);
    if (buffer[0] == '\0') {
        return 0;
    }

    char* endPtr = NULL;
    long parsed = strtol(buffer, &endPtr, 10);
    if (endPtr == buffer || *endPtr != '\0' || parsed <= 0 || parsed > INT_MAX) {
        return 0;
    }
    return (int)parsed;
}

void LoadConfig(void) {
    if (g_configPath[0] == '\0') {
        InitializeConfigPath();
    }
    int width = ParseConfigCodePaneWidth(g_configPath);
    if (width > 0) {
        int clamped = ClampCodePaneWidth(width);
        if (clamped != width) {
            DebugLog("[CONFIG] Config width %d out of bounds; clamping to %d\n", width, clamped);
        }
        g_currentInputWidth = clamped;
    } else {
        DebugLog("[CONFIG] Invalid or missing CodePaneWidth; resetting to default internal width\n");
        g_currentInputWidth = 0;
    }
    DebugLog("[CONFIG] Loaded config from %s, CodePaneWidth=%d\n", g_configPath, g_currentInputWidth);
}

void SaveConfig(void) {
    if (g_configPath[0] == '\0') {
        InitializeConfigPath();
    }
    if (g_currentInputWidth > 0) {
        int clamped = ClampCodePaneWidth(g_currentInputWidth);
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%d", clamped);
        WritePrivateProfileStringA("Layout", "CodePaneWidth", buffer, g_configPath);
        DebugLog("[CONFIG] Saved CodePaneWidth=%d to %s\n", clamped, g_configPath);
    } else {
        DebugLog("[CONFIG] Internal width is default so SaveConfig will skip writing CodePaneWidth\n");
    }
}

/* Integrated debug viewer removed: using console/debug.log only */

/* Tab management */
#define MAX_TABS 32
typedef struct {
    char filePath[MAX_PATH];
    char title[MAX_PATH];
    BOOL isModified;
    HWND editorWnd;
} TabInfo;

static TabInfo g_tabs[MAX_TABS];
static int g_tabCount = 0;
static int g_activeTab = -1;
static int g_tabScrollIndex = 0; /* highest-priority visible tab for scroll buttons */
static BOOL g_ignoreTabSelectionChange = FALSE;

/* Recursive helper to update a treeview item by filename anywhere in the tree */
static BOOL UpdateTreeItemRecursive(HWND hwndTree, HTREEITEM hItem, const char* displayName, const char* searchName) {
    for (HTREEITEM it = hItem; it; it = TreeView_GetNextSibling(hwndTree, it)) {
        TVITEM tvi;
        char buffer[MAX_PATH];
        tvi.mask = TVIF_TEXT | TVIF_HANDLE;
        tvi.hItem = it;
        tvi.pszText = buffer;
        tvi.cchTextMax = sizeof(buffer);
        TreeView_GetItem(hwndTree, &tvi);

        const char* comparePtr = buffer;
        if (buffer[0] == '*') comparePtr = buffer + 1;
        if (strcmp(comparePtr, displayName) == 0) {
            TVITEM updateItem;
            updateItem.mask = TVIF_TEXT | TVIF_HANDLE;
            updateItem.hItem = it;
            updateItem.pszText = (LPSTR)searchName;
            TreeView_SetItem(hwndTree, &updateItem);
            return TRUE;
        }

        HTREEITEM child = TreeView_GetChild(hwndTree, it);
        if (child) {
            if (UpdateTreeItemRecursive(hwndTree, child, displayName, searchName)) return TRUE;
        }
    }
    return FALSE;
}

/* Project settings */
static char g_platform[64] = "Windows";
static char g_compiler[64] = "GCC";
static char g_architecture[64] = "x86";

/* File tracking */
#define MAX_OPENED_FILES 256
static char g_openedFiles[MAX_OPENED_FILES][MAX_PATH];
static int g_openedFileCount = 0;
static BOOL g_isFolderBased = FALSE;
static BOOL g_projectOpened = FALSE;

/* Enable/disable save menu items */
void UpdateSaveMenuState(BOOL enable) {
    HMENU hMenu = GetMenu(hwndMain);
    HMENU hFileMenu = GetSubMenu(hMenu, 0);
    UINT flags = enable ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(hFileMenu, IDM_FILE_SAVE, flags);
    EnableMenuItem(hFileMenu, IDM_FILE_SAVEAS, flags);
    EnableMenuItem(hFileMenu, IDM_FILE_SAVEALL, flags);
}

/* Forward declarations for file operations */
void OpenFilesWithDialog(HWND hwnd);
void OpenFolder(HWND hwnd, const char* folderPath);
void PopulateProjectTree(HWND hwndTree, const char* rootPath, BOOL isFlat);
void LoadFileIntoEditor(const char* filePath);
int PromptSaveTab(int tabIdx);
void UpdateTreeViewItemModified(const char* filePath, BOOL isModified);
void UpdateTabTitle(int tabIdx, BOOL isModified);
void RefreshTabControl(void);
void EnsureUntitledTabExists(void);
void SaveFileWithDialog(HWND hwnd, BOOL saveAs);
void SaveAllFiles(HWND hwnd);
BOOL IsCOrHFile(const char* ext);
void AddFileToProject(const char* filePath);
void AddUntitledToTreeView(void);

/* Forward declarations */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateMainLayout(HWND hwnd);
void CreateMenus(HWND hwnd);
void CreateMainToolbar(HWND hwnd);
void CreateCodeToolbar(HWND hwnd);
void CreateStatusBar(HWND hwnd);
void InsertCodeTemplate(int templateId);
void ShowManipulationToolbar(BOOL show);
void UpdateStatusBar(LPCTSTR text);
void PositionTabCloseButton();
static BOOL TabControlNeedsScroll(void);
static void UpdateTabNavigationButtons(void);
static void EnsureTabVisible(int tabIndex);

/* Code templates */
static const char* codeTemplates[] = {
    "void function_name(void) {\n    \n}",                           /* IDT_INSERT_FUNC */
    "if (condition) {\n    \n}",                                      /* IDT_INSERT_IF */
    "for (int i = 0; i < n; i++) {\n    \n}",                           /* IDT_INSERT_FOR */
    "while (condition) {\n    \n}",                                     /* IDT_INSERT_WHILE */
    "switch (value) {\n    case 1:\n        break;\n    default:\n        break;\n}",                                              /* IDT_INSERT_SWITCH */
    "typedef struct {\n    \n} StructName;",                                 /* IDT_INSERT_STRUCT */
    "typedef union {\n    \n} UnionName;",                                  /* IDT_INSERT_UNION */
    "typedef enum {\n    \n} EnumName;",                                    /* IDT_INSERT_ENUM */
    "typedef existing_type new_type;",                                   /* IDT_INSERT_TYPEDEF */
    "#include \"header.h\"",                                             /* IDT_INSERT_INCLUDE */
    "#define NAME value",                                                /* IDT_INSERT_DEFINE */
};

void InsertCodeTemplate(int templateId) {
    int index = templateId - IDT_INSERT_FUNC;
    if (index >= 0 && index < 12) {
        SendMessage(hwndInput, EM_REPLACESEL, TRUE, (LPARAM)codeTemplates[index]);
        SetFocus(hwndInput);
    }
}

/* Project Settings Dialog */
INT_PTR CALLBACK ProjectSettingsDlg(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    (void)lParam;
    static HWND hPlatform, hCompiler, hArch;
    switch (msg) {
    case WM_INITDIALOG:
        hPlatform = GetDlgItem(hdlg, 100);
        hCompiler = GetDlgItem(hdlg, 101);
        hArch = GetDlgItem(hdlg, 102);
        /* Populate combo boxes */
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"Windows");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"Linux");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"macOS");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"Embedded");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"FreeBSD");
        
        SendMessage(hCompiler, CB_ADDSTRING, 0, (LPARAM)"GCC");
        SendMessage(hCompiler, CB_ADDSTRING, 0, (LPARAM)"Clang");
        SendMessage(hCompiler, CB_ADDSTRING, 0, (LPARAM)"MSVC");
        
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"x86");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"x64");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"ARM");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"ARM64");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"RISC-V");
        
        /* Set defaults */
        SendMessage(hPlatform, CB_SETCURSEL, 0, 0);
        SendMessage(hCompiler, CB_SETCURSEL, 0, 0);
        SendMessage(hArch, CB_SETCURSEL, 0, 0);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            char buf[64];
            SendMessage(hPlatform, WM_GETTEXT, 64, (LPARAM)buf);
            strcpy(g_platform, buf);
            SendMessage(hCompiler, WM_GETTEXT, 64, (LPARAM)buf);
            strcpy(g_compiler, buf);
            SendMessage(hArch, WM_GETTEXT, 64, (LPARAM)buf);
            strcpy(g_architecture, buf);
            EndDialog(hdlg, IDOK);
        } else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hdlg, IDCANCEL);
        }
        break;
    
    }
    return FALSE;
}

void ShowProjectSettings(HWND parent) {
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(1), parent, ProjectSettingsDlg);
    char status[256];
    sprintf(status, "Platform: %s | Compiler: %s | Architecture: %s", g_platform, g_compiler, g_architecture);
    UpdateStatusBar(status);
}

/* Get selected text from edit control */
void GetSelectedText(HWND hwndEdit, char* buffer, int bufsize) {
    int start, end;
    SendMessage(hwndEdit, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
    if (start == end) {
        buffer[0] = '\0';
        return;
    }
    int len = end - start;
    if (len >= bufsize) len = bufsize - 1;
    /* Get all text and extract selection */
    char* allText = (char*)GlobalAlloc(GPTR, len + 1);
    if (allText) {
        SendMessage(hwndEdit, WM_GETTEXT, len + 1, (LPARAM)allText);
        int i, j = 0;
        for (i = start; i < end && allText[i]; i++) {
            buffer[j++] = allText[i];
        }
        buffer[j] = '\0';
        GlobalFree((HGLOBAL)allText);
    } else {
        buffer[0] = '\0';
    }
}

/* Manipulation functions */
void ManipulateSelection(int manipId) {
    int start, end;
    SendMessage(hwndInput, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
    if (start == end) return;
    
    char sel[4096] = {0};
    GetSelectedText(hwndInput, sel, 4096);
    
    char result[8192] = {0};
    
    switch (manipId) {
    case IDM_WRAP_IF:
        sprintf(result, "if (%s) {\n    %s\n}", sel, sel);
        break;
    case IDM_WRAP_WHILE:
        sprintf(result, "while (%s) {\n    %s\n}", sel, sel);
        break;
    case IDM_WRAP_FOR:
        sprintf(result, "for (int i = 0; i < %s; i++) {\n    %s\n}", sel, sel);
        break;
    case IDM_CONVERT_FUNC:
        sprintf(result, "void %s_function(void) {\n    %s\n}", sel, sel);
        break;
    case IDM_EXTRACT_FUNC:
        sprintf(result, "void extracted_function(void) {\n    %s\n}", sel);
        break;
    case IDM_ADD_COMMENT:
        sprintf(result, "/* %s */", sel);
        break;
    case IDM_REMOVE_COMMENT:
        if (sel[0] == '/' && sel[1] == '*') {
            strcpy(result, sel + 2);
            int len = strlen(result);
            if (len >= 2 && result[len-2] == '*' && result[len-1] == '/') {
                result[len-2] = '\0';
            }
        } else {
            strcpy(result, sel);
        }
        break;
    case IDM_FORMAT_CODE:
        strcpy(result, sel);
        break;
    case IDM_CONVERT_TO_MACRO:
        sprintf(result, "#define %s", sel);
        break;
    case IDM_EXTRACT_MACRO:
        sprintf(result, "#define MACRO_%s", sel);
        break;
    default:
        strcpy(result, sel);
    }
    
    SendMessage(hwndInput, EM_SETSEL, start, end);
    SendMessage(hwndInput, EM_REPLACESEL, TRUE, (LPARAM)result);
}

void ShowManipulationToolbar(BOOL show) {
    if (show) {
        ShowWindow(hwndToolbarCode, SW_SHOW);
    } else {
        ShowWindow(hwndToolbarCode, SW_HIDE);
    }
}

void UpdateStatusBar(LPCTSTR text) {
    SendMessage(hwndStatusBar, SB_SETTEXT, 0, (LPARAM)text);
}

/* Tab management functions */
int FindTabByPath(const char* filePath) {
    for (int i = 0; i < g_tabCount; i++) {
        if (strcmp(g_tabs[i].filePath, filePath) == 0) {
            return i;
        }
    }
    return -1;
}

int CreateNewTab(const char* filePath, const char* title) {
    if (g_tabCount >= MAX_TABS) {
        MessageBox(hwndMain, "Too many tabs open", "Error", MB_ICONWARNING);
        return -1;
    }
    
    int idx = g_tabCount++;
    strcpy(g_tabs[idx].filePath, filePath);
    strcpy(g_tabs[idx].title, title);
    g_tabs[idx].isModified = FALSE;
    g_tabs[idx].editorWnd = NULL;
    
    return idx;
}

void EnsureUntitledTabExists(void) {
    if (g_tabCount > 0) {
        return;
    }

    int untitledTab = CreateNewTab("", "untitled");
    if (untitledTab >= 0) {
        g_activeTab = untitledTab;
        RefreshTabControl();
        DebugLog("[TAB] Recreated untitled tab after closing the last tab\n");
    }
}

void CloseTab(int tabIdx) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return;
    
    /* Shift remaining tabs */
    for (int i = tabIdx; i < g_tabCount - 1; i++) {
        g_tabs[i] = g_tabs[i + 1];
    }
    g_tabCount--;
    
    if (g_activeTab >= g_tabCount) {
        g_activeTab = g_tabCount - 1;
    }
}

/* Close a tab after prompting to save if there are unsaved changes */
int CloseTabWithPrompt(int tabIdx) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return IDYES;
    
    /* Check if tab has unsaved changes (marked with asterisk) and prompt to save */
    int result = PromptSaveTab(tabIdx);
    
    /* If user canceled, leave the tab open */
    if (result == IDCANCEL) return IDCANCEL;

    /* If user chose 'No', clear the modified state in memory and in the treeview */
    if (result == IDNO) {
        if (g_tabs[tabIdx].isModified) {
            g_tabs[tabIdx].isModified = FALSE;
            UpdateTreeViewItemModified(g_tabs[tabIdx].filePath, FALSE);
            UpdateTabTitle(tabIdx, FALSE);
        }
    }

    /* Close the tab */
    CloseTab(tabIdx);

    /* If the last tab was closed, recreate an untitled tab immediately. */
    if (g_tabCount == 0) {
        EnsureUntitledTabExists();
    }

    return result;
}

/* Update TreeView item text to include/exclude asterisk for modified files */
void UpdateTreeViewItemModified(const char* filePath, BOOL isModified) {
    if (!filePath || !hwndProjectTree) return;
    
    /* Get the filename from the path */
    const char* displayName = strrchr(filePath, '\\');
    if (displayName) displayName++;
    else displayName = filePath;
    
    /* Handle untitled files - check if active tab is untitled */
    if ((filePath[0] == '\0' || displayName[0] == '\0') && g_activeTab >= 0 && g_activeTab < g_tabCount) {
        if (strcmp(g_tabs[g_activeTab].title, "untitled") == 0) {
            displayName = "untitled";
        }
    }
    
    /* Build the name to search for (with or without asterisk) */
    char searchName[MAX_PATH];
    if (isModified) {
        snprintf(searchName, sizeof(searchName), "*%s", displayName);
    } else {
        strcpy(searchName, displayName);
    }
    
    HTREEITEM hRoot = TreeView_GetRoot(hwndProjectTree);
    if (!hRoot) return;

    UpdateTreeItemRecursive(hwndProjectTree, hRoot, displayName, searchName);
}

void UpdateTabTitle(int tabIdx, BOOL isModified) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return;
    
    g_tabs[tabIdx].isModified = isModified;
    
    /* Truncate long titles to 14 chars */
    char title[MAX_PATH];
    char* src = g_tabs[tabIdx].title;
    int len = strlen(src);
    if (len > 14) {
        /* Copy first 11 chars + "..." = 14 total */
        strncpy(title, src, 11);
        title[11] = '\0';
        strcat(title, "...");
    } else {
        strcpy(title, src);
    }
    
    TCITEM tci;
    tci.mask = TCIF_TEXT;
    tci.pszText = title;
    TabCtrl_SetItem(hwndCodeTab, tabIdx, &tci);
}

void RefreshTabControl() {
    /* Clear all tabs */
    TabCtrl_DeleteAllItems(hwndCodeTab);
    
    /* Re-add all tabs */
    TCITEM tci;
    tci.mask = TCIF_TEXT;
    
    for (int i = 0; i < g_tabCount; i++) {
        char title[MAX_PATH];
        char* src = g_tabs[i].title;
        int len = strlen(src);
        if (len > 14) {
            strncpy(title, src, 11);
            title[11] = '\0';
            strcat(title, "...");
        } else {
            strcpy(title, src);
        }
        
        tci.pszText = title;
        TabCtrl_InsertItem(hwndCodeTab, i, &tci);
    }
    
    /* Select active tab */
    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
        TabCtrl_SetCurSel(hwndCodeTab, g_activeTab);
        EnsureTabVisible(g_activeTab);
    }
    
    UpdateTabNavigationButtons();
    
    /* Position close button next to active tab */
    PositionTabCloseButton();
}

/* Position the close button next to the active tab */
void PositionTabCloseButton() {
    if (g_activeTab < 0 || g_activeTab >= g_tabCount) {
        ShowWindow(hwndTabClose, SW_HIDE);
        return;
    }
    
    /* Get the bounding rectangle of the active tab */
    RECT tabRect;
    if (TabCtrl_GetItemRect(hwndCodeTab, g_activeTab, &tabRect)) {
        /* Get tab control position */
        RECT tabCtrlRect;
        GetWindowRect(hwndCodeTab, &tabCtrlRect);
        
        /* Calculate close button position - to the right of the tab text */
        int btnX = tabCtrlRect.left + tabRect.right - 5;
        int btnY = tabCtrlRect.top + 3;
        
        /* Only show if there's room */
        if (btnX + 20 < tabCtrlRect.right) {
            SetWindowPos(hwndTabClose, HWND_TOP, btnX, btnY, 16, 16, SWP_SHOWWINDOW);
            ShowWindow(hwndTabClose, SW_SHOW);
        } else {
            ShowWindow(hwndTabClose, SW_HIDE);
        }
    }
}

static BOOL TabControlNeedsScroll(void) {
    if (g_tabCount < 2 || !hwndCodeTab) return FALSE;
    RECT rc;
    GetClientRect(hwndCodeTab, &rc);
    HDC hdc = GetDC(hwndCodeTab);
    HFONT hFont = (HFONT)SendMessage(hwndCodeTab, WM_GETFONT, 0, 0);
    HFONT hOld = (HFONT)SelectObject(hdc, hFont ? hFont : GetStockObject(SYSTEM_FONT));
    int totalWidth = 0;
    for (int i = 0; i < g_tabCount; i++) {
        char title[MAX_PATH];
        char* src = g_tabs[i].title;
        int len = strlen(src);
        if (len > 14) {
            strncpy(title, src, 11);
            title[11] = '\0';
            strcat(title, "...");
        } else {
            strcpy(title, src);
        }
        SIZE size;
        GetTextExtentPoint32(hdc, title, strlen(title), &size);
        totalWidth += size.cx + 30;
        if (totalWidth > rc.right - rc.left) {
            SelectObject(hdc, hOld);
            ReleaseDC(hwndCodeTab, hdc);
            return TRUE;
        }
    }
    SelectObject(hdc, hOld);
    ReleaseDC(hwndCodeTab, hdc);
    return FALSE;
}

static void UpdateTabNavigationButtons(void) {
    BOOL needScroll = TabControlNeedsScroll();
    if (hwndTabPrev) ShowWindow(hwndTabPrev, needScroll ? SW_SHOW : SW_HIDE);
    if (hwndTabNext) ShowWindow(hwndTabNext, needScroll ? SW_SHOW : SW_HIDE);
}

static void EnsureTabVisible(int tabIndex) {
    if (tabIndex >= 0 && tabIndex < g_tabCount && hwndCodeTab) {
        int currentSel = TabCtrl_GetCurSel(hwndCodeTab);
        if (currentSel != tabIndex) {
            g_ignoreTabSelectionChange = TRUE;
            TabCtrl_SetCurSel(hwndCodeTab, tabIndex);
            if (currentSel >= 0) {
                TabCtrl_SetCurSel(hwndCodeTab, currentSel);
            }
            g_ignoreTabSelectionChange = FALSE;
        }
        g_tabScrollIndex = tabIndex;
    }
}

int PromptSaveTab(int tabIdx) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return IDYES;
    
    if (!g_tabs[tabIdx].isModified) return IDYES;
    
    char msg[MAX_PATH + 64];
    sprintf(msg, "Save changes to %s?", g_tabs[tabIdx].title);
    
    int result = MessageBox(hwndMain, msg, "Save", MB_YESNOCANCEL | MB_ICONQUESTION);
    
    if (result == IDYES) {
        /* Check if this is an untitled file - if so, need SaveAs dialog */
        if (g_tabs[tabIdx].filePath[0] == '\0' || strcmp(g_tabs[tabIdx].title, "untitled") == 0) {
            DebugLog("[SAVE] Untitled file in PromptSaveTab, opening SaveAs dialog\n");
            OPENFILENAME ofn;
            char fileBuffer[MAX_PATH] = {0};
            
            memset(&ofn, 0, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwndMain;
            ofn.lpstrFile = fileBuffer;
            ofn.nMaxFile = sizeof(fileBuffer);
            ofn.lpstrFilter = "C Files (*.c)\0*.c\0Header Files (*.h)\0*.h\0All Files (*.*)\0*.*\0";
            ofn.lpstrDefExt = "c";
            ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;
            
            if (GetSaveFileName(&ofn)) {
                char content[65536];
                SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
                
                FILE* fp = fopen(fileBuffer, "wb");
                if (fp) {
                    size_t len = strlen(content);
                    if (len > 0) fwrite(content, 1, len, fp);
                    fclose(fp);
                    /* Update the tab's filepath and title */
                    strcpy(g_tabs[tabIdx].filePath, fileBuffer);
                    char* filename = strrchr(fileBuffer, '\\');
                    if (filename) filename++;
                    else filename = fileBuffer;
                    strcpy(g_tabs[tabIdx].title, filename);
                    AddFileToProject(fileBuffer);
                    g_tabs[tabIdx].isModified = FALSE;
                    UpdateTabTitle(tabIdx, FALSE);
                    UpdateTreeViewItemModified(g_tabs[tabIdx].filePath, FALSE);
                    return IDYES;
                } else {
                    MessageBox(hwndMain, "Failed to save file", "Error", MB_ICONERROR);
                    return IDCANCEL;
                }
            } else {
                /* User cancelled the SaveAs dialog */
                return IDCANCEL;
            }
        }
        
        /* Regular file save */
        FILE* fp = fopen(g_tabs[tabIdx].filePath, "wb");
        if (fp) {
            char content[65536];
            SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
            size_t len = strlen(content);
            if (len > 0) fwrite(content, 1, len, fp);
            fclose(fp);
            g_tabs[tabIdx].isModified = FALSE;
            UpdateTabTitle(tabIdx, FALSE);
            UpdateTreeViewItemModified(g_tabs[tabIdx].filePath, FALSE);
        } else {
            MessageBox(hwndMain, "Failed to save file", "Error", MB_ICONERROR);
            return IDCANCEL;
        }
    }
    
    return result;
}

int PromptSaveAllTabs() {
    for (int i = 0; i < g_tabCount; i++) {
        int result = PromptSaveTab(i);
        if (result == IDCANCEL) return IDCANCEL;
    }
    return IDYES;
}

/* Activate the currently selected file in the project tree */
void ActivateSelectedTreeFile(void) {
    HTREEITEM hItem = TreeView_GetSelection(hwndProjectTree);
    if (!hItem) return;

    TVITEM tvi;
    char buffer[MAX_PATH];
    tvi.mask = TVIF_TEXT | TVIF_HANDLE;
    tvi.hItem = hItem;
    tvi.pszText = buffer;
    tvi.cchTextMax = MAX_PATH;
    TreeView_GetItem(hwndProjectTree, &tvi);

    if (strcmp(buffer, "Project Files") == 0) {
        DebugLog("[TREEVIEW] Root folder selected, skipping\n");
        return;
    }

    /* Handle untitled tab special case */
    if (strcmp(buffer, "untitled") == 0) {
        DebugLog("[TREEVIEW] Untitled tab selected\n");
        /* Find and activate the untitled tab */
        for (int i = 0; i < g_tabCount; i++) {
            if (strcmp(g_tabs[i].title, "untitled") == 0) {
                g_activeTab = i;
                TabCtrl_SetCurSel(hwndCodeTab, i);
                EnsureTabVisible(i);
                if (g_tabs[i].filePath[0] != '\0') {
                    LoadFileIntoEditor(g_tabs[i].filePath);
                }
                return;
            }
        }

        /* If no untitled tab exists, create a fresh one and activate it. */
        DebugLog("[TREEVIEW] No untitled tab found, creating one\n");
        int untitledTab = CreateNewTab("", "untitled");
        if (untitledTab >= 0) {
            g_activeTab = untitledTab;
            RefreshTabControl();
            TabCtrl_SetCurSel(hwndCodeTab, untitledTab);
            EnsureTabVisible(untitledTab);
        }
        return;
    }

    DebugLog("[TREEVIEW] Activating selected: '%s'\n", buffer);
    BOOL found = FALSE;
    for (int i = 0; i < g_openedFileCount; i++) {
        char* filename = strrchr(g_openedFiles[i], '\\');
        if (filename) filename++;
        else filename = g_openedFiles[i];

        const char* compareBuffer = buffer;
        if (buffer[0] == '*') compareBuffer = buffer + 1;

        if (strcmp(filename, compareBuffer) == 0) {
            DebugLog("[TREEVIEW] FOUND: %s\n", g_openedFiles[i]);
            LoadFileIntoEditor(g_openedFiles[i]);
            found = TRUE;
            break;
        }
    }

    if (!found) {
        DebugLog("[TREEVIEW] File not found in g_openedFiles\n");
    }
}

void ClearAllTabs() {
    g_tabCount = 0;
    g_activeTab = -1;
    TabCtrl_DeleteAllItems(hwndCodeTab);
}

/* Check if file extension is .c or .h */
BOOL IsCOrHFile(const char* ext) {
    return (stricmp(ext, ".c") == 0 || stricmp(ext, ".h") == 0 || stricmp(ext, ".cpp") == 0 || stricmp(ext, ".hpp") == 0);
}

/* Add file to project tracking */
void AddFileToProject(const char* filePath) {
    if (g_openedFileCount < MAX_OPENED_FILES) {
        strcpy(g_openedFiles[g_openedFileCount++], filePath);
    }
}

/* Load file content into editor - preserve all formatting */
void LoadFileIntoEditor(const char* filePath) {
    DebugLog("[EDITOR] LoadFileIntoEditor called with: %s\n", filePath);

    if (!filePath || filePath[0] == '\0') {
        DebugLog("[EDITOR] Untitled tab detected, clearing editor\n");
        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
        SendMessage(hwndInput, EM_FMTLINES, FALSE, 0);
        UpdateLineNumbers(hwndInput, hwndLineNumbers);
        UpdateStatusBar("untitled");
        return;
    }

    FILE* fp = fopen(filePath, "rb");
    if (!fp) {
        DebugLog("[ERROR] fopen failed for: %s (errno=%d)\n", filePath, errno);
        MessageBox(hwndMain, "Failed to open file", "Error", MB_ICONERROR);
        return;
    }
    
    DebugLog("[EDITOR] File opened successfully\n");
    
    /* Get file size */
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (fileSize <= 0) {
        fclose(fp);
        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
        return;
    }
    
    /* Allocate buffer and read raw bytes */
    char* buffer = (char*)GlobalAlloc(GPTR, fileSize + 1);
    if (!buffer) {
        fclose(fp);
        MessageBox(hwndMain, "Out of memory", "Error", MB_ICONERROR);
        return;
    }
    
    size_t bytesRead = fread(buffer, 1, fileSize, fp);
    fclose(fp);
    
    /* Strip UTF-8 BOM if present so ANSI edit control does not get weird characters */
    if (bytesRead >= 3 && (unsigned char)buffer[0] == 0xEF && (unsigned char)buffer[1] == 0xBB && (unsigned char)buffer[2] == 0xBF) {
        memmove(buffer, buffer + 3, bytesRead - 3);
        bytesRead -= 3;
        DebugLog("[EDITOR] Stripped UTF-8 BOM from file\n");
    }

    /* Normalize line endings to CRLF for Windows edit control compatibility */
    char* normalized = (char*)GlobalAlloc(GPTR, bytesRead * 2 + 1);
    if (!normalized) {
        GlobalFree((HGLOBAL)buffer);
        MessageBox(hwndMain, "Out of memory", "Error", MB_ICONERROR);
        return;
    }

    char* src = buffer;
    char* dst = normalized;
    for (size_t i = 0; i < bytesRead; i++) {
        if (src[i] == '\n') {
            if (i == 0 || src[i - 1] != '\r') {
                *dst++ = '\r';
            }
            *dst++ = '\n';
        } else if (src[i] == '\r') {
            *dst++ = '\r';
            if (i + 1 >= bytesRead || src[i + 1] != '\n') {
                *dst++ = '\n';
            }
        } else {
            *dst++ = src[i];
        }
    }
    *dst = '\0';

    /* Set the text - this preserves all whitespace */
    SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)normalized);
    /* Ensure the edit control does not auto-wrap lines */
    SendMessage(hwndInput, EM_FMTLINES, FALSE, 0);
    UpdateLineNumbers(hwndInput, hwndLineNumbers);

    GlobalFree((HGLOBAL)normalized);
    GlobalFree((HGLOBAL)buffer);
    
    /* Add to tab if not already open */
    char* filename = strrchr(filePath, '\\');
    if (filename) filename++;
    else filename = (char*)filePath;
    
    int tabIdx = FindTabByPath(filePath);
    if (tabIdx == -1) {
        tabIdx = CreateNewTab(filePath, filename);
        RefreshTabControl();
    }
    
    g_activeTab = tabIdx;
    TabCtrl_SetCurSel(hwndCodeTab, g_activeTab);
    EnsureTabVisible(g_activeTab);
    
    UpdateStatusBar(filePath);
}

/* Recursively scan folder for C/H files */
void ScanFolderForFiles(const char* folderPath, char files[][MAX_PATH], int* count, int maxCount) {
    WIN32_FIND_DATA fd;
    char searchPath[MAX_PATH];
    char fullPath[MAX_PATH];
    
    sprintf(searchPath, "%s\\*", folderPath);
    HANDLE hFind = FindFirstFile(searchPath, &fd);
    
    if (hFind == INVALID_HANDLE_VALUE) return;
    
    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;
        
        sprintf(fullPath, "%s\\%s", folderPath, fd.cFileName);
        
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            ScanFolderForFiles(fullPath, files, count, maxCount);
        } else {
            char* ext = strrchr(fd.cFileName, '.');
            if (ext && IsCOrHFile(ext) && *count < maxCount) {
                strcpy(files[(*count)++], fullPath);
            }
        }
    } while (FindNextFile(hFind, &fd) && *count < maxCount);
    
    FindClose(hFind);
}

/* Populate project tree with folder structure or flat list */
void PopulateProjectTree(HWND hwndTree, const char* rootPath, BOOL isFlat) {
    TVINSERTSTRUCT tvis;
    HTREEITEM hRoot;
    char files[MAX_OPENED_FILES][MAX_PATH];
    int fileCount = 0;
    
    TreeView_DeleteAllItems(hwndTree);
    
    if (isFlat) {
        /* Flat mode - just list files */
        tvis.hParent = TVI_ROOT;
        tvis.hInsertAfter = TVI_LAST;
        tvis.item.mask = TVIF_TEXT;
        tvis.item.pszText = "Project Files";
        hRoot = TreeView_InsertItem(hwndTree, &tvis);
        
        for (int i = 0; i < g_openedFileCount; i++) {
            char* filename = strrchr(g_openedFiles[i], '\\');
            if (!filename) filename = g_openedFiles[i];
            else filename++;
            
            tvis.hParent = hRoot;
            tvis.item.mask = TVIF_TEXT;
            tvis.item.pszText = filename;
            TreeView_InsertItem(hwndTree, &tvis);
        }
    } else {
        /* Folder-based mode - show tree structure */
        tvis.hParent = TVI_ROOT;
        tvis.hInsertAfter = TVI_LAST;
        tvis.item.mask = TVIF_TEXT;
        
        /* Get folder name from path */
        char rootName[MAX_PATH];
        const char* lastSlash = strrchr(rootPath, '\\');
        if (lastSlash) {
            strcpy(rootName, lastSlash + 1);
        } else {
            strcpy(rootName, rootPath);
        }
        tvis.item.pszText = rootName;
        hRoot = TreeView_InsertItem(hwndTree, &tvis);
        
        /* Scan folder recursively */
        ScanFolderForFiles(rootPath, files, &fileCount, MAX_OPENED_FILES);
        
        /* Add files to tree under root */
        for (int i = 0; i < fileCount; i++) {
            char* filename = strrchr(files[i], '\\');
            if (filename) filename++;
            else filename = files[i];
            
            tvis.hParent = hRoot;
            tvis.item.mask = TVIF_TEXT;
            tvis.item.pszText = filename;
            TreeView_InsertItem(hwndTree, &tvis);
        }
    }
    
    TreeView_Expand(hwndTree, TreeView_GetRoot(hwndTree), TVE_EXPAND);
}

/* Open folder and populate tree */
void OpenFolder(HWND hwnd, const char* folderPath) {
    (void)hwnd;
    g_isFolderBased = TRUE;
    g_openedFileCount = 0;
    
    /* Scan for all C/H files in folder */
    ScanFolderForFiles(folderPath, g_openedFiles, &g_openedFileCount, MAX_OPENED_FILES);
    
    PopulateProjectTree(hwndProjectTree, folderPath, FALSE);
    
    char status[256];
    sprintf(status, "Opened folder: %s (%d files)", folderPath, g_openedFileCount);
    UpdateStatusBar(status);
}

/* Add untitled tab to the treeview */
void AddUntitledToTreeView(void) {
    TVINSERTSTRUCT tvis;
    HTREEITEM hRoot = TreeView_GetRoot(hwndProjectTree);
    if (!hRoot) return;
    
    tvis.hParent = hRoot;
    tvis.hInsertAfter = TVI_FIRST;
    tvis.item.mask = TVIF_TEXT;
    tvis.item.pszText = "untitled";
    TreeView_InsertItem(hwndProjectTree, &tvis);
}

/* Open files with dialog */
void OpenFilesWithDialog(HWND hwnd) {
    OPENFILENAME ofn;
    char fileBuffer[65536] = {0};
    char files[MAX_OPENED_FILES][MAX_PATH];
    int fileCount = 0;
    
    DebugLog("[DIALOG] OpenFilesWithDialog called\n");
    
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileBuffer;
    ofn.nMaxFile = sizeof(fileBuffer);
    ofn.lpstrFilter = "C/H Files (*.c;*.h)\0*.c;*.h\0All Files (*.*)\0*.*\0";
    ofn.lpstrDefExt = "c";
    ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn)) {
        DebugLog("[DIALOG] GetOpenFileName returned TRUE\n");
        ClearAllTabs();
        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
        SendMessage(hwndOutput, WM_SETTEXT, 0, (LPARAM)"");
        TreeView_DeleteAllItems(hwndProjectTree);
        g_openedFileCount = 0;
        char* p = fileBuffer;
        
        /* Check if single folder selected or multiple files */
        if (strlen(p) > 0 && p[strlen(p)-1] == '\\') {
            /* Single folder selected */
            DebugLog("[DIALOG] Folder mode: %s\n", p);
            OpenFolder(hwnd, p);
        } else {
            /* Multiple files selected - format: "dir\0file1\0file2\0\0" */
            DebugLog("[DIALOG] Multi-file mode\n");
            g_isFolderBased = FALSE;
            
            /* Determine whether a single file or multiple files were selected */
            char dirPath[MAX_PATH];
            strcpy(dirPath, p);
            p += strlen(p) + 1;
            
            if (*p == '\0') {
                /* Single file selected: full path is returned as the first string */
                if (fileCount < MAX_OPENED_FILES) {
                    strcpy(files[fileCount++], dirPath);
                    DebugLog("[DIALOG] Single file selected: %s\n", dirPath);
                    AddFileToProject(dirPath);
                }
            } else {
                /* Multiple files selected - first string is the directory */
                DebugLog("[DIALOG] Directory: %s\n", dirPath);
                while (*p) {
                    char fullPath[MAX_PATH];
                    sprintf(fullPath, "%s\\%s", dirPath, p);
                    
                    if (fileCount < MAX_OPENED_FILES) {
                        strcpy(files[fileCount++], fullPath);
                        DebugLog("[DIALOG] File %d: %s\n", fileCount, fullPath);
                        AddFileToProject(fullPath);
                    }
                    p += strlen(p) + 1;
                }
            }
            
            DebugLog("[DIALOG] Total files selected: %d\n", fileCount);
            
            /* Load the first file into editor */
            if (fileCount > 0) {
                DebugLog("[DIALOG] Loading first file: %s\n", files[0]);
                LoadFileIntoEditor(files[0]);
            }
            
            PopulateProjectTree(hwndProjectTree, "", TRUE);
            
            char status[256];
            sprintf(status, "Opened %d files", fileCount);
            UpdateStatusBar(status);
        }
    }
}

/* Save file with dialog */
void SaveFileWithDialog(HWND hwnd, BOOL saveAs) {
    OPENFILENAME ofn;
    char fileBuffer[MAX_PATH] = {0};
    
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileBuffer;
    ofn.nMaxFile = sizeof(fileBuffer);
    ofn.lpstrFilter = "C Files (*.c)\0*.c\0Header Files (*.h)\0*.h\0All Files (*.*)\0*.*\0";
    ofn.lpstrDefExt = "c";
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;
    
    if (saveAs) {
        if (GetSaveFileName(&ofn)) {
            char content[65536];
            SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
            
            FILE* fp = fopen(fileBuffer, "wb");
            if (fp) {
                size_t len = strlen(content);
                if (len > 0) fwrite(content, 1, len, fp);
                fclose(fp);
                UpdateStatusBar(fileBuffer);
                /* Clear modified state and update tab if it was untitled */
                if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                    /* Check if this was an untitled tab */
                    if (g_tabs[g_activeTab].filePath[0] == '\0' || strcmp(g_tabs[g_activeTab].title, "untitled") == 0) {
                        /* Update the tab's filepath and title to the new filename */
                        strcpy(g_tabs[g_activeTab].filePath, fileBuffer);
                        char* filename = strrchr(fileBuffer, '\\');
                        if (filename) filename++;
                        else filename = fileBuffer;
                        strcpy(g_tabs[g_activeTab].title, filename);
                        /* Add to opened files list */
                        AddFileToProject(fileBuffer);
                        /* Update treeview to show the real filename instead of untitled */
                        PopulateProjectTree(hwndProjectTree, "", TRUE);
                        RefreshTabControl();
                    }
                    g_tabs[g_activeTab].isModified = FALSE;
                    UpdateTreeViewItemModified(g_tabs[g_activeTab].filePath, FALSE);
                    UpdateTabTitle(g_activeTab, FALSE);
                }
            } else {
                MessageBox(hwnd, "Failed to save file", "Error", MB_ICONERROR);
            }
        }
    } else {
        /* Simple save - just save current content */
        char content[65536];
        SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
        
        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
            /* Check if this is an untitled file - if so, force SaveAs dialog */
            if (g_tabs[g_activeTab].filePath[0] == '\0' || strcmp(g_tabs[g_activeTab].title, "untitled") == 0) {
                DebugLog("[SAVE] Untitled file detected, forcing SaveAs dialog\n");
                SaveFileWithDialog(hwnd, TRUE);
                return;
            }
            FILE* fp = fopen(g_tabs[g_activeTab].filePath, "wb");
            if (fp) {
                size_t len = strlen(content);
                if (len > 0) fwrite(content, 1, len, fp);
                fclose(fp);
                UpdateStatusBar(g_tabs[g_activeTab].filePath);
                /* Clear modified state */
                g_tabs[g_activeTab].isModified = FALSE;
                UpdateTreeViewItemModified(g_tabs[g_activeTab].filePath, FALSE);
                UpdateTabTitle(g_activeTab, FALSE);
            }
        } else if (g_openedFileCount > 0) {
            FILE* fp = fopen(g_openedFiles[0], "wb");
            if (fp) {
                size_t len = strlen(content);
                if (len > 0) fwrite(content, 1, len, fp);
                fclose(fp);
                UpdateStatusBar(g_openedFiles[0]);
                /* Clear modified state */
                if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                    g_tabs[g_activeTab].isModified = FALSE;
                    UpdateTreeViewItemModified(g_tabs[g_activeTab].filePath, FALSE);
                    UpdateTabTitle(g_activeTab, FALSE);
                }
            }
        } else {
            /* No file open, do Save As */
            SaveFileWithDialog(hwnd, TRUE);
        }
    }
}

/* Save all files (placeholder) */
void SaveAllFiles(HWND hwnd) {
    (void)hwnd;
    UpdateStatusBar("Save All - Not implemented yet");
}

/* Update line numbers based on editor content */
void RepositionCodeArea(int clientWidth, int clientHeight) {
    int codeLeft = 220 + g_lineNumberWidth;
    int availableCodeWidth = clientWidth - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
    if (availableCodeWidth < 240) availableCodeWidth = 240;
    int inputWidth = (g_currentInputWidth > 0) ? g_currentInputWidth : (availableCodeWidth * 85 / 100);
    if (g_currentInputWidth == 0) g_currentInputWidth = inputWidth;
    int splitterX = codeLeft + inputWidth;
    int outputX = splitterX + g_splitterWidth + 5;
    int outputWidth = clientWidth - outputX - g_propertiesWidth - 10;
    if (outputWidth < 100) outputWidth = 100;

    MoveWindow(hwndProjectTree, 10, 90, 200, clientHeight - 150, TRUE);
    MoveWindow(hwndLineNumbers, 220, 115, g_lineNumberWidth, clientHeight - 165, TRUE);
    MoveWindow(hwndCodeTab, codeLeft, 90, inputWidth, 25, TRUE);
    /* Position tab navigation buttons on the right side of the tab bar */
    if (hwndTabPrev) MoveWindow(hwndTabPrev, codeLeft + inputWidth - 50, 88, 22, 22, TRUE);
    if (hwndTabNext) MoveWindow(hwndTabNext, codeLeft + inputWidth - 26, 88, 22, 22, TRUE);
    MoveWindow(hwndInput, codeLeft, 115, inputWidth, clientHeight - 165, TRUE);
    MoveWindow(hwndCodeSplitter, splitterX, 90, g_splitterWidth, clientHeight - 150, TRUE);
    MoveWindow(hwndOutput, outputX, 90, outputWidth, clientHeight - 150, TRUE);
    MoveWindow(hwndProperties, clientWidth - g_propertiesWidth, 90, g_propertiesWidth, clientHeight - 150, TRUE);
    PositionTabCloseButton();
    UpdateTabNavigationButtons();
}

void UpdateLineNumbers(HWND hwndEditor, HWND hwndGutter) {
    int lineCount = (int)SendMessage(hwndEditor, EM_GETLINECOUNT, 0, 0);
    if (lineCount < 1) lineCount = 1;

    int digits = 1;
    for (int n = lineCount; n >= 10; n /= 10) digits++;

    HDC hdc = GetDC(hwndGutter);
    HFONT hFont = (HFONT)SendMessage(hwndGutter, WM_GETFONT, 0, 0);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    TEXTMETRIC tm;
    GetTextMetrics(hdc, &tm);
    int desiredWidth = digits * tm.tmAveCharWidth + 14;
    if (desiredWidth < 24) desiredWidth = 24;
    SelectObject(hdc, hOldFont);
    ReleaseDC(hwndGutter, hdc);

    if (desiredWidth != g_lineNumberWidth) {
        g_lineNumberWidth = desiredWidth;
        RECT rc;
        GetClientRect(hwndMain, &rc);
        RepositionCodeArea(rc.right - rc.left, rc.bottom - rc.top);
    }

    InvalidateRect(hwndGutter, NULL, TRUE);
    UpdateWindow(hwndGutter);
}

LRESULT CALLBACK EditorSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_VSCROLL || msg == WM_MOUSEWHEEL || msg == EM_SCROLL || msg == WM_KEYDOWN) {
        LRESULT result = CallWindowProc((WNDPROC)hwndOldEditorProc, hwnd, msg, wParam, lParam);
        UpdateLineNumbers(hwndInput, hwndLineNumbers);
        return result;
    }
    return CallWindowProc((WNDPROC)hwndOldEditorProc, hwnd, msg, wParam, lParam);
}

/* Subclass procedure for line number gutter */
LRESULT CALLBACK LineNumberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        int lineCount = (int)SendMessage(hwndInput, EM_GETLINECOUNT, 0, 0);
        if (lineCount < 1) lineCount = 1;
        
        /* Draw line numbers */
        HFONT hFont = g_codeFont;
        if (!hFont) {
            hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
        }
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(128, 128, 128));
        
        TEXTMETRIC tm;
        GetTextMetrics(hdc, &tm);
        int lineHeight = tm.tmHeight + tm.tmExternalLeading;
        
        RECT editRect = {0};
        SendMessage(hwndInput, EM_GETRECT, 0, (LPARAM)&editRect);
        
        int firstVisibleLine = (int)SendMessage(hwndInput, EM_GETFIRSTVISIBLELINE, 0, 0);
        int y = editRect.top + 1; /* shift down by 1px for better alignment */
        
        int startLine = firstVisibleLine + 1;
        char buf[16];
        for (int i = startLine; i <= lineCount && y < ps.rcPaint.bottom; i++) {
            sprintf(buf, "%d", i);
            RECT rc = {0, y, ps.rcPaint.right, y + lineHeight};
            DrawText(hdc, buf, -1, &rc, DT_RIGHT | DT_NOPREFIX | DT_SINGLELINE | DT_TOP);
            y += lineHeight;
        }
        
        SelectObject(hdc, hOldFont);
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CreateMenus(HWND hwnd) {
    DebugLog("[FUNC] CreateMenus called\n");
    HMENU hMenuBar = CreateMenu();
    HMENU hFile = CreateMenu();
    HMENU hEdit = CreateMenu();
    HMENU hProject = CreateMenu();
    HMENU hBuild = CreateMenu();
    HMENU hTools = CreateMenu();
    HMENU hOptions = CreateMenu();
    
    /* File menu with keyboard shortcuts */
    AppendMenu(hFile, MF_STRING, IDM_FILE_NEW_FILE, "&New File\tCtrl+N");
    AppendMenu(hFile, MF_STRING, IDM_FILE_NEW, "New &Project\tCtrl+Shift+N");
    AppendMenu(hFile, MF_STRING, IDM_FILE_OPEN_FILE, "&Open File\tCtrl+O");
    AppendMenu(hFile, MF_STRING, IDM_FILE_OPEN, "Open P&roject...\tCtrl+Shift+O");
    AppendMenu(hFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFile, MF_STRING, IDM_FILE_SAVE, "&Save\tCtrl+S");
    AppendMenu(hFile, MF_STRING, IDM_FILE_SAVEAS, "Save &As...\tCtrl+Shift+S");
    AppendMenu(hFile, MF_STRING, IDM_FILE_SAVEALL, "Save A&ll\tCtrl+Shift+Alt+S");
    AppendMenu(hFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFile, MF_STRING, IDM_FILE_EXIT, "E&xit\tAlt+F4");
    
    /* Edit menu with keyboard shortcuts */
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_UNDO, "&Undo\tCtrl+Z");
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_REDO, "&Redo\tCtrl+Y");
    AppendMenu(hEdit, MF_SEPARATOR, 0, NULL);
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_CUT, "Cu&t\tCtrl+X");
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_COPY, "&Copy\tCtrl+C");
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_PASTE, "&Paste\tCtrl+V");
    AppendMenu(hEdit, MF_SEPARATOR, 0, NULL);
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_SELECTALL, "Select &All\tCtrl+A");
    
    /* Project menu with keyboard shortcuts */
    AppendMenu(hProject, MF_STRING, IDM_PROJECT_SETTINGS, "&Settings...\tF9");
    
    /* Build menu with keyboard shortcuts */
    AppendMenu(hBuild, MF_STRING, IDM_BUILD_COMPILE, "&Compile\tF5");
    AppendMenu(hBuild, MF_STRING, IDM_BUILD_RUN, "&Run\tF6");
    
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "&File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, "&Edit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hProject, "&Project");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hBuild, "&Build");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hTools, "&Tools");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hOptions, "&Options");
    
    SetMenu(hwnd, hMenuBar);
    DebugLog("[FUNC] CreateMenus complete\n");
}

void CreateMainToolbar(HWND hwnd) {
    hwndToolbarMain = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | CCS_TOP,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TOOLBAR_MAIN, GetModuleHandle(NULL), NULL);
    
    TBBUTTON tbb[8];
    memset(tbb, 0, sizeof(tbb));
    tbb[0].iBitmap = 0; tbb[0].idCommand = IDM_FILE_NEW; tbb[0].fsState = TBSTATE_ENABLED; tbb[0].fsStyle = BTNS_BUTTON; tbb[0].iString = -1;
    tbb[1].iBitmap = 0; tbb[1].idCommand = IDM_FILE_OPEN; tbb[1].fsState = TBSTATE_ENABLED; tbb[1].fsStyle = BTNS_BUTTON; tbb[1].iString = -1;
    tbb[2].iBitmap = 0; tbb[2].idCommand = IDM_FILE_SAVE; tbb[2].fsState = TBSTATE_ENABLED; tbb[2].fsStyle = BTNS_BUTTON; tbb[2].iString = -1;
    tbb[3].iBitmap = 0; tbb[3].idCommand = 0; tbb[3].fsState = 0; tbb[3].fsStyle = BTNS_SEP; tbb[3].iString = -1;
    tbb[4].iBitmap = 0; tbb[4].idCommand = IDM_EDIT_UNDO; tbb[4].fsState = TBSTATE_ENABLED; tbb[4].fsStyle = BTNS_BUTTON; tbb[4].iString = -1;
    tbb[5].iBitmap = 0; tbb[5].idCommand = IDM_EDIT_REDO; tbb[5].fsState = TBSTATE_ENABLED; tbb[5].fsStyle = BTNS_BUTTON; tbb[5].iString = -1;
    tbb[6].iBitmap = 0; tbb[6].idCommand = 0; tbb[6].fsState = 0; tbb[6].fsStyle = BTNS_SEP; tbb[6].iString = -1;
    tbb[7].iBitmap = 0; tbb[7].idCommand = IDM_PROJECT_SETTINGS; tbb[7].fsState = TBSTATE_ENABLED; tbb[7].fsStyle = BTNS_BUTTON; tbb[7].iString = -1;
    
    SendMessage(hwndToolbarMain, TB_ADDBUTTONS, 8, (LPARAM)tbb);
    SendMessage(hwndToolbarMain, TB_AUTOSIZE, 0, 0);
}

void CreateCodeToolbar(HWND hwnd) {
    hwndToolbarCode = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | CCS_TOP,
        0, 40, 0, 0, hwnd, (HMENU)IDC_TOOLBAR_CODE, GetModuleHandle(NULL), NULL);
    
    /* Code insertion buttons */
    TBBUTTON codeTbb[11];
    memset(codeTbb, 0, sizeof(codeTbb));
    int i;
    int cmdIds[] = {IDT_INSERT_FUNC, IDT_INSERT_IF, IDT_INSERT_FOR, IDT_INSERT_WHILE, IDT_INSERT_SWITCH,
                    IDT_INSERT_STRUCT, IDT_INSERT_UNION, IDT_INSERT_ENUM, IDT_INSERT_TYPEDEF, IDT_INSERT_INCLUDE, IDT_INSERT_DEFINE};
    for (i = 0; i < 11; i++) {
        codeTbb[i].iBitmap = 0; codeTbb[i].idCommand = cmdIds[i]; codeTbb[i].fsState = TBSTATE_ENABLED; codeTbb[i].fsStyle = BTNS_BUTTON; codeTbb[i].iString = -1;
    }
    
    SendMessage(hwndToolbarCode, TB_ADDBUTTONS, 11, (LPARAM)codeTbb);
    SendMessage(hwndToolbarCode, TB_AUTOSIZE, 0, 0);
    
    /* Initially hidden until selection */
    ShowWindow(hwndToolbarCode, SW_HIDE);
}

void CreateStatusBar(HWND hwnd) {
    hwndStatusBar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
        0, 0, 0, 0, hwnd, (HMENU)IDC_STATUSBAR, GetModuleHandle(NULL), NULL);
    
    int parts[] = {200, 400, 600, -1};
    SendMessage(hwndStatusBar, SB_SETPARTS, 4, (LPARAM)parts);
    SendMessage(hwndStatusBar, SB_SETTEXT, 0, (LPARAM)"Ready");
    SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)"Platform: Windows");
    SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)"Compiler: GCC");
    SendMessage(hwndStatusBar, SB_SETTEXT, 3, (LPARAM)"Arch: x86");
}

void CreateMainLayout(HWND hwnd) {
    /* Main toolbar */
    CreateMainToolbar(hwnd);
    
    /* Code toolbar (initially hidden) */
    CreateCodeToolbar(hwnd);
    
    /* Project explorer (left pane) - with buttons for expand/collapse */
    hwndProjectTree = CreateWindowEx(WS_EX_CLIENTEDGE, "SysTreeView32", NULL,
        WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
        10, 50, 200, 500, hwnd, (HMENU)IDC_PROJECT_TREE, GetModuleHandle(NULL), NULL);
    
    /* Line number gutter */
    hwndLineNumbers = CreateWindowEx(0, "OrcaLineNumberWnd", NULL,
        WS_CHILD | WS_VISIBLE,
        220, 115, g_lineNumberWidth, 500, hwnd, (HMENU)5001, GetModuleHandle(NULL), NULL);
    
    /* Set font for line numbers */
    SendMessage(hwndLineNumbers, WM_SETFONT, (WPARAM)g_codeFont, TRUE);
    
    /* Tab control for code files */
    hwndCodeTab = CreateWindowEx(0, WC_TABCONTROL, NULL,
        WS_CHILD | WS_VISIBLE | TCS_TABS | TCS_OWNERDRAWFIXED,
        255, 50, 415, 25, hwnd, (HMENU)IDC_CODE_TAB, GetModuleHandle(NULL), NULL);

    /* Tab navigation buttons (prev/next) */
    hwndTabPrev = CreateWindowEx(0, "BUTTON", "<",
        WS_CHILD | BS_CENTER | BS_PUSHBUTTON | WS_VISIBLE,
        0, 0, 22, 22, hwnd, (HMENU)IDC_TAB_PREV, GetModuleHandle(NULL), NULL);

    hwndTabNext = CreateWindowEx(0, "BUTTON", ">",
        WS_CHILD | BS_CENTER | BS_PUSHBUTTON | WS_VISIBLE,
        0, 0, 22, 22, hwnd, (HMENU)IDC_TAB_NEXT, GetModuleHandle(NULL), NULL);
    
    /* Input code pane - below tabs */
    hwndInput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_NOHIDESEL,
        255, 75, 415, 475, hwnd, (HMENU)IDC_CODE_INPUT, GetModuleHandle(NULL), NULL);
    
    /* Set monospace font for code editor */
    g_codeFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, "Courier New");
    SendMessage(hwndInput, WM_SETFONT, (WPARAM)g_codeFont, TRUE);
    SendMessage(hwndInput, EM_FMTLINES, FALSE, 0);
    hwndOldEditorProc = (WNDPROC)SetWindowLongPtr(hwndInput, GWLP_WNDPROC, (LONG_PTR)EditorSubclassProc);
    
    /* Output code pane */
    hwndOutput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY,
        680, 50, 450, 500, hwnd, (HMENU)IDC_CODE_OUTPUT, GetModuleHandle(NULL), NULL);
    SendMessage(hwndOutput, WM_SETFONT, (WPARAM)g_codeFont, TRUE);
    SendMessage(hwndOutput, EM_FMTLINES, FALSE, 0);
    
    /* Splitter handle between code output and properties */
    hwndCodeSplitter = CreateWindowEx(0, "STATIC", NULL,
        WS_CHILD | WS_VISIBLE,
        1140 - g_splitterWidth, 50, g_splitterWidth, 500, hwnd, (HMENU)IDC_CODE_SPLITTER, GetModuleHandle(NULL), NULL);

    /* Properties window (right pane) */
    hwndProperties = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", NULL,
        WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOINTEGRALHEIGHT,
        1140, 50, 200, 500, hwnd, (HMENU)IDC_PROPERTIES, GetModuleHandle(NULL), NULL);
    
    /* Status bar */
    CreateStatusBar(hwnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    /* Initialize debug console - spawn separate window */
    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    (void)hPrevInstance;
    (void)lpCmdLine;
    
    /* Initialize console logging */
    InitDebugConsole();
    DebugLog("[INIT] WinMain started\n");
    DebugLog("[DEBUG] Console initialized\n");
    
    INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_BAR_CLASSES };
    InitCommonControlsEx(&icex);
    DebugLog("[INIT] Common controls initialized\n");

    WNDCLASS lnwc = {0};
    lnwc.lpfnWndProc = LineNumberWndProc;
    lnwc.hInstance = hInstance;
    lnwc.lpszClassName = "OrcaLineNumberWnd";
    lnwc.hCursor = LoadCursor(NULL, IDC_ARROW);
    lnwc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&lnwc);

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OrcaMainWnd";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    /* Load the embedded PE icon resource first, then fallback to generated data. */
    HICON hIcon = (HICON)LoadImageA(hInstance, MAKEINTRESOURCEA(IDI_MAINICON), IMAGE_ICON,
        GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
    HICON hIconSm = (HICON)LoadImageA(hInstance, MAKEINTRESOURCEA(IDI_MAINICON), IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);

    if (!hIcon || !hIconSm) {
        if (icon_image_1_len > 0) {
            HICON autoIcon = CreateIconFromResourceEx((PBYTE)icon_image_1, icon_image_1_len,
                TRUE, 0x00030000,
                GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON),
                LR_DEFAULTCOLOR | LR_SHARED);
            if (!hIcon) hIcon = autoIcon;
        }
        if (icon_image_0_len > 0) {
            HICON autoIconSm = CreateIconFromResourceEx((PBYTE)icon_image_0, icon_image_0_len,
                TRUE, 0x00030000,
                GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
                LR_DEFAULTCOLOR | LR_SHARED);
            if (!hIconSm) hIconSm = autoIconSm;
        }
        if (!hIcon && icon_image_0_len > 0) {
            hIcon = CreateIconFromResourceEx((PBYTE)icon_image_0, icon_image_0_len,
                TRUE, 0x00030000,
                GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON),
                LR_DEFAULTCOLOR | LR_SHARED);
        }
        if (!hIconSm && icon_image_1_len > 0) {
            hIconSm = CreateIconFromResourceEx((PBYTE)icon_image_1, icon_image_1_len,
                TRUE, 0x00030000,
                GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
                LR_DEFAULTCOLOR | LR_SHARED);
        }
    }

    if (!hIcon) {
        hIcon = LoadIcon(NULL, IDI_APPLICATION);
    }
    if (!hIconSm) {
        hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    }
    wc.hIcon = hIcon;
    wc.hIconSm = hIconSm;
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    RegisterClassEx(&wc);

    LoadConfig();

    hwndMain = CreateWindow("OrcaMainWnd", "Orca - C Code Generator & Manipulator", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1400, 800, NULL, NULL, hInstance, NULL);
    
    /* Set custom icon for window (titlebar, taskbar, alt+tab) */
    if (hIcon) {
        SendMessage(hwndMain, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwndMain, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
    }
    
    /* Start maximized by default */
    ShowWindow(hwndMain, SW_SHOWMAXIMIZED);
    UpdateWindow(hwndMain);

    HACCEL hAccel;
    
    /* Create accelerator table for keyboard shortcuts */
    ACCEL accels[] = {
        {FVIRTKEY | FCONTROL | FSHIFT, 0x4E, IDM_FILE_NEW},       /* Ctrl+Shift+N */
        {FVIRTKEY | FCONTROL, 0x4F, IDM_FILE_OPEN},                /* Ctrl+O */
        {FVIRTKEY | FCONTROL, 0x53, IDM_FILE_SAVE},                /* Ctrl+S */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x53, IDM_FILE_SAVEAS},     /* Ctrl+Shift+S */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x41, IDM_FILE_SAVEALL},    /* Ctrl+Shift+A */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x50, IDM_PROJECT_NEW},     /* Ctrl+Shift+P */
        {FVIRTKEY | FCONTROL, 0x57, IDM_TAB_CLOSE_SINGLE},         /* Ctrl+W */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x57, IDM_TAB_CLOSE_OTHERS},/* Ctrl+Shift+W */
        {FVIRTKEY | FCONTROL, 0x5A, IDM_EDIT_UNDO},                 /* Ctrl+Z */
        {FVIRTKEY | FCONTROL, 0x59, IDM_EDIT_REDO},                 /* Ctrl+Y */
        {FVIRTKEY | FCONTROL, 0x58, IDM_EDIT_CUT},                  /* Ctrl+X */
        {FVIRTKEY | FCONTROL, 0x43, IDM_EDIT_COPY},                 /* Ctrl+C */
        {FVIRTKEY | FCONTROL, 0x56, IDM_EDIT_PASTE},                /* Ctrl+V */
        {FVIRTKEY | FCONTROL, 0x41, IDM_EDIT_SELECTALL},            /* Ctrl+A */
        {FVIRTKEY, 0x70, IDM_PROJECT_SETTINGS},                    /* F9 */
        {FVIRTKEY, 0x74, IDM_BUILD_COMPILE},                        /* F5 */
        {FVIRTKEY, 0x75, IDM_BUILD_RUN},                            /* F6 */
    };
    hAccel = CreateAcceleratorTable(accels, sizeof(accels) / sizeof(accels[0]));
    
    /* Parse command line parameters - load files passed as arguments */
    BOOL filesLoaded = FALSE;
    if (lpCmdLine && strlen(lpCmdLine) > 0) {
        DebugLog("[CMDLINE] Processing command line: %s\n", lpCmdLine);
        char cmdCopy[2048];
        strcpy(cmdCopy, lpCmdLine);
        
        /* Parse arguments separated by spaces/quotes */
        char filePaths[32][MAX_PATH];
        int fileCount = 0;
        
        char* p = cmdCopy;
        while (*p && fileCount < 32) {
            /* Skip whitespace */
            while (*p && (*p == ' ' || *p == '\t')) p++;
            if (!*p) break;
            
            /* Check if quoted */
            BOOL isQuoted = (*p == '"');
            if (isQuoted) p++;
            
            /* Extract filename */
            int idx = 0;
            while (*p && idx < MAX_PATH - 1) {
                if (isQuoted && *p == '"') break;
                if (!isQuoted && (*p == ' ' || *p == '\t')) break;
                filePaths[fileCount][idx++] = *p;
                p++;
            }
            filePaths[fileCount][idx] = '\0';
            
            if (idx > 0) {
                DebugLog("[CMDLINE] File %d: %s\n", fileCount + 1, filePaths[fileCount]);
                AddFileToProject(filePaths[fileCount]);
                fileCount++;
            }
            
            if (isQuoted && *p == '"') p++;
        }
        
        if (fileCount > 0) {
            g_isFolderBased = FALSE;
            g_projectOpened = TRUE;
            PopulateProjectTree(hwndProjectTree, "", TRUE);
            
            /* Load first file into editor */
            DebugLog("[CMDLINE] Loading first file: %s\n", filePaths[0]);
            LoadFileIntoEditor(filePaths[0]);
            
            UpdateSaveMenuState(TRUE);
            char status[256];
            sprintf(status, "Loaded %d files from command line", fileCount);
            UpdateStatusBar(status);
            filesLoaded = TRUE;
        }
    }
    
    /* If no files were loaded from any source, create untitled tab */
    if (!filesLoaded) {
        DebugLog("[INIT] No files loaded - creating untitled tab\n");
        g_projectOpened = TRUE;
        int untitledTab = CreateNewTab("", "untitled");
        if (untitledTab >= 0) {
            g_activeTab = untitledTab;
            RefreshTabControl();
            /* Add to treeview */
            TVINSERTSTRUCT tvis;
            tvis.hParent = TVI_ROOT;
            tvis.hInsertAfter = TVI_LAST;
            tvis.item.mask = TVIF_TEXT;
            tvis.item.pszText = "Project Files";
            HTREEITEM hRoot = TreeView_InsertItem(hwndProjectTree, &tvis);
            
            tvis.hParent = hRoot;
            tvis.item.pszText = "untitled";
            TreeView_InsertItem(hwndProjectTree, &tvis);
            TreeView_Expand(hwndProjectTree, hRoot, TVE_EXPAND);
        }
        UpdateSaveMenuState(TRUE);
        UpdateStatusBar("Ready");
    }
    
    MSG msg;
    DebugLog("[LOOP] Entering message loop\n");
    while (GetMessage(&msg, NULL, 0, 0)) {
        /* Only log important messages */
        if (msg.message == WM_COMMAND) {
            DebugLog("[LOOP] WM_COMMAND dispatching - ID: 0x%X\n", LOWORD(msg.wParam));
        } else if (msg.message == WM_NOTIFY) {
            DebugLog("[LOOP] WM_NOTIFY dispatching\n");
        } else if (msg.message == WM_KEYDOWN) {
            DebugLog("[LOOP] WM_KEYDOWN dispatching - Key: 0x%X\n", msg.wParam);
        } else if (msg.message == WM_LBUTTONDOWN) {
            DebugLog("[LOOP] WM_LBUTTONDOWN dispatching\n");
        } else if (msg.message == WM_LBUTTONUP) {
            DebugLog("[LOOP] WM_LBUTTONUP dispatching\n");
        }
        if (!TranslateAccelerator(hwndMain, hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    DebugLog("[LOOP] Exiting message loop\n");
    DestroyAcceleratorTable(hAccel);
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    /* Log all important messages at entry point */
    switch (msg) {
    case WM_CREATE:
        DebugLog("[MSG] WM_CREATE\n");
        DebugLog("[EVENT] WindowCreate\n");
        CreateMenus(hwnd);
        CreateMainLayout(hwnd);
        /* Gray out save menu items initially */
        UpdateSaveMenuState(FALSE);
        break;
        
    case WM_SIZE: {
        RECT rc;
        GetClientRect(hwnd, &rc);
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;
        DebugLog("[MSG] WM_SIZE\n");
        DebugLog("[SIZE] Window resized to %dx%d\n", width, height);
        
        /* Resize main toolbar */
        MoveWindow(GetDlgItem(hwnd, IDC_TOOLBAR_MAIN), 0, 0, width, 40, TRUE);
        
        /* Resize code toolbar */
        MoveWindow(GetDlgItem(hwnd, IDC_TOOLBAR_CODE), 0, 40, width, 40, TRUE);
        
        /* Resize rest of layout */
        RepositionCodeArea(width, height);
        
        /* Resize status bar */
        MoveWindow(GetDlgItem(hwnd, IDC_STATUSBAR), 0, height-30, width, 30, TRUE);
        break;
    }
    
    case WM_COMMAND:
        DebugLog("[MSG] WM_COMMAND received (wParam=0x%X, lParam=0x%X)\n", wParam, lParam);
        switch (LOWORD(wParam)) {
        /* File menu */
        case IDM_FILE_NEW:
            DebugLog("[MENU] FileNewProjectMenuItemClick\n");
            /* Prompt to save before creating new project */
            if (PromptSaveAllTabs() == IDCANCEL) break;
            ClearAllTabs();
            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(hwndOutput, WM_SETTEXT, 0, (LPARAM)"");
            g_openedFileCount = 0;
            g_projectOpened = TRUE;
            TreeView_DeleteAllItems(hwndProjectTree);
            UpdateSaveMenuState(TRUE);
            /* Create initial untitled tab */
            {
                int untitledTab = CreateNewTab("", "untitled");
                if (untitledTab >= 0) {
                    g_activeTab = untitledTab;
                    RefreshTabControl();
                    /* Add to treeview */
                    TVINSERTSTRUCT tvis;
                    tvis.hParent = TVI_ROOT;
                    tvis.hInsertAfter = TVI_LAST;
                    tvis.item.mask = TVIF_TEXT;
                    tvis.item.pszText = "Project Files";
                    HTREEITEM hRoot = TreeView_InsertItem(hwndProjectTree, &tvis);
                    
                    tvis.hParent = hRoot;
                    tvis.item.pszText = "untitled";
                    TreeView_InsertItem(hwndProjectTree, &tvis);
                    TreeView_Expand(hwndProjectTree, hRoot, TVE_EXPAND);
                }
            }
            UpdateStatusBar("New project created");
            break;
        case IDM_FILE_OPEN:
            DebugLog("[MENU] FileOpenProjectMenuItemClick\n");
            /* Prompt to save before opening new project */
            if (PromptSaveAllTabs() == IDCANCEL) break;
            OpenFilesWithDialog(hwnd);
            g_projectOpened = TRUE;
            UpdateSaveMenuState(TRUE);
            break;
        case IDM_FILE_SAVE:
            DebugLog("[MENU] FileSaveMenuItemClick\n");
            SaveFileWithDialog(hwnd, FALSE);
            break;
        case IDM_FILE_SAVEAS:
            DebugLog("[MENU] FileSaveAsMenuItemClick\n");
            SaveFileWithDialog(hwnd, TRUE);
            break;
        case IDM_FILE_SAVEALL:
            DebugLog("[MENU] FileSaveAllMenuItemClick\n");
            SaveAllFiles(hwnd);
            break;
        case IDM_FILE_EXIT:
            DebugLog("[MENU] FileExitMenuItemClick\n");
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            
        case IDC_CODE_INPUT:
            if (HIWORD(wParam) == EN_CHANGE) {
                /* Mark current file as modified and update TreeView */
                if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                    if (!g_tabs[g_activeTab].isModified) {
                        g_tabs[g_activeTab].isModified = TRUE;
                        UpdateTreeViewItemModified(g_tabs[g_activeTab].filePath, TRUE);
                        UpdateTabTitle(g_activeTab, TRUE);
                    }
                }
                UpdateLineNumbers(hwndInput, hwndLineNumbers);
            } else if (HIWORD(wParam) == EN_VSCROLL) {
                UpdateLineNumbers(hwndInput, hwndLineNumbers);
            }
            break;

        /* Tab close button */
        case IDC_TAB_CLOSE:
            DebugLog("[TAB] TabCloseButtonClick(%s)\n", g_activeTab >= 0 ? g_tabs[g_activeTab].title : "none");
            if (g_activeTab >= 0) {
                int result = CloseTabWithPrompt(g_activeTab);
                if (result != IDCANCEL) {
                    RefreshTabControl();
                    
                    /* Load the new active tab's content */
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                }
            }
            break;
        case IDM_TAB_CLOSE_SINGLE:
            DebugLog("[SHORTCUT] Close active tab or window\n");
            if (g_activeTab >= 0) {
                int result = CloseTabWithPrompt(g_activeTab);
                if (result != IDCANCEL) {
                    RefreshTabControl();
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                }
            } else {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            }
            break;
        case IDM_TAB_CLOSE_OTHERS:
            DebugLog("[SHORTCUT] Close other tabs\n");
            if (g_activeTab >= 0) {
                for (int i = g_tabCount - 1; i >= 0; i--) {
                    if (i == g_activeTab) continue;
                    int result = CloseTabWithPrompt(i);
                    if (result == IDCANCEL) {
                        break;
                    }
                }
                RefreshTabControl();
                if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                    LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                } else {
                    SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                }
            }
            break;
        /* Tab navigation buttons */
        case IDC_TAB_PREV:
            DebugLog("[TAB] Prev button clicked\n");
            if (g_tabScrollIndex > 0) {
                g_tabScrollIndex--;
                EnsureTabVisible(g_tabScrollIndex);
            }
            break;
        case IDC_TAB_NEXT:
            DebugLog("[TAB] Next button clicked\n");
            if (g_tabScrollIndex < g_tabCount - 1) {
                g_tabScrollIndex++;
                EnsureTabVisible(g_tabScrollIndex);
            }
            break;
            
        /* Edit menu */
        case IDM_EDIT_UNDO:
            DebugLog("[MENU] EditUndoMenuItemClick\n");
            SendMessage(hwndInput, EM_UNDO, 0, 0);
            break;
        case IDM_EDIT_REDO:
            DebugLog("[MENU] EditRedoMenuItemClick\n");
            SendMessage(hwndInput, EM_UNDO, 1, 0);
            break;
        case IDM_EDIT_CUT:
            DebugLog("[MENU] EditCutMenuItemClick\n");
            SendMessage(hwndInput, WM_CUT, 0, 0);
            break;
        case IDM_EDIT_COPY:
            DebugLog("[MENU] EditCopyMenuItemClick\n");
            SendMessage(hwndInput, WM_COPY, 0, 0);
            break;
        case IDM_EDIT_PASTE:
            DebugLog("[MENU] EditPasteMenuItemClick\n");
            SendMessage(hwndInput, WM_PASTE, 0, 0);
            break;
        case IDM_EDIT_SELECTALL:
            DebugLog("[MENU] EditSelectAllMenuItemClick\n");
            SendMessage(hwndInput, EM_SETSEL, 0, -1);
            break;
            
        /* Build menu */
        case IDM_BUILD_COMPILE:
            DebugLog("[MENU] BuildCompileMenuItemClick\n");
            {
                /* Get current code and compile with GCC */
                char content[65536];
                SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
                if (strlen(content) == 0) {
                    MessageBox(hwnd, "No code to compile", "Compile", MB_ICONINFORMATION);
                } else {
                    /* Save to temp file and compile */
                    FILE* fp = fopen("build\\temp.c", "wb");
                    if (fp) {
                        size_t len = strlen(content);
                        if (len > 0) fwrite(content, 1, len, fp);
                        fclose(fp);
                        UpdateStatusBar("Compiling...");
                        /* Note: Actual compilation would require running GCC */
                        MessageBox(hwnd, "Compile feature ready. GCC would compile build\\temp.c", "Compile", MB_ICONINFORMATION);
                    }
                }
            }
            break;
        case IDM_BUILD_RUN:
            DebugLog("[MENU] BuildRunMenuItemClick\n");
            {
                /* Check if there's an executable to run */
                if (GetFileAttributes("build\temp.exe") != INVALID_FILE_ATTRIBUTES) {
                    UpdateStatusBar("Running executable...");
                    /* Would run the executable here */
                    MessageBox(hwnd, "Run feature ready. Would execute build\temp.exe", "Run", MB_ICONINFORMATION);
                } else {
                    MessageBox(hwnd, "No executable found. Please compile first.", "Run", MB_ICONWARNING);
                }
            }
            break;
            
        /* Project menu */
        case IDM_PROJECT_SETTINGS:
            DebugLog("[MENU] ProjectSettingsMenuItemClick\n");
            ShowProjectSettings(hwnd);
            break;
            
        /* Code insertion toolbar */
        case IDT_INSERT_FUNC:
            DebugLog("[TOOLBAR] Insert Function button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_IF:
            DebugLog("[TOOLBAR] Insert If statement button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_FOR:
            DebugLog("[TOOLBAR] Insert For loop button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_WHILE:
            DebugLog("[TOOLBAR] Insert While loop button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_SWITCH:
            DebugLog("[TOOLBAR] Insert Switch statement button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_STRUCT:
            DebugLog("[TOOLBAR] Insert Struct button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_UNION:
            DebugLog("[TOOLBAR] Insert Union button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_ENUM:
            DebugLog("[TOOLBAR] Insert Enum button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_TYPEDEF:
            DebugLog("[TOOLBAR] Insert Typedef button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_INCLUDE:
            DebugLog("[TOOLBAR] Insert Include button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_DEFINE:
            DebugLog("[TOOLBAR] Insert Define button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        default:
            DebugLog("[COMMAND] Unknown command ID: 0x%X (wParam=0x%X, lParam=0x%X)\n", LOWORD(wParam), wParam, lParam);
            break;
        }
        break;
        
    case WM_NOTIFY:
        /* Handle TreeView single-click to open file */
        if (wParam == IDC_PROJECT_TREE) {
            LPNMHDR pnmh = (LPNMHDR)lParam;
            int code = pnmh ? (int)pnmh->code : 0;
            DebugLog("[TREEVIEW] NM code: 0x%X\n", code);
            if (code == (int)TVN_SELCHANGED) {
                DebugLog("[TREEVIEW] TVN_SELCHANGED - selection changed\n");
                ActivateSelectedTreeFile();
            } else if (code == (int)NM_CLICK || code == (int)NM_DBLCLK) {
                DebugLog("[TREEVIEW] Click/double-click on tree item\n");
                ActivateSelectedTreeFile();
            } else {
                DebugLog("[TREEVIEW] Unknown NM code: 0x%X\n", code);
            }
        }
        /* Handle tab selection changes and right-clicks */
        else if (wParam == IDC_CODE_TAB) {
            LPNMHDR pnmh = (LPNMHDR)lParam;
            if (pnmh->code == TCN_SELCHANGE) {
                if (g_ignoreTabSelectionChange) break;
                DebugLog("[TAB] TCN_SELCHANGE\n");
                int newTab = TabCtrl_GetCurSel(hwndCodeTab);
                DebugLog("[TAB] Selected tab: %d\n", newTab);
                if (newTab >= 0 && newTab < g_tabCount) {
                    g_activeTab = newTab;
                    EnsureTabVisible(newTab);
                    /* Load the file for this tab */
                    if (g_tabs[newTab].filePath[0]) {
                        DebugLog("[TAB] TabClick(%s)\n", g_tabs[newTab].title);
                        LoadFileIntoEditor(g_tabs[newTab].filePath);
                    }
                    /* Update close button position */
                    PositionTabCloseButton();
                }
            } else if (pnmh->code == TCN_RCLICK) {
                DebugLog("[TAB] TCN_RCLICK\n");
                POINT pt;
                GetCursorPos(&pt);
                POINT hitPt = pt;
                ScreenToClient(hwndCodeTab, &hitPt);
                TCHITTESTINFO tchi = {0};
                tchi.pt = hitPt;
                int tabIdx = TabCtrl_HitTest(hwndCodeTab, &tchi);
                if (tabIdx >= 0 && tabIdx < g_tabCount) {
                    DebugLog("[TAB] Right-clicked tab %d: %s\n", tabIdx, g_tabs[tabIdx].title);
                    g_rightClickedTab = tabIdx;
                    HMENU hMenu = CreatePopupMenu();
                    AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_SINGLE, "Close\tCtrl+W");
                    AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_OTHERS, "Close Others\tCtrl+Shift+W");
                    int cmd = TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, 0, hwndCodeTab, NULL);
                    DestroyMenu(hMenu);
                    if (cmd == IDM_TAB_CLOSE_SINGLE) {
                        int result = CloseTabWithPrompt(g_rightClickedTab);
                        if (result != IDCANCEL) {
                            RefreshTabControl();
                            if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                                LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                            } else {
                                SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                            }
                        }
                    } else if (cmd == IDM_TAB_CLOSE_OTHERS) {
                        for (int i = g_tabCount - 1; i >= 0; i--) {
                            if (i == g_rightClickedTab) continue;
                            int result = CloseTabWithPrompt(i);
                            if (result == IDCANCEL) {
                                break;  /* User cancelled, stop closing tabs */
                            }
                        }
                        RefreshTabControl();
                        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                            LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                        } else {
                            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                        }
                    } else if (cmd == IDM_TAB_CLOSE_RIGHT) {
                        for (int i = g_tabCount - 1; i > g_rightClickedTab; i--) {
                            int result = CloseTabWithPrompt(i);
                            if (result == IDCANCEL) {
                                break;  /* User cancelled, stop closing tabs */
                            }
                        }
                        RefreshTabControl();
                        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                            LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                        } else {
                            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                        }
                    }
                    g_rightClickedTab = -1;
                }
            }
        }
        break;
    
    case WM_DRAWITEM: {
        LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;
        if (!dis) break;
        /* Only handle tab control owner-draw */
        if (dis->CtlType == ODT_TAB && dis->hwndItem == hwndCodeTab) {
            RECT rc = dis->rcItem;
            HDC hdc = dis->hDC;
            /* Get tab text */
            char textBuf[256] = {0};
            TCITEMA tci;
            tci.mask = TCIF_TEXT;
            tci.pszText = textBuf;
            tci.cchTextMax = sizeof(textBuf);
            TabCtrl_GetItem(hwndCodeTab, (int)dis->itemID, &tci);

            /* Determine if this tab is the active one */
            int cur = TabCtrl_GetCurSel(hwndCodeTab);
            BOOL isActive = ((int)dis->itemID == cur);

            /* Choose background color: slightly darker (subtle) for active tab */
            /* Use a lighter darkening so tab names remain clearly visible */
            COLORREF activeColor = RGB(210,210,210); /* subtle darker gray */
            COLORREF normalColor = GetSysColor(COLOR_3DFACE);

            HBRUSH hBrush = CreateSolidBrush(isActive ? activeColor : normalColor);
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);

            /* Draw border for clarity */
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(120,120,120));
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, rc.left, rc.bottom - 1, NULL);
            LineTo(hdc, rc.right, rc.bottom - 1);
            SelectObject(hdc, hOldPen);
            DeleteObject(hPen);

            /* Draw text in black, transparent background */
            SetTextColor(hdc, RGB(0,0,0));
            SetBkMode(hdc, TRANSPARENT);
            DrawTextA(hdc, textBuf, -1, &rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        }
        break;
    }
        
    case WM_KEYDOWN:
        DebugLog("[KEYBOARD] Key pressed: 0x%X (repeat=%d)\n", wParam, LOWORD(lParam));
        /* Handle Ctrl+A for select all in code pane */
        if (wParam == 0x41 && (GetKeyState(VK_CONTROL) & 0x8000)) {
            /* Ctrl+A - select all text in input pane */
            if (GetFocus() == hwndInput) {
                SendMessage(hwndInput, EM_SETSEL, 0, -1);
                return 0;
            }
        }
        break;
        
    case WM_SETCURSOR: {
        if (LOWORD(lParam) == HTCLIENT) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc;
            GetClientRect(hwnd, &rc);
            int codeLeft = 220 + g_lineNumberWidth;
            int availableCodeWidth = rc.right - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
            if (availableCodeWidth < 240) availableCodeWidth = 240;
            int inputWidth = availableCodeWidth / 2;
            int splitterX = codeLeft + inputWidth;
            RECT splitterRect = { splitterX, 90, splitterX + g_splitterWidth, rc.bottom - 150 };
            if (PtInRect(&splitterRect, pt)) {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                return TRUE;
            }
        }
        break;
    }
    case WM_LBUTTONDOWN: {
        int x = (int)(short)LOWORD(lParam);
        int y = (int)(short)HIWORD(lParam);
        RECT rc;
        GetClientRect(hwnd, &rc);
        int codeLeft = 220 + g_lineNumberWidth;
        int availableCodeWidth = rc.right - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
        if (availableCodeWidth < 240) availableCodeWidth = 240;
        int inputWidth = (g_currentInputWidth > 0) ? g_currentInputWidth : (availableCodeWidth * 85 / 100);
        int splitterX = codeLeft + inputWidth;
        RECT splitterRect = { splitterX - 5, 115, splitterX + g_splitterWidth + 5, rc.bottom - 150 };
        if (x >= splitterRect.left && x < splitterRect.right && y >= splitterRect.top && y < splitterRect.bottom) {
            g_isDraggingSplitter = TRUE;
            g_splitterDragStartX = x;
            g_dragInitialInputWidth = inputWidth;
            g_splitterStartPropertiesWidth = g_propertiesWidth;
            SetCapture(hwnd);
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            return 0;
        }
        DebugLog("[MOUSE] Left button DOWN at (%d, %d)\n", x, y);
        break;
    }
    case WM_LBUTTONUP:
        if (g_isDraggingSplitter) {
            g_isDraggingSplitter = FALSE;
            ReleaseCapture();
            return 0;
        }
        DebugLog("[MOUSE] Left button UP at (%d, %d)\n", (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam));
        break;
    case WM_MOUSEMOVE: {
        int x = (int)(short)LOWORD(lParam);
        int y = (int)(short)HIWORD(lParam);
        RECT rc;
        GetClientRect(hwnd, &rc);
        int codeLeft = 220 + g_lineNumberWidth;
        
        if (g_isDraggingSplitter) {
            int dx = x - g_splitterDragStartX;
            int newInputWidth = g_dragInitialInputWidth + dx;
            int minWidth = 150;
            int maxWidth = rc.right - codeLeft - 100 - g_propertiesWidth;
            if (newInputWidth < minWidth) newInputWidth = minWidth;
            if (newInputWidth > maxWidth) newInputWidth = maxWidth;
            
            g_currentInputWidth = newInputWidth;
            
            int newSplitterX = codeLeft + newInputWidth;
            int outputX = newSplitterX + g_splitterWidth + 5;
            int outputWidth = rc.right - outputX - g_propertiesWidth - 10;
            if (outputWidth < 100) outputWidth = 100;
            
            MoveWindow(hwndCodeTab, codeLeft, 90, newInputWidth, 25, TRUE);
            if (hwndTabPrev) MoveWindow(hwndTabPrev, codeLeft + newInputWidth - 50, 88, 22, 22, TRUE);
            if (hwndTabNext) MoveWindow(hwndTabNext, codeLeft + newInputWidth - 26, 88, 22, 22, TRUE);
            MoveWindow(hwndInput, codeLeft, 115, newInputWidth, rc.bottom - 165, TRUE);
            MoveWindow(hwndCodeSplitter, newSplitterX, 90, g_splitterWidth, rc.bottom - 150, TRUE);
            MoveWindow(hwndOutput, outputX, 90, outputWidth, rc.bottom - 150, TRUE);
            UpdateLineNumbers(hwndInput, hwndLineNumbers);
            return 0;
        }
        {
            int availableCodeWidth = rc.right - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
            if (availableCodeWidth < 240) availableCodeWidth = 240;
            int inputWidth = (g_currentInputWidth > 0) ? g_currentInputWidth : (availableCodeWidth * 85 / 100);
            int splitterX = codeLeft + inputWidth;
            RECT splitterRect = { splitterX - 5, 115, splitterX + g_splitterWidth + 5, rc.bottom - 150 };
            POINT pt = { x, y };
            if (PtInRect(&splitterRect, pt)) {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                return 0;
            }
        }
        break;
    }
    case WM_CTLCOLORSTATIC: {
        if ((HWND)lParam == hwndCodeSplitter) {
            HDC hdc = (HDC)wParam;
            SetBkMode(hdc, OPAQUE);
            SetBkColor(hdc, RGB(140, 140, 140));
            return (LRESULT)CreateSolidBrush(RGB(140, 140, 140));
        }
        break;
    }
case WM_CONTEXTMENU: {
        HWND hWndCtrl = (HWND)wParam;
        if (hWndCtrl == hwndCodeTab) {
            POINT pt;
            if ((short)LOWORD(lParam) == -1 && (short)HIWORD(lParam) == -1) {
                GetCursorPos(&pt);
            } else {
                pt.x = (int)(short)LOWORD(lParam);
                pt.y = (int)(short)HIWORD(lParam);
            }
            POINT hitPt = pt;
            ScreenToClient(hwndCodeTab, &hitPt);
            TCHITTESTINFO tchi = {0};
            tchi.pt = hitPt;
            int tabIdx = TabCtrl_HitTest(hwndCodeTab, &tchi);
            if (tabIdx >= 0 && tabIdx < g_tabCount) {
                DebugLog("[TAB] Context menu on tab %d: %s\n", tabIdx, g_tabs[tabIdx].title);
                g_rightClickedTab = tabIdx;
                HMENU hMenu = CreatePopupMenu();
                AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_SINGLE, "Close\tCtrl+W");
                AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_OTHERS, "Close Others\tCtrl+Shift+W");
                int cmd = TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, 0, hwndCodeTab, NULL);
                DestroyMenu(hMenu);
                if (cmd == IDM_TAB_CLOSE_SINGLE) {
                    int result = CloseTabWithPrompt(g_rightClickedTab);
                    if (result != IDCANCEL) {
                        RefreshTabControl();
                        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                            LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                        } else {
                            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                        }
                    }
                } else if (cmd == IDM_TAB_CLOSE_OTHERS) {
                    for (int i = g_tabCount - 1; i >= 0; i--) {
                        if (i == g_rightClickedTab) continue;
                        int result = CloseTabWithPrompt(i);
                        if (result == IDCANCEL) {
                            break;  /* User cancelled, stop closing tabs */
                        }
                    }
                    RefreshTabControl();
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                } else if (cmd == IDM_TAB_CLOSE_RIGHT) {
                    for (int i = g_tabCount - 1; i > g_rightClickedTab; i--) {
                        int result = CloseTabWithPrompt(i);
                        if (result == IDCANCEL) {
                            CloseTab(i);
                        }
                    }
                    RefreshTabControl();
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                }
                g_rightClickedTab = -1;
            }
            return 0;
        }
        break;
    }
        
    case WM_CLOSE:
        DebugLog("[MSG] WM_CLOSE - Window close requested\n");
        /* Prompt to save all modified tabs before closing */
        if (PromptSaveAllTabs() == IDCANCEL) {
            DebugLog("[EVENT] Close cancelled by user\n");
            return 0;
        }
        DebugLog("[EVENT] Window closing\n");
        DestroyWindow(hwnd);
        break;
        
    case WM_DESTROY:
        SaveConfig();
        PostQuitMessage(0);
        break;
        
    default:
        /* Log unhandled messages occasionally */
        if (msg == WM_COMMAND || msg == WM_NOTIFY) {
            DebugLog("[UNHANDLED] msg=0x%X, wParam=0x%X, lParam=0x%X\n", msg, wParam, lParam);
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
