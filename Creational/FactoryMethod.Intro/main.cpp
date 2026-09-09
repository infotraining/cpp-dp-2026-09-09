#include "factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

namespace StronglyCoupled
{
    class MusicApp
    {
    public:
        MusicApp() = default;

        void play(const std::string &track_title)
        {
            // creation of product
            SpotifyService music_service("spotify_user", "rjdaslf276%2", 45);

            std::optional<Track> track = music_service.get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto &note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

namespace StaticFactory
{
    std::unique_ptr<MusicService> create_music_service(const std::string &id)
    {
        if (id == "Tidal")
            return std::make_unique<TidalService>("tidal_user", "KJH8324d&df");
        if (id == "Spotify")
            return std::make_unique<SpotifyService>("spotify_user", "rjdaslf276%2", 45);
        if (id == "Filesystem")
            return std::make_unique<FilesystemMusicService>("/user/my_music");
        if (id == "YouTube")
            return std::make_unique<YouTubeService>("youtube_user", "password123");
        throw std::invalid_argument("Unknown music service id: " + id);
    }

    class MusicApp
    {
        std::string service_id_;

    public:
        MusicApp(const std::string &service_id)
            : service_id_(service_id)
        {
        }

        void play(const std::string &track_title)
        {
            // creation of the object
            std::unique_ptr<MusicService> music_service = create_music_service(service_id_);

            // usage of the object
            std::optional<Track> track = music_service->get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto &note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

namespace CanonicalFactoryMethod
{

    class MusicServiceFactory
    {
        std::unordered_map<std::string, std::shared_ptr<MusicServiceCreator>> creators_;

    public:
        void register_creator(const std::string &id, std::shared_ptr<MusicServiceCreator> creator)
        {
            creators_[id] = creator;
        }

        std::shared_ptr<MusicServiceCreator> get_creator(const std::string &id)
        {
            if (creators_.find(id) != creators_.end())
                return creators_.at(id);
            throw std::invalid_argument("Unknown music service id: " + id);
        }

        std::unique_ptr<MusicService> create_music_service(const std::string &id)
        {
            if (creators_.find(id) != creators_.end())
                return creators_.at(id)->create_music_service();
            throw std::invalid_argument("Unknown music service id: " + id);
        }
    };

    // Client
    class MusicApp
    {
        std::shared_ptr<MusicServiceCreator> music_service_creator_;

    public:
        MusicApp(std::shared_ptr<MusicServiceCreator> music_service_creator)
            : music_service_creator_(music_service_creator)
        {
        }

        void play(const std::string &track_title)
        {
            // creation of the object
            std::unique_ptr<MusicService> music_service = music_service_creator_->create_music_service();

            // usage of the object
            std::optional<Track> track = music_service->get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto &note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

namespace ModernCpp
{
    class MusicServiceFactory
    {
        std::unordered_map<std::string, MusicServiceCreator> creators_;

    public:
        void register_creator(const std::string &id, MusicServiceCreator creator)
        {
            creators_[id] = creator;
        }

        MusicServiceCreator get_creator(const std::string &id)
        {
            if (creators_.find(id) != creators_.end())
                return creators_.at(id);
            throw std::invalid_argument("Unknown music service id: " + id);
        }

        std::unique_ptr<MusicService> create_music_service(const std::string &id)
        {
            if (creators_.find(id) != creators_.end())
                return creators_.at(id)();
            throw std::invalid_argument("Unknown music service id: " + id);
        }
    };

    class MusicApp
    {
        MusicServiceCreator music_service_creator_;

    public:
        MusicApp(MusicServiceCreator music_service_creator)
            : music_service_creator_(music_service_creator)
        {
        }

        void play(const std::string &track_title)
        {
            // creation of the object
            std::unique_ptr<MusicService> music_service = music_service_creator_();

            // usage of the object
            std::optional<Track> track = music_service->get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto &note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

int main()
{
    using namespace ModernCpp;

    // bootstrap the music service factory with available creators
    MusicServiceFactory music_service_factory;
    music_service_factory.register_creator("Tidal", TidalServiceCreator("tidal_user", "KJH8324d&df"));
    music_service_factory.register_creator("Spotify", SpotifyServiceCreator("spotify_user", "rjdaslf276%2", 45));
    music_service_factory.register_creator("Filesystem", []()
                                           { return std::make_unique<FilesystemMusicService>(); });
    music_service_factory.register_creator("YouTube", []()
                                           { return std::make_unique<YouTubeService>("youtube_user", "password123"); });

    std::string id_from_config = "Tidal";
    auto service_creator = music_service_factory.get_creator(id_from_config);

    MusicApp app(service_creator);
    app.play("Would?");
}