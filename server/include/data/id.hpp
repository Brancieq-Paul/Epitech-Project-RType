/*
** EPITECH PROJECT, 2021
** ID
** File description:
** ID
*/

#ifndef ID_HPP_
#define ID_HPP_

namespace id {
    typedef struct s_id {
        int typeId;
        int spriteId;
    } id_t;

    static id_t *createID(int tid, int sid) {
        id_t *res = new id_t();

        res->spriteId = sid;
        res->typeId = tid;
        return (res);
    }
};

#endif