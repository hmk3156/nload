/*
 * nload
 * real time monitor for network traffic
 * Copyright (C) 2001 - 2018 by Roland Riegel <feedback@roland-riegel.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "stringutils.h"

using namespace std;

string trim(const string& s)
{
    // find end of whitespace at the beginning
    string::size_type posBegin = s.find_first_not_of(" \011\012\015");
    if(posBegin == string::npos)
        return string();

    // find beginning of whitespace at the end
    string::size_type posEnd = s.find_last_not_of(" \011\012\015");

    return s.substr(posBegin, posEnd - posBegin + 1);
}

vector<string> split(const string& s, const string& separators)
{
    vector<string> words;
    if(s.empty())
        return words;

    string::size_type pos = s.find_first_of(separators);
    string::size_type posOld = 0;
    while(pos != string::npos)
    {
        words.push_back(s.substr(posOld, pos - posOld));
        posOld = pos + 1;

        pos = s.find_first_of(separators, posOld);
    }

    words.push_back(s.substr(posOld));

    return words;
}

vector<string> splitQuoted(const string& s, const string& separators, const string& quotes)
{
    if(s.empty())
        return vector<string>();

    vector<string> words(1);
    string::size_type pos = s.find_first_of(separators + quotes);
    string::size_type posOld = 0;
    bool quoted = false;

    while(true)
    {
        words.back() += s.substr(posOld, pos - posOld);
        posOld = pos + 1;

        if(pos == string::npos)
            return words;

        if(separators.find(s[pos]) != string::npos)
        {
            // separator found

            words.push_back(string());

            pos = s.find_first_of(separators + quotes, posOld);
        }
        else
        {
            // quote found

            posOld = pos + 1;

            quoted = !quoted;

            if(quoted)
                pos = s.find_first_of(quotes, posOld);
            else
                pos = s.find_first_of(separators + quotes, posOld);
        }
    }
}

