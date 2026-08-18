#pragma once

#include "..\Shellcode\shellcode.hpp"

#define ALIGN_TO_PAGE(address) (((address) + 0xFFF) & ~0xFFF)

namespace Mapper
{
uint8_t g_threadHijackShellCode[] = {0x9C, 0x50, 0x53, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41,
                                     0x53, 0x48, 0x83, 0xEC, 0x28, 0x48, 0xB8, 0xEF, 0xBE, 0xAD, 0xDE, 0xEF,
                                     0xBE, 0xAD, 0xDE, 0xFF, 0xD0, 0x48, 0x83, 0xC4, 0x28, 0x41, 0x5B, 0x41,
                                     0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x5B, 0x58, 0x9D, 0xC3};

uint8_t g_mapperStubShellcode[] = {
    0x48, 0x81, 0xEC, 0x78, 0x01, 0x00, 0x00, 0x48, 0xB8, 0xEF, 0xBE, 0xAD, 0xDE, 0xEF, 0xBE, 0xAD, 0xDE, 0x48, 0x89,
    0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x83, 0xBC, 0x24, 0x70, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x85, 0x05, 0x00,
    0x00, 0x00, 0xE9, 0x13, 0x06, 0x00, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x70, 0x01, 0x00, 0x00, 0xB8, 0x01, 0x00, 0x00,
    0x00, 0x87, 0x41, 0x60, 0x83, 0xF8, 0x00, 0x0F, 0x85, 0xF5, 0x05, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01,
    0x00, 0x00, 0x48, 0x8B, 0x40, 0x18, 0x48, 0x89, 0x84, 0x24, 0x68, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70,
    0x01, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x10, 0x48, 0x89, 0x84, 0x24, 0x60, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24,
    0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x20, 0x48, 0x89, 0x84, 0x24, 0x58, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84,
    0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x30, 0x48, 0x89, 0x84, 0x24, 0x50, 0x01, 0x00, 0x00, 0x48, 0x8B,
    0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x38, 0x48, 0x89, 0x84, 0x24, 0x48, 0x01, 0x00, 0x00, 0x48,
    0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x40, 0x48, 0x89, 0x84, 0x24, 0x40, 0x01, 0x00, 0x00,
    0x48, 0x83, 0xBC, 0x24, 0x40, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x84, 0xF6, 0x01, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00,
    0x00, 0x48, 0x8B, 0x84, 0x24, 0x40, 0x01, 0x00, 0x00, 0x83, 0x38, 0x00, 0x0F, 0x84, 0xDB, 0x01, 0x00, 0x00, 0x48,
    0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x40, 0x01, 0x00, 0x00, 0x8B,
    0x09, 0x48, 0x01, 0xC8, 0x48, 0x89, 0x84, 0x24, 0x38, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00,
    0x00, 0x48, 0x8B, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x40, 0x01, 0x00, 0x00, 0x8B, 0x49, 0x10, 0x48, 0x01, 0xC8, 0x48,
    0x89, 0x84, 0x24, 0x30, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x00, 0x48,
    0x8B, 0x8C, 0x24, 0x40, 0x01, 0x00, 0x00, 0x8B, 0x49, 0x0C, 0x48, 0x01, 0xC8, 0x48, 0x89, 0x84, 0x24, 0x28, 0x01,
    0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x50, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x28, 0x01, 0x00, 0x00, 0xFF,
    0xD0, 0x48, 0x89, 0x84, 0x24, 0x20, 0x01, 0x00, 0x00, 0x48, 0x83, 0xBC, 0x24, 0x20, 0x01, 0x00, 0x00, 0x00, 0x0F,
    0x85, 0x14, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x05, 0x00, 0x00,
    0x00, 0xE9, 0xBE, 0x04, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x38, 0x01, 0x00, 0x00,
    0x48, 0x83, 0x38, 0x00, 0x0F, 0x84, 0x0C, 0x01, 0x00, 0x00, 0x48, 0xC7, 0x84, 0x24, 0x18, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x48, 0xC7, 0x84, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x8C, 0x24,
    0x38, 0x01, 0x00, 0x00, 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x48, 0x23, 0x01, 0x48, 0x83,
    0xF8, 0x00, 0x0F, 0x84, 0x1E, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x38, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x00,
    0x48, 0x25, 0xFF, 0xFF, 0x00, 0x00, 0x48, 0x89, 0x84, 0x24, 0x10, 0x01, 0x00, 0x00, 0xE9, 0x32, 0x00, 0x00, 0x00,
    0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x38, 0x01, 0x00, 0x00,
    0x48, 0x03, 0x01, 0x48, 0x89, 0x84, 0x24, 0x08, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x08, 0x01, 0x00, 0x00,
    0x48, 0x83, 0xC0, 0x02, 0x48, 0x89, 0x84, 0x24, 0x10, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x48, 0x01, 0x00,
    0x00, 0x48, 0x8B, 0x94, 0x24, 0x10, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x20, 0x01, 0x00, 0x00, 0xFF, 0xD0,
    0x48, 0x89, 0x84, 0x24, 0x18, 0x01, 0x00, 0x00, 0x48, 0x83, 0xBC, 0x24, 0x18, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x85,
    0x14, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x06, 0x00, 0x00, 0x00,
    0xE9, 0xDB, 0x03, 0x00, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x18, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x30, 0x01,
    0x00, 0x00, 0x48, 0x89, 0x08, 0x48, 0x8B, 0x84, 0x24, 0x38, 0x01, 0x00, 0x00, 0x48, 0x83, 0xC0, 0x08, 0x48, 0x89,
    0x84, 0x24, 0x38, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x30, 0x01, 0x00, 0x00, 0x48, 0x83, 0xC0, 0x08, 0x48,
    0x89, 0x84, 0x24, 0x30, 0x01, 0x00, 0x00, 0xE9, 0xE2, 0xFE, 0xFF, 0xFF, 0x48, 0x8B, 0x84, 0x24, 0x40, 0x01, 0x00,
    0x00, 0x48, 0x83, 0xC0, 0x14, 0x48, 0x89, 0x84, 0x24, 0x40, 0x01, 0x00, 0x00, 0xE9, 0x14, 0xFE, 0xFF, 0xFF, 0xE9,
    0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x83, 0x78, 0x48, 0x00, 0x0F, 0x84, 0xF8,
    0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x83, 0x78, 0x4C, 0x00, 0x0F, 0x84, 0xE6, 0x00,
    0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x8B, 0x40, 0x58, 0x83, 0xE0, 0x02, 0x83, 0xF8, 0x00,
    0x0F, 0x84, 0xCF, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x83, 0xC0, 0x48, 0x48,
    0x89, 0x84, 0x24, 0x00, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x00, 0x48,
    0x8B, 0x8C, 0x24, 0x00, 0x01, 0x00, 0x00, 0x8B, 0x09, 0x48, 0x01, 0xC8, 0x48, 0x89, 0x84, 0x24, 0xF8, 0x00, 0x00,
    0x00, 0x48, 0x8B, 0x84, 0x24, 0xF8, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x18, 0x48, 0x89, 0x84, 0x24, 0xF0, 0x00,
    0x00, 0x00, 0x31, 0xC0, 0x48, 0x83, 0xBC, 0x24, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x88, 0x44, 0x24, 0x43, 0x0F, 0x84,
    0x13, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0xF0, 0x00, 0x00, 0x00, 0x48, 0x83, 0x38, 0x00, 0x0F, 0x95, 0xC0,
    0x88, 0x44, 0x24, 0x43, 0x8A, 0x44, 0x24, 0x43, 0xA8, 0x01, 0x0F, 0x85, 0x05, 0x00, 0x00, 0x00, 0xE9, 0x49, 0x00,
    0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0xF0, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x00, 0x48, 0x89, 0x84, 0x24, 0xE8, 0x00,
    0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0xE8, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48,
    0x8B, 0x09, 0xBA, 0x01, 0x00, 0x00, 0x00, 0x45, 0x31, 0xC0, 0xFF, 0xD0, 0x48, 0x8B, 0x84, 0x24, 0xF0, 0x00, 0x00,
    0x00, 0x48, 0x83, 0xC0, 0x08, 0x48, 0x89, 0x84, 0x24, 0xF0, 0x00, 0x00, 0x00, 0xE9, 0x7E, 0xFF, 0xFF, 0xFF, 0xE9,
    0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xBC, 0x24, 0x68, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x84, 0xAB, 0x00, 0x00, 0x00,
    0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x8B, 0x40, 0x58, 0x83, 0xE0, 0x04, 0x83, 0xF8, 0x00, 0x0F, 0x84,
    0x94, 0x00, 0x00, 0x00, 0x0F, 0x57, 0xC0, 0x0F, 0x29, 0x44, 0x24, 0x30, 0x0F, 0x29, 0x84, 0x24, 0xD0, 0x00, 0x00,
    0x00, 0x0F, 0x29, 0x84, 0x24, 0xC0, 0x00, 0x00, 0x00, 0x0F, 0x29, 0x84, 0x24, 0xB0, 0x00, 0x00, 0x00, 0x0F, 0x29,
    0x84, 0x24, 0xA0, 0x00, 0x00, 0x00, 0x0F, 0x29, 0x84, 0x24, 0x90, 0x00, 0x00, 0x00, 0x0F, 0x29, 0x84, 0x24, 0x80,
    0x00, 0x00, 0x00, 0x0F, 0x29, 0x44, 0x24, 0x70, 0x0F, 0x29, 0x44, 0x24, 0x60, 0x0F, 0x29, 0x44, 0x24, 0x50, 0x48,
    0xC7, 0x84, 0x24, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00,
    0x48, 0x8B, 0x00, 0x48, 0x89, 0x84, 0x24, 0x80, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x4C, 0x24, 0x50, 0xFF, 0x94, 0x24,
    0x68, 0x01, 0x00, 0x00, 0x83, 0xF8, 0x00, 0x0F, 0x8D, 0x14, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01,
    0x00, 0x00, 0xC7, 0x40, 0x5C, 0x02, 0x00, 0x00, 0x00, 0xE9, 0xBE, 0x01, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00,
    0x48, 0x83, 0xBC, 0x24, 0x60, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x84, 0xB9, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24,
    0x70, 0x01, 0x00, 0x00, 0x83, 0x78, 0x50, 0x00, 0x0F, 0x84, 0xA7, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70,
    0x01, 0x00, 0x00, 0x83, 0x78, 0x54, 0x00, 0x0F, 0x84, 0x95, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01,
    0x00, 0x00, 0x8B, 0x40, 0x58, 0x83, 0xE0, 0x08, 0x83, 0xF8, 0x00, 0x0F, 0x84, 0x7E, 0x00, 0x00, 0x00, 0x48, 0x8B,
    0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x83, 0xC0, 0x50, 0x48, 0x89, 0x44, 0x24, 0x48, 0x48, 0x8B, 0x84, 0x24,
    0x60, 0x01, 0x00, 0x00, 0x48, 0x89, 0x44, 0x24, 0x28, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x4C, 0x8B,
    0x00, 0x48, 0x8B, 0x44, 0x24, 0x48, 0x8B, 0x40, 0x04, 0xB9, 0x0C, 0x00, 0x00, 0x00, 0x31, 0xD2, 0x48, 0xF7, 0xF1,
    0x48, 0x89, 0xC1, 0x48, 0x8B, 0x44, 0x24, 0x28, 0x89, 0xCA, 0x48, 0x8B, 0x8C, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48,
    0x8B, 0x09, 0x4C, 0x8B, 0x4C, 0x24, 0x48, 0x45, 0x8B, 0x09, 0x4C, 0x01, 0xC9, 0xFF, 0xD0, 0x3C, 0x00, 0x0F, 0x85,
    0x14, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x03, 0x00, 0x00, 0x00,
    0xE9, 0xF6, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xBC, 0x24, 0x58, 0x01, 0x00, 0x00, 0x00,
    0x0F, 0x84, 0x52, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x8B, 0x40, 0x58, 0x83, 0xE0,
    0x10, 0x83, 0xF8, 0x00, 0x0F, 0x84, 0x3B, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x58, 0x01, 0x00, 0x00, 0x48,
    0x8B, 0x8C, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x51, 0x28, 0x31, 0xC9, 0xFF, 0xD0, 0x48, 0x83, 0xF8, 0x00,
    0x0F, 0x85, 0x14, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x04, 0x00,
    0x00, 0x00, 0xE9, 0x95, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00,
    0x00, 0x8B, 0x40, 0x58, 0x83, 0xE0, 0x01, 0x83, 0xF8, 0x00, 0x0F, 0x84, 0x14, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x84,
    0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x01, 0x00, 0x00, 0x00, 0xE9, 0x65, 0x00, 0x00, 0x00, 0x48, 0x8B,
    0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x00, 0x48, 0x8B, 0x8C, 0x24, 0x70, 0x01, 0x00, 0x00, 0x8B, 0x49,
    0x0C, 0x48, 0x01, 0xC8, 0x48, 0x8B, 0x8C, 0x24, 0x70, 0x01, 0x00, 0x00, 0x48, 0x8B, 0x09, 0xBA, 0x01, 0x00, 0x00,
    0x00, 0x45, 0x31, 0xC0, 0xFF, 0xD0, 0x89, 0x44, 0x24, 0x44, 0x83, 0x7C, 0x24, 0x44, 0x01, 0x0F, 0x85, 0x14, 0x00,
    0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x01, 0x00, 0x00, 0x00, 0xE9, 0x14,
    0x00, 0x00, 0x00, 0x48, 0x8B, 0x84, 0x24, 0x70, 0x01, 0x00, 0x00, 0xC7, 0x40, 0x5C, 0x07, 0x00, 0x00, 0x00, 0xE9,
    0x00, 0x00, 0x00, 0x00, 0x48, 0x81, 0xC4, 0x78, 0x01, 0x00, 0x00, 0xC3};

uint8_t g_exceptionHandlerStubShellcode[] = {
    0x48, 0x83, 0xEC, 0x18, 0x48, 0x89, 0x4C, 0x24, 0x10, 0x48, 0xB8, 0xEF, 0xBE, 0xAD, 0xDE, 0xEF, 0xBE, 0xAD, 0xDE,
    0x48, 0x89, 0x44, 0x24, 0x08, 0xC7, 0x44, 0x24, 0x04, 0xAD, 0xDE, 0xEF, 0xBE, 0x48, 0x8B, 0x44, 0x24, 0x10, 0x48,
    0x8B, 0x00, 0x81, 0x38, 0x63, 0x73, 0x6D, 0xE0, 0x0F, 0x85, 0x8C, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44, 0x24, 0x10,
    0x48, 0x8B, 0x00, 0x48, 0x8B, 0x40, 0x30, 0x48, 0x3B, 0x44, 0x24, 0x08, 0x0F, 0x82, 0x70, 0x00, 0x00, 0x00, 0x48,
    0x8B, 0x44, 0x24, 0x10, 0x48, 0x8B, 0x00, 0x48, 0x8B, 0x40, 0x30, 0x48, 0x8B, 0x4C, 0x24, 0x08, 0x8B, 0x54, 0x24,
    0x04, 0x48, 0x01, 0xD1, 0x48, 0x39, 0xC8, 0x0F, 0x83, 0x4F, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44, 0x24, 0x10, 0x48,
    0x8B, 0x00, 0x48, 0x81, 0x78, 0x20, 0x00, 0x40, 0x99, 0x01, 0x0F, 0x85, 0x34, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44,
    0x24, 0x10, 0x48, 0x8B, 0x00, 0x48, 0x83, 0x78, 0x38, 0x00, 0x0F, 0x85, 0x21, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44,
    0x24, 0x10, 0x48, 0x8B, 0x00, 0x48, 0xC7, 0x40, 0x20, 0x20, 0x05, 0x93, 0x19, 0x48, 0x8B, 0x4C, 0x24, 0x08, 0x48,
    0x8B, 0x44, 0x24, 0x10, 0x48, 0x8B, 0x00, 0x48, 0x89, 0x48, 0x38, 0xE9, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00,
    0x00, 0x00, 0x31, 0xC0, 0x48, 0x83, 0xC4, 0x18, 0xC3};

template <class T> PIMAGE_SECTION_HEADER TranslateRawSection(T nt, ULONGLONG rva)
{
    auto section = IMAGE_FIRST_SECTION(nt);
    for (auto i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (rva >= section->VirtualAddress && rva < section->VirtualAddress + section->Misc.VirtualSize)
        {
            return section;
        }
    }

    return NULL;
}

template <class T> PVOID TranslateRaw(PBYTE base, T nt, ULONGLONG rva)
{
    auto section = TranslateRawSection(nt, rva);
    if (!section)
    {
        return NULL;
    }

    return base + section->PointerToRawData + (rva - section->VirtualAddress);
}

template <class T> void ResolveRelocations(uint8_t *imageBase, T ntHeaders, uint8_t *mappedBase)
{
    auto &baseRelocDir = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
    if (!baseRelocDir.VirtualAddress)
    {
        // No relocations to process.
        return;
    }

    auto reloc =
        reinterpret_cast<PIMAGE_BASE_RELOCATION>(TranslateRaw(imageBase, ntHeaders, baseRelocDir.VirtualAddress));
    if (!reloc)
    {
        return;
    }

    for (auto currentSize = 0UL; currentSize < baseRelocDir.Size;)
    {
        auto relocCount = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
        auto relocData = reinterpret_cast<PWORD>(reinterpret_cast<PBYTE>(reloc) + sizeof(IMAGE_BASE_RELOCATION));
        auto relocBase = reinterpret_cast<PBYTE>(TranslateRaw(imageBase, ntHeaders, reloc->VirtualAddress));

        for (auto i = 0UL; i < relocCount; ++i, ++relocData)
        {
            WORD data = *relocData;
            auto type = data >> 12;
            auto offset = data & 0xFFF;

            ULONG_PTR relocDelta = (ULONG_PTR)((ULONG_PTR)mappedBase - (ULONG_PTR)ntHeaders->OptionalHeader.ImageBase);

            switch (type)
            {
            case IMAGE_REL_BASED_DIR64:
                *(ULONG64 *)(relocBase + offset) += (ULONG64)(relocDelta);
                break;
            case IMAGE_REL_BASED_HIGH:
                *(WORD *)(relocBase + offset) += HIWORD(relocDelta);
                break;
            case IMAGE_REL_BASED_LOW:
                *(WORD *)(relocBase + offset) += LOWORD(relocDelta);
                break;
            case IMAGE_REL_BASED_HIGHLOW:
                *(DWORD *)(relocBase + offset) += (DWORD)(relocDelta);
                break;
            }
        }

        currentSize += reloc->SizeOfBlock;
        reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION>(relocData);
    }
}

void *LoadLibraryRemote(const std::unique_ptr<Comms::CommsManager_t> &commsManager, const std::string &libName)
{
    char fmt[256]{};

    const std::wstring libNameWide = Utils::ConvertAsciiToUnicode(libName);

    // First try to retrieve information about library, maybe it's loaded already.
    //
    PVOID moduleBase = nullptr;
    NTSTATUS status = commsManager->GetModuleInformation(libNameWide, &moduleBase);
    if (NT_SUCCESS(status))
    {
        return moduleBase;
    }
    else if (status != STATUS_NOT_FOUND)
    {
        sprintf_s(fmt, "Failed to get information about module %s. NtStatus 0x%08X", libName.c_str(), status);

        throw std::runtime_error(fmt);
    }

    // Proceed to load library
    //
    PVOID libNameAllocatedBase = nullptr;
    SIZE_T regionSize = 0x1000;

    status = commsManager->Alloc(&libNameAllocatedBase, &regionSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to allocate memory for library name. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    SCOPE_EXIT
    {
        commsManager->Free(&libNameAllocatedBase, 0, MEM_RELEASE);
    };

    status = commsManager->Write(libNameAllocatedBase, (void *)libName.data(), libName.length() + 1);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write library name in memory. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    HANDLE threadHandle = INVALID_HANDLE_VALUE;

    status = commsManager->CreateThread(&threadHandle, &LoadLibraryA, libNameAllocatedBase, true);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to create remote thread for library. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    SCOPE_EXIT
    {
        commsManager->CloseHandle(threadHandle);
    };

    // Check if library was loaded
    //
    status = commsManager->GetModuleInformation(libNameWide, &moduleBase);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to get information about module %s. NtStatus 0x%08X", libName.c_str(), status);

        throw std::runtime_error(fmt);
    }

    return moduleBase;
}

ULONGLONG GetProcAddressRva(const std::string &libName, const std::string &procedure)
{
    HMODULE module = LoadLibraryExA(libName.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
    if (!module)
    {
        std::runtime_error("Failed to load library " + libName + " error " + std::to_string(GetLastError()));
    }

    SCOPE_EXIT
    {
        FreeLibrary(module);
    };

    ULONGLONG funcRva = reinterpret_cast<ULONGLONG>(GetProcAddress(module, procedure.c_str()));
    if (!funcRva)
    {
        std::runtime_error("Procedure " + procedure + " not found!");
    }

    funcRva -= reinterpret_cast<ULONGLONG>(module);

    return funcRva;
}

template <class T>
void ResolveImports(const std::unique_ptr<Comms::CommsManager_t> &commsManager, uint8_t *imageBase, T nth)
{
    auto &importDirectory = nth->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!importDirectory.VirtualAddress)
    {
        // No imports to process.
        return;
    }

    auto importDesc =
        reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(TranslateRaw(imageBase, nth, importDirectory.VirtualAddress));
    if (!importDesc)
    {
        return;
    }

    while (importDesc->Characteristics)
    {
        const auto libraryName = reinterpret_cast<const PCHAR>(TranslateRaw(imageBase, nth, importDesc->Name));

        void *libraryBase = LoadLibraryRemote(commsManager, libraryName);
        if (!libraryBase)
        {
            std::runtime_error("Failed to load remote library " + std::string(libraryName));
        }

        if constexpr (std::is_same_v<T, PIMAGE_NT_HEADERS32>)
        {
            // TODO: implement
        }
        else if constexpr (std::is_same_v<T, PIMAGE_NT_HEADERS64>)
        {
            PIMAGE_THUNK_DATA64 originalThunkData =
                reinterpret_cast<PIMAGE_THUNK_DATA64>(TranslateRaw(imageBase, nth, importDesc->OriginalFirstThunk));

            PIMAGE_THUNK_DATA64 thunkData =
                reinterpret_cast<PIMAGE_THUNK_DATA64>(TranslateRaw(imageBase, nth, importDesc->FirstThunk));

            while (originalThunkData->u1.AddressOfData)
            {
                LPCSTR procName;

                if (originalThunkData->u1.Ordinal & IMAGE_ORDINAL_FLAG64)
                {
                    procName = (LPCSTR)(originalThunkData->u1.Ordinal & 0xFFFF);
                }
                else
                {
                    PIMAGE_IMPORT_BY_NAME importByName = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(
                        TranslateRaw(imageBase, nth, originalThunkData->u1.AddressOfData));

                    procName = (LPCSTR)(importByName->Name);
                }

                thunkData->u1.Function = (ULONGLONG)libraryBase + GetProcAddressRva(libraryName, procName);

                printf("[+] Resolved import %s!%s -> 0x%-16llX\n", libraryName, procName, thunkData->u1.Function);

                thunkData++;
                originalThunkData++;
            }
        }

        importDesc++;
    }
}

DWORD GetSectionProtection(DWORD characteristics)
{
    DWORD dwResult = PAGE_NOACCESS;

    if (characteristics & IMAGE_SCN_MEM_EXECUTE)
    {
        if (characteristics & IMAGE_SCN_MEM_WRITE)
            dwResult = PAGE_EXECUTE_READWRITE;
        else if (characteristics & IMAGE_SCN_MEM_READ)
            dwResult = PAGE_EXECUTE_READ;
        else
            dwResult = PAGE_EXECUTE;
    }
    else
    {
        if (characteristics & IMAGE_SCN_MEM_WRITE)
            dwResult = PAGE_READWRITE;
        else if (characteristics & IMAGE_SCN_MEM_READ)
            dwResult = PAGE_READONLY;
        else
            dwResult = PAGE_NOACCESS;
    }

    return dwResult;
}

void Map(const std::unique_ptr<Comms::CommsManager_t> &commsManager, std::vector<uint8_t> dllBuffer, int mode)
{
    char fmt[256]{};

    bool shouldFreeModule = true;

    void *moduleAllocatedBase = nullptr;
    SIZE_T moduleRegionSize = 0;

    VOID *exceptionHandlerAllocatedBase = nullptr;
    SIZE_T exceptionHandlerRegionSize = 0x1000;

    VOID *mapperAllocatedBase = nullptr;
    SIZE_T mapperRegionSize = 0x1000;

    SCOPE_EXIT
    {
        if (shouldFreeModule)
        {
            if (moduleAllocatedBase)
            {
                commsManager->Free(&moduleAllocatedBase, 0, MEM_RELEASE);
                moduleAllocatedBase = nullptr;
            }

            if (exceptionHandlerAllocatedBase)
            {
                commsManager->Free(&exceptionHandlerAllocatedBase, 0, MEM_RELEASE);
                exceptionHandlerAllocatedBase = nullptr;
            }
        }

        if (mapperAllocatedBase)
        {
            commsManager->Free(&mapperAllocatedBase, 0, MEM_RELEASE);
            mapperAllocatedBase = nullptr;
        }
    };

    // validate file
    //
    printf("[#] Validating image...\n");

    if (dllBuffer.empty() || dllBuffer.size() < sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS))
    {
        throw std::runtime_error("Invalid PE file!");
    }

    uint8_t *const imageBuffer = dllBuffer.data();

    auto dosHeaders = reinterpret_cast<PIMAGE_DOS_HEADER>(imageBuffer);
    if (dosHeaders->e_magic != IMAGE_DOS_SIGNATURE)
    {
        throw std::runtime_error("Invalid DOS header!");
    }

    auto nth64 = reinterpret_cast<PIMAGE_NT_HEADERS64>(imageBuffer + dosHeaders->e_lfanew);
    if (nth64->Signature != IMAGE_NT_SIGNATURE)
    {
        throw std::runtime_error("Invalid PE signature!");
    }

    if (nth64->FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64)
    {
        throw std::runtime_error("File machine not supported!");
    }

    // Calculate image size needed excluding the PE headers
    //
    ULONG imageSize = nth64->OptionalHeader.SizeOfImage - IMAGE_FIRST_SECTION(nth64)->VirtualAddress;
    moduleRegionSize = imageSize;

    // validate mode
    //
    if (mode >= ECommsType::CommsTypeMax)
    {
        throw std::runtime_error("Invalid injection mode " + std::to_string(mode));
    }

    // Allocate memory for image
    //
    NTSTATUS status =
        commsManager->Alloc(&moduleAllocatedBase, &moduleRegionSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Image allocation failed. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    uint8_t *moduleBase = reinterpret_cast<uint8_t *>(moduleAllocatedBase) - IMAGE_FIRST_SECTION(nth64)->VirtualAddress;
    uint8_t *moduleEp = moduleBase + nth64->OptionalHeader.AddressOfEntryPoint;

    printf("[+] Allocated image at 0x%p total size 0x%08llX\n", moduleAllocatedBase, moduleRegionSize);

    // Handle relocations
    //
    printf("[+] Resolving relocations...\n");
    ResolveRelocations(imageBuffer, nth64, moduleBase);

    // Handle imports
    //
    ResolveImports(commsManager, imageBuffer, nth64);

    // Map sections
    //
    printf("[+] Mapping sections...\n");

    const DWORD relocVa = nth64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
    std::vector<IMAGE_SECTION_HEADER> discardableSections{};

    IMAGE_SECTION_HEADER *section = IMAGE_FIRST_SECTION(nth64);

    for (auto i = 0; i < nth64->FileHeader.NumberOfSections; ++i)
    {
        SIZE_T sectionSize = std::min(section[i].SizeOfRawData, section[i].Misc.VirtualSize);
        if (!sectionSize)
        {
            continue;
        }

        // Ignore relocation table
        //
        if (section[i].VirtualAddress >= relocVa && relocVa <= section[i].VirtualAddress + sectionSize)
        {
            continue;
        }

        if (section[i].Characteristics & IMAGE_SCN_MEM_DISCARDABLE)
        {
            discardableSections.emplace_back(section[i]);
        }

        uint8_t *mappedSection = moduleBase + section[i].VirtualAddress;

        // Write section
        //
        status = commsManager->Write(mappedSection, imageBuffer + section[i].PointerToRawData, sectionSize);
        if (!NT_SUCCESS(status))
        {
            sprintf_s(fmt, "Failed to map section (%s) at 0x%p with size 0x%08llX. NtStatus 0x%08X", section[i].Name,
                      mappedSection, sectionSize, status);

            throw std::runtime_error(fmt);
        }

        ULONG newAccess = GetSectionProtection(section[i].Characteristics);

        // Fix section protection
        //
        status = commsManager->Protect(reinterpret_cast<PVOID *>(&mappedSection), &sectionSize, newAccess);
        if (!NT_SUCCESS(status))
        {
            sprintf_s(fmt, "Failed to apply section (%s) protection at 0x%p with size 0x%08llX. NtStatus 0x%08X\n",
                      section[i].Name, mappedSection, sectionSize, status);

            throw std::runtime_error(fmt);
        }
    }

    printf("[+] Image entrypoint at 0x%p\n", moduleEp);

    // Resolve C++ exceptions
    //
    *(uint64_t *)(&g_exceptionHandlerStubShellcode[11]) = (uint64_t)moduleBase;
    *(uint32_t *)(&g_exceptionHandlerStubShellcode[28]) = imageSize;

    // Allocate memory for exception handler
    //
    status = commsManager->Alloc(&exceptionHandlerAllocatedBase, &exceptionHandlerRegionSize, MEM_RESERVE | MEM_COMMIT,
                                 PAGE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Exception handler allocation failed. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    printf("[+] Allocated exception handler at 0x%p\n", moduleEp);

    // Write exception handler to memory
    //
    status = commsManager->Write(exceptionHandlerAllocatedBase, &g_exceptionHandlerStubShellcode,
                                 sizeof(g_exceptionHandlerStubShellcode));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write exception handler to memory. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Fix exception handler page protection
    //
    status = commsManager->Protect(&exceptionHandlerAllocatedBase, &exceptionHandlerRegionSize, PAGE_EXECUTE_READ);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to fix exception handler page protection. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Allocate memory for mapper shellcode
    //
    status =
        commsManager->Alloc(&mapperAllocatedBase, &mapperRegionSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Shellcode allocation failed. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    printf("[+] Allocated mapper shellcode at 0x%p\n", mapperAllocatedBase);

    // Setup mapper shellcode args
    //
    MAPPER_SHELLCODE_ARGS64 mapperShellArgs = MAPPER_SHELLCODE_ARGS64(
        (ULONG_PTR)moduleBase, imageSize, nth64->OptionalHeader.AddressOfEntryPoint,
        SHELLCODE_FLAG_STATIC_TLS | SHELLCODE_FLAG_TLS_CALLBACKS | SHELLCODE_FLAG_EXCEPTIONS |
            SHELLCODE_FLAG_CPP_EXCEPTIONS,
        &nth64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS],
        &nth64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION], (PVOID)&RtlAddFunctionTable, nullptr,
        (PVOID)&RtlAddVectoredExceptionHandler, exceptionHandlerAllocatedBase);

    uint8_t *mapperBase = reinterpret_cast<uint8_t *>(mapperAllocatedBase);

    // Write shellcode args to memory
    //
    status = commsManager->Write(mapperBase, &mapperShellArgs, sizeof(mapperShellArgs));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write mapper shellcode args. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    uint8_t *shellCodeArgsBase = mapperBase;
    printf("[+] Wrote shellcode args at 0x%p\n", shellCodeArgsBase);

    // Advance memory pointer to next offset
    //
    mapperBase += 1 + sizeof(mapperShellArgs);

    printf("[+] Wrote shellcode stub at 0x%p\n", mapperBase);

    *(uint8_t **)(&g_threadHijackShellCode[19]) = mapperBase; // params

    // write mapper shellcode procedure
    //
    status = commsManager->Write(mapperBase, &g_mapperStubShellcode, ARRAYSIZE(g_mapperStubShellcode));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write mapper shellcode procedure. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    *(PVOID *)(&g_mapperStubShellcode[9]) = shellCodeArgsBase;

    // Advance memory pointer to next offset
    //
    mapperBase += 1 + ARRAYSIZE(g_mapperStubShellcode);

    printf("[+] Wrote thread hijack shellcode stub at 0x%p\n", mapperBase);

    // Write thread hijack shellcode
    //
    status = commsManager->Write(mapperBase, &g_threadHijackShellCode, ARRAYSIZE(g_threadHijackShellCode));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write thread hijack shellcode. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Perform thread hijack
    //
    HANDLE threadId = Utils::GetProcessMainThreadId(commsManager->GetProcessId());
    if (threadId == INVALID_HANDLE_VALUE)
    {
        throw std::runtime_error("Failed to find process main thread id!");
    }

    printf("[+] Hijacking thread id %d\n", HandleToUlong(threadId));

    HANDLE threadHandle = INVALID_HANDLE_VALUE;

    status = commsManager->OpenThread(threadId, &threadHandle);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to open thread. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    SCOPE_EXIT
    {
        commsManager->CloseHandle(threadHandle);
    };

    status = commsManager->SuspendThread(threadHandle);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to suspend thread. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    CONTEXT context{};
    context.ContextFlags = CONTEXT_FULL;

    status = commsManager->GetThreadContext(threadHandle, &context);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to get thread context. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    context.Rsp -= sizeof(DWORD64);

    status = commsManager->Write(reinterpret_cast<void *>(context.Rsp), &context.Rip, sizeof(DWORD64));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write context Rsp. NtStatus 0x%08X\n", status);

        throw std::runtime_error(fmt);
    }

    context.Rip = (DWORD64)mapperBase; // thread hijack shellcode procedure

    status = commsManager->SetThreadContext(threadHandle, &context);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to set thread context. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    status = commsManager->ResumeThread(threadHandle);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to resume thread. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // wait for mapper to execute
    //
    printf("[+] Waiting for mapper to execute!\n");

    while (true)
    {
        MAPPER_SHELLCODE_ARGS64 mapperResultArgs = {};
        status = commsManager->Read(&mapperResultArgs, shellCodeArgsBase, sizeof(mapperResultArgs));
        if (!NT_SUCCESS(status))
        {
            sprintf_s(fmt, "Failed to read mapper args. NtStatus 0x%08X\n", status);

            throw std::runtime_error(fmt);
        }

        switch (mapperResultArgs.Status)
        {
        case EShellcodeStatus::SHELLCODE_STATUS_AWAITING: {
            // Still awaiting execution, sleep current thread.
            //
            goto Sleep;
        }
        case EShellcodeStatus::SHELLCODE_STATUS_SUCCESS: {

            auto EraseDiscardableCode = [&]() {
                for (auto sec : discardableSections)
                {
                    const ULONG sectionSize = sec.Misc.VirtualSize;
                    uint8_t *mappedSection = moduleBase + sec.VirtualAddress;

                    // Fill data with zero's
                    //
                    std::vector<uint8_t> emptyBuffer(sectionSize);
                    ZeroMemory(emptyBuffer.data(), sectionSize);

                    status = commsManager->Write(mappedSection, emptyBuffer.data(), sectionSize);
                    if (!NT_SUCCESS(status))
                    {
                        sprintf_s(fmt,
                                  "Failed to erase discardable section (%s) at 0x%p with size 0x%X. NtStatus "
                                  "0x%08X\n",
                                  (PCHAR)sec.Name, mappedSection, sectionSize, status);

                        throw std::runtime_error(fmt);
                    }
                }
            };

            printf("[+] Erasing discardable code!\n");

            EraseDiscardableCode();

            shouldFreeModule = false;
            printf("[+] Image successfully mapped!\n");
            return;
        }
        default: {
            sprintf_s(fmt, "Failed to map image, shellcode status %d\n", mapperResultArgs.Status);

            throw std::runtime_error(fmt);
        }
        }

    Sleep:
        std::this_thread::sleep_for(std::chrono::milliseconds(512));
    }
}

void Map(const std::unique_ptr<Comms::CommsManager_t> &commsManager, PMAPPER_IMAGE mapperImage)
{
    char fmt[256]{};

    bool shouldFreeModule = true;

    void *moduleAllocatedBase = nullptr;
    SIZE_T moduleRegionSize = 0;

    VOID *exceptionHandlerAllocatedBase = nullptr;
    SIZE_T exceptionHandlerRegionSize = 0x1000;

    VOID *mapperAllocatedBase = nullptr;
    SIZE_T mapperRegionSize = 0x1000;

    SCOPE_EXIT
    {
        if (shouldFreeModule)
        {
            if (moduleAllocatedBase)
            {
                commsManager->Free(&moduleAllocatedBase, 0, MEM_RELEASE);
                moduleAllocatedBase = nullptr;
            }

            if (exceptionHandlerAllocatedBase)
            {
                commsManager->Free(&exceptionHandlerAllocatedBase, 0, MEM_RELEASE);
                exceptionHandlerAllocatedBase = nullptr;
            }
        }

        if (mapperAllocatedBase)
        {
            commsManager->Free(&mapperAllocatedBase, 0, MEM_RELEASE);
            mapperAllocatedBase = nullptr;
        }
    };

    moduleRegionSize = mapperImage->ImageSize;

    // Allocate memory for image
    //
    NTSTATUS status =
        commsManager->Alloc(&moduleAllocatedBase, &moduleRegionSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Image allocation failed. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    uint8_t *moduleBase = reinterpret_cast<uint8_t *>(moduleAllocatedBase);
    uint8_t *moduleEp = moduleBase + mapperImage->EntryPoint;

    printf("[+] Allocated image at 0x%p total size 0x%08llX\n", moduleAllocatedBase, moduleRegionSize);
    printf("[+] Image entrypoint at 0x%p\n", moduleEp);

    status = mapperImage->Map(moduleBase);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to map image. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Resolve C++ exceptions
    //
    *(uint64_t *)(&Mapper::g_exceptionHandlerStubShellcode[11]) = (uint64_t)moduleBase;
    *(uint32_t *)(&Mapper::g_exceptionHandlerStubShellcode[28]) = mapperImage->ImageSize;

    // Allocate memory for exception handler
    //
    status = commsManager->Alloc(&exceptionHandlerAllocatedBase, &exceptionHandlerRegionSize, MEM_RESERVE | MEM_COMMIT,
                                 PAGE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Exception handler allocation failed. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    printf("[+] Allocated exception handler at 0x%p\n", moduleEp);

    // Write exception handler to memory
    //
    status = commsManager->Write(exceptionHandlerAllocatedBase, &Mapper::g_exceptionHandlerStubShellcode,
                                 sizeof(Mapper::g_exceptionHandlerStubShellcode));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write exception handler to memory. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Fix exception handler page protection
    //
    status = commsManager->Protect(&exceptionHandlerAllocatedBase, &exceptionHandlerRegionSize, PAGE_EXECUTE_READ);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to fix exception handler page protection. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Allocate memory for mapper shellcode
    //
    status =
        commsManager->Alloc(&mapperAllocatedBase, &mapperRegionSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Shellcode allocation failed. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    printf("[+] Allocated mapper shellcode at 0x%p\n", mapperAllocatedBase);

    // Setup mapper shellcode args
    //
    MAPPER_SHELLCODE_ARGS64 mapperShellArgs = MAPPER_SHELLCODE_ARGS64(
        (ULONG_PTR)moduleBase, mapperImage->ImageSize, mapperImage->EntryPoint, mapperImage->Flags,
        &mapperImage->TlsDirectory, &mapperImage->ExceptionsDirectory, &RtlAddFunctionTable, nullptr,
        &RtlAddVectoredExceptionHandler, (PVECTORED_EXCEPTION_HANDLER)exceptionHandlerAllocatedBase, &LoadLibraryA,
        &GetProcAddress, (PIMAGE_IMPORT_DESCRIPTOR)(moduleBase + mapperImage->ImportDirectory.VirtualAddress));

    uint8_t *mapperBase = reinterpret_cast<uint8_t *>(mapperAllocatedBase);

    // Write shellcode args to memory
    //
    status = commsManager->Write(mapperBase, &mapperShellArgs, sizeof(mapperShellArgs));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write mapper shellcode args. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    uint8_t *shellCodeArgsBase = mapperBase;
    printf("[+] Wrote shellcode args at 0x%p\n", shellCodeArgsBase);

    // Advance memory pointer to next offset
    //
    mapperBase += 1 + sizeof(mapperShellArgs);

    printf("[+] Wrote shellcode stub at 0x%p\n", mapperBase);

    *(uint8_t **)(&Mapper::g_threadHijackShellCode[19]) = mapperBase; // params
    *(PVOID *)(&g_mapperStubShellcode[9]) = shellCodeArgsBase;

    // write mapper shellcode procedure
    //
    status = commsManager->Write(mapperBase, &Mapper::g_mapperStubShellcode, ARRAYSIZE(Mapper::g_mapperStubShellcode));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write mapper shellcode procedure. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Advance memory pointer to next offset
    //
    mapperBase += 1 + ARRAYSIZE(Mapper::g_mapperStubShellcode);

    printf("[+] Wrote thread hijack shellcode stub at 0x%p\n", mapperBase);

    // Write thread hijack shellcode
    //
    status =
        commsManager->Write(mapperBase, &Mapper::g_threadHijackShellCode, ARRAYSIZE(Mapper::g_threadHijackShellCode));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write thread hijack shellcode. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // Perform thread hijack
    //
    HANDLE threadId = Utils::GetProcessMainThreadId(commsManager->GetProcessId());
    if (threadId == INVALID_HANDLE_VALUE)
    {
        throw std::runtime_error("Failed to find process main thread id!");
    }

    printf("[+] Hijacking thread id %d\n", HandleToUlong(threadId));

    HANDLE threadHandle = INVALID_HANDLE_VALUE;

    status = commsManager->OpenThread(threadId, &threadHandle);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to open thread. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    SCOPE_EXIT
    {
        commsManager->CloseHandle(threadHandle);
    };

    status = commsManager->SuspendThread(threadHandle);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to suspend thread. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    CONTEXT context{};
    context.ContextFlags = CONTEXT_FULL;

    status = commsManager->GetThreadContext(threadHandle, &context);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to get thread context. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    context.Rsp -= sizeof(DWORD64);

    status = commsManager->Write(reinterpret_cast<void *>(context.Rsp), &context.Rip, sizeof(DWORD64));
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to write context Rsp. NtStatus 0x%08X\n", status);

        throw std::runtime_error(fmt);
    }

    context.Rip = (DWORD64)mapperBase; // thread hijack shellcode procedure

    status = commsManager->SetThreadContext(threadHandle, &context);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to set thread context. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    status = commsManager->ResumeThread(threadHandle);
    if (!NT_SUCCESS(status))
    {
        sprintf_s(fmt, "Failed to resume thread. NtStatus 0x%08X", status);

        throw std::runtime_error(fmt);
    }

    // wait for mapper to execute
    //
    printf("[+] Waiting for mapper to execute!\n");

    while (true)
    {
        MAPPER_SHELLCODE_ARGS64 mapperResultArgs = {};
        status = commsManager->Read(&mapperResultArgs, shellCodeArgsBase, sizeof(mapperResultArgs));
        if (!NT_SUCCESS(status))
        {
            sprintf_s(fmt, "Failed to read mapper args. NtStatus 0x%08X\n", status);

            throw std::runtime_error(fmt);
        }

        switch (mapperResultArgs.Status)
        {
        case EShellcodeStatus::SHELLCODE_STATUS_AWAITING: {
            // Still awaiting execution, sleep current thread.
            //
            goto Sleep;
        }
        case EShellcodeStatus::SHELLCODE_STATUS_SUCCESS: {

            auto FixPageProtections = [&]() {
                for (auto i = 0ul; i < mapperImage->NumberOfSections; ++i)
                {
                    auto section = &mapperImage->Sections[i];

                    SIZE_T sectionSize = section->Size;
                    uint8_t *mappedSection = moduleBase + section->VirtualAddress;

                    if (section->Discardable)
                    {
                        // Fill data with zero's
                        //
                        std::vector<uint8_t> emptyBuffer(sectionSize);
                        ZeroMemory(emptyBuffer.data(), sectionSize);

                        status = commsManager->Write(mappedSection, emptyBuffer.data(), sectionSize);
                        if (!NT_SUCCESS(status))
                        {
                            sprintf_s(fmt,
                                      "Failed to erase discardable section at 0x%p with size 0x%X. NtStatus "
                                      "0x%08X\n",
                                      mappedSection, sectionSize, status);

                            throw std::runtime_error(fmt);
                        }
                    }
                    else
                    {
                        ULONG newAccess = section->Protection;

                        // Fix section protection
                        //
                        status =
                            commsManager->Protect(reinterpret_cast<PVOID *>(&mappedSection), &sectionSize, newAccess);
                        if (!NT_SUCCESS(status))
                        {
                            sprintf_s(
                                fmt, "Failed to apply section protection at 0x%p with size 0x%08llX. NtStatus 0x%08X\n",
                                mappedSection, sectionSize, status);

                            throw std::runtime_error(fmt);
                        }
                    }
                }
            };

            printf("[+] Fixing page protections!\n");

            FixPageProtections();

            shouldFreeModule = false;
            printf("[+] Image successfully mapped!\n");
            return;
        }
        default: {
            sprintf_s(fmt, "Failed to map image, shellcode status %d\n", mapperResultArgs.Status);

            throw std::runtime_error(fmt);
        }
        }

    Sleep:
        std::this_thread::sleep_for(std::chrono::milliseconds(512));
    }
}

void Map(const std::unique_ptr<Comms::CommsManager_t> &commsManager, const std::wstring &dllPath, int mode)
{
#if 0
    /*const NTSTATUS status = commsManager->Inject(Utils::ReadFileBinary(dllPath), SHELLCODE_FLAG_ALL);
    if (!NT_SUCCESS(status))
    {
        char fmt[256]{};
        sprintf_s(fmt, "Failed to map image, 0x%08X\n", status);
        throw std::runtime_error(fmt);
    }*/

    auto mapperImg = ManualMap::MAPPER_IMAGE::BuildMapperImage(Utils::ReadFileBinary(dllPath), SHELLCODE_FLAG_ALL);

    auto injectRequest = new Comms::DRIVER_COMMUNICATION_REQUEST_INJECT(
#if _DEBUG
        commsManager->GetProcessId(),
#endif
        mapperImg.data(), mapperImg.size());

    const NTSTATUS status = injectRequest->Send();
    if (!NT_SUCCESS(status))
    {
        char fmt[256]{};
        sprintf_s(fmt, "Failed to map image, 0x%08X\n", status);
        throw std::runtime_error(fmt);
    }
#endif
    auto mapperPayload = MAPPER_IMAGE::SerializeImage(Utils::ReadFileBinary(dllPath), SHELLCODE_FLAG_ALL);

    return Mapper::Map(commsManager, (PMAPPER_IMAGE)mapperPayload.data());

    // return Map(commsManager, Utils::ReadFileBinary(dllPath), mode);
}

} // namespace Mapper