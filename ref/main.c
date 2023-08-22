#include <stdio.h>

#include "playlist.h"
#include "song.h"

#define SONG_AMOUNT 10
#define ALBUMS_AMOUNT 3

int main()
{
    int err;
    song_t all_songs[SONG_AMOUNT]       = {0};
    playlist_t albums[ALBUMS_AMOUNT]    = {0};
    const char *song_names[SONG_AMOUNT] = {
        "Take on Me",
        "The Sun Always Shines on T.V.",
        "Hunting High and Low",
        "Stay on These Roads",
        "Thouchy!",
        "Crying in the Rain",
        "Early Morning",
        "Slender Frame",
        "East of the Sun",
        "Waiting for Her",
    };
    const char *albums_names[ALBUMS_AMOUNT] = {
        "Hunting High and Low",
        "Stay on These Roads",
        "East of the Sun, West of the Moon",
    };
    size_t first_songs_indexes[ALBUMS_AMOUNT] = {0, 3, 5};
    size_t song_amounts[ALBUMS_AMOUNT]        = {3, 2, 5};
    size_t start_index;
    char buffer[1024] = {0};


    err = mpl_sd_card_init();
    if (err) {
        return err;
    }

    for (int i = 0; i < SONG_AMOUNT; ++i) {
        err = mpl_song_load(&all_songs[i], song_names[i]);
        if (err) {
            printf("[ERR] Cannot load %s from disk: %d\n", song_names[i], err);
            return err;
        }
    }

    for (int i = 0; i < ALBUMS_AMOUNT; ++i) {
        start_index = first_songs_indexes[i];

        err = mpl_playlist_load(&albums[i], (char *) albums_names[i], all_songs);
        if (!err) {
            printf("Playlist %s loaded from disk", albums[i].name);
            continue;
        }

        if (err && err != -ENOENT) {
            return err;
        }

        err = mpl_playlist_new(&albums[i], (char *) albums_names[i], &all_songs[start_index]);
        if (err) {
            printf("[ERR] Cannot create %s playlist: %d\n", albums_names[i], err);
            return err;
        }

        for (int j = 0; j < song_amounts[i] - 1; ++j) {
            err = mpl_playlist_add_song(&albums[i], &all_songs[start_index + 1 + j]);
            if (err) {
                printf("[ERR] Cannot add %s to playlist %s: %d\n",
                       all_songs[start_index + 1].name, albums[i].name, err);
            }
        }
    }

    for (int i = 0; i < ALBUMS_AMOUNT; ++i) {
        err = mpl_playlist_format(&albums[i], buffer, sizeof(buffer));
        if (err) {
            printf("[ERR] Cannot format album %s: %d\n", albums[i].name, err);
            return err;
        }
        printf("%s\n", buffer);

        for (int j = 0; j < albums[i].songs_len; ++j) {
            memset(buffer, 0, sizeof(buffer));
            err = mpl_song_format(albums[i].songs[j], buffer, sizeof(buffer));
            if (err) {
                printf("[ERR] Cannot format song %s: %d\n", albums[i].songs[j]->name,
                       err);
                return err;
            }
            printf("\t%s\n", buffer);
        }
    }

    return 0;
}
