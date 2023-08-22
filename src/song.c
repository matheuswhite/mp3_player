/**
 * @file song.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementação do módulo que gerência as músicas
 * @version 0.1.0
 * @date 25/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#include "song.h"

/**
 * @brief Tamanho do buffer de leitura das músicas.
 */
#define BUFFER_LEN 256

/**
 * @brief Tamanho máximo do caminho do arquivo de música.
 */
#define FILEPATH_LEN 256

/**
 * @brief Estrutura com os campos globais do song
 */
static struct song_fields {
    uint8_t buffer[BUFFER_LEN]; /**< Buffer de leitura das músicas. */
    char filepath[FILEPATH_LEN]; /**< Caminho do arquivo de música. */
} self = {
    .buffer   = 0,
    .filepath = 0,
};

int mpl_song_load(song_t *song, const char *name)
{
    if (song == NULL || name == NULL) {
        return -ENODEV;
    }

    if (strlen(name) > SONG_NAME_LEN) {
        return -EINVAL;
    }

    int err;
    uint8_t *cursor = self.buffer;

    memset(song, 0, sizeof(song_t));
    memset(self.filepath, 0, FILEPATH_LEN);

    strcat(self.filepath, "../sdcard/songs/");
    strcat(self.filepath, name);
    strcat(self.filepath, ".bmp3");

    err = mpl_sd_card_read(self.filepath, self.buffer, BUFFER_LEN);
    if (err) {
        return err;
    }

    strcpy(song->name, name);

    strcpy(song->artist, (char *) cursor);
    cursor += strlen(song->artist) + 1;

    memcpy(&song->duration_secs, cursor, sizeof(song->duration_secs));
    cursor += sizeof(song->duration_secs);

    memcpy(&song->data_len, cursor, sizeof(song->data_len));
    cursor += sizeof(song->data_len);

    memcpy(song->data, cursor, song->data_len);
    cursor += song->data_len;

    return 0;
}

int mpl_song_format(song_t *song, char *buffer, size_t buffer_len)
{
    if (song == NULL || buffer == NULL) {
        return -ENODEV;
    }

    if (buffer_len == 0) {
        return 0;
    }

    uint8_t minutes = song->duration_secs / 60;
    uint8_t seconds = song->duration_secs % 60;

    snprintf(buffer, buffer_len, "[%d:%d] %s - %s", minutes, seconds, song->name,
             song->artist);

    return 0;
}
