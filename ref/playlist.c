/**
 * @file playlist.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1.0
 * @date 02/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#include "playlist.h"

/**
 * @brief Macro para obter a representação do modo de repetição
 */
#define REPEAT_MODE_STR(mode) \
    (((mode) == REPEAT_MODE_PLAYLIST) ? "P" : (((mode) == REPEAT_MODE_ONE) ? "1" : " "))

/**
 * @brief Tamanho do buffer de escrita e leitura da playlist
 */
#define BUFFER_LEN 2048

/**
 * @brief Tamanho máximo do caminho do arquivo da playlist
 */
#define FILEPATH_LEN 256

/**
 * @brief Estrutura com os campos globais da playlist
 */
static struct {
    uint8_t buffer[BUFFER_LEN]; /**< Buffer de leitura e escrita das playlists */
    char filepath[FILEPATH_LEN]; /**< Caminho do arquivo da playlist. */
} self = {
    .buffer   = {0},
    .filepath = {0},
};

/**
 * @brief Armazena a playlist no disco.
 *
 * @param[in] playlist Referência da playlist.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
static int save_playlist(playlist_t *playlist);

/**
 * @brief Encontra o índice da música pelo nome da música.
 *
 * @param[in] songs Lista com todas as músicas presentes no disco.
 * @param songs_len Quantidade de músicas na lista de todas as músicas.
 * @param[in] name Nome da música para a busca.
 * @param[out] song_index Índice da música encontrada.
 * @return int 0 em caso de sucesso e um inteiro negativo em caso de falha.
 */
static int find_song_by_index(song_t *songs, size_t songs_len, char *name, size_t *song_index);

int mpl_playlist_new(playlist_t *playlist, char *name, song_t *first_song)
{
    if (playlist == NULL || name == NULL || first_song == NULL) {
        return -ENODEV;
    }

    size_t name_len = strlen(name);

    if (name_len == 0) {
        return -EINVAL;
    }

    snprintf(playlist->name, sizeof(playlist->name), "%s", name);
    playlist->songs[0]            = first_song;
    playlist->songs_len           = 1;
    playlist->selected_song_index = 0;
    playlist->is_shuffle_en       = false;
    playlist->repeat_mode         = REPEAT_MODE_NONE;

    return save_playlist(playlist);
}

int mpl_playlist_load(playlist_t *playlist, char *name, song_t *songs, size_t songs_len)
{
    if (playlist == NULL || name == NULL || songs == NULL) {
        return -ENODEV;
    }

    if (strlen(name) == 0) {
        return -ENOENT;
    }

    int err;
    uint8_t *cursor = self.buffer;
    char song_name[SONG_NAME_LEN + 1];
    size_t song_index;
    size_t playlist_songs_len;
    size_t songs_cursor;

    memset(playlist, 0, sizeof(playlist_t));
    memset(self.filepath, 0, FILEPATH_LEN);

    strcat(self.filepath, "../sdcard/playlist");
    strcat(self.filepath, name);

    err = mpl_sd_card_read(self.filepath, self.buffer, BUFFER_LEN);
    if (err) {
        return err;
    }

    playlist->selected_song_index = 0;

    memcpy(&playlist->songs_len, cursor, sizeof(playlist->songs_len));
    cursor += sizeof(playlist->songs_len);
    playlist_songs_len = playlist->songs_len;

    for (int i = 0; i < playlist_songs_len; ++i) {
        strcpy(song_name, (char *) cursor);
        cursor += strlen(song_name) + 1;

        err = find_song_by_index(songs, songs_len, song_name, &song_index);
        if (err) {
            printf("[WRN] Song %s is in the playlist %s, but the song list there is no "
                   "song with this name\n",
                   song_name, name);
            playlist->songs_len -= 1;
            continue;
        }

        playlist->songs[songs_cursor] = &songs[song_index];
        songs_cursor += 1;
    }

    memcpy(&playlist->is_shuffle_en, cursor, sizeof(playlist->is_shuffle_en));
    cursor += sizeof(playlist->is_shuffle_en);

    memcpy(&playlist->repeat_mode, cursor, sizeof(playlist->repeat_mode));
    cursor += sizeof(playlist->repeat_mode);

    return 0;
}

int mpl_playlist_add_song(playlist_t *playlist, song_t *song)
{
    if (playlist == NULL || song == NULL) {
        return -ENODEV;
    }

    if (playlist->songs_len >= PLAYLIST_MAX_SONGS) {
        return -ENOBUFS;
    }

    playlist->songs[playlist->songs_len] = song;
    playlist->songs_len += 1;

    return save_playlist(playlist);
}

int mpl_playlist_remove_song(playlist_t *playlist, char *name)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_remove_song_by_index(playlist_t *playlist, size_t index)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_current_playing_song(playlist_t *playlist, song_t *song)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_prev_song(playlist_t *playlist)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_next_song(playlist_t *playlist)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_select_song(playlist_t *playlist, size_t index)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_set_shuffle(playlist_t *playlist, bool en)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_set_repeat_mode(playlist_t *playlist, repeat_mode_t mode)
{
    // TODO

    return -EPROTO;
}

int mpl_playlist_format(playlist_t *playlist, char *buffer, size_t buffer_len)
{
    if (playlist == NULL || buffer == NULL) {
        return -ENODEV;
    }

    if (buffer_len == 0) {
        return 0;
    }

    snprintf(buffer, buffer_len, "[Playlist|%lu|%s|%s] %s - %s", playlist->songs_len,
             REPEAT_MODE_STR(playlist->repeat_mode), playlist->is_shuffle_en ? "R" : " ",
             playlist->name, playlist->songs[playlist->selected_song_index]->name);

    return 0;
}

static int save_playlist(playlist_t *playlist)
{
    int err;
    uint8_t *cursor = self.buffer;

    memset(self.filepath, 0, FILEPATH_LEN);
    memset(self.buffer, 0, sizeof(self.buffer));

    strcat(self.filepath, "../sdcard/playlist/");
    strcat(self.filepath, playlist->name);

    memcpy(cursor, &playlist->songs_len, sizeof(playlist->songs_len));
    cursor += sizeof(playlist->songs_len);

    for (int i = 0; i < playlist->songs_len; ++i) {
        song_t *song = playlist->songs[i];
        memcpy(cursor, song->name, strlen(song->name) + 1);
        cursor += strlen(song->name) + 1;
    }

    memcpy(cursor, &playlist->is_shuffle_en, sizeof(playlist->is_shuffle_en));
    cursor += sizeof(playlist->is_shuffle_en);

    memcpy(cursor, &playlist->repeat_mode, sizeof(playlist->repeat_mode));
    cursor += sizeof(playlist->repeat_mode);

    err = mpl_sd_card_write(self.filepath, self.buffer, cursor - self.buffer);
    if (err) {
        return err;
    }

    return 0;
}

static int find_song_by_index(song_t *songs, size_t songs_len, char *name, size_t *song_index)
{
    song_t *song = NULL;

    for (int i = 0; i < songs_len; ++i) {
        song = &songs[i];
        if (strcmp(song->name, name) == 0) {
            *song_index = i;
            return 0;
        }
    }

    return -ENOENT;
}
