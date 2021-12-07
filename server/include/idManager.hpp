/*
** EPITECH PROJECT, 2021
** IdManager
** File description:
** IdManager
*/

#ifndef ID_MANAGER_HPP_
#define ID_MANAGER_HPP_

#include <vector>
#include <algorithm>
#include <stack>

class IdManager {
    public:
        IdManager() {
            unusedIDs.push(1);
        };
        ~IdManager() {};

        int getNewID() {
            int res = unusedIDs.top();
            unusedIDs.pop();
            if (unusedIDs.size() == 0)
                unusedIDs.push(res + 1);
            usedIDs.emplace_back(res);
            return (res);
        };

        void freeUnusedID(int id) {
            usedIDs.erase(std::remove(usedIDs.begin(), usedIDs.end(), id), usedIDs.end());
            unusedIDs.push(id);
        };

    private:
        std::stack<int> unusedIDs;
        std::vector<int> usedIDs;
};

#endif