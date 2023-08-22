/**
 * @file sd_card.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1.0
 * @date 25/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#ifndef MP3_PLAYER_SD_CARD_H
#define MP3_PLAYER_SD_CARD_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/**
 * @brief
 *
 * @return
 */
int mpl_sd_card_init(void);

/**
 * @brief
 *
 * @param[in] filepath
 * @param[out] buffer
 * @param buffer_len
 * @return
 */
int mpl_sd_card_read(const char *filepath, uint8_t *buffer, size_t buffer_len);

/**
 * @brief
 *
 * @param[in] filepath
 * @param[out] buffer
 * @param buffer_len
 * @return
 */
int mpl_sd_card_write(const char *filepath, uint8_t *buffer, size_t buffer_len);

/**
 * @brief
 *
 * @param[in] filepath
 * @return
 */
int mpl_sd_card_delete(const char *filepath);

#endif /* MP3_PLAYER_SD_CARD_H */
