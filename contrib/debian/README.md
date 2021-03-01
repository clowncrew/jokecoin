
Debian
====================
This directory contains files used to package jokecoind/jokecoin-qt
for Debian-based Linux systems. If you compile jokecoind/jokecoin-qt yourself, there are some useful files here.

## jokecoin: URI support ##


jokecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install jokecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your jokecoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/jokecoin128.png` to `/usr/share/pixmaps`

jokecoin-qt.protocol (KDE)

