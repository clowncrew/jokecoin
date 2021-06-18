// Copyright (c) 2018 The JokeCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef JokeCoin_INVALID_H
#define JokeCoin_INVALID_H

#include <set>
#include <string>

class COutPoint;
class UniValue;

namespace invalid_out
{
    extern std::set<COutPoint> setInvalidOutPoints;

    UniValue read_json(const std::string& jsondata);

    bool ContainsOutPoint(const COutPoint& out);
    bool LoadOutpoints();
}

#endif //JokeCoin_INVALID_H
