import random

songs = [
    {'artist': 'a-ha', 'name': "Take on Me", 'duration': (3, 45)},
    {'artist': 'a-ha', 'name': "The Sun Always Shines on T.V.", 'duration': (5, 2)},
    {'artist': 'a-ha', 'name': "Hunting High and Low", 'duration': (3, 49)},
    {'artist': 'a-ha', 'name': "Stay on These Roads", 'duration': (4, 44)},
    {'artist': 'a-ha', 'name': "Thouchy!", 'duration': (4, 37)},
    {'artist': 'a-ha', 'name': "Crying in the Rain", 'duration': (4, 20)},
    {'artist': 'a-ha', 'name': "Early Morning", 'duration': (2, 59)},
    {'artist': 'a-ha', 'name': "Slender Frame", 'duration': (3, 44)},
    {'artist': 'a-ha', 'name': "East of the Sun", 'duration': (4, 48)},
    {'artist': 'a-ha', 'name': "Waiting for Her", 'duration': (4, 49)},
]

if __name__ == '__main__':
    for song in songs:
        with open(f'songs/{song["name"]}.bmp3', 'wb') as file:
            file.write(song['artist'].encode('utf-8'))
            file.write(b'\x00')
            duration = song['duration'][0] * 60 + song['duration'][1]
            file.write(duration.to_bytes(2, 'little'))
            file.write(duration.to_bytes(2, 'little'))
            file.write(random.randbytes(duration))
