#include <iostream>
#include <sstream>
#include "stdafx.h"
#include "util.h"
#include "preferences.h"
#include <ctime>;
#define _CRT_SECURE_NO_WARNING

const char* APPLICATION_ID = "460908483030679563";

void handleDiscordReady() {}

void handleDiscordDisconnected(int errcode, const char* message) {}

void handleDiscordError(int errcode, const char* message) {}

static double foostarttime;

void discordInit()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.disconnected = handleDiscordDisconnected;
	handlers.errored = handleDiscordError;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
	foostarttime = std::time(nullptr);
}

static char *savedsongname;
static char *savedartist;
static char *savedalbum;
static double start_epoch;
static double pause_epoch;
static double savedlength;
// Code for selecting the art that appears on the rich presence.
const char* GetArtType() {
	int arttype = preferences::get_art_type();

	if (arttype == 1) {
		return "caitlin";
	}
	else if (arttype == 2) {
		return "windowslogic";
	}
	else if (arttype == 3) {
		return "plaindinks";
	}
	else if (arttype == 4) {
		return "kms";
	}
	else if (arttype == 5) {
		return "skeletor";
	}
	else if (arttype == 6) {
		return "fireprancer";
	}
	else if (arttype == 7) {
		return "hentai";
	}
	else if (arttype == 8) {
		return "ie";
	}
	else if (arttype == 9) {
		return "soviet";
	}
	else if (arttype == 10) {
		return "swastika";
	}
	else if (arttype == 11) {
		return "yuri";
	}
	else if (arttype == 12) {
		return "lewd";
	}

	return "caitlin";
}
// Determine if a song is playing.
void UpdatePresence(wchar_t *songname, wchar_t *artist, double tracklength, wchar_t *filename, wchar_t *album)
{
	if (preferences::get_enabled()) {
		savedsongname = util::wide_to_utf8(songname);
		savedartist = util::wide_to_utf8(artist);
		savedalbum = util::wide_to_utf8(album);

		if (strlen(savedsongname) < 1) {
			savedsongname = util::wide_to_utf8(filename);
		}
		if (strlen(savedartist) < 1) {
			savedartist = "";
		}
		savedlength = tracklength;
		std::time_t result = std::time(nullptr);
		start_epoch = result;

		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.details = savedsongname;
		if (preferences::get_show_image()) {
			discordPresence.largeImageKey = GetArtType();
		}
		discordPresence.smallImageKey = "play";
		discordPresence.smallImageText = "Playing";
		if (GetArtType() == "caitlin") {
			discordPresence.largeImageText = "Caitlin's Music";
		}
		else if (GetArtType() == "windowslogic") {
			discordPresence.largeImageText = "WindowsLogic's Music";
		}
		else if (GetArtType() == "plaindinks") {
			discordPresence.largeImageText = "Dolphin's Music";
		}
		else if (GetArtType() == "kms") {
			discordPresence.largeImageText = "Kill Myself";
		}
		else if (GetArtType() == "skeletor") {
			discordPresence.largeImageText = "Nyah!";
		}
		else if (GetArtType() == "fireprancer") {
			discordPresence.largeImageText = "FirePrancer:- I'm a pansexual furry fuck.";
		}
		else if (GetArtType() == "hentai") {
			discordPresence.largeImageText = "Drowning In Ecstasy~ OwO";
		}
		else if (GetArtType() == "ie") {
			discordPresence.largeImageText = "Onestop.mid";
		}
		else if (GetArtType() == "soviet") {
			discordPresence.largeImageText = "Our Music";
		}
		else if (GetArtType() == "swastika") {
			discordPresence.largeImageText = "Heil Hitler";
		}
		else if (GetArtType() == "yuri") {
			discordPresence.largeImageText = "With The Girls~ <3";
		}
		else if (GetArtType() == "lewd") {
			discordPresence.largeImageText = "O-oh my... What are you doing?~ >///<";
		}
		if (preferences::get_show_album() && strlen(savedalbum) > 0) {
			std::stringstream ss;
			ss << savedartist << " [" << savedalbum << "]";
			discordPresence.state = ss.str().c_str();
		}
		else {
			discordPresence.state = savedartist;
		}
		discordPresence.instance = 1;

		if (preferences::get_elapsed()) {
			discordPresence.startTimestamp = foostarttime;
		}
		else {
			discordPresence.startTimestamp = result;
			discordPresence.endTimestamp = result + tracklength;
		}

		Discord_UpdatePresence(&discordPresence);
	}
}
// Determine if a song is seeked to.
void UpdatePresenceSeeked(double seek) {
	if (preferences::get_enabled()) {
		std::time_t result = std::time(nullptr);

		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.details = savedsongname;
		if (preferences::get_show_image()) {
			discordPresence.largeImageKey = GetArtType();
		}
		discordPresence.smallImageKey = "play";
		discordPresence.smallImageText = "Playing";
		if (GetArtType() == "caitlin") {
			discordPresence.largeImageText = "Caitlin's Music";
		}
		else if (GetArtType() == "windowslogic") {
			discordPresence.largeImageText = "WindowsLogic's Music";
		}
		else if (GetArtType() == "plaindinks") {
			discordPresence.largeImageText = "Dolphin's Music";
		}
		else if (GetArtType() == "kms") {
			discordPresence.largeImageText = "Kill Myself";
		}
		else if (GetArtType() == "skeletor") {
			discordPresence.largeImageText = "Nyah!";
		}
		else if (GetArtType() == "fireprancer") {
			discordPresence.largeImageText = "FirePrancer:- I'm a pansexual furry fuck.";
		}
		else if (GetArtType() == "hentai") {
			discordPresence.largeImageText = "Drowning In Ecstasy~ OwO";
		}
		else if (GetArtType() == "ie") {
			discordPresence.largeImageText = "Onestop.mid";
		}
		else if (GetArtType() == "soviet") {
			discordPresence.largeImageText = "Our Music";
		}
		else if (GetArtType() == "swastika") {
			discordPresence.largeImageText = "Heil Hitler";
		}
		else if (GetArtType() == "yuri") {
			discordPresence.largeImageText = "With The Girls~ <3";
		}
		else if (GetArtType() == "lewd") {
			discordPresence.largeImageText = "O-oh my... What are you doing?~ >///<";
		}
		if (preferences::get_show_album() && strlen(savedalbum) > 0) {
			std::stringstream ss;
			ss << savedartist << " [" << savedalbum << "]";
			discordPresence.state = ss.str().c_str();
		}
		else {
			discordPresence.state = savedartist;
		}
		discordPresence.instance = 1;

		if (preferences::get_elapsed()) {
			discordPresence.startTimestamp = foostarttime;
		}
		else {
			discordPresence.startTimestamp = result;
			discordPresence.endTimestamp = result + (savedlength - seek);
		}

		Discord_UpdatePresence(&discordPresence);
	}
}
// Determine if there's no song name.
void UpdatePresenceResumed() {
	if (savedartist == NULL && savedsongname == NULL) {
		return;
	}
	if (preferences::get_enabled()) {
		std::time_t result = std::time(nullptr);
		double played = pause_epoch - start_epoch;

		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.details = savedsongname;
		if (preferences::get_show_image()) {
			discordPresence.largeImageKey = GetArtType();
		}
		discordPresence.smallImageKey = "play";
		discordPresence.smallImageText = "Playing";
		if (GetArtType() == "caitlin") {
			discordPresence.largeImageText = "Caitlin's Music";
		}
		else if (GetArtType() == "windowslogic") {
			discordPresence.largeImageText = "WindowsLogic's Music";
		}
		else if (GetArtType() == "plaindinks") {
			discordPresence.largeImageText = "Dolphin's Music";
		}
		else if (GetArtType() == "kms") {
			discordPresence.largeImageText = "Kill Yourself";
		}
		else if (GetArtType() == "skeletor") {
			discordPresence.largeImageText = "Nyah!";
		}
		else if (GetArtType() == "fireprancer") {
			discordPresence.largeImageText = "FirePrancer:- I'm a pansexual furry fuck.";
		}
		else if (GetArtType() == "hentai") {
			discordPresence.largeImageText = "Drowning In Ecstasy~ OwO";
		}
		else if (GetArtType() == "ie") {
			discordPresence.largeImageText = "Onestop.mid";
		}
		else if (GetArtType() == "soviet") {
			discordPresence.largeImageText = "Our Music";
		}
		else if (GetArtType() == "swastika") {
			discordPresence.largeImageText = "Heil Hitler";
		}
		else if (GetArtType() == "yuri") {
			discordPresence.largeImageText = "With The Girls~ <3";
		}
		else if (GetArtType() == "lewd") {
			discordPresence.largeImageText = "O-oh my... What are you doing?~ >///<";
		}
		if (preferences::get_show_album() && strlen(savedalbum) > 0) {
			std::stringstream ss;
			ss << savedartist << " [" << savedalbum << "]";
			discordPresence.state = ss.str().c_str();
		}
		else {
			discordPresence.state = savedartist;
		}
		discordPresence.instance = 1;

		if (preferences::get_elapsed()) {
			discordPresence.startTimestamp = foostarttime;
		}
		else {
			discordPresence.startTimestamp = result;
			discordPresence.endTimestamp = result + (savedlength - played);
		}

		Discord_UpdatePresence(&discordPresence);
	}
}
// Determine if the song is paused.
void UpdatePresencePaused() {
	if (preferences::get_enabled()) {
		pause_epoch = std::time(nullptr);
		char buffer[256];
		sprintf_s(buffer, 256, "%s (Paused)", savedsongname);
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.details = buffer;
		if (preferences::get_show_image()) {
			discordPresence.largeImageKey = GetArtType();
		}
		discordPresence.smallImageKey = "pause";
		discordPresence.smallImageText = "Paused";
		if (GetArtType() == "caitlin") {
			discordPresence.largeImageText = "Caitlin's Music";
		}
		else if (GetArtType() == "windowslogic") {
			discordPresence.largeImageText = "WindowsLogic's Music";
		}
		else if (GetArtType() == "plaindinks") {
			discordPresence.largeImageText = "Dolphin's Music";
		}
		else if (GetArtType() == "kms") {
			discordPresence.largeImageText = "Kill Myself";
		}
		else if (GetArtType() == "skeletor") {
			discordPresence.largeImageText = "Nyah!";
		}
		else if (GetArtType() == "fireprancer") {
			discordPresence.largeImageText = "FirePrancer:- I'm a pansexual furry fuck.";
		}
		else if (GetArtType() == "hentai") {
			discordPresence.largeImageText = "Drowning In Ecstasy~ OwO";
		}
		else if (GetArtType() == "ie") {
			discordPresence.largeImageText = "Onestop.mid";
		}
		else if (GetArtType() == "soviet") {
			discordPresence.largeImageText = "Our Music";
		}
		else if (GetArtType() == "swastika") {
			discordPresence.largeImageText = "Heil Hitler";
		}
		else if (GetArtType() == "yuri") {
			discordPresence.largeImageText = "With The Girls~ <3";
		}
		else if (GetArtType() == "lewd") {
			discordPresence.largeImageText = "O-oh my... What are you doing?~ >///<";
		}
		if (preferences::get_show_album() && strlen(savedalbum) > 0) {
			std::stringstream ss;
			ss << savedartist << " [" << savedalbum << "]";
			discordPresence.state = ss.str().c_str();
		}
		else {
			discordPresence.state = savedartist;
		}

		if (preferences::get_elapsed()) {
			discordPresence.startTimestamp = foostarttime;
		}

		discordPresence.instance = 1;
		Discord_UpdatePresence(&discordPresence);
	}
}
// Determine if the song is stopped.
void UpdatePresenceStopped()
{
	if (preferences::get_enabled()) {
		if (preferences::get_show_stop()) {
			if (preferences::get_show_songstop() == false) {
				char buffer[256];
				DiscordRichPresence discordPresence;
				memset(&discordPresence, 0, sizeof(discordPresence));
				if (preferences::get_show_image()) {
					discordPresence.largeImageKey = GetArtType();
				}
				discordPresence.smallImageKey = "stop";
				discordPresence.smallImageText = "Stopped";
				if (GetArtType() == "caitlin") {
					discordPresence.largeImageText = "Caitlin's Music";
				}
				else if (GetArtType() == "windowslogic") {
					discordPresence.largeImageText = "WindowsLogic's Music";
				}
				else if (GetArtType() == "plaindinks") {
					discordPresence.largeImageText = "Dolphin's Music";
				}
				else if (GetArtType() == "kms") {
					discordPresence.largeImageText = "Kill Myself";
				}
				else if (GetArtType() == "skeletor") {
					discordPresence.largeImageText = "Nyah!";
				}
				else if (GetArtType() == "fireprancer") {
					discordPresence.largeImageText = "FirePrancer:- I'm a pansexual furry fuck.";
				}
				else if (GetArtType() == "hentai") {
					discordPresence.largeImageText = "Drowning In Ecstasy~ OwO";
				}
				else if (GetArtType() == "ie") {
					discordPresence.largeImageText = "Onestop.mid";
				}
				else if (GetArtType() == "soviet") {
					discordPresence.largeImageText = "Our Music";
				}
				else if (GetArtType() == "swastika") {
					discordPresence.largeImageText = "Heil Hitler";
				}
				else if (GetArtType() == "yuri") {
					discordPresence.largeImageText = "With The Girls~ <3";
				}
				else if (GetArtType() == "lewd") {
					discordPresence.largeImageText = "O-oh my... What are you doing?~ >///<";
				}
				discordPresence.details = "Stopped";
				discordPresence.instance = 1;
				if (preferences::get_elapsed()) {
					discordPresence.startTimestamp = foostarttime;
				}
				Discord_UpdatePresence(&discordPresence);
			}
			else {
				char buffer[256];
				sprintf_s(buffer, 256, "%s (Stopped)", savedsongname);
				DiscordRichPresence discordPresence;
				memset(&discordPresence, 0, sizeof(discordPresence));
				discordPresence.details = buffer;
				if (preferences::get_show_image()) {
					discordPresence.largeImageKey = GetArtType();
				}
				discordPresence.smallImageKey = "stop";
				discordPresence.smallImageText = "Stopped";
				if (GetArtType() == "caitlin") {
					discordPresence.largeImageText = "Caitlin's Music";
				}
				else if (GetArtType() == "windowslogic") {
					discordPresence.largeImageText = "WindowsLogic's Music";
				}
				else if (GetArtType() == "plaindinks") {
					discordPresence.largeImageText = "Dolphin's Music";
				}
				else if (GetArtType() == "kms") {
					discordPresence.largeImageText = "Kill Yourself";
				}
				else if (GetArtType() == "skeletor") {
					discordPresence.largeImageText = "Nyah!";
				}
				else if (GetArtType() == "fireprancer") {
					discordPresence.largeImageText = "FirePrancer:- I'm a pansexual furry fuck.";
				}
				else if (GetArtType() == "hentai") {
					discordPresence.largeImageText = "Drowning In Ecstasy~ OwO";
				}
				else if (GetArtType() == "ie") {
					discordPresence.largeImageText = "Onestop.mid";
				}
				else if (GetArtType() == "soviet") {
					discordPresence.largeImageText = "Our Music";
				}
				else if (GetArtType() == "swastika") {
					discordPresence.largeImageText = "Heil Hitler";
				}
				else if (GetArtType() == "yuri") {
					discordPresence.largeImageText = "With The Girls~ <3";
				}
				else if (GetArtType() == "lewd") {
					discordPresence.largeImageText = "O-oh my... What are you doing?~ >///<";
				}
				if (preferences::get_show_album() && strlen(savedalbum) > 0) {
					std::stringstream ss;
					ss << savedartist << " [" << savedalbum << "]";
					discordPresence.state = ss.str().c_str();
				}
				else {
					discordPresence.state = savedartist;
				}
				discordPresence.instance = 1;
				if (preferences::get_elapsed()) {
					discordPresence.startTimestamp = foostarttime;
				}
				Discord_UpdatePresence(&discordPresence);
			}
		}
		else { // If there's nothing detected, clear the discord presence.
			Discord_ClearPresence();
		}
	}
}