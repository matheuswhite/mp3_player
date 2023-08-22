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

#include <stdlib.h>
#include <stdbool.h>
#include "song.h"

/**
 * @brief
 */
#define PLAYLIST_NAME_LEN 64

/**
 * @brief
 */
#define PLAYLIST_MAX_SONGS 50

/**
 * @brief
 */
typedef enum repeat_mode {
    REPEAT_MODE_NONE = 0, /**< */
    REPEAT_MODE_PLAYLIST, /**< */
    REPEAT_MODE_ONE, /**< */
} repeat_mode_t;

/**
 * @brief
 */
typedef struct playlist {
    char name[PLAYLIST_NAME_LEN];      /**< */
    song_t *songs[PLAYLIST_MAX_SONGS]; /**< */
    size_t songs_len;                  /**< */
    size_t selected_song_index; /**< */
    bool is_shuffle_en; /**< */
    repeat_mode_t repeat_mode; /**< */
} playlist_t;

/**
 * @brief
 *
 * @param playlist
 * @param name
 * @param first_song
 * @return
 */
int mpl_playlist_new(playlist_t *playlist, char *name, song_t *first_song);

/**
 * @brief
 *
 * @param playlist
 * @param name
 * @param songs
 * @return
 */
int mpl_playlist_load(playlist_t *playlist, char *name, song_t *songs);

/**
 * @brief
 *
 * @param playlist
 * @param song
 * @return
 */
int mpl_playlist_add_song(playlist_t *playlist, song_t *song);

/**
 * @brief
 *
 * @param playlist
 * @param name
 * @return
 */
int mpl_playlist_remove_song(playlist_t *playlist, char *name);

/**
 * @brief
 *
 * @param playlist
 * @param index
 * @return
 */
int mpl_playlist_remove_song_by_index(playlist_t *playlist, size_t index);

/**
 * @brief
 *
 * @param playlist
 * @param song
 * @return
 */
int mpl_playlist_selected_song(playlist_t *playlist, song_t *song);

/**
 * @brief
 *
 * @param playlist
 * @return
 */
int mpl_playlist_prev_song(playlist_t *playlist);

/**
 * @brief
 *
 * @param playlist
 * @return
 */
int mpl_playlist_next_song(playlist_t *playlist);

/**
 * @brief
 *
 * @param playlist
 * @param index
 * @return
 */
int mpl_playlist_select_song(playlist_t *playlist, size_t index);

/**
 * @brief
 *
 * @param playlist
 * @param en
 * @return
 */
int mpl_playlist_set_shuffle(playlist_t *playlist, bool en);

/**
 * @brief
 *
 * @param playlist
 * @param mode
 * @return
 */
int mpl_playlist_set_repeat_mode(playlist_t *playlist, repeat_mode_t mode);

/**
 * @brief
 *
 * @param playlist
 * @param buffer
 * @param buffer_len
 * @return
 */
int mpl_playlist_format(playlist_t *playlist, char *buffer, size_t buffer_len);

#endif /* MP3_PLAYER_PLAYLIST_H */
