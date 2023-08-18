#ifndef GARRYSMOD_LUA_USERDATA_H
#define GARRYSMOD_LUA_USERDATA_H

#ifdef GMOD_ALLOW_DEPRECATED
    struct UserData
    {
        void*         data;
        unsigned char type;
    };
#endif

#endif
