/*
 * Timmy Wang
 * tqwang 10/21/18
 * CS12B
 * list.h
 * Defines structure rider
 */
struct rider
{
    int ID; /* ID of the rider, internal code */
    char *first_name;/* name of rider, first */
    char *last_name;/* name of rider, second */
    double ave_rating;/* average rating over all rides taken */
    double distance;  /* miles from driver */
    struct rider *next;
} typedef rider_st;
