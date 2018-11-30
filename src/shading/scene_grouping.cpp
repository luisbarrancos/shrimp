
/*
    Copyright 2008-2009, Romain Behar <romainbehar@users.sourceforge.net>

    This file is part of Shrimp 2.

    Shrimp 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Shrimp 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Shrimp 2.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "scene.h"

#include "../miscellaneous/misc_string_functions.h"

shrimp::group_set_t scene::group_list()
{
    shrimp::group_set_t groups;
    for (auto& m_group : m_groups)
    {
        groups.insert(m_group.second);
    }

    return groups;
}

void scene::add_to_group(const std::string& Block, const int Group)
{
    if (Block.size() && Group)
        m_groups.insert(std::make_pair(Block, Group));
}

int scene::get_block_group(const shader_block* Block)
{
    auto g = m_groups.find(Block->name());
    if (g == m_groups.end())
        return 0;

    return g->second;
}

void scene::ungroup(const int Group)
{
    shrimp::groups_t groups2;
    for (auto& m_group : m_groups)
    {
        if (m_group.second != Group)
        {
            groups2.insert(m_group);
        }
    }

    m_groups = groups2;

    m_group_names.erase(Group);
}

void scene::group_blocks(const shrimp::shader_blocks_t& Blocks)
{
    // find the next group number
    int max = 0;
    for (auto& m_group : m_groups)
    {
        if (m_group.second > max)
            max = m_group.second;
    }
    ++max;

    // store new group
    for (auto Block : Blocks)
    {
        m_groups.insert(std::make_pair(Block->name(), max));
    }
}

shrimp::shader_blocks_t scene::get_group_blocks(const int Group)
{
    shrimp::shader_blocks_t blocks;

    for (auto& m_group : m_groups)
    {
        if (m_group.second == Group)
        {
            blocks.insert(get_block(m_group.first));
        }
    }

    return blocks;
}

const std::string scene::get_group_name(const int Group) const
{
    auto name = m_group_names.find(Group);
    if (name == m_group_names.end())
        return "Group " + string_cast(Group);

    return name->second;
}

void scene::set_group_name(const int Group, const std::string& Name)
{
    auto g = m_group_names.find(Group);
    if (g == m_group_names.end())
    {
        m_group_names.insert(std::make_pair(Group, Name));
    }
    else
    {
        // insert() does not erase an existing record
        g->second = Name;
    }
}
