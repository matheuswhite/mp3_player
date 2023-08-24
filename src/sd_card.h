/**
 * @file sd_card.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definições do módulo que carrega e salva dados no cartão SD
 * @version 0.1.0
 * @date 02/08/23
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
 * @brief Inicializa o módulo do cartão SD.
 *
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_sd_card_init(void);

/**
 * @brief Carrega dados do cartão SD.
 *
 * @param[in] filepath Caminho para o arquivo no cartão SD.
 * @param[out] buffer Buffer onde os dados lidos serão preenchidos.
 * @param buffer_len Tamanho do buffer de leitura.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_sd_card_read(const char *filepath, uint8_t *buffer, size_t buffer_len);

/**
 * @brief Escreve dados no cartão SD.
 *
 * @param[in] filepath Caminho para o arquivo no cartão SD.
 * @param[in] buffer Referência para os dados de escrita.
 * @param buffer_len Tamanho do buffer de escrita.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_sd_card_write(const char *filepath, uint8_t *buffer, size_t buffer_len);

/**
 * @brief Apaga um arquivo do cartão SD.
 *
 * @param[in] filepath
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_sd_card_delete(const char *filepath);

#endif /* MP3_PLAYER_SD_CARD_H */
