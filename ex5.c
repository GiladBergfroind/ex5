/******************
Name: Gilad Bergfroind
ID: 331749978
Assignment: ex5
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FIRST_SIZE 30
#define FIRST_SIZE_S "30"


typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
	void* prev;
	void* next;
} Song;

typedef struct Playlist {
    char* name;
    Song* songs;
    int songsNum;
    int songsSize;
    void* prev;
    void* next;
} Playlist;

int howManySongs(struct Song* song);

struct Song* songByIndex(struct Song* song, int index);

struct Playlist* playlistByIndex(struct Playlist* playlist, int index);

void freeSong(struct Song* song); 

void freePlaylist(struct Playlist* playlist)
{
    for (int i = 0; i < howManySongs(playlist->songs); i++) {
        struct Song* tempSong = songByIndex(playlist->songs, 0);
        freeSong(tempSong);
    }
}

void freeAllPlaylists(struct Playlist* playlist)
{
    if (playlist == NULL)
        return;

    struct Playlist* currentPlaylist = playlist;
    struct Playlist* nextPlaylist = playlist->next;
    while (currentPlaylist != NULL)
    {
        freePlaylist(currentPlaylist);
        currentPlaylist = nextPlaylist;
        if (nextPlaylist != NULL)
            nextPlaylist = nextPlaylist->next;
    }
}

void sortPlaylist(struct Playlist* playlist);

//some recommendations for functions, you may implement however you want

struct Song* minStreams(struct Song* song, int startIndex)
{
    struct Song* currentSong = songByIndex(song,startIndex);
    struct Song* minSong = currentSong;
    while (currentSong != NULL) {
        if (currentSong->streams < minSong->streams)
            minSong = currentSong;
        currentSong = currentSong->next;
    }
    return minSong;
}

struct Song* maxStreams(struct Song* song, int startIndex)
{
    struct Song* currentSong = songByIndex(song, startIndex);
    struct Song* maxSong = currentSong;
    while (currentSong != NULL) {
        if (currentSong->streams > maxSong->streams)
            maxSong = currentSong;
        currentSong = currentSong->next;
    }
    return maxSong;
}

struct Song* minWord(struct Song* song, int startIndex)
{
    struct Song* currentSong = songByIndex(song, startIndex);
    struct Song* minSong = currentSong;
    while (currentSong != NULL) {
        if (strcmp(currentSong->title, minSong->title) < 0)
            minSong = currentSong;
        currentSong = currentSong->next;
    }
    return minSong;
}

struct Song* minYear(struct Song* song, int startIndex)
{
    struct Song* currentSong = songByIndex(song, startIndex);
    struct Song* minSong = currentSong;
    while (currentSong != NULL) {
        if (currentSong->year < minSong->year)
            minSong = currentSong;
        currentSong = currentSong->next;
    }
    return minSong;
}

void swap(struct Song** head,struct Song* song1, struct Song* song2)
{
	if (song1 == song2)
		return;

    struct Song* temp = malloc(sizeof(struct Song));
	if (temp == NULL)
		return;
    temp->prev = song1->prev;
    temp->next = song1->next;
    song1->prev = song2->prev;
	song1->next = song2->next;
	song2->prev = temp->prev;
	song2->next = temp->next;
    if (temp->next == song2)
    {
        song1->prev = song2;
        song2->next = song1;
    }

    // if song1 is the first song
	// temp hold the old first song
	if (temp->prev == NULL)
	{
		*head = song2;
	}
    else
    {
        struct Song* prevSong2 = song2->prev;
		prevSong2->next = song2;
    }
	// if new song2 is not the last song
	if (song2->next != NULL)
	{
		struct Song* nextSong2 = song2->next;
		nextSong2->prev = song2;
	}
	// correct all relation between songs
    if (song1->prev != NULL)
    {
        struct Song* prevSong1 = song1->prev;
        prevSong1->next = song1;
    }
    // if new song1 is not the last song
    if (song1->next != NULL)
    {
        struct Song* nextSong1 = song1->next;
        nextSong1->prev = song1;
    }

    free(temp);
}

void sortByStreamsAscending(struct Playlist* playlist, int startIndex, int endIndex)
    {
	for (int i = startIndex; i < endIndex; i++)
    {
		struct Song* song = playlist->songs;
        struct Song* currentSong = songByIndex(song,i);
        struct Song* minSong = minStreams(song,i);
        swap(&(playlist->songs),currentSong, minSong);
    }
}

void sortByStreamsDescending(struct Playlist* playlist, int startIndex, int endIndex)
    {
        for (int i = startIndex; i < endIndex; i++)
        {
            struct Song* song = playlist->songs;
            struct Song* currentSong = songByIndex(song, i);
            struct Song* maxSong = maxStreams(song, i);
            swap(&(playlist->songs), currentSong, maxSong);
        }
    }


void sortByWord(struct Playlist* playlist, int startIndex, int endIndex)
{
    for (int i = startIndex; i < endIndex; i++)
    {
        struct Song* song = playlist->songs;
        struct Song* currentSong = songByIndex(song, i);
        struct Song* minSong = minWord(song, i);
        swap(&(playlist->songs), currentSong, minSong);
    }

}
void sortByYear(struct Playlist* playlist, int startIndex, int endIndex)
{
    for (int i = startIndex; i < endIndex; i++)
    {
        struct Song* song = playlist->songs;
        struct Song* currentSong = songByIndex(song, i);
        struct Song* minSong = minYear(song, i);
        swap(&(playlist->songs), currentSong, minSong);
    }
}

struct Playlist* playlistByIndex(struct Playlist* playlist, int index)
{
	struct Playlist* currentPlaylist = playlist;
    for (int j = 0; j < index; j++) {
        currentPlaylist = currentPlaylist->next;
    }
	return currentPlaylist;
}

struct Song* songByIndex(struct Song* song, int index)
{
    struct Song* currentSong = song;
    for (int j = 0; j < index; j++) {
        currentSong = currentSong->next;
    }
	return currentSong;
}

struct Playlist* getLastPlaylist(struct Playlist* playlist) {
    struct Playlist* currentPlaylist = playlist;
    if (currentPlaylist == NULL) return NULL;
    while (currentPlaylist->next != NULL) {
        currentPlaylist = currentPlaylist->next;
    }
    return currentPlaylist;
}

struct Song* getLastSong(struct Song* song) {
    struct Song* currentSong = song;
    while (currentSong->next != NULL) {
        currentSong = currentSong->next;
    }
    return currentSong;
}

void* getString() {
    int endOfLine = 0;
    char* line = NULL;
    int length;
    char* tempPointer = NULL;
    int size = FIRST_SIZE;
    while (!endOfLine) {
        char temp[FIRST_SIZE+1] = { 0 };
        char* temp1 = temp;
        scanf(" %" FIRST_SIZE_S "[^\n\r]s", temp1);
        if (temp[size - 2] == '\n' || temp[size - 2] == 0) {
            endOfLine = 1;
        }
        if (line == NULL) {
            length = 0;
        }
        else {
            length = strlen(line);
        }
        tempPointer = line;
        line = realloc(line, strlen(temp) + length + 1);
        if (line == NULL) {
            line = malloc(strlen(temp) + length + 1);
			if (line == NULL) {
				free(tempPointer);
				return NULL;
			}
            strcpy(line, tempPointer);
            free(tempPointer);
        }
        strcpy(line + length, temp);
    }
    return line;
}

void printSongs(struct Song *song, int songNum)
{
    printf("%d. Title: %s\n   Artist: %s\n   Released: %d\n   Streams: %d\n\n",songNum,song->title,
        song->artist,song->year,song->streams);
    fflush(NULL);
}

void addSong(struct  Playlist* playlists) {
    struct Song* newSong = malloc(sizeof(struct Song));
    if (newSong == NULL)
    {
        printf("Memory allocation failed\n");
        fflush(NULL);
        return;
    }
    printf("Enter song's details:\n");
	printf("Title:\n");
    newSong->title = getString();
	printf("Artist:\n");
    newSong->artist = getString();
    newSong->streams = 0;
	printf("Year of release:\n");
    int year; 
    scanf(" %d",&year);
    newSong->year = year;
	printf("Lyrics:\n");
    fflush(NULL);
    newSong->lyrics = getString();
    newSong->next = NULL;
    newSong->prev = NULL;
    if (playlists->songs == NULL)
        playlists->songs = newSong;
    else {
        newSong->prev = getLastSong(playlists->songs);
        getLastSong(playlists->songs)->next = newSong;
    }

    return;
}

void showPlaylist(struct Playlist *playlist) {
    if (playlist->songs != NULL) {
        struct Song* currentSong = playlist->songs;
        int j = 1;
        while (currentSong != NULL) {
            printSongs(currentSong, j);
            currentSong = currentSong->next;
            j++;
        }
        int songToPlay = 5;
		while (songToPlay != 0)
        {
            printf("Choose a song to play, or 0 to quit:\n");
            fflush(NULL);
            scanf(" %d", &songToPlay);
            if (songToPlay == 0)
                return;

            currentSong = playlist->songs;
            for (int j = 1; j < songToPlay; j++) {
                currentSong = currentSong->next;
            }
            printf("Now playing %s:\n$ %s $\n", currentSong->title, currentSong->lyrics);
            fflush(NULL);
            currentSong->streams++;
        }
    }
    else {
        int temp;
        printf("Choose a song to play, or 0 to quit:\n");
        fflush(NULL);
        scanf("%d", &temp);
        }
    return;
}

int deleteSong(struct Playlist* playlist) {
    if (playlist->songs != NULL) {
        struct Song* currentSong = playlist->songs;
        int j = 1;
        while (currentSong != NULL) {
            printSongs(currentSong, j);
            currentSong = currentSong->next;
            j++;
        }
    }
    else {
        printf("No songs in the playlist.\n");
        fflush(NULL);
        return 0;
    }
    printf("Choose a song to delete, or 0 to quit:\n");
    fflush(NULL);
    int songToDelete;
    scanf(" %d", &songToDelete);
    if (songToDelete == 0) {
        return 0;
    }
    struct Song* tempSong = songByIndex(playlist->songs, songToDelete - 1);
    struct Song* prevSong = tempSong->prev;
    struct Song* nextSong = tempSong->next;
    if (prevSong == NULL)
        playlist->songs = nextSong;
    else
        prevSong->next = nextSong;
    if (nextSong == NULL)
    {
        if (prevSong != NULL)
            prevSong->next = NULL;
    }
   	else
        nextSong->prev = prevSong;
	freeSong(tempSong);
	return 1;
}

void playPlaylist(struct Playlist* playlist) {
	struct Song* currentSong = playlist->songs;
    while (currentSong!= NULL) {
        printf("Now playing %s:\n$ %s $\n", currentSong->title, currentSong->lyrics);
        fflush(NULL);
        currentSong->streams++;
		currentSong = currentSong->next;
    }
}

void watchPlaylists(struct Playlist* playlists) {
    struct Playlist* currentPlaylist = playlists;
	int i = 1;

    printf("Choose a playlist:\n");
	while (currentPlaylist != NULL) {
		printf("\t%d. %s\n", i, currentPlaylist->name);
		currentPlaylist = currentPlaylist->next;
		i++;
	}
 
    printf("\t%d. Back to main menu\n", i);
    fflush(NULL);
    int whichPlaylist;
    scanf("%d", &whichPlaylist);

    if (whichPlaylist >= i || whichPlaylist <= 0) {
        return;
    }

    currentPlaylist = playlists;
    for (i = 1; i < whichPlaylist; i++)
        currentPlaylist = currentPlaylist->next;
    int exitPlaylist = 0;
    printf("Playlist %s:\n\t", currentPlaylist->name);
    fflush(NULL);
    while (!exitPlaylist)
    {
        printf(" 1. Show Playlist \n\t 2. Add Song \n\t 3. Delete song \n\t 4. Sort \n\t "
            "5. Play \n\t 6. exit\n");
        fflush(NULL);
        int task;
        int result;
        scanf("%d", &task);
        switch (task) {
        case 1:
            showPlaylist(currentPlaylist);
            break;
        case 2:
            addSong(currentPlaylist);
            break;
        case 3:
            if ((result = deleteSong(currentPlaylist)) == 1)
                printf("Song deleted successfully.\n");
            fflush(NULL);
            break;
        case 4:
            sortPlaylist(currentPlaylist);
            break;
        case 5:
            playPlaylist(currentPlaylist);
            break;
        case 6:
			exitPlaylist = 1;
            break;
            return;
        }
    }
    watchPlaylists(playlists);
}

void removePlaylist(struct Playlist** playlist) {
    struct Playlist* currentPlaylist = *playlist;
    int i = 1;
        printf("Choose a playlist:\n");
        while (currentPlaylist != NULL) {
            printf("\t%d. %s\n", i, currentPlaylist->name);
            currentPlaylist = currentPlaylist->next;
            i++;
        }
		printf("\t%d. Back to main menu\n", i);
        fflush(NULL);
        int playlistToDelete;
    scanf(" %d", &playlistToDelete);
	if (playlistToDelete == i) {
		return;
	}
    currentPlaylist = *playlist;
    struct Playlist* tempPlaylist = playlistByIndex(currentPlaylist, playlistToDelete - 1);
    struct Playlist* prevPlaylist = tempPlaylist->prev;
    struct Playlist* nextPlaylist = tempPlaylist->next;
    if (prevPlaylist == NULL)
        *playlist = nextPlaylist;
    else
        prevPlaylist->next = nextPlaylist;
    if (nextPlaylist == NULL)
    {
        if (prevPlaylist != NULL) {
            prevPlaylist->next = NULL;
        }
    }
    else {
        nextPlaylist->prev = prevPlaylist;
    }
        free(tempPlaylist->name);
	for (int i = 0; i < howManySongs(tempPlaylist->songs); i++) {
        struct Song* tempSong = songByIndex(tempPlaylist->songs,0);
        freeSong(tempSong);
        return;
	}
    free(tempPlaylist);
    return;
}

void addPlaylist(struct  Playlist** playlists) {
    struct Playlist* newPlaylist = malloc(sizeof(struct Playlist));
	if (newPlaylist == NULL) {
		printf("Memory allocation failed.\n");
        fflush(NULL);
        return;
	}
    printf("Enter playlist's name:\n");
    fflush(NULL);
    newPlaylist->name = getString();
    newPlaylist->songs = NULL;
    newPlaylist->songsNum = 0;
    newPlaylist->songsSize = 0;
    newPlaylist->next = NULL;
    newPlaylist->prev = NULL;
    if (*playlists == NULL)
        *playlists = newPlaylist;
    else {
        newPlaylist->prev = getLastPlaylist(*playlists);
        getLastPlaylist(*playlists)->next = newPlaylist;
         }
    return;
}

void freeSong(struct Song* song) {
	free(song->title);
	free(song->artist);
	free(song->lyrics);
	free(song);
}

void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
    fflush(NULL);
}

int howManySongs(struct Song* song) {
	int i = 0;
	struct Song* currentSong = song;
	while (currentSong != NULL) {
		i++;
		currentSong = currentSong->next;
	}
	return i;
}

void sortPlaylist(struct Playlist* playlist) {
    printf("choose:\n1. sort by year\n2. sort by streams - ascending order\n3. sort by streams - descending order\n4. sort alphabetically\n");
    fflush(NULL);
    int task;
    scanf("%d", &task);
    switch (task) {
    case 1:
        sortByYear(playlist, 0, howManySongs(playlist->songs));
        printf("sorted\n");
        break;
    case 2:
        sortByStreamsAscending(playlist, 0, howManySongs(playlist->songs));
        printf("sorted\n");
        break;
    case 3:
        sortByStreamsDescending(playlist, 0, howManySongs(playlist->songs));
        printf("sorted\n");
        break;
    case 4:
        sortByWord(playlist, 0, howManySongs(playlist->songs));
        printf("sorted\n");
        break;
    default:
        sortByWord(playlist, 0, howManySongs(playlist->songs));
        printf("sorted\n");
        break;
        
    }
    fflush(NULL);
}

int main() {
    struct Playlist *playlists = NULL;
    int task, exitProgram = 0;
    while (!exitProgram) {
        printPlaylistsMenu();
        scanf("%d", &task);
        switch (task) {
        case 1:
            watchPlaylists(playlists);
            break;
        case 2:
            addPlaylist(&playlists);
            break;
        case 3:
            removePlaylist(&playlists);
            break;
        case 4:
            printf("Goodbye!\n");
            fflush(NULL);
            exitProgram = 1;
            freeAllPlaylists(playlists);
            break;
        default:
            printf("Invalid input");
            fflush(NULL);
            break;
        
        }
    }
}
