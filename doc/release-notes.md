(note: this is a temporary file, to be added-to by anybody, and moved to release-notes at release time)

JokeCoin Core version *version* is now available from:  <https://github.com/jokecoin-project/jokecoin/releases>

This is a new major version release, including various bug fixes and performance improvements, as well as updated translations.

Please report bugs using the issue tracker at github: <https://github.com/jokecoin-project/jokecoin/issues>


How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/JokeCoin-Qt (on Mac) or jokecoind/jokecoin-qt (on Linux).

Sapling Parameters
==================

In order to run, JokeCoin Core now requires two files, `sapling-output.params` and `sapling-spend.params` (with total size ~50 MB), to be saved in a specific location.

For the following packages, no action is required by the user:
- macOS release `dmg` binaries will use the params that are bundled into the .app bundle.
- Windows installer `.exe` will automatically copy the files in the proper location.
- Linux `PPA/Snap` installs will automatically copy the files in the proper location.

For the other packages, the user must save the param files in the proper location, before being able to run JokeCoin v5.0.0:
- macOS/Linux `tar.gz` tarballs include a bash script (`install-params.sh`) to copy the parameters in the appropriate location.
- Windows `.zip` users need to manually copy the files from the `share/jokecoin` folder to the `%APPDATA%\JokeCoinParams` directory.
- self compilers can run the script from the repository sources (`params/install-params.sh`), or copy the files directly from the `params` subdirectory.

Compatibility
==============

JokeCoin Core is extensively tested on multiple operating systems using the Linux kernel, macOS 10.12+, and Windows 7 and later.

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support), No attempt is made to prevent installing or running the software on Windows XP, you can still do so at your own risk but be aware that there are known instabilities and issues. Please do not report issues about Windows XP to the issue tracker.

From JokeCoin Core 6.0 onwards, macOS versions earlier than 10.12 are no longer supported.

JokeCoin Core should also work on most other Unix-like systems but is not frequently tested on them.


Notable Changes
==============

(Developers: add your notes here as part of your pull requests whenever possible)


Cold-Staking Re-Activation
--------------------------
JokeCoin Core v6.0.0 includes a fix for the vulnerability identified within the cold-staking protocol (see PR [#2258](https://github.com/JokeCoin-Project/JokeCoin/pull/2258)).
Therefore the feature will be re-enabled on the network, via `SPORK_19`, shortly after the upgrade enforcement.

### Protocol changes

A new opcode (`0xd2`) is introduced (see PR [#2275](https://github.com/JokeCoin-Project/JokeCoin/pull/2275)). It enforces the same rules as the legacy cold-staking opcode, but without allowing a "free" script for the last output of the transaction.
This is in accord with the consensus change introduced with the "Deterministic Masternodes" update, as masternode/budget payments are now outputs of the *coinbase* transaction (rather than the *coinstake*), therefore a "free" output for the coinstake is no longer needed.
The new opcode takes the name of `OP_CHECKCOLDSTAKEVERIFY`, and the legacy opcode (`0xd1`) is renamed to `OP_CHECKCOLDSTAKEVERIFY_LOF` (last-output-free).
Scripts with the old opcode are still accepted on the network (the restriction on the last-output is enforced after the script validation in this case), but the client creates new delegations with the new opcode, by default, after the upgrade enforcement.


Multi-wallet support
--------------------

JokeCoin Core now supports loading multiple, separate wallets (See [PR #2337](https://github.com/JokeCoin-Project/JokeCoin/pull/2337)). The wallets are completely separated, with individual balances, keys and received transactions.

Multi-wallet is enabled by using more than one `-wallet` argument when starting JokeCoin client, either on the command line or in the jokecoin.conf config file.

**In jokecoin-qt, only the first wallet will be displayed and accessible for creating and signing transactions.** GUI selectable multiple wallets will be supported in a future version. However, even in 6.0 other loaded wallets will remain synchronized to the node's current tip in the background.

JokeCoin Core 6.0.0 contains the following changes to the RPC interface and jokecoin-cli for multi-wallet:

* When running JokeCoin Core with a single wallet, there are **no** changes to the RPC interface or `jokecoin-cli`. All RPC calls and `jokecoin-cli` commands continue to work as before.
* When running JokeCoin Core with multi-wallet, all *node-level* RPC methods continue to work as before. HTTP RPC requests should be send to the normal `<RPC IP address>:<RPC port>` endpoint, and `jokecoin-cli` commands should be run as before. A *node-level* RPC method is any method which does not require access to the wallet.
* When running JokeCoin Core with multi-wallet, *wallet-level* RPC methods must specify the wallet for which they're intended in every request. HTTP RPC requests should be send to the `<RPC IP address>:<RPC port>/wallet/<wallet name>` endpoint, for example `127.0.0.1:8332/wallet/wallet1.dat`. `jokecoin-cli` commands should be run with a `-rpcwallet` option, for example `jokecoin-cli -rpcwallet=wallet1.dat getbalance`.

* A new *node-level* `listwallets` RPC method is added to display which wallets are currently loaded. The names returned by this method are the same as those used in the HTTP endpoint and for the `rpcwallet` argument.

The `getwalletinfo` RPC method returns the name of the wallet used for the query.

Note that while multi-wallet is now fully supported, the RPC multi-wallet interface should be considered unstable for version 6.0.0, and there may backwards-incompatible changes in future versions.


GUI changes
-----------

### RPC-Console

The GUI RPC-Console now accepts "parenthesized syntax", nested commands, and simple queries (see [PR #2282](https://github.com/JokeCoin-Project/JokeCoin/pull/2282).
A new command `help-console` (available only on the GUI console) documents how to use it:

```
This console accepts RPC commands using the standard syntax.
    example:    getblockhash 0

This console can also accept RPC commands using parenthesized syntax.
    example:    getblockhash(0)

Commands may be nested when specified with the parenthesized syntax.
    example:    getblock(getblockhash(0) true)

A space or a comma can be used to delimit arguments for either syntax.
    example:    getblockhash 0
                getblockhash,0

Named results can be queried with a non-quoted key string in brackets.
    example:    getblock(getblockhash(0) true)[tx]

Results without keys can be queried using an integer in brackets.
    example:    getblock(getblockhash(0),true)[tx][0]
```


Support for JSON-RPC Named Arguments
------------------------------------

Commands sent over the JSON-RPC interface and through the `jokecoin-cli` binary can now use named arguments. This follows the [JSON-RPC specification](http://www.jsonrpc.org/specification) for passing parameters by-name with an object.
`jokecoin-cli` has been updated to support this by parsing `name=value` arguments when the `-named` option is given.

Some examples:

```
    src/jokecoin-cli -named help command="help"
    src/jokecoin-cli -named getblockhash height=0
    src/jokecoin-cli -named getblock blockhash=000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f
    src/jokecoin-cli -named sendtoaddress address="DMJRSsuU9zfyrvxVaAEFQqK4MxZg6vgeS6" amount="1.0" comment="donation"
```

The order of arguments doesn't matter in this case. Named arguments are also useful to leave out arguments that should stay at their default value.
The RPC server remains fully backwards compatible with positional arguments.


Low-level RPC changes
---------------------

### Query options for listunspent RPC

- The `listunspent` RPC now takes a `query_options` argument (see [PR #2317](https://github.com/JokeCoin-Project/JokeCoin/pull/2317)), which is a JSON object
  containing one or more of the following members:
  - `minimumAmount` - a number specifying the minimum value of each UTXO
  - `maximumAmount` - a number specifying the maximum value of each UTXO
  - `maximumCount` - a number specifying the minimum number of UTXOs
  - `minimumSumAmount` - a number specifying the minimum sum value of all UTXOs

- The `listunspent` RPC also takes an additional boolean argument `include_unsafe` (true by default) to optionally exclude "unsafe" utxos.
  An unconfirmed output from outside keys is considered unsafe (see [PR #2351](https://github.com/JokeCoin-Project/JokeCoin/pull/2351)).

- The `listunspent` output also shows whether the utxo is considered safe to spend or not.

- the `stop` RPC no longer accepts the (already deprecated, ignored, and undocumented) optional boolean argument `detach`.

### Subtract fee from recipient amount for RPC

A new argument `subtract_fee_from` is added to `sendmany`/`shieldsendmany` RPC functions.
It can be used to provide the list of recipent addresses paying the fee.
```
subtract_fee_from         (array, optional) 
A json array with addresses.
The fee will be equally deducted from the amount of each selected address.
  [\"address\"          (string) Subtract fee from this address\n"
   ,...
  ]

For `fundrawtransaction` a new key (`subtractFeeFromOutputs`) is added to the `options` argument.
It can be used to specify a list of output indexes.
```
subtractFeeFromOutputs    (array, optional)  A json array of integers.
The fee will be equally deducted from the amount of each specified output.
The outputs are specified by their zero-based index, before any change output is added.
  [vout_index,...]
```

For `sendtoaddress`, the new parameter is called `subtract_fee` and it is a simple boolean.

In all cases those recipients will receive less JOKE than you enter in their corresponding amount field.
If no outputs/addresses are specified, the sender pays the fee as usual.

### Show wallet's auto-combine settings in getwalletinfo

`getwalletinfo` now has two additional return fields. `autocombine_enabled` (boolean) and `autocombine_threshold` (numeric) that will show the auto-combine threshold and whether or not it is currently enabled.

### Deprecate the autocombine RPC command

The `autocombine` RPC command has been replaced with specific set/get commands (`setautocombinethreshold` and `getautocombinethreshold`, respectively) to bring this functionality further in-line with our RPC standards. Previously, the `autocombine` command gave no user-facing feedback when the setting was changed. This is now resolved with the introduction of the two new commands as detailed below:

* `setautocombinethreshold`
    ```  
    setautocombinethreshold enable ( value )
    This will set the auto-combine threshold value.
    Wallet will automatically monitor for any coins with value below the threshold amount, and combine them if they reside with the same JokeCoin address
    When auto-combine runs it will create a transaction, and therefore will be subject to transaction fees.
    
    Arguments:
    1. enable          (boolean, required) Enable auto combine (true) or disable (false)
    2. threshold       (numeric, optional. required if enable is true) Threshold amount. Must be greater than 1.
    
    Result:
    {
      "enabled": true|false,     (boolean) true if auto-combine is enabled, otherwise false
      "threshold": n.nnn,        (numeric) auto-combine threshold in JOKE
      "saved": true|false        (boolean) true if setting was saved to the database, otherwise false
    }
    ```

* `getautocombinethreshold`
    ```
    getautocombinethreshold
    Returns the current threshold for auto combining UTXOs, if any

    Result:
    {
      "enabled": true|false,    (boolean) true if auto-combine is enabled, otherwise false
      "threshold": n.nnn         (numeric) the auto-combine threshold amount in JOKE
    }
    ```

Build system changes
--------------------

The minimum supported miniUPnPc API version is set to 10. This keeps compatibility with Ubuntu 16.04 LTS and Debian 8 `libminiupnpc-dev` packages. Please note, on Debian this package is still vulnerable to [CVE-2017-8798](https://security-tracker.debian.org/tracker/CVE-2017-8798) (in jessie only) and [CVE-2017-1000494](https://security-tracker.debian.org/tracker/CVE-2017-1000494) (both in jessie and in stretch).

OpenSSL is no longer used by JokeCoin Core


Configuration changes
---------------------

### Configuration sections for testnet and regtest

It is now possible for a single configuration file to set different options for different networks. This is done by using sections or by prefixing the option with the network, such as:

    main.uacomment=jokecoin
    test.uacomment=jokecoin-testnet
    regtest.uacomment=regtest
    [main]
    mempoolsize=300
    [test]
    mempoolsize=100
    [regtest]
    mempoolsize=20

The `addnode=`, `connect=`, `port=`, `bind=`, `rpcport=`, `rpcbind=`, and `wallet=` options will only apply to mainnet when specified in the configuration file, unless a network is specified.

### Allow to optional specify the directory for the blocks storage

A new init option flag '-blocksdir' will allow one to keep the blockfiles external from the data directory.

### Disable PoW mining RPC Commands

A new configure flag has been introduced to allow more granular control over weather or not the PoW mining RPC commands are compiled into the wallet. By default they are not. This behavior can be overridden by passing `--enable-mining-rpc` to the `configure` script.

### Removed startup options

- `printstakemodifier`

### Logging

The log timestamp format is now ISO 8601 (e.g. "2021-02-28T12:34:56Z").

### Automatic Backup File Naming

The file extension applied to automatic backups is now in ISO 8601 basic notation (e.g. "20210228T123456Z"). The basic notation is used to prevent illegal `:` characters from appearing in the filename.


*version* Change log
==============

Detailed release notes follow. This overview includes changes that affect behavior, not code moves, refactors and string updates. For convenience in locating the code changes and accompanying discussion, both the pull request and git merge commit are mentioned.

### GUI

### Wallet

### RPC

### Masternodes/Budget

### Core

### Build Systems

### P2P/Network

### Testing

### Cleanup/Refactoring

### Docs/Output

## Credits

Thanks to everyone who directly contributed to this release:


As well as everyone that helped translating on [Transifex](https://www.transifex.com/projects/p/jokecoin-project-translations/), the QA team during Testing and the Node hosts supporting our Testnet.
