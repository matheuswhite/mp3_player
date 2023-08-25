/**
 * @file playlist.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1.0
 * @date 02/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#ifndef MP3_PLAYER_PLAYLIST_H
#define MP3_PLAYER_PLAYLIST_H

#include <stdbool.h>
#include <stdlib.h>

#include "song.h"

/**
 * @brief Tamanho máximo do nome da playlist
 */
#define PLAYLIST_NAME_LEN 64

/**
 * @brief Quantidade máxima de músicas por playlists
 */
#define PLAYLIST_MAX_SONGS 50

/**
 * @brief Modo de repetição das músicas em uma playlist
 */
typedef enum repeat_mode {
    REPEAT_MODE_NONE = 0, /**< Sem repetição. Após a última música a playlist é
                             pausada. */
    REPEAT_MODE_PLAYLIST, /**< Repetir a playlist. Após a última música é reproduzida a
                             primeira música da playlist. */
    REPEAT_MODE_SINGLE,   /**< A música atual é repetida ao termino da reprodução. */
} repeat_mode_t;

/**
 * @brief Armazena as informações de uma playlist.
 */
typedef struct playlist {
    char name[PLAYLIST_NAME_LEN];      /**< Nome da playlist. */
    song_t *songs[PLAYLIST_MAX_SONGS]; /**< Lista de músicas da playlist. */
    size_t songs_len;                  /**< Quantidade de músicas na playlist. */
    size_t selected_song_index;        /**< Índice da música selecionada (pausada ou em
                                          reprodução). */
    bool is_shuffle_en;        /**< Indica se o modo aleatório está habilitado. */
    repeat_mode_t repeat_mode; /**< Modo de repetição da playlist. */
} playlist_t;

/**
 * @brief Cria uma nova playlist com 1 música.
 *
 * @param[out] playlist Referência para a nova playlist.
 * @param[in] name Nome da playlist.
 * @param[in] first_song Referência para a primeira música da playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_new(playlist_t *playlist, char *name, song_t *first_song);

/**
 * @brief Carrega uma playlist do disco.
 *
 * @param[out] playlist Referência para a playlist carregada.
 * @param[in] name Nome da playlist.
 * @param[in] songs Lista com todas as músicas presentes no disco.
 * @param songs_len Quantidade de músicas na lista com todas as músicas.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_load(playlist_t *playlist, char *name, song_t *songs, size_t songs_len);

/**
 * @brief Adiciona uma música na playlist
 *
 * @param[in] playlist Referência para a playlist.
 * @param[in] song Referência para a música.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_add_song(playlist_t *playlist, song_t *song);

/**
 * @brief Remove uma música da playlist, usando o nome da música.
 *
 * @param[in] playlist Referência para a playlist.
 * @param[in] name Nome da música que deve ser removida.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_remove_song(playlist_t *playlist, char *name);

/**
 * @brief Remove uma música da playlist, usando o índice da música.
 *
 * @param[in] playlist Referência para a playlist.
 * @param index Índice da música na playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_remove_song_by_index(playlist_t *playlist, size_t index);

/**
 * @brief Obtém a música seleciona da playlist.
 *
 * @param[in] playlist Referência para a playlist.
 * @param[out] song Referência para a música selecionada da playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_selected_song(playlist_t *playlist, song_t *song);

/**
 * @brief Seleciona a música anterior da playlist, respeitando o modo de repetição.
 *
 * @param playlist Referência para a playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_prev_song(playlist_t *playlist);

/**
 * @brief Seleciona a próxima música da playlist, respeitando o modo de repetição e o modo
 * aleatório.
 *
 * @param[in] playlist Referência para a playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_next_song(playlist_t *playlist);

/**
 * @brief Seleciona uma música da playlist, usando um índice.
 *
 * @param[in] playlist Referência para a playlist.
 * @param index Índice da música selecionada.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_select_song(playlist_t *playlist, size_t index);

/**
 * @brief Habilita/Desabilita o modo aleatório da playlist.
 *
 * @param[in] playlist Referência para a playlist.
 * @param en Indica se o modo aleatório deve ser habilitado ou desabilitado.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_set_shuffle(playlist_t *playlist, bool en);

/**
 * @brief Altera o modo de repetição da playlist.
 *
 * @param[in] playlist Referência para a playlist.
 * @param mode Modo de repetição da playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_set_repeat_mode(playlist_t *playlist, repeat_mode_t mode);

/**
 * @brief Formata as informações da playlist em um buffer.
 *
 * @param[in] playlist Referência para a playlist.
 * @param[out] buffer Buffer de saída onde as informações da playlist serão preenchidas.
 * @param buffer_len Tamanho do buffer de saída.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
int mpl_playlist_format(playlist_t *playlist, char *buffer, size_t buffer_len);

#endif /* MP3_PLAYER_PLAYLIST_H */
