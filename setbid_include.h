/*
 * It is not said that int setbid(int) has to be here, so here is a place
 * for you to change that.
 */
#ifndef SETBID_INCLUDE_H
#define SETBID_INCLUDE_H
#include <unistd.h>
#ifndef MAX_BID
#define MAX_BID (100)
#else
#warning MAX_BID defined in unistd.h
#endif/*MAX_BID*/
#endif/*SETBID_INCLUDE_H*/
