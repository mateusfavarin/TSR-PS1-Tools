#include "raw.h"

#define WORD 4
#define HALF_WORD 2
#define BYTE 1

using namespace std;

uint8_t * store_word(uint8_t * buffer, uint8_t * data) {
    *((int *) buffer) = *((int *) data);
    return buffer + WORD;
}

uint8_t * store_half_word(uint8_t * buffer, uint8_t * data) {
    *((short *) buffer) = *((short *) data);
    return buffer + HALF_WORD;
}

uint8_t * store_byte(uint8_t * buffer, uint8_t * data) {
    *buffer = *data;
    return buffer + BYTE;
}

void unpack_section(uint8_t * raw_buffer, uint8_t * out_buffer) {

    uint8_t cVar5;
    uint8_t *pcVar6;
    uint8_t *pcVar7;
    int iVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint32_t uVar12;
    uint32_t uVar13;
    uint32_t uVar14;

    pcVar6 = raw_buffer + 0xf;
    uVar10 = ((uint32_t)raw_buffer[0xe] * 2 + 1) * 2;

LAB_8002617c:
    while(true) {

        pcVar7 = pcVar6;
        uVar10 = uVar10 * 2;
        if ((uVar10 & 0x100) != 0)
            break;

        pcVar7 = pcVar6 + BYTE;

        out_buffer = store_byte(out_buffer, pcVar6);
        uVar10 = uVar10 * 2;
        if ((uVar10 & 0x100) != 0)
            break;

LAB_8002616c:
        pcVar6 = pcVar7 + BYTE;
        out_buffer = store_byte(out_buffer, pcVar7);
    }

    uVar10 = uVar10 & 0xff;
    if (uVar10 == 0) {
        uVar10 = (uint32_t) pcVar7[0] * 2 + 1;
        pcVar7 = pcVar7 + BYTE;
        if ((uVar10 & 0x100) == 0)
            goto LAB_8002616c;
    }

    uVar9 = 2;
    uVar13 = 0;
    uVar14 = uVar10 * 2 >> 8 & 1;
    uVar10 = uVar10 * 2 & 0xff;
    if (uVar10 == 0) {
        uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
        pcVar7 = pcVar7 + BYTE;
        uVar14 = uVar10 >> 8 & 1;
    }

    if (uVar14 == 0) {
        uVar14 = uVar10 * 2 >> 8 & 1;
        uVar10 = uVar10 * 2 & 0xff;
        pcVar6 = pcVar7;
        if (uVar10 == 0) {
            pcVar6 = pcVar7 + BYTE;
            uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
            uVar14 = uVar10 >> 8 & 1;
        }
        uVar9 = uVar14 + 4;
        uVar12 = uVar10 * 2 >> 8 & 1;
        uVar10 = uVar10 * 2 & 0xff;
        if (uVar10 == 0) {
            uVar10 = (uint32_t) pcVar6[0] * 2 + uVar12;
            pcVar6 = pcVar6 + BYTE;
            uVar12 = uVar10 >> 8 & 1;
        }
        if (uVar12 != 0) {
            uVar9 = uVar10 * 2 >> 8 & 1;
            uVar10 = uVar10 * 2 & 0xff;
            if (uVar10 == 0) {
                uVar10 = (uint32_t) pcVar6[0] * 2 + uVar9;
                pcVar6 = pcVar6 + BYTE;
                uVar9 = uVar10 >> 8 & 1;
            }
            uVar9 = (uVar14 + 3) * 2 + uVar9;

            if (uVar9 != 9)
                goto LAB_8002600c;

            for (iVar8 = 0; iVar8 < 4; iVar8++) {
                uVar9 = uVar10 * 2 >> 8 & 1;
                uVar10 = uVar10 * 2 & 0xff;
                if (uVar10 == 0) {
                    uVar10 = (uint32_t) pcVar6[0] * 2 + uVar9;
                    pcVar6 = pcVar6 + BYTE;
                    uVar9 = uVar10 >> 8 & 1;
                }
                uVar13 = uVar13 * 2 + uVar9;
            }

            for (iVar8 = 0; iVar8 < uVar13 + 3; iVar8++) {
                out_buffer = store_word(out_buffer, pcVar6);
                pcVar6 += WORD;
            }

            goto LAB_8002617c;
        }
    }

    // if uVar14 != 0
    else {
        uVar14 = uVar10 * 2 >> 8 & 1;
        uVar10 = uVar10 * 2 & 0xff;
        if (uVar10 == 0) {
            uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
            pcVar7 = pcVar7 + BYTE;
            uVar14 = uVar10 >> 8 & 1;
        }
        if (uVar14 == 0) {
LAB_800260b0:
            cVar5 = pcVar7[0];
            pcVar6 = pcVar7 + BYTE;
            int temp = (cVar5 | uVar13);
            pcVar7 = out_buffer - temp - 1;
            if ((uVar9 & 1) != 0) {
                out_buffer = store_byte(out_buffer, pcVar7);
                pcVar7 += BYTE;
            }

            if ((cVar5 | uVar13) == 0) {
                for (iVar8 = 0; iVar8 < (uVar9 & ~1); iVar8++) {
                    out_buffer = store_byte(out_buffer, pcVar7);
                }
            }
            else {
                for (iVar8 = 0; iVar8 < uVar9 / 2; iVar8++) {
                    out_buffer = store_half_word(out_buffer, pcVar7);
                    pcVar7 += HALF_WORD;
                }
            }
            goto LAB_8002617c;
        }
        uVar9 = 3;
        uVar14 = uVar10 * 2 >> 8 & 1;
        uVar10 = uVar10 * 2 & 0xff;
        if (uVar10 == 0) {
            uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
            pcVar7 = pcVar7 + BYTE;
            uVar14 = uVar10 >> 8 & 1;
        }
        pcVar6 = pcVar7;
        if (uVar14 != 0) {
            pcVar6 = pcVar7 + BYTE;
            uVar9 = pcVar7[0] + 8;
            if (pcVar7[0] != 0)
                goto LAB_8002600c;
            uVar9 = uVar10 * 2 >> 8 & 1;
            uVar10 = uVar10 * 2 & 0xff;
            if (uVar10 == 0) {
                uVar10 = (uint32_t) pcVar6[0] * 2 + uVar9;
                pcVar6 = pcVar7 + HALF_WORD;
                uVar9 = uVar10 >> 8 & 1;
            }
            if (uVar9 == 0) {
                return;
            }
            goto LAB_8002617c;
        }
    }

LAB_8002600c:
    uVar14 = uVar10 * 2 >> 8 & 1;
    uVar10 = uVar10 * 2 & 0xff;
    pcVar7 = pcVar6;
    if (uVar10 == 0) {
        pcVar7 = pcVar6 + BYTE;
        uVar10 = (uint32_t) pcVar6[0] * 2 + uVar14;
        uVar14 = uVar10 >> 8 & 1;
    }
    if (uVar14 != 0) {
        uVar13 = uVar10 * 2 >> 8 & 1;
        uVar10 = uVar10 * 2 & 0xff;
        if (uVar10 == 0) {
            uVar10 = (uint32_t) pcVar7[0] * 2 + uVar13;
            pcVar7 = pcVar7 + BYTE;
            uVar13 = uVar10 >> 8 & 1;
        }
        uVar14 = uVar10 * 2 >> 8 & 1;
        uVar10 = uVar10 * 2 & 0xff;
        if (uVar10 == 0) {
            uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
            pcVar7 = pcVar7 + BYTE;
            uVar14 = uVar10 >> 8 & 1;
        }
        if (uVar14 == 0) {
            if (uVar13 == 0) {
                uVar13 = 1;
LAB_80026078:
                uVar14 = uVar10 * 2 >> 8 & 1;
                uVar10 = uVar10 * 2 & 0xff;
                if (uVar10 == 0) {
                    uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
                    pcVar7 = pcVar7 + BYTE;
                    uVar14 = uVar10 >> 8 & 1;
                }
                uVar13 = uVar13 * 2 + uVar14;
            }
        }
        else {
            uVar14 = uVar10 * 2 >> 8 & 1;
            uVar10 = uVar10 * 2 & 0xff;
            if (uVar10 == 0) {
                uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
                pcVar7 = pcVar7 + BYTE;
                uVar14 = uVar10 >> 8 & 1;
            }
            uVar13 = uVar13 * 2 + uVar14 | 4;
            uVar14 = uVar10 * 2 >> 8 & 1;
            uVar10 = uVar10 * 2 & 0xff;
            if (uVar10 == 0) {
                uVar10 = (uint32_t) pcVar7[0] * 2 + uVar14;
                pcVar7 = pcVar7 + BYTE;
                uVar14 = uVar10 >> 8 & 1;
            }
            if (uVar14 == 0)
                goto LAB_80026078;
        }
        uVar13 = uVar13 << 8;
    }
    goto LAB_800260b0;
}