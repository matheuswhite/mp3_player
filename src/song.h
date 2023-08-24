/**
 * @file song.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definição do módulo que gerencia as músicas
 * @version 0.1.0
 * @date 02/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#ifndef MP3_PLAYER_SONG_H
#define MP3_PLAYER_SONG_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sd_card.h"

/**
 * @brief Tamanho máximo do nome da música
 */
#define SONG_NAME_LEN 64

/**
 * @brief Tamanho máximo do nome do artista
 */
#define SONG_ARTIST_LEN 32

/**
 * @brief Tamanho máximo do conteúdo da música
 */
#define SONG_DATA_MAX_LEN 1024

/**
 * @brief Armazena dados de uma música
 */
typedef struct song {
    char name[SONG_NAME_LEN + 1];     /**< Nome da música */
    char artist[SONG_ARTIST_LEN + 1]; /**< Nome do artista da música */
    uint16_t duration_secs;           /** Duração da música em segundos */
    uint16_t data_len;                /**< Tamanho do buffer com o áudio */
    uint8_t data[SONG_DATA_MAX_LEN];  /** Buffer com o áudio da música (em bytes)
                                       * codificada em MP3 */
} song_t;

/**
 * @brief Carrega uma de música do disco.
 *
 * @param[out] song Referência para a música.
 * @param[in] name Nome da música.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_song_load(song_t *song, const char *name);

/**
 * @brief Formata as informações da música em um buffer.
 *
 * @param[in] song Referência para a música.
 * @param[out] buffer Buffer onde as informações da música serão imprimidas.
 * @param buffer_len Tamanho do buffer de saída.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_song_format(song_t *song, char *buffer, size_t buffer_len);

#endif /* MP3_PLAYER_SONG_H */
