//
// Copyright 2012 Josh Blum
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef INCLUDED_LIB_APOLOGY_VEC_UTILS_HPP
#define INCLUDED_LIB_APOLOGY_VEC_UTILS_HPP

//! return true if an instance was found and removed
template <typename V, typename T>
bool remove_one(V &v, const T &t)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == t)
        {
            v.erase(v.begin() + i);
            return true;
        }
    }
    return false;
}

template <typename V, typename T>
bool insert_unique(V &v, const T &t)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == t)
        {
            return false;
        }
    }
    v.push_back(t);
    return true;
}

template <typename V, typename T>
void vector_vector_add(V &v, const size_t index, const T &t)
{
    //ensure that there is room
    if (index >= v.size())
    {
        v.resize(index+1);
    }

    //add the element
    v[index].push_back(t);
}

template <typename V, typename T>
void vector_vector_remove(V &v, const size_t index, const T &t)
{
    //remove the first match found
    if (v.size() > index) remove_one(v[index], t);

    //trim (dont want trailing empty ones)
    while (not v.empty() and v.back().empty())
    {
        v.resize(v.size()-1);
    }
}

//! The result is X without the intersection of X and Y
template <typename V>
V vector_subtract(const V &x, const V &y)
{
    V result = x;
    for (size_t i = 0; i < y.size(); i++)
    {
        remove_one(result, y[i]);
    }
    return result;
}

template <typename V>
void extend(V &v, const V &x)
{
    for (size_t i = 0; i < x.size(); i++)
    {
        v.push_back(x[i]);
    }
}

#endif /*INCLUDED_LIB_APOLOGY_VEC_UTILS_HPP*/
