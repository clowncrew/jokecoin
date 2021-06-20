JokeCoin Core
=============

Setup
---------------------
[JokeCoin Core](http://jokecoin.org/wallet) is the original JokeCoin client and it builds the backbone of the network. However, it downloads and stores the entire history of JokeCoin transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once.

Running
---------------------
The following are some helpful notes on how to run JokeCoin Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/jokecoin-qt` (GUI) or
- `bin/jokecoind` (headless)

If this is the first time running JokeCoin Core (since v5.0.0), you'll need to install the sapling params by running the included `install-params.sh` script, which copies the two params files to `$HOME/.jokecoin-params`

### Windows

Unpack the files into a directory, and then run jokecoin-qt.exe.

### macOS

Drag JokeCoin-Qt to your applications folder, and then run JokeCoin-Qt.

### Need Help?

* See the documentation at the [JokeCoin Wiki](https://github.com/JokeCoin-Project/JokeCoin/wiki)
for help and more information.
* Ask for help on [BitcoinTalk](https://bitcointalk.org/index.php?topic=1262920.0) or on the [JokeCoin Forum](http://forum.jokecoin.org/).
* Join our Discord server [Discord Server](https://discord.jokecoin.org)

Building
---------------------
The following are developer notes on how to build JokeCoin Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The JokeCoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://www.fuzzbawls.pw/jokecoin/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [BitcoinTalk](https://bitcointalk.org/index.php?topic=1262920.0) or the [JokeCoin](http://forum.jokecoin.org/) forum.
* Join the [JokeCoin Discord](https://discord.jokecoin.org).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Memory](reduce-memory.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
