/**
 * @file sd_card.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementação do módulo que carrega e salva dados no cartão SD
 * @version 0.1.0
 * @date 25/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#include "sd_card.h"

int mpl_sd_card_init(void)
{
    return 0;
}

int mpl_sd_card_read(const char *filepath, uint8_t *buffer, size_t buffer_len)
{
    FILE *f = fopen(filepath, "rb");

    if (f == NULL) {
        return -ENOENT;
    }

    fseek(f, 0, SEEK_SET);
    fread(buffer, buffer_len, 1, f);
    fclose(f);

    return 0;
}

int mpl_sd_card_write(const char *filepath, uint8_t *buffer, size_t buffer_len)
{
    FILE *f = fopen(filepath, "wb");

    if (f == NULL) {
        return -ENOBUFS;
    }

    fseek(f, 0, SEEK_SET);
    fwrite(buffer, buffer_len, 1, f);
    fclose(f);

    return 0;
}