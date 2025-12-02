#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Song class
class Song
{
    string title;
    string artist;
    int duration; // in seconds

public:
    Song(string t, string a, int d)
    {
        title = t;
        artist = a;
        duration = d;
    }

    string getTitle() const
    {
        return title;
    }

    string getArtist() const
    {
        return artist;
    }

    int getDuration() const
    {
        return duration;
    }
};

// Iterator Interface
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual Song *next() = 0;
    virtual void reset() = 0;
    virtual Song *current() = 0;
    virtual ~Iterator() {}
};

// Playlist (Aggregate Interface)
class Playlist
{
public:
    virtual Iterator *createForwardIterator() = 0;
    virtual Iterator *createReverseIterator() = 0;
    virtual Iterator *createArtistIterator(const string &) = 0;
    virtual ~Playlist() {}
};

// Concrete Playlist
class MyPlaylist : public Playlist
{
    vector<Song *> songs;

public:
    void addSong(Song *s)
    {
        songs.push_back(s);
    }

    const vector<Song *> &getSongs() const
    {
        return songs; // internal structure NOT exposed to clients
    }

    Iterator *createForwardIterator() override;
    Iterator *createReverseIterator() override;
    Iterator *createArtistIterator(const string &artist) override;
};

// Forward Iterator
class ForwardIterator : public Iterator
{
    const MyPlaylist &playlist;
    size_t index;

public:
    ForwardIterator(const MyPlaylist &p) : playlist(p), index(0) {}

    bool hasNext() override
    {
        return index < playlist.getSongs().size();
    }

    Song *next() override
    {
        if (!hasNext())
            return nullptr;
        return playlist.getSongs()[index++];
    }

    void reset() override
    {
        index = 0;
    }

    Song *current() override
    {
        if (index == 0 || index > playlist.getSongs().size())
            return nullptr;

        return playlist.getSongs()[index - 1];
    }
};

class ReverseIterator : public Iterator
{
    const MyPlaylist &playlist;
    int index;

public:
    ReverseIterator(const MyPlaylist &p) : playlist(p), index((int)p.getSongs().size() - 1) {}

    bool hasNext() override
    {
        return index >= 0;
    }

    Song *next() override
    {
        if (!hasNext())
            return nullptr;
        return playlist.getSongs()[index--];
    }

    void reset() override
    {
        index = (int)playlist.getSongs().size() - 1;
    }

    Song *current() override
    {
        int curr = index + 1;
        if (curr < 0 || curr >= (int)playlist.getSongs().size())
            return nullptr;

        return playlist.getSongs()[curr];
    }
};

// Artist Filter Iterator
class ArtistIterator : public Iterator
{
    const MyPlaylist &playlist;
    string artist;
    size_t index;

    void moveToNextValid()
    {
        while (index < playlist.getSongs().size() && playlist.getSongs()[index]->getArtist() != artist)
        {
            index++;
        }
    }

public:
    ArtistIterator(const MyPlaylist &p, const string &a) : playlist(p), artist(a), index(0)
    {
        moveToNextValid();
    }

    bool hasNext() override
    {
        return index < playlist.getSongs().size();
    }

    Song *next() override
    {
        if (!hasNext())
            return nullptr;
        Song *s = playlist.getSongs()[index++];
        moveToNextValid();
        return s;
    }

    void reset() override
    {
        index = 0;
        moveToNextValid();
    }

    Song *current() override
    {
        if (index == 0 || index > playlist.getSongs().size())
            return nullptr;
        return playlist.getSongs()[index - 1];
    }
};

// Connect iterators with playlist
Iterator *MyPlaylist::createForwardIterator()
{
    return new ForwardIterator(*this);
}

Iterator *MyPlaylist::createReverseIterator()
{
    return new ReverseIterator(*this);
}

Iterator *MyPlaylist::createArtistIterator(const string &artist)
{
    return new ArtistIterator(*this, artist);
}

int main()
{
    MyPlaylist playlist;

    playlist.addSong(new Song("Believer", "Imagine Dragons", 210));
    playlist.addSong(new Song("Thunder", "Imagine Dragons", 190));
    playlist.addSong(new Song("Shape of You", "Ed Sheeran", 230));
    playlist.addSong(new Song("Perfect", "Ed Sheeran", 250));

    cout << "=== Forward Playlist ===\n";
    Iterator *it1 = playlist.createForwardIterator();
    while (it1->hasNext())
    {
        Song *s = it1->next();
        cout << s->getTitle() << " - " << s->getArtist() << "\n";
    }

    cout << "\n=== Reverse Playlist ===\n";
    Iterator *it2 = playlist.createReverseIterator();
    while (it2->hasNext())
    {
        Song *s = it2->next();
        cout << s->getTitle() << " - " << s->getArtist() << "\n";
    }

    cout << "\n=== Songs by Ed Sheeran ===\n";
    Iterator *it3 = playlist.createArtistIterator("Ed Sheeran");
    while (it3->hasNext())
    {
        Song *s = it3->next();
        cout << s->getTitle() << " - " << s->getArtist() << "\n";
    }

    // Cleanup
    delete it1;
    delete it2;
    delete it3;

    return 0;
}